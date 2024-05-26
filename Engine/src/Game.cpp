//--------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include <d3d11.h>
#include <d3dcompiler.h>
#include <WinUser.h>
#include "Game.h"
#include "Engine.h"
#include "MathEngine.h"
#include "Camera.h"
#include "Colors.h"
#include "GameObject.h"
#include "GameObjectAnimSkin.h"
#include "ShaderObject.h"
#include "ShaderObject_ColorByVertex.h"
#include "ShaderObject_FlatTexture.h"
#include "ShaderObject_SkinFlatTexture.h"
#include "ShaderObject_LightTexture.h"
#include "ShaderObject_ConstColor.h"
#include "ShaderObject_Sprite.h"
#include "ShaderObject_MixerCompute.h"
#include "ShaderObject_WorldCompute.h"
#include "Mesh.h"
#include "MeshProto.h"
#include "GraphicsObject_ColorByVertex.h"
#include "GraphicsObject_Wireframe.h"
#include "GraphicsObject_FlatTexture.h"
#include "GraphicsObject_SkinFlatTexture.h"
#include "GraphicsObject_LightTexture.h"
#include "GraphicsObject_ConstColor.h"
#include "GraphicsObject_Sprite.h"
#include "GameObjectMan.h"
#include "MeshNodeMan.h"
#include "ShaderObjectNodeMan.h"
#include "TextureObject.h"
#include "TextureProto.h"
#include "TexNodeMan.h"
#include "DirectXDeviceMan.h"
#include "CameraMan.h"
#include "CameraDemoInput.h"
#include "CameraMesh.h"
#include "AnimTimer.h"
#include "MathApp.h"
#include "Anim.h"
#include "GameObjectBasic.h"
#include "TimerController.h"
#include "AnimController.h"
#include "Clip.h"
#include "Image.h"
#include "ImageMan.h"
#include "Sprite.h"
#include "GlyphMan.h"
#include "HierarchyMan.h"
#include "InvBindMan.h"

#include "FontSprite.h"
#include "SkelMan.h"
#include "ClipMan.h"

#include "ComputeRSVBuffer.h"
#include "ComputeUAVBuffer.h"
#include "Mixer.h"
#include "WorldCompute.h"

#include "AnimControllerMan.h"


using namespace Azul;

namespace Azul
{
	AnimController *pAnimController;
	AnimController* pAnimController1;
	AnimController* pAnimController2;
	AnimController* pAnimController3;
	FontSprite *pFontSprite1;

	AnimController* pAnimControllerM;

	//-----------------------------------------------------------------------------
	//  Game::Game()
	//		Game Engine Constructor
	//-----------------------------------------------------------------------------

	Game::Game(const char *const pName, int width, int height)
		: Engine(pName, width, height)
	{
		this->globalTimer.Tic();
		this->intervalTimer.Tic();
	}

	//-----------------------------------------------------------------------------
	//  Game::~Game()
	//		Game Engine destructor
	//-----------------------------------------------------------------------------
	Game::~Game()
	{
	}

