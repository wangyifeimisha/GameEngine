//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "MeshProto.h"
#include "MathEngine.h"
#include "Engine.h"
#include "File.h"
#include "meshData.h"
#include "DirectXDeviceMan.h"

namespace Azul
{
	MeshProto::MeshProto(const char *const pMeshFileName)
		: Mesh(0, 0)   // need to update numVerts and numIndices
	{
		// future proofing it for a file
		assert(pMeshFileName);
		AZUL_UNUSED_VAR(pMeshFileName);

		// ----------------------------------------------
		// READ the data from the file ONLY
		// ----------------------------------------------

		// File stuff
		File::Handle fh;
		File::Error  ferror;

		ferror = File::Open(fh, pMeshFileName, File::Mode::READ);
		assert(ferror == File::Error::SUCCESS);

		// Get the size
		ferror = File::Seek(fh, File::Position::END, 0);
		assert(ferror == File::Error::SUCCESS);

		DWORD length;
		ferror = File::Tell(fh, length);
		assert(ferror == File::Error::SUCCESS);

		ferror = File::Seek(fh, File::Position::BEGIN, 0);
		assert(ferror == File::Error::SUCCESS);

		char *poBuff = new char[length];
		assert(poBuff);

		ferror = File::Read(fh, poBuff, length);
		assert(ferror == File::Error::SUCCESS);

		ferror = File::Close(fh);
		assert(ferror == File::Error::SUCCESS);

		// Now the raw data is poBUff
		// deserialize the data --> mB
		std::string strIn(poBuff, length);
		meshData_proto mB_proto;

		mB_proto.ParseFromString(strIn);

		meshData mB;
		mB.Deserialize(mB_proto);
		delete[] poBuff;

		// Now the model is mB...
		// move it into the Mesh

		// Do I know this format?
		assert(strcmp(mB.pVersion, "1.0.5") == 0);


		// Using the hdr, allocate the space for the buffers
		this->numVerts = (int)mB.vbo_vert.count;
		this->numIndices = (int)mB.triCount * 3;

		assert(this->numIndices > 0);
		assert(this->numVerts > 0);

		// Load the verts data: ---------------------------------------------------------

		// ------------------------------------------------
		// Create an initialize the vertex buffer - pos
		// ------------------------------------------------

		unsigned int numBytes;
		void *pBuff;

		if(mB.vbo_vert.enabled)
		{
			assert(mB.vbo_vert.poData);
			assert(mB.vbo_vert.dataSize > 0);
			assert(mB.vbo_vert.vboType == vboData::VBO_TYPE::VEC3);
			assert(mB.vbo_vert.componentType == vboData::VBO_COMPONENT::FLOAT);

			numBytes = mB.vbo_vert.dataSize;
			pBuff = mB.vbo_vert.poData;

			poVertexBuffer_pos = CreateVertexBuffer(numBytes, pBuff);
		}
		else
		{
			poVertexBuffer_pos = nullptr;
		}

		// ------------------------------------------------
		// Create an initialize the vertex buffer - color
		// ------------------------------------------------
		if(mB.vbo_color.enabled)
		{
			// color - fix
			assert(false);
			poVertexBuffer_color = nullptr;
		}
		else
		{
			poVertexBuffer_color = nullptr;
		}

		// ------------------------------------------------
		// Create an initialize the vertex buffer - uv
		// ------------------------------------------------
		if(mB.vbo_uv.enabled)
		{
			assert(mB.vbo_uv.poData);
			assert(mB.vbo_uv.dataSize > 0);
			assert(mB.vbo_uv.vboType == vboData::VBO_TYPE::VEC2);
			assert(mB.vbo_uv.componentType == vboData::VBO_COMPONENT::FLOAT);

			numBytes = mB.vbo_uv.dataSize;
			pBuff = mB.vbo_uv.poData;

			poVertexBuffer_texCoord = CreateVertexBuffer(numBytes, pBuff);
		}
		else
		{
			poVertexBuffer_texCoord = nullptr;
		}

		// ------------------------------------------------
		// Create an initialize the vertex buffer - norms
		// ------------------------------------------------
		if(mB.vbo_norm.enabled)
		{
			assert(mB.vbo_norm.poData);
			assert(mB.vbo_norm.dataSize > 0);
			assert(mB.vbo_norm.vboType == vboData::VBO_TYPE::VEC3);
			assert(mB.vbo_norm.componentType == vboData::VBO_COMPONENT::FLOAT);

			numBytes = mB.vbo_norm.dataSize;
			pBuff = mB.vbo_norm.poData;

			poVertexBuffer_norm = CreateVertexBuffer(numBytes, pBuff);
		}
		else
		{
			poVertexBuffer_norm = nullptr;
		}

		// ------------------------------------------------
		// Create an initialize the vertex buffer - weights
		// ------------------------------------------------
		if(mB.vbo_weights.enabled)
		{
			assert(mB.vbo_weights.poData);
			assert(mB.vbo_weights.dataSize > 0);
			assert(mB.vbo_weights.vboType == vboData::VBO_TYPE::VEC4);
			assert(mB.vbo_weights.componentType == vboData::VBO_COMPONENT::FLOAT);

			numBytes = mB.vbo_weights.dataSize;
			pBuff = mB.vbo_weights.poData;


			//Vec4f *pTmp = (Vec4f *)pBuff;
			//for(size_t i = 0; i < mB.vbo_joints.count; i++)
			//{
			//	Trace::out("[%d]  %f %f %f %f \n", i,
			//			   pTmp[i].x, pTmp[i].y, pTmp[i].z, pTmp[i].w);
			//}

			poVertexBuffer_weights= CreateVertexBuffer(numBytes, pBuff);
		}
		else
		{
			poVertexBuffer_weights = nullptr;
		}


		// ------------------------------------------------
		// Create an initialize the vertex buffer - joints
		// ------------------------------------------------
		if(mB.vbo_joints.enabled)
		{
			assert(mB.vbo_joints.poData);
			assert(mB.vbo_joints.dataSize > 0);
			assert(mB.vbo_joints.vboType == vboData::VBO_TYPE::VEC4);
			assert(mB.vbo_joints.componentType == vboData::VBO_COMPONENT::UNSIGNED_INT);

			numBytes = mB.vbo_joints.dataSize;
			pBuff = mB.vbo_joints.poData;

			//Vec4ui *pTmp = (Vec4ui *)pBuff;
			//for(size_t i = 0; i < mB.vbo_joints.count; i++)
			//{
			//	Trace::out("[%d]  %d %d %d %d \n", i,
			//			   pTmp[i].x, pTmp[i].y, pTmp[i].z, pTmp[i].w);
			//}


			poVertexBuffer_joints = CreateVertexBuffer(numBytes, pBuff);
		}
		else
		{
			poVertexBuffer_joints = nullptr;
		}


		// ------------------------------------------------
		// Create and initialize the index buffer.
		// ------------------------------------------------
		if(mB.vbo_index.enabled)
		{
			assert(mB.vbo_index.vboType == vboData::VBO_TYPE::SCALAR);
			assert(mB.vbo_index.componentType != vboData::VBO_COMPONENT::DOUBLE
				   && mB.vbo_index.componentType != vboData::VBO_COMPONENT::FLOAT);
			assert(mB.vbo_index.dataSize > 0);
			assert(mB.vbo_index.poData);

			numBytes = mB.vbo_index.dataSize;
			pBuff = mB.vbo_index.poData;

			//Vec3ui *pTmp = (Vec3ui *)pBuff;
			//for (size_t i = 0; i < mB.vbo_index.count; i++)
			//{
			//	Trace::out("[%d] %d %d %d \n", i, pTmp[i].x, pTmp[i].y, pTmp[i].z);
			//}


			poIndexBuffer = CreateIndexBuffer(numBytes, pBuff);
		}
		else
		{
			poIndexBuffer = nullptr;
		}

		// Create the constant buffers for the variables defined in the vertex shader.
		poConstantBuff_vsProjection = CreateConstantBuffer(sizeof(Mat4));
		poConstantBuff_vsView = CreateConstantBuffer(sizeof(Mat4));
		poConstantBuff_vsWorld = CreateConstantBuffer(sizeof(Mat4));

		// Additional material owned by meshProto
		poConstantBuff_vsLightColor = CreateConstantBuffer(sizeof(Vec3));
		poConstantBuff_vsLightPos = CreateConstantBuffer(sizeof(Vec3));

		poConstantBuff_psUvMatrix = CreateConstantBuffer(sizeof(Mat4));
		poConstantBuff_psSpriteColor = CreateConstantBuffer(sizeof(Vec4));
		poConstantBuff_vsBoneWorld = CreateConstantBuffer( (Mesh::BoneCountMax * sizeof(Mat4)) );



		//// Inverse Bind Matrix Array
		//if(mB.vbo_invBind.enabled)
		//{
		//	assert(mB.vbo_invBind.vboType == vboData::VBO_TYPE::MAT4);
		//	assert(mB.vbo_invBind.componentType == vboData::VBO_COMPONENT::FLOAT);
		//	assert(mB.vbo_invBind.dataSize > 0);
		//	assert(mB.vbo_invBind.poData);

		//	numBytes = mB.vbo_invBind.dataSize;
		//	pBuff = mB.vbo_invBind.poData;
		//	unsigned int count = mB.vbo_invBind.count;

		//	poConstantBuff_vsInvBind = CreateConstantBuffer(Mesh::BoneCountMax*sizeof(Mat4));

		//	// transfer to local copy
		//	Mat4 *pMat = (Mat4 *)pBuff;
		//	for(size_t i = 0; i < count; i++)
		//	{
		//		this->poInvBindArray[i] = pMat[i];
		//	}

		//}
		//else
		//{
		//	poConstantBuff_vsInvBind = nullptr;
		//}





	}

	MeshProto::~MeshProto()
	{
		// remove anything dynamic here
	}
}

// --- End of File ---
