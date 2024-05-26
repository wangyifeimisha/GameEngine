//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#include "GLTF.h"
#include "GLTF_Helper.h"
#include "meshData.h"
#include "meshDataConverter.h"
#include "json.hpp"
#include "File.h"

using namespace Azul;
using namespace tinygltf;
using json = nlohmann::json;

void ConvertModel(const char *const pFileName, const char *const pTargetName)
{
	bool status;
	tinygltf::Model gltfModel;

	// runtime model
	meshData  runModel;

	Trace::out("%-25s", pFileName);

	// Strip the extension .tga off the name
	unsigned int len = strlen(pFileName);
	char *pTmp = new char[len + 1]();
	memset(pTmp, 0, len);
	memcpy(pTmp, pFileName, len - strlen(".glb"));

	// base name
	std::string BaseName = pTargetName;
	delete[] pTmp;

	// Load the gltfModel
	status = GLTF::LoadBinary(gltfModel, pFileName);
	assert(status);

	// Read glb into memory (raw buffer)
	char *poBuff = nullptr;
	unsigned int BuffSize(0);

	status = GLTF::GetGLBRawBuffer(poBuff, BuffSize, pFileName);
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

	// Fill out the runtime Model data

	// Model Name
	memcpy_s(runModel.pMeshName, meshData::FILE_NAME_SIZE, gltfModel.materials[0].name.c_str(), gltfModel.materials[0].name.length());

	// Set vbo 
	GLTF::SetVBO(gltfModel, "POSITION", runModel.vbo_vert, pBinaryBuff);
	GLTF::SetVBO(gltfModel,"NORMAL", runModel.vbo_norm, pBinaryBuff);
	GLTF::SetVBO(gltfModel,"TEXCOORD_0", runModel.vbo_uv, pBinaryBuff);
	GLTF::SetVBO(gltfModel, "COLOR_0", runModel.vbo_color, pBinaryBuff);
	GLTF::SetVBO_index(gltfModel, "INDICES", runModel.vbo_index, pBinaryBuff);

	// PolyCount
	runModel.triCount = runModel.vbo_index.count / 3;
	runModel.vertCount = runModel.vbo_vert.count;

	// RenderMode
	runModel.mode = meshDataConverter::GetMode(gltfModel.meshes[0].primitives[0].mode);

	delete[] poBuff;

	meshData_proto mA_proto;
	runModel.Serialize(mA_proto);

	// -------------------------------
	//  Write to file
	//--------------------------------

	File::Handle fh;
	File::Error err;

	const char *pProtoFileType = nullptr;
	status = GLTF::GetAzulProtoType(pProtoFileType, runModel);
	assert(status);

	std::string OutputFileName = BaseName + pProtoFileType + ".proto.azul";
	Trace::out(" --> %22s\n", OutputFileName.c_str());

	err = File::Open(fh, OutputFileName.c_str(), File::Mode::WRITE);
	assert(err == File::Error::SUCCESS);

	std::string strOut;
	mA_proto.SerializeToString(&strOut);

	File::Write(fh, strOut.data(), strOut.length());
	assert(err == File::Error::SUCCESS);

	err = File::Close(fh);
	assert(err == File::Error::SUCCESS);

	// -------------------------------
	// Read and recreate model data
	// -------------------------------

	err = File::Open(fh, OutputFileName.c_str(), File::Mode::READ);
	assert(err == File::Error::SUCCESS);

	err = File::Seek(fh, File::Position::END, 0);
	assert(err == File::Error::SUCCESS);

	DWORD FileLength;
	err = File::Tell(fh, FileLength);
	assert(err == File::Error::SUCCESS);

	char *poNewBuff = new char[FileLength]();
	assert(poNewBuff);

	err = File::Seek(fh, File::Position::BEGIN, 0);
	assert(err == File::Error::SUCCESS);

	err = File::Read(fh, poNewBuff, FileLength);
	assert(err == File::Error::SUCCESS);

	err = File::Close(fh);
	assert(err == File::Error::SUCCESS);


	std::string strIn(poNewBuff, FileLength);
	meshData_proto mB_proto;

	mB_proto.ParseFromString(strIn);

	meshData mB;
	mB.Deserialize(mB_proto);

	delete[] poJSON;

	delete[] poNewBuff;

}

// --- End of File ---