	//-----------------------------------------------------------------------------
	// Game::LoadContent()
	//		Allows you to load all content needed for your engine,
	//	    such as objects, graphics, etc.
	//-----------------------------------------------------------------------------
	bool Game::LoadContent()
	{
		ShaderObjectNodeMan::Create();
		MeshNodeMan::Create();
		GameObjectMan::Create();
		TexNodeMan::Create();
		CameraMan::Create();
		ImageMan::Create();
		GlyphMan::Create();
		SkelMan::Create();
		ClipMan::Create();
		HierarchyMan::Create();
		InvBindMan::Create();
		AnimControllerMan::Create();

		// --------------------------
		// Camera setup
		// --------------------------

		// Camera_0		

		//---------------------------------------------------------------------------------------------------------
		// Setup the current 3D perspective Camera
		//---------------------------------------------------------------------------------------------------------
		Camera *pCam0 = new Camera(Camera::Type::PERSPECTIVE_3D);

		pCam0->setViewport(0, 0, this->WindowWidth, this->WindowHeight);
		pCam0->setPerspective(35.0f, float(pCam0->getScreenWidth()) / float(pCam0->getScreenHeight()), 1.0f, 10000.0f);

		pCam0->setOrientAndPosition(Vec3(0.0f, 1.0f, 0.0f),
									Vec3(0.0f, 0.0f, 0.0f),
									Vec3(0.0f, 0.0f, 12.0f));
		pCam0->updateCamera();
		CameraMan::Add(Camera::Name::CAMERA_0, pCam0);
		CameraMan::SetCurrent(Camera::Name::CAMERA_0, Camera::Type::PERSPECTIVE_3D);

		//---------------------------------------------------------------------------------------------------------
		// Setup the current 2D orthographic Camera
		//---------------------------------------------------------------------------------------------------------
		Camera *pCam2D = new Camera(Camera::Type::ORTHOGRAPHIC_2D);

		pCam2D->setViewport(0, 0, this->WindowWidth, this->WindowHeight);
		pCam2D->setOrthographic((float)-pCam2D->getScreenWidth() / 2.0f, (float)pCam2D->getScreenWidth() / 2.0f,
								(float)-pCam2D->getScreenHeight() / 2.0f, (float)pCam2D->getScreenHeight() / 2.0f,
								1.0f, 1000.0f);
		pCam2D->setOrientAndPosition(Vec3(0.0f, 1.0f, 0.0f), Vec3(0.0f, 0.0f, -1.0f), Vec3(0.0f, 0.0f, 2.0f));

		// Holder for the current 2D  cameras
		CameraMan::Add(Camera::Name::CAMERA_1, pCam2D);
		CameraMan::SetCurrent(Camera::Name::CAMERA_1, Camera::Type::ORTHOGRAPHIC_2D);


		// --------------------------------
		//  Mesh
		// --------------------------------

		Mesh *poSpriteMesh = new MeshProto("Sprite.m.proto.azul");
		MeshNodeMan::Add(Mesh::Name::SPRITE, poSpriteMesh);

		Mesh *poSpaceFrigate = new MeshProto("SpaceFrigate.m.proto.azul");
		MeshNodeMan::Add(Mesh::Name::SpaceFrigate, poSpaceFrigate);

		Mesh *poChickenBot = new MeshProto("ChickenBot.m.proto.azul");
		MeshNodeMan::Add(Mesh::Name::ChickenBot, poChickenBot);

		Mesh* pCrateMesh = new MeshProto("crate.m.proto.azul");
		MeshNodeMan::Add(Mesh::Name::CRATE, pCrateMesh);

		Mesh* pR2D2 = new MeshProto("R2D2.m.proto.azul");
		MeshNodeMan::Add(Mesh::Name::R2D2, pR2D2);

		Mesh* pMouse = new MeshProto("Mouse.m.proto.azul");
		MeshNodeMan::Add(Mesh::Name::Mouse, pMouse);


		// --------------------------------
		//  Shader
		// --------------------------------

		ShaderObject *poShaderC = new ShaderObject_Sprite(ShaderObject::Name::Sprite);
		ShaderObjectNodeMan::Add(poShaderC);

		ShaderObject *poShaderA0 = new ShaderObject_ColorByVertex(ShaderObject::Name::ColorByVertex);
		ShaderObject *poShaderA1 = new ShaderObject_FlatTexture(ShaderObject::Name::FlatTexture);
		ShaderObject *poShaderA2 = new ShaderObject_LightTexture(ShaderObject::Name::LightTexture);
		ShaderObject *poShaderA3 = new ShaderObject_ConstColor(ShaderObject::Name::ConstColor);
		ShaderObject *poShaderA4 = new ShaderObject_SkinFlatTexture(ShaderObject::Name::SkinFlatTexture);

		ShaderObject *poShaderA6 = new ShaderObject_MixerCompute(ShaderObject::Name::MixerCompute);
		ShaderObject *poShaderA7 = new ShaderObject_WorldCompute(ShaderObject::Name::WorldCompute);

		ShaderObjectNodeMan::Add(poShaderA0);
		ShaderObjectNodeMan::Add(poShaderA1);
		ShaderObjectNodeMan::Add(poShaderA2);
		ShaderObjectNodeMan::Add(poShaderA3);
		ShaderObjectNodeMan::Add(poShaderA4);

		ShaderObjectNodeMan::Add(poShaderA6);
		ShaderObjectNodeMan::Add(poShaderA7);

		// -----------------------------------
		//  Texture
		// -----------------------------------

		TextureObject *pTex0 = new TextureProto("TEST_PNG_RGB.t.proto.azul");
		TextureObject *pTex1 = new TextureProto("TEST_PNG_RGBA.t.proto.azul");
		TextureObject *pTex2 = new TextureProto("TEST_TGA_BGR.t.proto.azul");
		TextureObject *pTex3 = new TextureProto("TEST_TGA_BGRA.t.proto.azul");

		TexNodeMan::Add(TextureObject::Name::Test0, pTex0);
		TexNodeMan::Add(TextureObject::Name::Test1, pTex1);
		TexNodeMan::Add(TextureObject::Name::Test2, pTex2);
		TexNodeMan::Add(TextureObject::Name::Test3, pTex3);

		TextureObject *pTexChickenBot = new TextureProto("Chickenbot.t.proto.azul");
		TexNodeMan::Add(TextureObject::Name::ChickenBot, pTexChickenBot);

		TextureObject *pTexSpaceFrigate = new TextureProto("SpaceFrigate.t.proto.azul");
		TexNodeMan::Add(TextureObject::Name::SpaceFrigate, pTexSpaceFrigate);

		TextureObject* pTexR2D2 = new TextureProto("R2D2.t.proto.azul");
		TexNodeMan::Add(TextureObject::Name::R2D2, pTexR2D2);

		TextureObject* pTexMouse = new TextureProto("Mouse.t.proto.azul");
		TexNodeMan::Add(TextureObject::Name::Mouse, pTexMouse);

		// -----------------------------------
		//  Image
		// -----------------------------------

		ImageMan::Add(Image::Name::WhiteBird,
					  TextureObject::Name::Test1,
					  Rect(139.0f, 131.0f, 84.0f, 97.0f));
		ImageMan::Add(Image::Name::ALLBirds,
					  TextureObject::Name::Test1,
					  Rect(0.0f, 0.0f, 377.0f, 234.0f));
		ImageMan::Add(Image::Name::GreenBird,
					  TextureObject::Name::Test1,
					  Rect(244.0f, 134.0f, 102.0f, 75.0f));

		// ---------------------------------------------
		//  Font - load xml
		// ---------------------------------------------
		TextureObject *pTmp = new TextureProto("Arial36.t.proto.azul");
		TexNodeMan::Add(TextureObject::Name::FontAriel36, pTmp);

		GlyphMan::Add("Arial36.xml.proto.azul", TextureObject::Name::FontAriel36);


		// ---------------------------------------------
		//  GraphicsObject -- needs model + shader
		// ---------------------------------------------

		GraphicsObject *pGraphicsObject(nullptr);

		// ---------------------------------
		// Space Frigate
		// ---------------------------------
		pGraphicsObject = new GraphicsObject_FlatTexture(Mesh::Name::SpaceFrigate,
														 ShaderObject::Name::FlatTexture,
														 pTexSpaceFrigate);
		GameObjectBasic *pSpaceFrigate = new GameObjectBasic(pGraphicsObject);
		GameObjectMan::Add(pSpaceFrigate, GameObjectMan::GetRoot());
		pSpaceFrigate->SetScale(0.015f, 0.015f, 0.015f);
		Quat q(Rot1::Y, -MATH_PI2 + 0.15f);
		pSpaceFrigate->SetQuat(q);
		pSpaceFrigate->delta_x = 0.01f;
		pSpaceFrigate->delta_y = 0.01f;
		pSpaceFrigate->delta_z = -0.01f;
		pSpaceFrigate->SetTrans(-2, 0, 3);

		// Crate
		Vec3 lightColor(1, 1, 1);
		Vec3 lightPos(1, 50, 50);
		pGraphicsObject = new GraphicsObject_LightTexture(Mesh::Name::CRATE,
			ShaderObject::Name::LightTexture,
			TextureObject::Name::Test0, lightColor, lightPos);
		GameObjectBasic* pGameObj = new GameObjectBasic(pGraphicsObject);

		pGameObj->SetScale(0.5f, 0.5f, 0.5f);
		pGameObj->SetTrans(-4, 1.5, -1);
		pGameObj->delta_y = 0.01f;
		pGameObj->delta_x = 0.005f;

		GameObjectMan::Add(pGameObj, GameObjectMan::GetRoot());

		// R2D2
		pGraphicsObject = new GraphicsObject_LightTexture(Mesh::Name::R2D2,
			ShaderObject::Name::LightTexture,
			TextureObject::Name::R2D2, lightColor, lightPos);

		pGameObj = new GameObjectBasic(pGraphicsObject);

		pGameObj->SetScale(40.0f, 40.0f, 40.0f);
		pGameObj->SetTrans(-1, 3, 0);
		pGameObj->cur_rot_y = 1.57f;

		pGameObj->delta_x = 0.01f;
		pGameObj->delta_y = 0.01f;
		//pGameObj->delta_z = 0.01f;

		GameObjectMan::Add(pGameObj, GameObjectMan::GetRoot());

		Vec3 vColor = Vec3(0, 0, 1.0f);
		pGraphicsObject = new GraphicsObject_Wireframe(Mesh::Name::R2D2,
			ShaderObject::Name::ConstColor, vColor);

		pGameObj = new GameObjectBasic(pGraphicsObject);

		pGameObj->SetScale(40.0f, 40.0f, 40.0f);
		pGameObj->SetTrans(-1,1.5,0);
		pGameObj->delta_x = 0.01f;
		//pGameObj->delta_y = 0.01f;
		//pGameObj->delta_z = 0.01f;

		GameObjectMan::Add(pGameObj, GameObjectMan::GetRoot());

		// ----------------------------------
		// Sprite
		// ----------------------------------
		pGraphicsObject = new GraphicsObject_Sprite(Mesh::Name::SPRITE,
													ShaderObject::Name::Sprite,
													Image::ALLBirds,
													Rect(150, 150, 300, 200));
		Sprite *pSprite = new Sprite(pGraphicsObject);
		GameObjectMan::Add(pSprite, GameObjectMan::GetRoot());

		// ---------------------------------
		// FontSprite
		// ---------------------------------
		pGraphicsObject = new GraphicsObject_Sprite(Mesh::Name::SPRITE,
													ShaderObject::Name::Sprite,
													Image::GreenBird,  //anything
													Rect(100, 100, 100, 100));
		pFontSprite1 = new FontSprite(pGraphicsObject);
		GameObjectMan::Add(pFontSprite1, GameObjectMan::GetRoot());

		pFontSprite1->Set(FontSprite::Name::TestMessage, "ABCD", Glyph::Name::Arial36pt, 50, 500);

		pGraphicsObject = new GraphicsObject_Sprite(Mesh::Name::SPRITE,
													ShaderObject::Name::Sprite,
													Image::GreenBird,  //anything
													Rect(100, 100, 100, 100));
		FontSprite *pFontSprite = new FontSprite(pGraphicsObject);
		GameObjectMan::Add(pFontSprite, GameObjectMan::GetRoot());

		Color color(0, 0, 1.0f, 1.0f);
		pFontSprite->Set(FontSprite::Name::TestOneOff, "Milestone3", Glyph::Name::Arial36pt, 50, 550, color);


		// ---------------------------------
		// Create Animation
		// ---------------------------------
		//		po - pointer owned
		//		pt - pointer transient being owned by someone else to own
		//  ------------------------------------------------------------------

		// Load resources
		HierarchyMan::Add("ChickenBot.h.proto.azul", Hierarchy::Name::ChickenBot);
		HierarchyMan::Add("Mouse.h.proto.azul", Hierarchy::Name::Mouse);

		ClipMan::Add("ChickenBot_Walk.a.proto.azul", Clip::Name::Walk_ChickenBot, Skel::Name::ChickenBot);
		ClipMan::Add("ChickenBot_TurnLeft.a.proto.azul", Clip::Name::TurnLeft_ChickenBot, Skel::Name::ChickenBot);
		ClipMan::Add("ChickenBot_HitLeft.a.proto.azul", Clip::Name::HitLeft_ChickenBot, Skel::Name::ChickenBot);
		ClipMan::Add("ChickenBot_ShotFront.a.proto.azul", Clip::Name::ShotFront_ChickenBot, Skel::Name::ChickenBot);

		ClipMan::Add("MouseJump.a.proto.azul", Clip::Name::Jump_Mouse, Skel::Name::Mouse);
		ClipMan::Add("MouseSamba.a.proto.azul", Clip::Name::Samba_Mouse, Skel::Name::Mouse);
		ClipMan::Add("MouseRunForward.a.proto.azul", Clip::Name::Run_Mouse, Skel::Name::Mouse);

		InvBindMan::Add("ChickenBot.i.proto.azul", InvBind::Name::ChickenBot);
		InvBindMan::Add("Mouse.i.proto.azul", InvBind::Name::Mouse);


		// Create Anim
		Clip *pClip = ClipMan::Find(Clip::Name::Walk_ChickenBot);
		Clip* pClip2 = ClipMan::Find(Clip::Name::TurnLeft_ChickenBot);
		Clip* pClip3 = ClipMan::Find(Clip::Name::Samba_Mouse);
		Clip* pClip4 = ClipMan::Find(Clip::Name::Run_Mouse);
		Clip* pClipM = ClipMan::Find(Clip::Name::Jump_Mouse);

		// Setup Compute shaders data
		// Walk animation
		Mixer *ptMixer = new Mixer(pClip);
		WorldCompute *ptWorldCompute = new WorldCompute(ptMixer,
														Hierarchy::Name::ChickenBot,
														InvBind::Name::ChickenBot);
		assert(ptWorldCompute);

		// Anim needs: Clip, Skeleton, BoneResult
		Anim *ptAnim = new Anim(pClip, ptMixer);
		assert(ptAnim);

		// Skin Mesh
		GameObjectAnimSkin *pGameSkin;
		GraphicsObject_SkinFlatTexture *pGraphicsSkin;

		// add Mixer and WorldCompute to Graphics Object
		pGraphicsSkin = new GraphicsObject_SkinFlatTexture(Mesh::Name::ChickenBot,
														   ShaderObject::Name::SkinFlatTexture,
														   TextureObject::Name::ChickenBot,
														   ptMixer,
														   ptWorldCompute);

		// add Mixer and WorldCompute to Game Object
		pGameSkin = new GameObjectAnimSkin(pGraphicsSkin, ptMixer, ptWorldCompute);
		pGameSkin->SetName("ChickenSkin");
		pGameSkin->delta_y = 0.003f;
		pGameSkin->SetScale(40, 40, 40);
		pGameSkin->SetTrans(0, -3, 0);
		GameObjectMan::Add(pGameSkin, GameObjectMan::GetRoot());

		pAnimController = new AnimController(ptAnim, 0.2f * AnimTime(AnimTime::Duration::FILM_24_FRAME));

		// Turn left animation
		ptMixer = new Mixer(pClip2);
		ptWorldCompute = new WorldCompute(ptMixer,
			Hierarchy::Name::ChickenBot,
			InvBind::Name::ChickenBot);
		assert(ptWorldCompute);

		// Anim needs: Clip, Skeleton, BoneResult
		ptAnim = new Anim(pClip2, ptMixer);
		assert(ptAnim);

		// add Mixer and WorldCompute to Graphics Object
		pGraphicsSkin = new GraphicsObject_SkinFlatTexture(Mesh::Name::ChickenBot,
			ShaderObject::Name::SkinFlatTexture,
			TextureObject::Name::ChickenBot,
			ptMixer,
			ptWorldCompute);

		// add Mixer and WorldCompute to Game Object
		pGameSkin = new GameObjectAnimSkin(pGraphicsSkin, ptMixer, ptWorldCompute);
		pGameSkin->SetName("ChickenSkin");
		pGameSkin->delta_y = 0.003f;
		pGameSkin->SetScale(40, 40, 40);
		pGameSkin->SetTrans(3, -3, 0);
		GameObjectMan::Add(pGameSkin, GameObjectMan::GetRoot());

		pAnimController1 = new AnimController(ptAnim, 0.2f * AnimTime(AnimTime::Duration::FILM_24_FRAME));

		// Samba animation
		ptMixer = new Mixer(pClip3);
		ptWorldCompute = new WorldCompute(ptMixer,
			Hierarchy::Name::Mouse,
			InvBind::Name::Mouse);
		assert(ptWorldCompute);

		// Anim needs: Clip, Skeleton, BoneResult
		ptAnim = new Anim(pClip3, ptMixer);
		assert(ptAnim);

		// add Mixer and WorldCompute to Graphics Object
		pGraphicsSkin = new GraphicsObject_SkinFlatTexture(Mesh::Name::Mouse,
			ShaderObject::Name::SkinFlatTexture,
			TextureObject::Name::Mouse,
			ptMixer,
			ptWorldCompute);

		// add Mixer and WorldCompute to Game Object
		pGameSkin = new GameObjectAnimSkin(pGraphicsSkin, ptMixer, ptWorldCompute);
		pGameSkin->SetName("MouseSkin");
		pGameSkin->delta_y = 0.003f;
		pGameSkin->SetScale(2, 2, 2);
		pGameSkin->SetTrans(3, -1, 0);
		GameObjectMan::Add(pGameSkin, GameObjectMan::GetRoot());

		pAnimController2 = new AnimController(ptAnim, 0.2f * AnimTime(AnimTime::Duration::FILM_24_FRAME));

		// Run forward animation
		ptMixer = new Mixer(pClip4);
		ptWorldCompute = new WorldCompute(ptMixer,
			Hierarchy::Name::Mouse,
			InvBind::Name::Mouse);
		assert(ptWorldCompute);

		// Anim needs: Clip, Skeleton, BoneResult
		ptAnim = new Anim(pClip4, ptMixer);
		assert(ptAnim);

		// add Mixer and WorldCompute to Graphics Object
		pGraphicsSkin = new GraphicsObject_SkinFlatTexture(Mesh::Name::Mouse,
			ShaderObject::Name::SkinFlatTexture,
			TextureObject::Name::Mouse,
			ptMixer,
			ptWorldCompute);

		// add Mixer and WorldCompute to Game Object
		pGameSkin = new GameObjectAnimSkin(pGraphicsSkin, ptMixer, ptWorldCompute);
		pGameSkin->SetName("MouseSkin");
		pGameSkin->delta_y = 0.003f;
		pGameSkin->SetScale(2, 2, 2);
		pGameSkin->SetTrans(0, -1, 0);
		GameObjectMan::Add(pGameSkin, GameObjectMan::GetRoot());

		pAnimController3 = new AnimController(ptAnim, 0.2f * AnimTime(AnimTime::Duration::FILM_24_FRAME));


		// Joyful jump
		ptMixer = new Mixer(pClipM);
		ptWorldCompute = new WorldCompute(ptMixer,
			Hierarchy::Name::Mouse,
			InvBind::Name::Mouse);
		assert(ptWorldCompute);

		// Anim needs: Clip, Skeleton, BoneResult
		ptAnim = new Anim(pClipM, ptMixer);
		assert(ptAnim);

		// add Mixer and WorldCompute to Graphics Object
		pGraphicsSkin = new GraphicsObject_SkinFlatTexture(Mesh::Name::Mouse,
			ShaderObject::Name::SkinFlatTexture,
			TextureObject::Name::Mouse,
			ptMixer,
			ptWorldCompute);

		// add Mixer and WorldCompute to Game Object
		pGameSkin = new GameObjectAnimSkin(pGraphicsSkin, ptMixer, ptWorldCompute);
		pGameSkin->SetName("Mouse");
		pGameSkin->delta_y = 0.003f;
		pGameSkin->SetScale(2, 2, 2);
		pGameSkin->SetTrans(2, 1, 0);
		GameObjectMan::Add(pGameSkin, GameObjectMan::GetRoot());

		pAnimControllerM = new AnimController(ptAnim, 0.2f * AnimTime(AnimTime::Duration::FILM_24_FRAME));

		return true;
	}




