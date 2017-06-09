/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2017/05
----------------------------------------------*/
#ifndef __MESHMANAGERSINGLETON_H_
#define __MESHMANAGERSINGLETON_H_
#include "Simplex\Mesh\MeshDrawerSingleton.h"
#include "Simplex\Mesh\PrimitiveManagerSingleton.h"
#include "Simplex\Mesh\ModelManagerSingleton.h"
#include "Simplex\Mesh\TextSingleton.h"

namespace Simplex
{
//MeshManagerSingleton
class SimplexDLL MeshManagerSingleton
{
	static MeshManagerSingleton* m_pInstance; // Singleton pointer
	TextSingleton* m_pText; //Text Singleton

public:
	MeshDrawerSingleton* m_pMeshDrawer = nullptr;//pointer to the Mesh Drawer singleton
	PrimitiveManagerSingleton* m_pPrimitiveMngr = nullptr; //pointer to the Primitive Manager singleton
	ModelManagerSingleton* m_pModelMngr = nullptr; //pointer to the Model Manager singleton
	
	//Singleton Methods
	/*
	USAGE: Gets/Constructs the singleton pointer
	ARGUMENTS:
	OUTPUT:
	*/
	static MeshManagerSingleton* GetInstance();
	/*
	USAGE: Destroys the singleton
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	static void ReleaseInstance(void);
	//Gets/Sets
	/*
	USAGE: Gets the Instance by an index number
	ARGUMENTS:
	OUTPUT:
	*/
	InstanceClass* GetInstanceByIndex(int a_nIndex);
	/*
	USAGE: Gets the Instance by a name
	ARGUMENTS:
	OUTPUT:
	*/
	InstanceClass* GetInstanceByName(String a_sInstanceName);
	/*
	USAGE: Asks the Manager for the number of instances
	ARGUMENTS: ---
	OUTPUT:
	*/
	uint GetInstanceCount(void);
	/*
	USAGE: Asks for the name of the group in the specified instance
	ARGUMENTS:
	- uint a_nInstanceIndex -> Index of the instance
	- uint a_nGroupIndex -> Index of the group
	OUTPUT: Name in the index, empty if not found
	*/
	String GetInstanceGroupName(uint a_nInstanceIndex, uint a_nGroupIndex);
	/*
	USAGE: Asks for the name of the instance stored in the specified index
	ARGUMENTS:
	- uint a_nInstanceIndex -> Index of the instance
	OUTPUT: Name in the index, empty if not found
	*/
	String GetInstanceName(uint a_nInstanceIndex);
	/*
	USAGE: Asks the Manager for the number of models
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetModelCount(void);
	/*
	USAGE: Asks the manager for an specific instance's model to world matrix
	ARGUMENTS:
	OUTPUT:
	*/
	matrix4 GetModelMatrix(String a_sInstance);
	/*
	USAGE: Asks the name of the specified instance by its index returns empty if not found
	ARGUMENTS:
	OUTPUT:
	*/
	String GetNameOfInstanceByIndex(int a_nIndex);
	/*
	USAGE: Asks the manager for the list of vertices of an specified instance
	ARGUMENTS:
	OUTPUT:
	*/
	std::vector<vector3> GetVertexList(String a_sInstanceName);
	/*
	USAGE: Asks the manager for the list of vertices of an specified instance
	ARGUMENTS:
	OUTPUT:
	*/
	std::vector<vector3> GetVertexList(uint a_nIndex);
	/*
	USAGE: Sets the model matrix of an specific instance finding it by name
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetModelMatrix(matrix4 a_m4ToWorld, String a_sInstance = "ALL");
	/*
	USAGE: Sets the model matrix of an specific instance finding it by index
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetModelMatrix(matrix4 a_m4ToWorld, int a_nIndex);
	/*
	USAGE: Sets the shader program of an specific instance by name
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetShaderProgramByName(String a_sInstanceName = "ALL", String a_sShaderName = "Original", vector3 a_v3Tint = DEFAULT_V3NEG);
	/*
	USAGE: Sets the shader program of an specific instance by index
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetShaderProgramByNumber(int a_nInstance = -1, int a_nGroup = -1, String a_sShaderName = "Original", vector3 a_v3Tint = DEFAULT_V3NEG);
	/*
	USAGE: Sets the visibility of the axis of the instance
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetVisibleAxis(bool a_bVisible = false, String a_sInstanceName = "ALL", int a_nGroupIndex = -1);
	/*
	USAGE: Sets the visibility of the Bounding Object of the instance
	ARGUMENTS:
	- int a_nOption = BTO_DISPLAY::BD_NONE -> Display options BD_NONE | BD_BS | BD_OB | BD_AB
	- String a_sInstanceName = "ALL" -> Instance to apply to
	- bool a_bAllGroups = false -> Apply to all groups
	OUTPUT: ---
	*/
	void SetVisibleBO(int a_nOption = BTO_DISPLAY::BD_NONE, String a_sInstanceName = "ALL", int a_nGroupIndex = -1);
	/*
	USAGE: Sets the visibility of the Bounding Object of the instance
	ARGUMENTS:
	- int a_nOption = BTO_DISPLAY::BD_NONE -> Display options BD_NONE | BD_BS | BD_OB | BD_AB
	- int a_nInstanceIndex = -1 -> Instance index if less than 0 applies it to all
	- int a_nGroupIndex = -1 -> Group index if less than 0 applies it to all
	OUTPUT: ---
	*/
	void SetVisibleBO(int a_nOption = BTO_DISPLAY::BD_NONE, int a_nInstanceIndex = -1, int a_nGroupIndex = -1);
	/*
	USAGE: Updates the model manager
	ARGUMENTS:
	OUTPUT: ---
	*/
	void Update(void);
	//Methods
	/*
	USAGE: Render the axis on the specified position
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddAxisToRenderList(matrix4 a_m4ToWorld);
	/*
	USAGE: Renders the a Camera Mesh on the specified camera's position, -1 for active camera
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddCameraToRenderList(int a_nID = -1, vector3 a_v3Color = C_WHITE);
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddSkyboxToRenderList(String a_sTextureName = "Skybox.png");
	/*
	USAGE: Renders the cone on the specified position
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddConeToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color = DEFAULT_V3NEG, int a_RenderOption = BTO_RENDER::RENDER_SOLID | BTO_RENDER::RENDER_WIRE);
	/*
	USAGE: Renders the cube on the specified position
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddCubeToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color = DEFAULT_V3NEG, int a_RenderOption = BTO_RENDER::RENDER_SOLID | BTO_RENDER::RENDER_WIRE);
	/*
	USAGE: Renders the cylinder on the specified position
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddCylinderToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color = DEFAULT_V3NEG, int a_RenderOption = BTO_RENDER::RENDER_SOLID | BTO_RENDER::RENDER_WIRE);
	/*
	USAGE: Renders the sphere on the specified position
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddGridToRenderList(float a_fSize = 1.0f, int a_Axis = BTO_AXIS::AX_XY, vector3 a_v3Color = DEFAULT_V3NEG);
	/*
	USAGE: Sets where the objects are going to be rendered
	ARGUMENTS:
		GLuint a_FrameBuffer = 0 -> Where to render, 0 for the window
		GLuint a_TextureToRender = 0 -> Texture to render onto
	OUTPUT: ---
	*/
	void SetRenderTarget(GLuint a_nFrameBuffer = 0, GLuint a_nDepthBuffer = 0, GLuint a_nTextureToRender = 0);

