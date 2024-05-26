//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "InvBindProto.h"
#include "File.h"
#include "InvBindMan.h"
#include "InvBindData.h"

namespace Azul
{
	InvBindProto::~InvBindProto()
	{
	}

	InvBindProto::InvBindProto(const char *const pFileName, InvBind::Name InvBindName)
	{
		assert(pFileName);
		AZUL_UNUSED_VAR(pFileName);

		// ----------------------------------------------
		// READ the data from the file ONLY
		// ----------------------------------------------

		// File stuff
		File::Handle fh;
		File::Error  ferror;

		ferror = File::Open(fh, pFileName, File::Mode::READ);
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
		InvBindData_proto mB_proto;

		mB_proto.ParseFromString(strIn);

		InvBindData mB;
		mB.Deserialize(mB_proto);
		delete[] poBuff;

		// Do I know this format?
		assert(strcmp(mB.pVersion, "1.0.5") == 0);

		InvBindMan::Add(InvBindName, mB.numMat, (Mat4 *)mB.poData);
                        
	}
}

//--- End of File ---
