//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "GLTF.h"
#include "File.h"
#include "textureDataConverter.h"
#include "vboDataConverter.h"
#include "MeshLayout.h"

using namespace Azul;


bool GLTF::OutputQuat(Model &model, size_t AccessorIndex, size_t NodeIndex, size_t FrameIndex)
{
	Trace::out("Quat bone:%d Frame:%d \n", NodeIndex, FrameIndex);
	unsigned char *pBuff = (unsigned char *)&model.buffers[0].data[0];
	auto QuatAAccessor = model.accessors[AccessorIndex];
	auto QuatABuffView = model.bufferViews[(size_t)QuatAAccessor.bufferView];

	pBuff = pBuff + QuatABuffView.byteOffset;
	assert(QuatAAccessor.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT);
	assert(QuatAAccessor.type == TINYGLTF_TYPE_VEC4);
	Vec4f *pVect4 = (Vec4f *)pBuff;
	for(size_t i = 0; i < QuatAAccessor.count; i++)
	{
		if(FrameIndex == i)
		{
			Trace::out("\t Quat(%ff,%ff,%ff,%ff);\n",
					   pVect4->x, pVect4->y, pVect4->z, pVect4->w);
		}
		pVect4++;
	}

	Trace::out("\n");

	return true;
}


bool GLTF::OutputTrans(Model &model, size_t AccessorIndex, size_t NodeIndex, size_t FrameIndex)
{
	Trace::out("Trans bone:%d Frame:%d \n", NodeIndex, FrameIndex);
	unsigned char *pBuff = (unsigned char *)&model.buffers[0].data[0];
	auto TransAccessor = model.accessors[AccessorIndex];
	auto TransBuffView = model.bufferViews[(size_t)TransAccessor.bufferView];

	pBuff = pBuff + TransBuffView.byteOffset;
	assert(TransAccessor.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT);
	assert(TransAccessor.type == TINYGLTF_TYPE_VEC3);
	Vec3f *pVect3 = (Vec3f *)pBuff;
	for(size_t i = 0; i < TransAccessor.count; i++)
	{
		if(FrameIndex == i)
		{
			Trace::out("\t Vec3(%ff,%ff,%ff);  \n",
					   pVect3->x, pVect3->y, pVect3->z);
		}
		pVect3++;
	}
	Trace::out("\n");

	return true;
}

bool GLTF::LoadASCII(Model &model, const char *const pFileName)
{
	TinyGLTF loader;
	std::string err;
	std::string warn;

	bool status = loader.LoadASCIIFromFile(&model, &err, &warn, pFileName);

	if(!warn.empty())
	{
		Trace::out("Warn: %s\n", warn.c_str());
		assert(false);
	}

	if(!err.empty())
	{
		Trace::out("Err: %s\n", err.c_str());
		assert(false);
	}

	if(!status)
	{
		Trace::out2("Failed to parse glTF\n");
		assert(false);
	}

	return status;
}

bool GLTF::LoadBinary(Model &model, const char *const pFileName)
{
	TinyGLTF loader;
	std::string err;
	std::string warn;

	bool status = loader.LoadBinaryFromFile(&model, &err, &warn, pFileName);

	if(!warn.empty())
	{
		Trace::out("Warn: %s\n", warn.c_str());
		assert(false);
	}

	if(!err.empty())
	{
		Trace::out("Err: %s\n", err.c_str());
		assert(false);
	}

	if(!status)
	{
		Trace::out2("Failed to parse glTF\n");
		assert(false);
	}

	return status;
}

bool GLTF::GetGLBRawBuffer(char *&pBuff, unsigned int &BuffSize, const char *const pFileName)
{
	File::Handle fh;
	File::Error err;

	err = File::Open(fh, pFileName, File::Mode::READ);
	assert(err == File::Error::SUCCESS);

	err = File::Seek(fh, File::Position::END, 0);
	assert(err == File::Error::SUCCESS);

	DWORD FileSize(0);
	err = File::Tell(fh, FileSize);
	assert(err == File::Error::SUCCESS);

	// Cast it down to 32-bit size (limit 4GB)
	BuffSize = (unsigned int)FileSize;
	pBuff = new char[BuffSize]();
	assert(pBuff);

	err = File::Seek(fh, File::Position::BEGIN, 0);
	assert(err == File::Error::SUCCESS);

	err = File::Read(fh, pBuff, BuffSize);
	assert(err == File::Error::SUCCESS);

	err = File::Close(fh);
	assert(err == File::Error::SUCCESS);

	assert(pBuff);
	assert(BuffSize > 0);

	return true;
}

