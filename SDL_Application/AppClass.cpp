#include "AppClass.h"
void SDLApp::InitVariables(void)
{
	//setup camera position
	m_pCameraMngr->SetPositionTargetAndView(
		vector3(0.0f, 2.5f, 15.0f),//Camera position
		vector3(0.0f, 2.5f, 0.0f),//What Im looking at
		AXIS_Y);//What is up
	//init variables
	m_pModel = new Model();
	//load model
	m_pModel->Load("Lego\\Unikitty.BTO");
}
void SDLApp::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), C_YELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), C_RED);
}
void SDLApp::Display(void)
{
	// Clear the screen
	ClearScreen();
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window
	m_pMeshMngr->AddSkyboxToRenderList();
	//set the model matrix of the model
	m_pModel->SetModelMatrix(ToMatrix4(m_qArcBall));
	//play the default sequence of the model
	m_pModel->PlaySequence();
	//render list call
	m_pMeshMngr->Render();
	//clear the render list
	m_pMeshMngr->ClearRenderList();
	// end the current frame (internally swaps the front and back buffers)
	SDL_GL_SwapWindow(window);
}

void SDLApp::Release(void)
{
	//release variables
	SafeDelete(m_pModel);

	SDL_GL_DeleteContext(context);
	SDL_Quit();
}