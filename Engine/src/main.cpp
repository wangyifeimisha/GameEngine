//--------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include "GameMan.h"
#include "google\protobuf\message_lite.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmdLine, int cmdShow)
{
	// Verify that the version of the library that we linked against is
	// compatible with the version of the headers we compiled against.
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	// Game is inside a singleton
	Azul::GameMan::Create("W1(3)",  2*400, 2*300);

	// Launch the window
	int status = Azul::GameMan::GetGame()->wWinMain(hInstance, prevInstance, cmdLine, cmdShow);

	// Clean up
	Azul::GameMan::Destroy();

	// clean shut down
	google::protobuf::ShutdownProtobufLibrary();

	return status;
}

// --- End of File ---