bool GLTF::GetGLBHeader(GLB_header &header, const char *const pBuff, unsigned int BuffSize)
{
	GLB_header *pGlbHeader;

	pGlbHeader = (GLB_header *)&pBuff[0];
	assert(pGlbHeader);

	// boundary check
	assert((char *)(pGlbHeader + 1) < (pBuff + BuffSize));

	assert(pGlbHeader->version == 2);
	assert(pGlbHeader->magic == 0x46546C67);

	header = *pGlbHeader;

	return true;
}

bool GLTF::GetRawJSON(char *&pJSON, unsigned int &JsonSize, const char *const pBuff, unsigned int BuffSize)
{
	// BEGINNING...
	GLB_header *pGlbHeader;

	pGlbHeader = (GLB_header *)&pBuff[0];
	assert(pGlbHeader);

	// boundary check
	assert((char *)(pGlbHeader + 1) < (pBuff + BuffSize));

	// Now this next is CHUNK header
	CHUNK_header *pChunkHdr;
	pChunkHdr = (CHUNK_header *)(pGlbHeader + 1);

	assert(pChunkHdr->chunkType == 0x4E4F534A);
	JsonSize = pChunkHdr->chunkLength;
	pJSON = new char[JsonSize + 1]();
	memset(pJSON, 0, JsonSize + 1);
	memcpy(pJSON, (char *)pChunkHdr->chunkData, JsonSize);

	// boundary check - bottom of header
	assert((char *)(pChunkHdr + 1) < (pBuff + BuffSize));

	// boundary check - bottom of data
	assert(((char *)(pChunkHdr + 1) + pChunkHdr->chunkLength) < (pBuff + BuffSize));

	assert(pJSON);
	assert(JsonSize > 0);

	return true;
}

bool GLTF::GetBinaryBuffPtr(char *&pBinaryBuff, unsigned int &BinaryBuffSize, const char *const pBuff, unsigned int BuffSize)
{
	// BEGINNING...
	GLB_header *pGlbHeader;

	pGlbHeader = (GLB_header *)&pBuff[0];
	assert(pGlbHeader);

	// Now this next is CHUNK header - JSON
	CHUNK_header *pChunkHdr;
	pChunkHdr = (CHUNK_header *)(pGlbHeader + 1);

	assert(pChunkHdr);
	assert(pChunkHdr->chunkType == 0x4E4F534A);

	//Trace::out("CHUNK Header:\n");
	//Trace::out("\tType: 0x%08x \n", pChunkHdr->chunkType);
	//Trace::out("\tLength: 0x%x %d\n", pChunkHdr->chunkLength, pChunkHdr->chunkLength);

	// Now this next is CHUNK header - Binary
	pChunkHdr = (CHUNK_header *)((uint32_t)(pChunkHdr + 1) + pChunkHdr->chunkLength);

	assert(pChunkHdr->chunkType == 0x004E4942);

	//Trace::out("CHUNK Header:\n");
	//Trace::out("\tType: 0x%08x \n", pChunkHdr->chunkType);
	//Trace::out("\tLength: 0x%x %d\n", pChunkHdr->chunkLength, pChunkHdr->chunkLength);

	BinaryBuffSize = pChunkHdr->chunkLength;
	pBinaryBuff = (char *)pChunkHdr->chunkData;

	assert(((char *)(pChunkHdr + 1) + BinaryBuffSize) <= (pBuff + BuffSize));

	assert(pBinaryBuff);
	assert(BinaryBuffSize > 0);

	return true;

}

bool GLTF::GetAzulProtoType(const char *&pProtoFileType, textureData &_textData)
{
	bool status = false;
	if(_textData.enabled)
	{
		pProtoFileType = ".t";
		status = true;
	}
	else
	{
		assert(false);
		status = false;
	}

	return status;
}