	/*
	USAGE: Renders the specified texture on a plane right in front of the camera
	ARGUMENTS: GLuint a_uGLIndex index of the texture in opengl (not in the texture manager)
	OUTPUT: ---
	*/
	void RenderTexture(GLuint a_uGLIndex, vector3 a_v3Tint = vector3(1.0f));
	/*
	USAGE: Renders the Grid based on the active's camera mode
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddGridToRenderListBasedOnCamera(int a_nCameraMode = BTO_CAMERAMODE::CAM_PERSP, float a_fSize = 1.0f);
	/*
	USAGE: Renders a hexagon tile on the specified position
	ARGUMENTS:
	OUTPUT: ---
	*/
	MeshClass* AddHexagonTileToRenderList(matrix4 a_m4ToWorld, vector2 a_v2Size, vector3 a_v3Color = DEFAULT_V3NEG, int a_RenderOption = BTO_RENDER::RENDER_SOLID | BTO_RENDER::RENDER_WIRE);
	/*
	USAGE: Renders a hexagon on the specified position
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddHexagonToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color = DEFAULT_V3NEG, int a_RenderOption = BTO_RENDER::RENDER_SOLID | BTO_RENDER::RENDER_WIRE);
	/*
	USAGE: Adds an instance to the render list specified by index
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddInstanceToRenderList(uint a_nInstance);
	/*
	USAGE: Renders the specified instance
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddInstanceToRenderList(String a_sInstance = "ALL");
	/*
	USAGE: Renders the specified list of names to the render list
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddInstanceToRenderList(std::vector<String> a_lInstances);
	/*
	USAGE: Renders a line on with the specified vectors and color
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddLineToRenderList(vector3 a_v3Origin, vector3 a_v3Ending, vector3 a_v3StartColor = DEFAULT_V3NEG, vector3 a_v3EndColor = DEFAULT_V3NEG);
	/*
	USAGE: Renders a mesh on the specified space
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddMeshToRenderList(MeshClass* a_pMesh, matrix4& a_m4ToWorld);
	/*
	USAGE: Renders a mesh on the specified space
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddMeshToRenderList(int a_nIndex, matrix4& a_m4ToWorld);
	/*
	USAGE: Renders the cube on the specified position
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddPlaneToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color = DEFAULT_V3NEG);
	/*
	USAGE: Renders the sphere on the specified position
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddSphereToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color = DEFAULT_V3NEG, int a_RenderOption = BTO_RENDER::RENDER_SOLID | BTO_RENDER::RENDER_WIRE);
	/*
	USAGE: Renders a char array in the specified color
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddTextLineToRenderList(vector3 a_v3Color, const char * _Format, ...);
	/*
	USAGE: Renders a char array in the specified color
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddTextToRenderList(vector3 a_v3Color, const char * _Format, ...);
	/*
	USAGE: Renders the torus on the specified position
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddTorusToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color = DEFAULT_V3NEG, int a_RenderOption = BTO_RENDER::RENDER_SOLID | BTO_RENDER::RENDER_WIRE);
	/*
	USAGE: Renders the tube on the specified position
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddTubeToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color = DEFAULT_V3NEG, int a_RenderOption = BTO_RENDER::RENDER_SOLID | BTO_RENDER::RENDER_WIRE);
	/*
	USAGE: Returns the index of the specified instance name, -1 if not found
	ARGUMENTS:
	OUTPUT:
	*/
	int IdentifyInstance(String a_sInstanceName);
	/*
	USAGE: Will check if an Instance is colliding with the ray specified by the origin and directional vector and store
	- the distance from the origin till the collision in a_fDistance, the output will be an std::pair containing the index
	- of the instance and the index of the group is first colliding with, -1 if not colliding with anything
	ARGUMENTS:
	- vector3 a_v3RayOrigin -> start of the ray
	- vector3 a_v3RayDirection -> direction of the ray
	- float& a_fDistance -> distance for origin
	OUTPUT: <Instance index, group index>
	*/
	std::pair<int, int> IsColliding(vector3 a_v3RayOrigin, vector3 a_v3RayDirection, float& a_fDistance);
	/*
	USAGE: Asks the manager if an instance with this name has been created
	ARGUMENTS:
	OUTPUT:
	*/
	bool IsInstanceCreated(String a_sInstanceName);
	/*
	USAGE: Loads an add-on file for the specified instance
	ARGUMENTS:
	OUTPUT:
	*/
	BTO_OUTPUT LoadAddOn(String a_sInstanceName, String a_sFileName);
	/*
	USAGE: Loads the specified level file
	ARGUMENTS:
	OUTPUT: ---
	*/
	void LoadLevel(String a_sFileName);
	/*
	USAGE: Loads the specified model file
	ARGUMENTS:
	OUTPUT:
	*/
	BTO_OUTPUT LoadModel(String a_sFileName,
		String a_sInstanceName,
		bool a_bAbsoluteRoute = false,
		matrix4 a_m4ToWorld = matrix4(1.0),
		int a_nVisibility = 1,
		int a_nCollidable = 1,
		int a_nState = 0);
	/*
	USAGE: Renders a String in the specified color
	ARGUMENTS:
	OUTPUT: ---
	*/
	void Print(String a_sInput, vector3 a_v3Color = C_WHITE);
	/*
	USAGE: Renders a String Line in the specified color
	ARGUMENTS:
	OUTPUT: ---
	*/
	void PrintLine(String a_sInput, vector3 a_v3Color = C_WHITE);
	/*
	USAGE: Renders the list of meshes
	ARGUMENTS: 
		float f3DStereoDepth = 0 -> how much of stereoscopic effect in depth you want to see, 0 for none, 1 for high
	OUTPUT: ---
	*/
	void Render( float f3DStereoDepth = 0);
	/*
	USAGE: Renders the list of meshes
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ClearRenderList(void);
	/*
	USAGE: Saves the specified model file, needs to specify the file extension (ATO or BTO)
	ARGUMENTS:
	String a_sFileName -> Name of the file
	BTO_FORMAT a_Format -> Extension of the file ATO or BTO
	String a_sInstanceName -> Name of the instance to save
	bool a_bAbsoluteRoute = false -> whether the filename specifies an absolute route or not
	OUTPUT: BTO_OUTPUT -> OUT_ERR_NONE if everything went right, reason for failure otherwise
	*/
	BTO_OUTPUT SaveModel(String a_sFileName,
		BTO_FORMAT a_Format,
		String a_sInstanceName,
		bool a_bAbsoluteRoute = false);
	/*
	USAGE: Replaces the specified material of one Instance in memory by a new material with the
	name specified by newMaterial, using Original will keep the textures the instance already have
	in memory. If DuplicateInstanceMaterial is not called it will modify all instances of the model
	ARGUMENTS:
	String a_sInstance, // name of the instance to modify
	String a_sOldMaterialName, // name of the material to change
	String a_sNewMaterialName, // new name for that material
	String a_sDiffuseTexture = "Original", //new texture to load, Original for the same texture
	String a_sNormalTexture = "Original", //new texture to load, Original for the same texture
	String a_sSpecularTexture = "Original"); //new texture to load, Original for the same texture
	OUTPUT: void
	*/
	void ModifyMaterialOnInstance(String a_sInstance,
		String a_sOldMaterialName,
		String a_sNewMaterialName,
		String a_sDiffuseTexture = "Original",
		String a_sNormalTexture = "Original",
		String a_sSpecularTexture = "Original");

