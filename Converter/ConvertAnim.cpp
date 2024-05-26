//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "GLTF.h"
#include "meshData.h"
#include "meshDataConverter.h"

#include "json.hpp"
#include "File.h"
#include "MathEngine.h"
#include "ConvertAnim.h"
#include "Skeleton.h"
#include "Anim.h"

using namespace Azul;
using namespace tinygltf;
using json = nlohmann::json;

namespace Azul
{
	void ConvertAnim(const char *const pName, const char *const pTargetName)
	{
		assert(pName);

		char sBuff[40];
		sprintf_s(sBuff, 40, "Anim(%s)", pName);
		Trace::out("%-25s", sBuff);

		bool status;
		tinygltf::Model gltfModel;

		// runtime model
		meshData  runModel;

		// glb file name defined here:
		const char *pGLB_Name = pName;
		const char *pGLB_extension = ".glb";

		size_t FileNameSize = strlen(pGLB_Name) + strlen(pGLB_extension) + 1;

		char *poFileName = new char[FileNameSize]();
		strcat_s(poFileName, FileNameSize, pGLB_Name);
		strcat_s(poFileName, FileNameSize, pGLB_extension);

		// Load the gltfModel
		status = GLTF::LoadBinary(gltfModel, poFileName);
		assert(status);

		// Read glb into memory (raw buffer)
		char *poBuff = nullptr;
		unsigned int BuffSize(0);

		status = GLTF::GetGLBRawBuffer(poBuff, BuffSize, poFileName);
		assert(status);

		// Get GLB_Header
		GLB_header glbHeader;
		status = GLTF::GetGLBHeader(glbHeader, poBuff, BuffSize);
		assert(status);

		// Get Raw JSON
		char *poJSON = nullptr;
		unsigned int JsonSize(0);
		status = GLTF::GetRawJSON(poJSON, JsonSize, poBuff, BuffSize);
		assert(status);

		// Get the Binary Buffer Address
		char *pBinaryBuff = nullptr;
		unsigned int BinaryBuffSize = 0;
		status = GLTF::GetBinaryBuffPtr(pBinaryBuff, BinaryBuffSize, poBuff, BuffSize);
		assert(status);

		// ANIMATION
		ANIM animData;
		animData.CreateAnim(gltfModel, pTargetName);

		delete[] poBuff;
		delete[] poFileName;
		delete[] poJSON;

	}
}

// --- End of File ---
