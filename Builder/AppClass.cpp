#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Builder"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (DEFAULT_V3NEG in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
	//m_pSystem->SetWindowResolution(BTO_RESOLUTIONS::RES_M_1600x900_16x9_WXGA);
	m_pSystem->SetWindowResolution(BTO_RESOLUTIONS::RES_C_1280x720_16x9_HD);
	//m_pSystem->SetWindowFullscreen(); //Sets the window to be fullscreen
	//m_pSystem->SetWindowBorderless(true); //Sets the window to not have borders
}
void AppClass::InitVariables(void)
{
	//Set the camera position
	m_pCameraMngr->SetPositionTargetAndView(
		vector3(0.0f, 2.5f, 15.0f),//Camera position
		vector3(0.0f, 2.5f, 0.0f),//What Im looking at
		AXIS_Y);//What is up
	m_pMeshMngr = MeshManager::GetInstance();
	m_bGUI_Window_Main = true;
	m_bGUI_Window_Secondary = false;
	m_bGUI_Window_Test = false;
	InitIMGUI();
#pragma region Make some meshes, add them to a group and add the group to a model
	/*
	Mesh* pMesh1 = new Mesh();
	Mesh* pMesh2 = new Mesh();
	Mesh* pMesh3 = new Mesh();
	pMesh1->GenerateCone(1.0f, 1.0f, 10, C_RED);
	pMesh2->GenerateTorus(1.0f, 0.7f, 10, 10, C_MAGENTA);
	pMesh3->GenerateTube(1.0f, 0.7f, 1.0f, 10, C_BLUE);
	int nMesh1 = m_pMngr->AddMesh(pMesh1);
	int nMesh2 = m_pMngr->AddMesh(pMesh2);
	
	Group* pGroup1 = new Group();
	pGroup1->AddMesh(nMesh1, MeshOptions(glm::translate(AXIS_Y), WIRE));
	pGroup1->AddMesh(nMesh2, MeshOptions(glm::translate(-AXIS_Y), SOLID));
	Group* pGroup2 = new Group();
	pGroup2->AddMesh(pMesh3, MeshOptions(IDENTITY_M4, SOLID | WIRE));
	
	m_pModel1 = new Model();
	m_pModel1->AddGroup(pGroup1);
	m_pModel1->AddGroup(pGroup2);
	*/
#pragma endregion
#pragma region Load Model and change its rendering properties
	/*
	m_pModel1 = new Model();
	m_pModel1->Load("Macross\\YF19.BTO");
	m_pModel1->ChangeMeshOptions(MeshOptions(IDENTITY_M4, SOLID | WIRE), -1, -1);
	*/
#pragma endregion
#pragma region Load Model and change its materials
	/*
	m_pModel1 = new Model();
	m_pModel1->Load("Macross\\YF19.BTO");
	//m_pModel1->ChangeMeshOptions(MeshOptions(IDENTITY_M4, SOLID | WIRE), -1, -1);
	m_pMatMngr->AddMaterial("Cloud.png", "Cloud.png");
	m_pModel1->ChangeMaterialOfGroup("Cloud.png", "ALL");
	*/
#pragma endregion
#pragma region Load Model disconect and change its materials
	/*
	m_pModel1 = new Model();
	m_pModel1->Load("Macross\\YF19.BTO");
	//m_pModel1->ChangeMeshOptions(MeshOptions(IDENTITY_M4, SOLID | WIRE), -1, -1);
	m_pMatMngr->AddMaterial("Cloud.png", "Cloud.png");
	m_pModel1->DuplicateMaterialsUnique(-1, "_copy"); //dupliocate existing materials
	m_pModel1->CreateMaterials(); //duplicate one per mesh
	m_pModel1->ChangeMaterialOfGroup("Cloud.png", "ALL");
	*/
#pragma endregion
#pragma region Load Model and duplicate onto another one
	/*
	m_pModel3 = new Model();
	m_pModel3->Load("Macross\\YF19.BTO");
	m_pModel1 = new Model();
	m_pModel1->Instance(m_pModel3, "_copy_");
	*/
#pragma endregion
#pragma region Load Model
	/*	
	m_pModel1 = new Model();
	m_pModel1->Load("Macross\\YF19.BTO");
	*/
#pragma endregion
#pragma region Test
	m_pModel1 = new Model();
	String sModel;
	//sModel = "Macross\\YF19.BTO";
	//sModel = "Macross\\Glaug.ATO";
	//sModel = "Macross\\Glaug.BTO";
	//sModel = "Portal\\Wheatley.BTO";
	sModel = "Lego\\Unikitty.BTO";
	//sModel = "Minecraft\\Cow.FBX";
	//sModel = "Minecraft\\Cow.OBJ";
	//sModel = "BackedUp\\WallEye.obj";
	//sModel = "BackedUp\\chris.obj";
	//sModel = "Macross\\YF19G_NA.BTO";
	//sModel = "Freddy\\Freddy_Multiple.fbx";
	//sModel = "Portal\\CompanionCube.fbx";
	//sModel = "Minecraft\\Steve.FBX";
	m_pModel1->Load(sModel);
#pragma endregion

	//std::map<String, Model*> map = Model::GetModelsMap();
	//int i = 0;
	//m_pModel3->ChangeMeshOptions(MeshOptions(glm::translate(AXIS_Y), OFF), 0, 0);
	/*
	m_pModelList = new Model[1000];
	for (uint i = 0; i < 1000; i++)
	{
		m_pModelList[i].InstanceModel(m_pModel1, std::to_string(i));
	}
	*/
}
void AppClass::Update(void)
{
	//Update the system
	m_pSystem->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Call the arcball method
	ArcBall();

	m_pMeshMngr->AddSkyboxToRenderList();
	
	m_pModel1->SetModelMatrix(ToMatrix4(m_qArcBall));

	uint entities = 1;
	for (uint i = 0; i < entities; i++)
	{
		//uint n = i % 3;
		//m_pMeshMngr->AddPlaneToRenderList(glm::translate(vector3(i, 0, 0)), C_WHITE, n);
		//m_pMeshMngr->AddSphereToRenderList(glm::translate(vector3(i, 0, 0)), C_WHITE, RENDER_SOLID || RENDER_WIRE);
		//m_pMeshMngr->AddSkyboxToRenderList();
		m_pModel1->SetModelMatrix(glm::translate(vector3(i, 0, 0)));
		//m_pModel1->PlaySequence();
		m_pModel1->Play();
		//m_pModel1->AddToRenderList();
		//m_pGroup->AddRenderToList(glm::translate(vector3(i + 3, 0, 0)));
		//m_pModel3->SetModelMatrix(glm::translate(vector3(i + 3,0,0)));
		//m_pModel3->AddToRenderList();
		//m_pModel2->SetModelMatrix(glm::translate(vector3(i,-1,0)));
		//m_pModel2->AddToRenderList();
		//m_pModel3->SetModelMatrix(glm::translate(vector3(i, 0, 0)));
		//m_pModel3->AddToRenderList();
		//m_pModelList[i].SetModelMatrix(glm::translate(vector3(i + 3, 0, 0)));
		//m_pModelList[i].AddToRenderList();
	}
	
	//Adds all loaded instance to the render list
	//m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//Print info on the screen
	for(uint i = 0; i < 19; ++i)
		m_pMeshMngr->PrintLine("");//Add a line on top
	m_pMeshMngr->Print("						");
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), C_YELLOW);

	m_pMeshMngr->Print("						");
	m_pMeshMngr->Print("RenderCalls: ");//Add a line on top
	m_pMeshMngr->PrintLine(std::to_string(m_uRenderCallCount), C_YELLOW);

	m_v3Mouse = m_pWindow->GetMouseCoordinates();
	m_pMeshMngr->Print("						");
	m_pMeshMngr->Print("Mouse: ( ");//Add a line on top
	m_pMeshMngr->Print(std::to_string(m_v3Mouse.x), C_YELLOW);
	m_pMeshMngr->Print(" , ");//Add a line on top
	m_pMeshMngr->Print(std::to_string(m_v3Mouse.y), C_YELLOW);
	m_pMeshMngr->PrintLine(" )");//Add a line on top
		
	m_pMeshMngr->Print("						");
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), C_RED);
}
void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	//m_pMesh->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), ToMatrix4(m_qArcBall), vector3(0), SOLID | WIRE);
	//m_pMesh2->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3(2)), m_pCameraMngr->GetPosition(), SOLID);
	m_uRenderCallCount = m_pMeshMngr->Render();
	//Render the grid based on the camera's mode:
	//m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	//m_pMeshMngr->Render(); //renders the render list
	//m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pMeshMngr->ClearRenderList();
	DrawGUI();
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}
void AppClass::Release(void)
{
	ShutdownGUI();
	
	if (m_pModelList)
	{
		delete[] m_pModelList;
		m_pModelList = nullptr;
	}

	//SafeDelete(m_pGroup);
	SafeDelete(m_pModel1);
	SafeDelete(m_pModel2);
	SafeDelete(m_pModel3);
	
	super::Release(); //release the memory of the inherited fields
}