	/*
	USAGE: Returns the material pointer in the Material Manager from the specified Instance
	ARGUMENTS:
	String a_sInstance, // name of the instance to 
	OUTPUT: Material* nullptr if not found
	*/
	Material* GetMaterialOnInstance(String a_sInstance, String a_sMaterial);
	/*
	USAGE: Duplicate the material in the instance disconnecting it from the model's
	ARGUMENTS:
	String a_sInstance, // name of the instance to modify
	OUTPUT: ---
	*/
	void DuplicateMaterialsOnInstance(String a_sInstance);
	/*
	USAGE: Sets the texture for the font
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFont(String a_sTextureName);

	void InstanceCube(float a_fSize, vector3 a_v3Color, String a_sInstanceName);
	void InstanceCuboid(vector3 a_v3Dimentions, vector3 a_v3Color, String a_sInstanceName);
	void InstanceCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color, String a_sInstanceName);
	void InstanceCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color, String a_sInstanceName);
	void InstanceTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color, String a_sInstanceName);
	void InstanceTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionHeigh, int a_nSubdivisionAxis, vector3 a_v3Color, String a_sInstanceName);
	void InstanceSphere(float a_fDiameter, int a_nSubdivisions, vector3 a_v3Color, String a_sInstanceName);
	bool AreColliding(String a_sInstance1, String a_sInstance2);
private:
	//Rule of 3
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT:
	*/
	MeshManagerSingleton(void);
	/*
	USAGE: Copy Constructor
	ARGUMENTS:
	OUTPUT:
	*/
	MeshManagerSingleton(MeshManagerSingleton const& other);
	/*
	USAGE: Copy Assignment Operator
	ARGUMENTS:
	OUTPUT:
	*/
	MeshManagerSingleton& operator=(MeshManagerSingleton const& other);
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~MeshManagerSingleton(void);
	//Other methods
	/*
	USAGE: Initializes the objects fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
	/*
	USAGE: Releases the objects memory
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
};

}

#endif //__MESHMANAGERSINGLETON_H_