bool GLTF::GetAzulProtoType(const char *&pProtoFileType, meshData &_meshData)
{
	bool status = false;

	if(_meshData.vbo_vert.enabled)
	{
		pProtoFileType = ".m";
		status = true;
	}
	else
	{
		assert(false);
		status = false;
	}

	return status;
}

bool GLTF::SetVBO(Model &gltfModel, const char *pKey, vboData &vbo, char *pBinaryBuff)
{

	// Get the accessor, buffer view
	vbo.enabled = false;

	assert(pKey);
	auto map = gltfModel.meshes[0].primitives[0].attributes;
	auto it = map.find(pKey);

	if(it != map.end())
	{

		vbo.enabled = true;

		auto index = it->second;

		// Get the accessor, buffer view
		auto accessor = gltfModel.accessors[(size_t)index];
		size_t buffIndex = (size_t)accessor.bufferView;
		auto bufferView = gltfModel.bufferViews[buffIndex];

		vbo.targetType = vboDataConverter::GetTarget(bufferView.target);
		vbo.componentType = vboDataConverter::GetComponent(accessor.componentType);
		vbo.vboType = vboDataConverter::GetType(accessor.type);

		vbo.count = accessor.count;
		vbo.dataSize = bufferView.byteLength;

		// poData
		assert(pBinaryBuff);
		char *pBuffStart(nullptr);

		// Start address
		pBuffStart = pBinaryBuff + bufferView.byteOffset;

		// in case there's data
		delete[] vbo.poData;

		vbo.poData = new unsigned char[vbo.dataSize]();
		assert(vbo.poData);
		memcpy_s(vbo.poData, vbo.dataSize, pBuffStart, vbo.dataSize);
	}

	return vbo.enabled;
}

bool GLTF::SetVBO_index(Model &gltfModel, const char *pKey, vboData &vbo, char *pBinaryBuff)
{
	AZUL_UNUSED_VAR(pKey);

	vbo.enabled = true;

	auto index = gltfModel.meshes[0].primitives[0].indices;
	//assert(index > 0);

	// Get the accessor, buffer view
	auto accessor = gltfModel.accessors[(size_t)index];
	size_t buffIndex = (size_t)accessor.bufferView;
	auto bufferView = gltfModel.bufferViews[buffIndex];
	vbo.targetType = vboDataConverter::GetTarget(bufferView.target);
	vbo.componentType = vboDataConverter::GetComponent(accessor.componentType);
	vbo.vboType = vboDataConverter::GetType(accessor.type);
	vbo.count = accessor.count;
	vbo.dataSize = bufferView.byteLength;
	// poData
	assert(pBinaryBuff);
	char *pBuffStart(nullptr);
	// Start address
	pBuffStart = pBinaryBuff + bufferView.byteOffset;
	// in case there's data
	delete[] vbo.poData;
	if(vbo.componentType == vboData::VBO_COMPONENT::UNSIGNED_SHORT)
	{
		// Convert the unsigned short into unsigned int buffer
		// Engine will now be all unsigned int for index buffer
		unsigned int *pIndexData = new unsigned int[vbo.count]();
		unsigned int *pTmp = pIndexData;
		unsigned short *pShort = (unsigned short *)pBuffStart;
		for(unsigned int i = 0; i < vbo.count; i++)
		{
			// convert it
			*pTmp++ = *pShort++;
		}
		// this is the output buffer
		vbo.poData = (unsigned char *)pIndexData;
		// update the data
		vbo.dataSize = vbo.count * sizeof(unsigned int);
		// update the component
		vbo.componentType = vboData::VBO_COMPONENT::UNSIGNED_INT;
	}
	else if(vbo.componentType == vboData::VBO_COMPONENT::UNSIGNED_INT)
	{
		vbo.poData = new unsigned char[vbo.dataSize]();
		assert(vbo.poData);
		memcpy_s(vbo.poData, vbo.dataSize, pBuffStart, vbo.dataSize);
	}
	else
	{
		assert(false);
	}
	return true;
}


