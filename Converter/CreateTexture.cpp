//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "CreateTexture.h"
#include "textureData.h"
#include "GLTF.h"
#include "File.h"
#include "stb_image.h"

using namespace Azul;
using namespace tinygltf;

void gltReadTGABits(const char *pFileName, textureData &textData);
void gltReadPNGBits(const char *pFileName, textureData &textData);

// Define targa header. This is only used locally.
#pragma pack(1)
typedef struct
{
	char	identsize;               // Size of ID field that follows header (0)
	char	colorMapType;            // 0 = None, 1 = paletted
	char	imageType;               // 0 = none, 1 = indexed, 2 = rgb, 3 = grey, +8=rle
	unsigned short	colorMapStart;   // First colour map entry
	unsigned short	colorMapLength;  // Number of colors
	unsigned char 	colorMapBits;    // bits per palette entry
	unsigned short	xstart;          // image x origin
	unsigned short	ystart;          // image y origin
	unsigned short	width;           // width in pixels
	unsigned short	height;          // height in pixels
	char	bits;                    // bits per pixel (8 16, 24, 32)
	char	descriptor;              // image descriptor
} TGAHEADER;
#pragma pack(8)


void CreateTexturePNG(const char *const pFileName, const char *const pTargetName)
{
	assert(pFileName);

	Trace::out("%-25s", pFileName);

	// Strip the extension .tga off the name
	unsigned int len = strlen(pFileName);
	char *pTmp = new char[len + 1]();
	memset(pTmp, 0, len);
	memcpy(pTmp, pFileName, len - strlen(".png"));

	// base name
	std::string BaseName = pTargetName;
	delete[] pTmp;

	// runtime model
	textureData  runModel;

	//---------------------------------
	// Model Name
	//---------------------------------
	runModel.enabled = true;
	runModel.textType = textureData::TEXTURE_TYPE::PNG;
	runModel.magFilter = textureData::TEXTURE_MAG_FILTER::MAG_LINEAR;
	runModel.minFilter = textureData::TEXTURE_MIN_FILTER::MIN_LINEAR;
	runModel.wrapS = textureData::TEXTURE_WRAP::WRAP_CLAMP_TO_EDGE;
	runModel.wrapT = textureData::TEXTURE_WRAP::WRAP_CLAMP_TO_EDGE;
	runModel.pixel_type = textureData::TEXTURE_COMPONENT::UNSIGNED_BYTE;
	runModel.as_is = false;

	memcpy_s(runModel.pFileName, textureData::FILE_NAME_SIZE, pFileName, strlen(pFileName));

	gltReadPNGBits(pFileName, runModel);

	textureData_proto mA_proto;
	runModel.Serialize(mA_proto);

	// -------------------------------
	//  Write to file
	//--------------------------------

	File::Handle fh;
	File::Error err;
	bool status;

	// Create output name
	const char *pProtoFileType = nullptr;
	status = GLTF::GetAzulProtoType(pProtoFileType, runModel);
	assert(status);

	std::string OutputFileName = BaseName + pProtoFileType + ".proto.azul";

	Trace::out(" --> %s\n", OutputFileName.c_str());

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

	delete[] poNewBuff;

}

void CreateTextureTGA(const char *const pFileName, const char *const pTargetName)
{
	assert(pFileName);

	Trace::out("%-25s", pFileName);

	// Strip the extension .tga off the name
	unsigned int len = strlen(pFileName);
	char *pTmp = new char[len + 1]();
	memset(pTmp, 0, len);
	memcpy(pTmp, pFileName, len - strlen(".tga"));

	// base name
	std::string BaseName = pTargetName;
	delete[] pTmp;

	// runtime model
	textureData  runModel;

	//---------------------------------
	// Model Name
	//---------------------------------

	runModel.enabled = true;
	runModel.textType = textureData::TEXTURE_TYPE::TGA;
	runModel.magFilter = textureData::TEXTURE_MAG_FILTER::MAG_LINEAR;
	runModel.minFilter = textureData::TEXTURE_MIN_FILTER::MIN_LINEAR;
	runModel.wrapS = textureData::TEXTURE_WRAP::WRAP_CLAMP_TO_EDGE;
	runModel.wrapT = textureData::TEXTURE_WRAP::WRAP_CLAMP_TO_EDGE;
	runModel.pixel_type = textureData::TEXTURE_COMPONENT::UNSIGNED_BYTE;
	runModel.as_is = false;

	memcpy_s(runModel.pFileName, textureData::FILE_NAME_SIZE, pFileName, strlen(pFileName));


	gltReadTGABits(pFileName, runModel);

	textureData_proto mA_proto;
	runModel.Serialize(mA_proto);

	// -------------------------------
	//  Write to file
	//--------------------------------

	File::Handle fh;
	File::Error err;
	bool status;

	// Create output name
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

	delete[] poNewBuff;

}

