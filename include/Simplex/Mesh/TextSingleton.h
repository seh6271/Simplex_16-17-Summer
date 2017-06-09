/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/10
----------------------------------------------*/
#ifndef __TEXTSINGLETON_H_
#define __TEXTSINGLETON_H_

#include "Simplex\System\SimplexSystem.h"
#include "Simplex\System\ShaderManager.h"
#include "Simplex\Materials\MaterialManager.h"

namespace Simplex
{

	//System Class
	class SimplexDLL TextSingleton
	{
	protected:
		bool m_bBinded = false; //Binded flag

		uint m_uMaterialIndex = 0; //Material index of this mesh
		uint m_uVertexCount = 0; //Number of vertices in this Mesh

		GLuint m_vao = 0;	//OpenGL Vertex Array Object
		GLuint m_VBO = 0;	//OpenGL Buffer (Will hold the vertex buffer pointer)
		GLuint m_nShader = 0;	//Index of the shader

		ShaderManager* m_pShaderMngr = nullptr;	//Shader Manager
		MaterialManager* m_pMatMngr = nullptr;		//Material Manager
		
		std::vector<vector3> m_lVertex; //List of vertices

		std::vector<vector3> m_lVertexPos;	//List of Vertices
		std::vector<vector3> m_lVertexCol;	//List of Colors
		std::vector<vector3> m_lVertexUV;	//List of UVS

		vector3 m_v3Head = ZERO_V3;

		static TextSingleton* m_pInstance; // Singleton pointer
		SystemSingleton* m_pSystem = nullptr;

		String m_sText = "";
		String m_sTextPrev = "";
		String m_sFont;
		std::vector<vector3> m_lColor;
		std::vector<vector3> m_lColorPrev;

	public:
		/* Gets/Constructs the singleton pointer */
		/*
		USAGE:
		ARGUMENTS:
		OUTPUT:
		*/
		static TextSingleton* GetInstance();
		/* Destroys the singleton */
		/*
		USAGE:
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		static void ReleaseInstance(void);
		
		/* Compiles the Mesh for OpenGL 3.X use*/
		/*
		USAGE:
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void CompileOpenGL3X(void);
		
		/*
		USAGE:
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void Render(void);

		/*
		USAGE:
		ARGUMENTS:
		OUTPUT: ---
		*/
		void AddString(String a_sString, vector3 a_v3Color = C_WHITE);

		/*
		USAGE:
		ARGUMENTS:
		OUTPUT: ---
		*/
		void SetFont(String a_sTextureName);

	protected:
		/* Constructor */
		/*
		USAGE:
		ARGUMENTS: ---
		OUTPUT:
		*/
		TextSingleton(void);
		/* Copy Constructor */
		/*
		USAGE:
		ARGUMENTS:
		OUTPUT:
		*/
		TextSingleton(TextSingleton const& other);
		/* Copy Assignment Operator*/
		/*
		USAGE:
		ARGUMENTS:
		OUTPUT:
		*/
		TextSingleton& operator=(TextSingleton const& other);
		/* Destructor */
		/*
		USAGE:
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		~TextSingleton(void);

		/* Initialize the object's fields */
		/*
		USAGE:
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void Init(void);
		/* Releases the object from memory */
		/*
		USAGE:
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void Release(void);

		/*
		USAGE:
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void Reset(void);

		/*
		USAGE:
		ARGUMENTS:
		OUTPUT: ---
		*/
		void AddCharacter(char a_cInput, vector3 a_v3Color = C_WHITE);
	};
}

#endif //__TEXTSINGLETON_H_