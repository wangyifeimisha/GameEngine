//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "GLTF.h"
#include "ConvertModel.h"
#include "CreateTexture.h"
#include "CubeMesh.h"
#include "SphereMesh.h"
#include "PyramidMesh.h"
#include "ConvertAnim.h"
#include "ChickenBot.h"
#include "SpriteMesh.h"
#include "ConvertXML.h"
#include "ConvertSkeleton.h"
#include "ConvertSkin.h"
#include "ConvertHierarchy.h"

using namespace Azul;

int main()
{
	// Verify that the version of the library that we linked against is
	// compatible with the version of the headers we compiled against.
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	// Sprite
	CreateSpriteMesh("Sprite");

	// Test Images 
	CreateTexturePNG("TEST_PNG_RGB.png", "TEST_PNG_RGB");
	CreateTexturePNG("TEST_PNG_RGBA.png", "TEST_PNG_RGBA");
	CreateTextureTGA("TEST_TGA_BGR.tga", "TEST_TGA_BGR");
	CreateTextureTGA("TEST_TGA_BGRA.tga", "TEST_TGA_BGRA");

	// Font stuff
	CreateTexturePNG("FontArial36.png","Arial36");
	ConvertXML("MetricsArial36","Arial36");
	         
	// Space Frigate
	CreateTextureTGA("space_frigate.tga","SpaceFrigate");
	ConvertModel("space_frigate.glb","SpaceFrigate");

	ConvertModel("crate.glb","Crate");
	ConvertModel("R2-D2.glb", "R2D2");
	CreateTexturePNG("R2D2_BaseColor.png","R2D2");

	// ChickenBot	
	// CreateChickenBotModels();
	CreateTexturePNG("ChickenbotDiffuse.png","ChickenBot"); 
	ConvertSkin("walk_mesh", "Chickenbot");
	ConvertAnim("walk_mesh","ChickenBot_Walk");
	ConvertSkeleton("walk_mesh", "ChickenBot");
	ConvertHierarchy("walk_mesh", "ChickenBot");
	ConvertInvBind("walk_mesh", "ChickenBot");

	ConvertAnim("turn_left+mesh", "ChickenBot_TurnLeft");
	ConvertAnim("shot_front+mesh", "ChickenBot_ShotFront");
	ConvertAnim("hit_left+mesh", "ChickenBot_HitLeft");

	// Mouse
	CreateTexturePNG("Ch14_1001_Diffuse.png", "Mouse");
	ConvertSkin("Joyful Jump", "Mouse");
	ConvertAnim("Joyful Jump", "MouseJump");
	ConvertSkeleton("Joyful Jump", "Mouse");
	ConvertHierarchy("Joyful Jump", "Mouse");
	ConvertInvBind("Joyful Jump", "Mouse");

	ConvertAnim("Mousey_Samba_Dancing", "MouseSamba");
	ConvertAnim("Mousey_Run_Forward", "MouseRunForward");
	 
	// clean up data directory
	system("del *.png");
	system("del *.tga");
	system("del *.glb");
	system("del *.xml");

	google::protobuf::ShutdownProtobufLibrary();

	return 0;
}

// ---  End of File ---------------