//-----------------------------------------------------------------------------
// Allocate memory and load targa bits. Returns pointer to new buffer,
// height, and width of texture, and the OpenGL format of data.
// Call free() on buffer when finished!
// This only works on pretty vanilla targas... 8, 24, or 32 bit color
// only, no palettes, no RLE encoding.
//-----------------------------------------------------------------------------
void gltReadTGABits(const char *pFileName, textureData &textData)
{
	TGAHEADER tgaHeader;        // TGA file header
	unsigned long lImageSize;   // Size in bytes of image
	short sDepth;               // Pixel depth;
	char *pBits = nullptr;      // Pointer to bits

	// Default/Failed values
	unsigned int Width = 0;
	unsigned int Height = 0;
	textureData::TEXTURE_EFORMAT eFormat = textureData::TEXTURE_EFORMAT::EFORMAT_RGB;
	textureData::TEXTURE_NCOMPONENT nComponents = textureData::TEXTURE_NCOMPONENT::NCOMPONENT_RGB;

	// Attempt to open the file
	File::Handle fh;
	File::Error err;

	err = File::Open(fh, pFileName, File::Mode::READ);
	assert(err == File::Error::SUCCESS);

	err = File::Read(fh, &tgaHeader, sizeof(TGAHEADER));
	assert(err == File::Error::SUCCESS);

	Width = tgaHeader.width;
	Height = tgaHeader.height;
	sDepth = tgaHeader.bits / 8;

	if(sDepth == 3)
	{
		// Crap... DirectX loading issue... promote 3 bytes to 4 bytes
		unsigned int numTexels = (unsigned int)tgaHeader.width * (unsigned int)tgaHeader.height;
		unsigned int oldSize = numTexels * (unsigned int)sDepth;

		unsigned char *pBuff = new unsigned char[oldSize]();
		assert(pBuff);

		err = File::Read(fh, pBuff, oldSize);
		assert(err == File::Error::SUCCESS);

		err = File::Close(fh);
		assert(err == File::Error::SUCCESS);

		lImageSize = numTexels * 4;
		unsigned char *pNewBuff = new unsigned char[ lImageSize]();;
	
		unsigned int j(0);
		unsigned int i(0);
		for(unsigned int k = 0; k < numTexels; k++)
		{		

			// w1(4)
			pNewBuff[j] = pBuff[i];
			pNewBuff[j+1] = pBuff[i + 1];
			pNewBuff[j + 2] = pBuff[i + 2];
			pNewBuff[j + 3] = 0xFF;

			j = j + 4;
			i = i + 3;
		}

		delete[] pBuff;

		sDepth = 4;
		tgaHeader.bits = 32;
		pBits = (char *)pNewBuff;

		// w1(4)
		eFormat = textureData::TEXTURE_EFORMAT::EFORMAT_BGR;
		nComponents = textureData::TEXTURE_NCOMPONENT::NCOMPONENT_BGR;
	}
	else
	{
		// Put some validity checks here. Very simply, I only understand
		// or care about 8, 24, or 32 bit targa's.
		if(tgaHeader.bits != 8 && tgaHeader.bits != 24 && tgaHeader.bits != 32)
		{
			assert(false);
		}

		// Calculate size of image buffer
		lImageSize = (unsigned int)tgaHeader.width * (unsigned int)tgaHeader.height * (unsigned int)sDepth;

		pBits = new char[lImageSize * sizeof(char)]();
		assert(pBits);

		err = File::Read(fh, pBits, lImageSize);
		assert(err == File::Error::SUCCESS);

		err = File::Close(fh);
		assert(err == File::Error::SUCCESS);

		// w1(4)
		eFormat = textureData::TEXTURE_EFORMAT::EFORMAT_BGRA;
		nComponents = textureData::TEXTURE_NCOMPONENT::NCOMPONENT_BGRA;
	}

	textData.eFormat = eFormat;
	textData.nComponent = nComponents;
	textData.width = Width;
	textData.height = Height;
	textData.component = (unsigned int)sDepth;
	textData.bits = (unsigned int)tgaHeader.bits;
	textData.dataSize = lImageSize;
	textData.poData = (unsigned char *)pBits;

}

void gltReadPNGBits(const char *pFileName, textureData &textData)
{

	unsigned long ImageSize;   // Size in bytes of image
	unsigned char *pBits = nullptr;      // Pointer to bits

	// Default/Failed values
	int Width = 0;
	int Height = 0;
	int comp;
	int req_comp = 4;

	// some default value
	textureData::TEXTURE_EFORMAT eFormat = textureData::TEXTURE_EFORMAT::EFORMAT_RGB;
	textureData::TEXTURE_NCOMPONENT nComponents = textureData::TEXTURE_NCOMPONENT::NCOMPONENT_RGB;

	pBits = stbi_load(pFileName, &Width, &Height, &comp, req_comp);

	ImageSize = (unsigned int)(Width * Height * req_comp);

	if(comp == 3)
	{
		// w1(4)
		eFormat = textureData::TEXTURE_EFORMAT::EFORMAT_RGB;
		nComponents = textureData::TEXTURE_NCOMPONENT::NCOMPONENT_RGB;
	}
	else if(comp == 4)
	{
		// w1(4)
		eFormat = textureData::TEXTURE_EFORMAT::EFORMAT_RGBA;
		nComponents = textureData::TEXTURE_NCOMPONENT::NCOMPONENT_RGBA;
	}
	else
	{
		assert(false);
	}

	textData.eFormat = eFormat;
	textData.nComponent = nComponents;
	textData.width = (unsigned int)Width;
	textData.height = (unsigned int)Height;
	textData.component = (unsigned int)req_comp;
	textData.bits = (unsigned int)comp;
	textData.dataSize = ImageSize;
	textData.poData = (unsigned char *)pBits;

}

// --- End of File ---
