//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#include "FrameBucketEntry.h"

namespace Azul
{
	FrameBucketEntry::~FrameBucketEntry()
	{
		delete[] this->poBoneEntry;
		this->poBoneEntry = nullptr;
	}

	FrameBucketEntry::FrameBucketEntry()
	{
		this->keyFrame = 0;
		this->numBones = 0;
		this->keyTime = 0;
		this->keyTimeIndex = 0;

		this->poBoneEntry = nullptr;
	}
	
	FrameBucketEntry::FrameBucketEntry(unsigned int _numBones)
	{
		this->keyFrame = 0;
		this->numBones = _numBones;
		this->keyTime = 0.0f;
		this->keyTimeIndex = 0;

		this->poBoneEntry = new BoneEntry[_numBones]();
		assert(this->poBoneEntry);
	}

	FrameBucketEntry & FrameBucketEntry::operator = (const FrameBucketEntry &r)
	{
		if( this != &r)
		{
			// Nuke orginal
			this->keyFrame = 0;
			this->numBones = 0;
			this->keyTime = 0.0f;
			this->keyTimeIndex = 0;
			delete[] this->poBoneEntry;

			// copy the new
			this->keyFrame = r.keyFrame;
			this->numBones = r.numBones;
			this->keyTime = r.keyTime;
			this->keyTimeIndex = r.keyTimeIndex;
			this->poBoneEntry = new BoneEntry[r.numBones]();

			for(size_t i = 0; i < r.numBones; i++)
			{
				this->poBoneEntry[i] = r.poBoneEntry[i];
			}
		}

		return *this;
	}

	void FrameBucketEntry::Serialize(FrameBucketEntry_proto &out) const
	{
		AZUL_UNUSED_VAR(out);

		// Add the number of bones
		out.set_numbones(this->numBones);
		out.set_keyframe(this->keyFrame);
		out.set_keytime(this->keyTime);
		out.set_keytimeindex(this->keyTimeIndex);

		// Add the SkelEntry
		BoneEntry_proto tmpBoneEntry_proto;

		for(unsigned int i = 0; i < this->numBones; i++)
		{
			// create one proto
			this->poBoneEntry[i].Serialize(tmpBoneEntry_proto);

			// add it to the message(package)
			*out.add_poboneentry() = tmpBoneEntry_proto;
		}

		assert(out.numbones() == this->numBones);
	}

	void FrameBucketEntry::Deserialize(const FrameBucketEntry_proto &in)
	{
		AZUL_UNUSED_VAR(in);
		// Safety
		delete[] this->poBoneEntry;
		this->poBoneEntry = nullptr;

		this->keyFrame = in.keyframe();
		this->numBones = in.numbones();
		this->keyTime = in.keytime();
		this->keyTimeIndex = in.keytimeindex();

		this->poBoneEntry = new BoneEntry[this->numBones]();
		assert(this->poBoneEntry);

		for(unsigned int i = 0; i < this->numBones; i++)
		{
			poBoneEntry[i].Deserialize(in.poboneentry((int)i));
		}
	}

	void FrameBucketEntry::Print(const char *const pName) const
	{
		AZUL_UNUSED_VAR(pName);
		Trace::out("%s: \n", pName);

		Trace::out("     keyFrame: %d\n", this->keyFrame);
		Trace::out("     numBones: %d\n", this->numBones);
		Trace::out("      keyTime: %f\n", this->keyTime);
		Trace::out(" keyTimeIndex: %d\n", this->keyTimeIndex);

		for(size_t i = 0; i < this->numBones; i++)
		{
			this->poBoneEntry[i].Print(pName);
		}

		Trace::out("\n");
	}
}

// --- End of File ---