bool GLTF::SetTexture(Model &gltfModel, const char *pKey, textureData &text, char *pBinaryBuff)
{
	AZUL_UNUSED_VAR(gltfModel);
	AZUL_UNUSED_VAR(pKey);
	AZUL_UNUSED_VAR(text);
	AZUL_UNUSED_VAR(pBinaryBuff);

	text.enabled = false;

	auto index = gltfModel.materials[0].pbrMetallicRoughness.baseColorTexture.index;
	if(index >= 0 && index < (int)gltfModel.images.size())
	{

		text.enabled = true;

		if(strcmp(gltfModel.images[index].mimeType.c_str(), "image/png") == 0)
		{
			assert(gltfModel.textures[index].source == TINYGLTF_IMAGE_FORMAT_PNG);
			text.textType = textureData::TEXTURE_TYPE::PNG;
		}
		else
		{
			// Need a way to check this... just a place holder for now
			text.textType = textureData::TEXTURE_TYPE::TGA;
		}

		text.magFilter = textureData::TEXTURE_MAG_FILTER::DEFAULT;
		text.minFilter = textureData::TEXTURE_MIN_FILTER::DEFAULT;
		text.wrapS = textureData::TEXTURE_WRAP::DEFAULT;
		text.wrapT = textureData::TEXTURE_WRAP::DEFAULT;
		text.width = (unsigned int)gltfModel.images[index].width;
		text.height = (unsigned int)gltfModel.images[index].height;
		text.component = (unsigned int)gltfModel.images[index].component;
		text.bits = (unsigned int)gltfModel.images[index].bits;
		text.as_is = gltfModel.images[index].as_is;
		text.pixel_type = textureDataConverter::GetComponent(gltfModel.images[index].pixel_type);

		// pFileName
		unsigned int len = gltfModel.images[index].name.length();
		assert(len < text.FILE_NAME_SIZE);
		memcpy_s(text.pFileName,
				 text.FILE_NAME_SIZE,
				 gltfModel.images[index].name.c_str(),
				 len);



		if(gltfModel.images[index].as_is == false)
		{
			// at this point the data is decompressed into a raw buffer gltfModel
			text.dataSize = gltfModel.images[index].image.size();
			//Trace::out("byteLength: %d \n", text.dataSize);
			// in case there's data
			delete[] text.poData;

			text.poData = new unsigned char[text.dataSize]();
			assert(text.poData);
			auto pStart = &gltfModel.images[index].image[0];
			memcpy_s(text.poData, text.dataSize, pStart, text.dataSize);
		}
		else
		{
			// export the texture file in compressed mode 
			unsigned int buffViewIndex = (unsigned int)gltfModel.images[index].bufferView;
			auto buffView = gltfModel.bufferViews[buffViewIndex];
			text.dataSize = buffView.byteLength;

			char *pBuffStart = pBinaryBuff + buffView.byteOffset;

			//	Trace::out("byteLength: %d \n", text.dataSize);
			//	Trace::out("byteOffset: %d \n", buffView.byteOffset);

				// in case there's data
			delete[] text.poData;

			text.poData = new unsigned char[text.dataSize]();
			assert(text.poData);
			memcpy_s(text.poData, text.dataSize, pBuffStart, text.dataSize);
		}

	}

	return text.enabled;
}

bool GLTF::SetCustomVBO(vboData &vbo,
						void *pData,
						unsigned int sizeInBytes,
						unsigned int count,
						vboData::VBO_COMPONENT componentType,
						vboData::VBO_TYPE type,
						vboData::VBO_TARGET target)
{
	vbo.enabled = true;

	vbo.targetType = target;
	vbo.componentType = componentType;
	vbo.vboType = type;

	vbo.count = count;
	vbo.dataSize = sizeInBytes;

	vbo.poData = new unsigned char[vbo.dataSize]();
	assert(vbo.poData);
	memcpy_s(vbo.poData, vbo.dataSize, pData, vbo.dataSize);

	return true;
}


