//--------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#ifndef SHADER_OBJECT_H
#define SHADER_OBJECT_H

#include <d3d11.h>

namespace Azul
{
	class ShaderObject
	{
	public:
		enum class Name
		{
			NullShader,
			ColorByVertex,
			FlatTexture,
			LightTexture,
			ConstColor,

			MixerCompute,
			WorldCompute,

			SkinFlatTexture,

			Sprite,
			Uninitialized
		};


	public:
		ShaderObject() = delete;
		ShaderObject(const ShaderObject &) = delete;
		ShaderObject &operator = (const ShaderObject &) = delete;
		virtual ~ShaderObject();

		ShaderObject(ShaderObject::Name _name);

		void CreateComputeShader(const unsigned char *pCompiledVertexShaderObject,
								size_t codeSize);
		void CreateVertexShader(const unsigned char *pCompiledVertexShaderObject,
								size_t codeSize);
		void CreatePixelShader(const unsigned char *pCompiledPixelShaderObject,
							   size_t codeSize);
		void CreateInputLayout(const unsigned char *compiledVertexShaderObject,
							   size_t codeSize,
							   D3D11_INPUT_ELEMENT_DESC *pDesc,
							   unsigned int SizeInBytes);

		void ActivateShader();
		void ActivateCSShader();

		const char *GetLatestProfile_PixelShader() const;
		const char *GetLatestProfile_VertexShader() const;
		const char *GetLatestProfile_ComputeShader() const;

		char *GetName();
		void SetName(ShaderObject::Name _name);

		// ---------------------------------------------
		// 	   Data:
		// ---------------------------------------------
		ShaderObject::Name name;

		// Shaders
		ID3D11InputLayout *poInputLayout;
		ID3D11ComputeShader *poComputeShader;
		ID3D11VertexShader *poVertexShader;
		ID3D11PixelShader *poPixelShader;

	};
}

#endif

// --- End of File ---
