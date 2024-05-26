//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Game.h"
#include "MathEngine.h"
#include "GameObjectAnimSkin.h"
#include "GraphicsObject.h"
#include "ShaderMappings.h"
#include "Anim.h"
#include "ShaderObjectNodeMan.h"
#include "ComputeCBVBuffer.h"
#include "ComputeRSVBuffer.h"
#include "ComputeUAVBuffer.h"
#include "DirectXDeviceMan.h"
#include "Mixer.h"

namespace Azul
{
	GameObjectAnimSkin::GameObjectAnimSkin(GraphicsObject *pGraphicsObject, Mixer *_pMixer, WorldCompute *_pWorldCompute)
		: GameObjectAnim(pGraphicsObject),
		poScale{new Vec3(1.0f, 1.0f, 1.0f)},
		poQuat{new Quat(0.0f, 0.0f, 0.0f, 1.0f)},
		poTrans{new Vec3(0.0f, 0.0f, 0.0f)},
		delta_x{0.0f},
		delta_y{0.0f},
		delta_z{0.0f},
		cur_rot_x{0.0f},
		cur_rot_y{0.0f},
		cur_rot_z{0.0f},
		poMixer{_pMixer},
		poWorldCompute{_pWorldCompute}
	{
		assert(pGraphicsObject);

		assert(this->poTrans);
		assert(this->poScale);
		assert(this->poQuat);

		assert(this->poMixer);
		assert(this->poWorld);
	}

	GameObjectAnimSkin::~GameObjectAnimSkin()
	{
		delete this->poTrans;
		delete this->poScale;
		delete this->poQuat;
		delete this->poMixer;
		delete this->poWorldCompute;
	}

	void GameObjectAnimSkin::Update(AnimTime currentTime)
	{
		AZUL_UNUSED_VAR(currentTime);

		// Goal: update the world matrix
		this->privUpdate(currentTime);

		// update the bounding volume based on world matrix
		this->poGraphicsObject->SetWorld(*this->poWorld);

		// do the compute shaders
		this->privMixerExecute();
		this->privWorldComputeExecute();
	}

	void GameObjectAnimSkin::privMixerExecute()
	{
		// ------------------------------------------------
		//  execute Compute Shader 
		// ------------------------------------------------

		ShaderObject *pShaderObj = ShaderObjectNodeMan::Find(ShaderObject::Name::MixerCompute);
		pShaderObj->ActivateCSShader();

		assert(poMixer->pKeyA);
		poMixer->pKeyA->BindCompute(ShaderResourceBufferSlot::KeyA);   

		assert(poMixer->pKeyB);
		poMixer->pKeyB->BindCompute(ShaderResourceBufferSlot::KeyB);   

		assert(poMixer->poMixerABOut);
		poMixer->poMixerABOut->BindCompute(UnorderedAccessBufferSlot::MixerABOut);  

		assert(poMixer->poConstBuffer);
		poMixer->poConstBuffer->Transfer(poMixer->GetConstBuff());
		poMixer->poConstBuffer->BindCompute(ConstantBufferSlot::csMixer);  

		// Dispatch
		unsigned int count = (unsigned int)ceil((float)poMixer->numBones / 8.0f);
		DirectXDeviceMan::GetContext()->Dispatch(count, 1, 1);

	}

	void GameObjectAnimSkin::privWorldComputeExecute()
	{
		// ------------------------------------------------
		//  execute Compute Shader 
		// ------------------------------------------------

		ShaderObject *pShaderObj = ShaderObjectNodeMan::Find(ShaderObject::Name::WorldCompute);
		pShaderObj->ActivateCSShader();

		assert(poWorldCompute->pMixerABIn);
		poWorldCompute->pMixerABIn->BindCompute(UnorderedAccessBufferSlot::MixerABOut);   

		assert(poWorldCompute->poHierarchyTable);
		poWorldCompute->poHierarchyTable->BindCompute(ShaderResourceBufferSlot::HierarchyTable); 

		assert(poWorldCompute->poUAVWorldMat);
		poWorldCompute->poUAVWorldMat->BindCompute(UnorderedAccessBufferSlot::BoneWorldOut);  

		assert(poWorldCompute->poConstBuffer);
		poWorldCompute->poConstBuffer->Transfer(poWorldCompute->GetConstBuff());
		poWorldCompute->poConstBuffer->BindCompute(ConstantBufferSlot::csWorld);   

		// Dispatch
		unsigned int count = (unsigned int)ceil((float)poMixer->numBones / 8.0f);
		DirectXDeviceMan::GetContext()->Dispatch(count, 1, 1);

		// UAV buffers are not allowed in Vertex shaders
		// so copy the UAV buffer into an RSV buffer
		DirectXDeviceMan::GetContext()->CopyResource(poWorldCompute->poVsBoneWorld->poComputeRVSBuffer, 
													 poWorldCompute->poUAVWorldMat->poComputeUAVBuffer);
	}


	void GameObjectAnimSkin::SetIndex(int i)
	{
		AZUL_UNUSED_VAR(i);
		assert(false);
	}

	void GameObjectAnimSkin::privUpdate(AnimTime currentTime)
	{
		AZUL_UNUSED_VAR(currentTime);

		Trans T(*this->poTrans);
		Scale S(*this->poScale);
		Quat  Q(*this->poQuat);

		cur_rot_x += delta_x;
		cur_rot_y += delta_y;
		cur_rot_z += delta_z;

		Rot Rx(Rot1::X, cur_rot_x);
		Rot Ry(Rot1::Y, cur_rot_y);
		Rot Rz(Rot1::Z, cur_rot_z);

		// world matrix
		*this->poWorld = S * Q * Rx * Ry * Rz * T;
	}

	void GameObjectAnimSkin::SetQuat(float qx, float qy, float qz, float qw)
	{
		this->poQuat->set(qx, qy, qz, qw);
	}

	void GameObjectAnimSkin::SetScale(float sx, float sy, float sz)
	{
		this->poScale->set(sx, sy, sz);
	}

	void GameObjectAnimSkin::SetTrans(float x, float y, float z)
	{
		this->poTrans->set(x, y, z);
	}

	void GameObjectAnimSkin::SetScale(Vec3 &r)
	{
		*this->poScale = r;
	}

	void GameObjectAnimSkin::SetQuat(Quat &r)
	{
		*this->poQuat = r;
	}

	void GameObjectAnimSkin::SetTrans(Vec3 &r)
	{
		*this->poTrans = r;
	}
}

// --- End of File ---