bool GLTF::SetCustomVBO_index(vboData &vbo,
							  void *pData,
							  unsigned int sizeInBytes,
							  unsigned int count,
							  vboData::VBO_COMPONENT componentType,
							  vboData::VBO_TYPE type,
							  vboData::VBO_TARGET target)
{
	vbo.enabled = true;

	vbo.targetType = target;
	vbo.componentType = componentType;
	vbo.vboType = type;

	vbo.count = count * 3;
	vbo.dataSize = sizeInBytes;

	vbo.poData = new unsigned char[vbo.dataSize]();
	assert(vbo.poData);
	memcpy_s(vbo.poData, vbo.dataSize, pData, vbo.dataSize);

	return true;
}


bool GLTF::SetVBO_BONE_index(Model &gltfModel,
							 vboData &vbo,
							 char *pBuffStart,
							 unsigned int byteLength,
							 unsigned int count)
{
	// Get the accessor, buffer view
	vbo.enabled = true;

	auto index = gltfModel.meshes[0].primitives[0].indices;
	assert(index > 0);

	auto accessor = gltfModel.accessors[(size_t)index];
	size_t buffIndex = (size_t)accessor.bufferView;
	auto bufferView = gltfModel.bufferViews[buffIndex];

	vbo.targetType = vboDataConverter::GetTarget(bufferView.target);

	// it was converted to unsigned int earlier...
	assert(vbo.componentType == vboData::VBO_COMPONENT::UNSIGNED_INT);
	vbo.componentType = vboData::VBO_COMPONENT::UNSIGNED_INT;

	vbo.vboType = vboDataConverter::GetType(accessor.type);

	vbo.count = count;
	vbo.dataSize = byteLength;

	assert(pBuffStart);

	// in case there's data
	delete[] vbo.poData;

	if(vbo.componentType == vboData::VBO_COMPONENT::UNSIGNED_SHORT)
	{
		// Convert the unsigned short into unsigned int buffer
		// Engine will now be all unsigned int for index buffer
		unsigned int *pIndexData = new unsigned int[vbo.count]();
		unsigned int *pTmp = pIndexData;
		unsigned short *pShort = (unsigned short *)pBuffStart;

		for(unsigned int i = 0; i < vbo.count; i++)
		{
			// convert it
			*pTmp++ = *pShort++;
		}

		// this is the output buffer
		vbo.poData = (unsigned char *)pIndexData;
		// update the data
		vbo.dataSize = vbo.count * sizeof(unsigned int);
		// update the component
		vbo.componentType = vboData::VBO_COMPONENT::UNSIGNED_INT;
	}
	else if(vbo.componentType == vboData::VBO_COMPONENT::UNSIGNED_INT)
	{
		vbo.poData = new unsigned char[vbo.dataSize]();
		assert(vbo.poData);
		memcpy_s(vbo.poData, vbo.dataSize, pBuffStart, vbo.dataSize);
	}
	else
	{
		assert(false);
	}


	return true;
}

bool GLTF::SetVBO_BONE(Model &gltfModel,
					   const char *pKey,
					   vboData &vbo,
					   char *pBuffStart,
					   unsigned int byteLength,
					   unsigned int count)
{
	// Get the accessor, buffer view
	vbo.enabled = false;

	assert(pKey);
	auto map = gltfModel.meshes[0].primitives[0].attributes;
	auto it = map.find(pKey);

	if(it != map.end())
	{
		// Get the accessor, buffer view
		vbo.enabled = true;

		auto index = it->second;

		auto accessor = gltfModel.accessors[(size_t)index];
		size_t buffIndex = (size_t)accessor.bufferView;
		auto bufferView = gltfModel.bufferViews[buffIndex];

		vbo.targetType = vboDataConverter::GetTarget(bufferView.target);
		vbo.componentType = vboDataConverter::GetComponent(accessor.componentType);
		vbo.vboType = vboDataConverter::GetType(accessor.type);

		vbo.count = count;
		vbo.dataSize = byteLength;

		assert(pBuffStart);

		// in case there's data
		delete[] vbo.poData;

		vbo.poData = new unsigned char[vbo.dataSize]();
		assert(vbo.poData);
		memcpy_s(vbo.poData, vbo.dataSize, pBuffStart, vbo.dataSize);

	}

	return vbo.enabled;
}


// --- End of File ---
