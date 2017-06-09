/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2017/05
----------------------------------------------*/
#ifndef __APPLICATION_H_
#define __APPLICATION_H_

#include "Simplex\SimplexApplication.h"
#include <SFML\Graphics.hpp>
#include <vld.h>
#include "imgui\imgui.h"

using namespace Simplex; //Using ReEng namespace to use all the classes in the dll

struct ImGuiObject
{
	ImGuiIO& io = ImGui::GetIO(); //IO from ImGui

	int m_nShader = 0; //Shader handler
	int m_nTex = 0; //Text
	int m_nProjMtx = 0; //Projection Matrix
	uint m_uVBO = 0; //Vertex Buffered Object
	uint m_uVAO = 0; //Vertex Array Object
	uint m_uElements = 0; //elements handle

	int m_nVertHandle = 0; //Vertex Shader
	int m_nFragHandle = 0; //Fragment Shader

	int m_nPosition = 0; //Attribute location for position
	int m_nUV = 0; //Attribute location for UV
	int m_nColor = 0; //Attribute location for color

	uint m_nClock; //Clock to use for the gui
	double m_dTimeTotal = 0.0f; //Time
	bool m_bMousePressed[3] = { false, false, false }; //flags for mouse
	GLuint m_uFontTexture = 0; //Font texture
};

class AppClass : public SimplexApplication
{
	typedef SimplexApplication super;
	static ImGuiObject gui;

	bool m_bGUI_Window_Main = true;
	bool m_bGUI_Window_Secondary = false;
	bool m_bGUI_Window_Test = false;

	String m_sName;
	
	Group* m_pGroup = nullptr;
	Model* m_pModel1 = nullptr;
	Model* m_pModel2 = nullptr;
	Model* m_pModel3 = nullptr;
	Model* m_pModelList = nullptr;

	vector3 m_v3Mouse = vector3();
	
public:
	bool CreateFontsTexture();
	bool CreateDeviceObjects();
	void NewFrame();

	/*
	USAGE: Constructor
	ARGUMENTS: 
	- HINSTANCE hInstance -> Instance of the window
	- LPWSTR lpCmdLine -> Command line
	- int nCmdShow -> Number or arguments
	- bool a_bConsole = false -> create command window flag
	OUTPUT: ---
	*/
	AppClass(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow, bool a_bUsingConsole = false) : super(hInstance, lpCmdLine, nCmdShow, a_bUsingConsole) {}
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~AppClass(void) { Release(); }
	/*
	USAGE: Reads the configuration of the application to a file
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void ReadConfig(void) final {}
	/*
	USAGE: Writes the configuration of the application to a file
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void WriteConfig(void) final {}
	/*
	USAGE: Initialize ReEng variables necessary to create the window
	ARGUMENTS: String a_sWindowName -> Name of the window
	OUTPUT: ---
	*/
	virtual void InitWindow(String a_sWindowName) final;
	/*
	USAGE: Initializes user specific variables, this is executed right after InitApplicationVariables,
	the purpose of this member function is to initialize member variables specific for this lesson
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void InitVariables(void) final;
	/*
	USAGE: Updates the scene
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void Update(void) final;
	/*
	USAGE: Displays the scene
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void Display(void) final;
	/*
	USAGE: Manage the response of key presses
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void ProcessKeyboard(void) final;
	/*
	USAGE: Manage the response of key presses and mouse position
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void ProcessMouse(void) final;
	/*
	USAGE: Releases the application
	IF INHERITED AND OVERRIDEN MAKE SURE TO RELEASE BASE POINTERS (OR CALL BASED CLASS RELEASE)
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void Release(void) final;

	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void InitIMGUI(void) final;
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void DrawGUI(void) final;
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void ShutdownGUI(void) final;
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	static void RenderDrawLists(ImDrawData* draw_data);
};
/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/
#endif //__APPLICATION_H_