	//-----------------------------------------------------------------------------
	// Game::Update()
	//      Called once per frame, update data, tranformations, etc
	//      Use this function to control process order
	//      Input, AI, Physics, Animation, and Graphics
	//-----------------------------------------------------------------------------
	void Game::Update(float)
	{
		this->intervalTimer.Toc();
		this->intervalTimer.Tic();

		static int count = 0;
		count++;
		char buff[20];
		memset(buff, 0x0, 20);
		sprintf_s(buff, 20, "Count: %d", count);
		pFontSprite1->UpdateMessage(buff);
		// -----------------------
		// Read inputs
		// -----------------------
		CameraDemoInput();

		// ------------------------------------
		// Camera update
		// ------------------------------------

		Camera *pCam3D = CameraMan::GetCurrent(Camera::Type::PERSPECTIVE_3D);
		pCam3D->updateCamera();

		Camera *pCam2D = CameraMan::GetCurrent(Camera::Type::ORTHOGRAPHIC_2D);
		pCam2D->updateCamera();

		// ------------------------------------
		// Animate Me
		// ------------------------------------
		if(pAnimController)
		{
			pAnimController->Update();
		}

		if (pAnimController1)
		{
			pAnimController1->Update();
		}

		if (pAnimController2)
		{
			pAnimController2->Update();
		}

		if (pAnimController3)
		{
			pAnimController3->Update();
		}

		if (pAnimControllerM)
		{
			pAnimControllerM->Update();
		}
		// ------------------------------------
		// Update GameObjects
		// ------------------------------------
		GameObjectMan::Update(this->globalTimer.Toc());

	}

