//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "json.hpp"
#include "File.h"

#include "pugixml.hpp"
#include "FontData.h"
#include "FontEntry.h"
#include "ConvertXML.h"

using namespace Azul;

namespace Azul
{
	void ConvertXML(const char *const pName, const char *const pTargetName)
	{
		assert(pName);

		char sBuff[40];
		sprintf_s(sBuff, 40, "XML(%s)", pName);
		Trace::out("%-25s", sBuff);
		char pFileName[128];
		sprintf_s(pFileName, 128, "%s.xml", pName);

		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file(pFileName);
		assert(result);

		unsigned int count = 0;
		for(pugi::xml_node node = doc.child("fontMetrics").child("character"); node; node = node.next_sibling("character"))
		{
			count++;
		}

		FontData FontDataA(count);

		int i = -1;
		for(pugi::xml_node node = doc.child("fontMetrics").child("character"); node; node = node.next_sibling("character"))
		{
			unsigned int key = node.attribute("key").as_uint();
			assert(key > 31);
			assert(key < 128);

			float x = node.child("x").text().as_float();
			assert(x > -1);

			float y = node.child("y").text().as_float();
			assert(y > -1);

			float width = node.child("width").text().as_float();
			assert(width > -1);

			float height = node.child("height").text().as_float();
			assert(height > -1);

			i++;
			FontDataA.poFontEntry[i].set(key, x, y, width, height);
		}

		assert((unsigned int)(i + 1) == count);

		FontData_proto fontDataA_proto;
		FontDataA.Serialize(fontDataA_proto);

		// -------------------------------
		//  Write to file
		//--------------------------------

		File::Handle fh;
		File::Error err;

		const char *pProtoFileType = ".xml";

		// Create output name
		std::string BaseName(pTargetName);
		std::string OutputFileName = BaseName + pProtoFileType + ".proto.azul";

		Trace::out(" --> %s\n", OutputFileName.c_str());
		err = File::Open(fh, OutputFileName.c_str(), File::Mode::WRITE);
		assert(err == File::Error::SUCCESS);

		std::string strOut;
		fontDataA_proto.SerializeToString(&strOut);

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
}

// --- End of File ---
