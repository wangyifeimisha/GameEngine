//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "StringThis.h"

namespace Azul
{
	StringThis::StringThis(InvBind::Name status)
	{
		switch(status)
		{
		case InvBind::Name::ChickenBot:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(InvBind::ChickenBot));
			break;

		case InvBind::Name::Not_Initialized:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(InvBind::Not_Initialized));
			break;

		default:
			assert(false);
		}
	}
	StringThis::StringThis(Hierarchy::Name status)
	{
		switch(status)
		{
		case Hierarchy::Name::ChickenBot:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Hierarchy::ChickenBot));
			break;

		case Hierarchy::Name::Not_Initialized:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Hierarchy::Not_Initialized));
			break;

		default:
			assert(false);
		}
	}

	StringThis::StringThis(Clip::Name status)
	{
		switch(status)
		{
		case Clip::Name::Walk_ChickenBot:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Clip::Walk_ChickenBot));
			break;

		case Clip::Name::Not_Initialized:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Clip::Not_Initialized));
			break;

		default:
			assert(false);
		}
	}

	StringThis::StringThis(Skel::Name status)
	{
		switch(status)
		{
		case Skel::Name::ChickenBot:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Skel::ChickenBot));
			break;

		case Skel::Name::Not_Initialized:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Skel::Not_Initialized));
			break;

		default:
			assert(false);
		}
	}

	StringThis::StringThis(Mesh::Name status)
	{
		switch(status)
		{
		case Mesh::Name::CUBE:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::CUBE));
			break;

		case Mesh::Name::PYRAMID:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::PYRAMID));
			break;

		case Mesh::Name::CRATE:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::CRATE));
			break;

		case Mesh::Name::SPHERE:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::SPHERE));
			break;

		case Mesh::Name::NOT_INITIALIZED:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::NOT_INITIALIZED));
			break;

		case Mesh::Name::NULL_MESH:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::NULL_MESH));
			break;

		default:
			assert(false);
		}
	}

	//StringThis::StringThis(Glyph::Name status)
	//{
	//	switch(status)
	//	{
	//	case Glyph::Name::Arial36pt:
	//		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Glyph::Arial36pt));
	//		break;

	//	case Glyph::Name::NullObject:
	//		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Glyph::NullObject));
	//		break;

	//	case Glyph::Name::Uninitialized:
	//		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Glyph::Uninitialized));
	//		break;

	//	default:
	//		assert(false);
	//	}
	//}

	StringThis::StringThis(Image::Name status)
	{
		switch(status)
		{
		case Image::Name::WhiteBird:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Image::WhiteBird));
			break;

		case Image::Name::YellowBird:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Image::YellowBird));
			break;

		case Image::Name::GreenBird:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Image::GreenBird));
			break;

		case Image::Name::ALLBirds:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Image::ALLBirds));
			break;

		case Image::Name::Not_Initialized:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Image::Not_Initialized));
			break;

		default:
			assert(false);
		}
	}

	StringThis::StringThis(Camera::Name status)
	{
		switch(status)
		{
		case Camera::Name::CAMERA_0:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Camera::CAMERA_0));
			break;

		case Camera::Name::CAMERA_1:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Camera::CAMERA_1));
			break;

		case Camera::Name::NOT_INITIALIZED:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Camera::NOT_INITIALIZED));
			break;

		case Camera::Name::NullCamera:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Camera::NullCamera));
			break;

		default:
			assert(false);
		}
	}

	StringThis::StringThis(ShaderObject::Name status)
	{
		switch(status)
		{
		case ShaderObject::Name::NullShader:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(ShaderObject::NullShader));
			break;

		case ShaderObject::Name::ColorByVertex:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(ShaderObject::ColorByVertex));
			break;

		case ShaderObject::Name::FlatTexture:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(ShaderObject::FlatTexture));
			break;

		case ShaderObject::Name::Sprite:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(ShaderObject::Sprite));
			break;

		case ShaderObject::Name::LightTexture:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(ShaderObject::LightTexture));
			break;

		case ShaderObject::Name::Uninitialized:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(ShaderObject::Uninitialized));
			break;

		default:
			assert(false);
		}
	}



	StringThis::StringThis(TextureObject::Name status)
	{
		switch(status)
		{
		case TextureObject::Name::NullTexture:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(TextureObject::NullTexture));
			break;

		case TextureObject::Name::Duckweed:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(TextureObject::Duckweed));
			break;

		case TextureObject::Name::Brick:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(TextureObject::Brick));
			break;

		case TextureObject::Name::Stone:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(TextureObject::Stone));
			break;

		case TextureObject::Name::Rocks:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(TextureObject::Rocks));
			break;

		case TextureObject::Name::Crate:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(TextureObject::Crate));
			break;

		case TextureObject::Name::ChickenBot:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(TextureObject::ChickenBot));
			break;

		case TextureObject::Name::Test0:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(TextureObject::Test0));
			break;

		case TextureObject::Name::Test1:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(TextureObject::Test1));
			break;

		case TextureObject::Name::Test2:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(TextureObject::Test2));
			break;

		case TextureObject::Name::Test3:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(TextureObject::Test3));
			break;


		case TextureObject::Name::Uninitialized:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(TextureObject::Uninitialized));
			break;

		default:
			assert(false);
		}
	}


	StringThis::operator char *()
	{
		return this->buffer;
	}
}

// --- End of File ---