	//-----------------------------------------------------------------------------
	// Game::Render()
	//		This function is called once per frame
	//	    Use this for draw graphics to the screen.
	//      Only do rendering here
	//-----------------------------------------------------------------------------
	void Game::Render()
	{
		this->SetDefaultTargetMode();

		GameObjectMan::Draw();
	}

	//-----------------------------------------------------------------------------
	// Game::UnLoadContent()
	//       unload content (resources loaded above)
	//       unload all content that was loaded before the Engine Loop started
	//-----------------------------------------------------------------------------
	void Game::UnloadContent()
	{
		InvBindMan::Destroy();
		HierarchyMan::Destroy();
		ClipMan::Destroy();
		SkelMan::Destroy();
		GlyphMan::Destroy();
		ImageMan::Destroy();
		CameraMan::Destroy();
		ShaderObjectNodeMan::Destroy();
		MeshNodeMan::Destroy();
		GameObjectMan::Destroy();
		TexNodeMan::Destroy();
		DirectXDeviceMan::Destroy();
		AnimControllerMan::Destroy();

		
		delete pAnimController;
		delete pAnimController1;
		delete pAnimController2;
		delete pAnimController3;
		delete pAnimControllerM;
	}

	//------------------------------------------------------------------
	// Game::ClearBufferFunc()
	// Allows user to change the way the clear buffer function works
	// 
	// Clear the color and depth buffers.
	//------------------------------------------------------------------
	void Game::ClearDepthStencilBuffer()
	{
#ifdef _DEBUG
		const Vec4 ClearColor = Azul::Colors::LightGray;
#else
		const Vec4 ClearColor = Azul::Colors::Wheat;
#endif
		float clearDepth = 1.0f;
		uint8_t clearStencil = 0;
		g_d3dDeviceContext->ClearRenderTargetView(g_d3dRenderTargetView, (const float *)&ClearColor);
		g_d3dDeviceContext->ClearDepthStencilView(g_d3dDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, clearDepth, clearStencil);
	}

}

// --- End of File ---
