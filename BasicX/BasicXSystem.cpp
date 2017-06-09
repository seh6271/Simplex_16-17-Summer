#include "BasicX\System\BasicXSystem.h"
using namespace BasicX;
String GetProgramName()
{
	TCHAR stCurrentDir[MAX_PATH];
	GetModuleFileName( 0, stCurrentDir, MAX_PATH);
	int nLength = 0;
	char temp[MAX_PATH];
	
	while(stCurrentDir[nLength] != '\0')
	{
		temp[nLength] = static_cast<char>(stCurrentDir[nLength]);
		nLength++;
	}
	temp[nLength] = '\0';
	int nPeriods = 0;
	int nLength2 = nLength;
	while (temp[nLength2] != '\\')
	{
		nLength2 --;
		if(temp[nLength2] == '.')
			nPeriods++;
	}

	int newLength = nLength - nLength2;
	char temp2[MAX_PATH];

	int nOffset = 0;
	for(int i = nLength2 +1; i < nLength +1; i++)
	{
		temp2[nOffset] = temp[i];
		nOffset++;
	}

	while(newLength > 0)
	{
		if(temp2[newLength] == '.')
		{
			temp2[newLength] = '\0';
			break;
		}
		newLength--;
	}

	String output = temp2;
	return output;
}
//  BasicXSystem
BasicXSystem* BasicXSystem::m_pInstance = nullptr;
BasicXSystem* BasicXSystem::GetInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new BasicXSystem();
	}
	return m_pInstance;
}
BasicXSystem::BasicXSystem(){Init();}
BasicXSystem::BasicXSystem(BasicXSystem const& other){}
BasicXSystem& BasicXSystem::operator=(BasicXSystem const& other) {	return *this; }
BasicXSystem::~BasicXSystem(){Release();};
void BasicXSystem::ReleaseInstance()
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
//--- Non Standard Singleton Methods
void  BasicXSystem::Release(void)
{
	m_pFolder = nullptr;
	m_lClock.clear();
}
void BasicXSystem::Init(void)
{
	m_pFolder = Folder::GetInstance();

	m_sAppName = GetProgramName();

	m_nWindowX = 0;
	m_nWindowY = 0;

	m_bWindowFullscreen = false;
	m_bWindowBorderless = false;

	m_nWindowWidth = 1280;
	m_nWindowHeight = 720;
	m_sWindowName = "My Engine - Window";
	m_RenderingContext = OPT_OPENGL3X;

	m_dStartingTime = GetTickCount();
	m_dLastFPS = GetTickCount();
	m_uFrameCount = 0;
	m_nFPS = 0;

	m_dTimerStart = m_dStartingTime;

	StartClock();
}

String BasicXSystem::GetAppName(void){ return m_sAppName; }

void BasicXSystem::SetWindowX(int nX){ m_nWindowX = nX; }
int BasicXSystem::GetWindowX(void){ return m_nWindowX; }

void BasicXSystem::SetWindowY(int nY){ m_nWindowY = nY; }
int BasicXSystem::GetWindowY(void){ return m_nWindowY; }

void BasicXSystem::GetWindowPosition(int* a_nPosX, int* a_nPosY)
{
	*a_nPosX = m_nWindowX;
	*a_nPosY = m_nWindowY;
}

void BasicXSystem::GetWindowSize(int* a_nWidth, int* a_nHeight)
{
	*a_nWidth = m_nWindowWidth;
	*a_nHeight = m_nWindowHeight;
}

void BasicXSystem::SetWindowBorderless(bool bBorderless){ m_bWindowBorderless = bBorderless; }
bool BasicXSystem::IsWindowBorderless(void){	return m_bWindowBorderless; }

void BasicXSystem::SetWindowFullscreen(BTO_RESOLUTIONS a_Resolution)
{
	if (a_Resolution == BTO_RESOLUTIONS::RES_WINDOWED)
	{
		m_bWindowFullscreen = false;
		return;
	}
	m_bWindowFullscreen = true;
	m_bWindowBorderless = true;

	SetWindowResolution(a_Resolution);
}
bool BasicXSystem::IsWindowFullscreen(void){ return m_bWindowFullscreen; }

void BasicXSystem::SetWindowResolution(BTO_RESOLUTIONS a_Resolution)
{
	switch (a_Resolution)
	{
	default:
	case BTO_RESOLUTIONS::RES_C_720x480_4x3_NTSC:
		m_nWindowWidth = 720;
		m_nWindowHeight = 480;
		break;
	case BTO_RESOLUTIONS::RES_C_1280x720_16x9_HD:
		m_nWindowWidth = 1280;
		m_nWindowHeight = 720;
		break;
	case BTO_RESOLUTIONS::RES_C_1920x1080_16x9_FULLHD:
		m_nWindowWidth = 1920;
		m_nWindowHeight = 1080;
		break;
	case BTO_RESOLUTIONS::RES_M_640x480_4x3_VGA:
		m_nWindowWidth = 640;
		m_nWindowHeight = 480;
		break;
	case BTO_RESOLUTIONS::RES_M_1600x900_16x9_WXGA:
		m_nWindowWidth = 1600;
		m_nWindowHeight = 900;
		break;
	case BTO_RESOLUTIONS::RES_M_1920x1200_16x10_WUXGA:
		m_nWindowWidth = 1920;
		m_nWindowHeight = 1200;
		break;
	case BTO_RESOLUTIONS::RES_M_2560x1080_21x9_UWUXGA:
		m_nWindowWidth = 2560;
		m_nWindowHeight = 1080;
		break;
	case BTO_RESOLUTIONS::RES_O_800x600_4x3_SVGA:
		m_nWindowWidth = 800;
		m_nWindowHeight = 600;
		break;
	case BTO_RESOLUTIONS::RES_O_1024x768_4x3_XGA:
		m_nWindowWidth = 1024;
		m_nWindowHeight = 768;
		break;
	case BTO_RESOLUTIONS::RES_O_1280x800_16x10_WXGA:
		m_nWindowWidth = 1280;
		m_nWindowHeight = 800;
		break;
	case BTO_RESOLUTIONS::RES_O_1600x1200_4x3_UXGA:
		m_nWindowWidth = 1600;
		m_nWindowHeight = 1200;
		break;
	case BTO_RESOLUTIONS::RES_O_2048x1080_17x9_2K:
		m_nWindowWidth = 2048;
		m_nWindowHeight = 1080;
		break;
	case BTO_RESOLUTIONS::RES_O_3840x2160_17x9_4K:
		m_nWindowWidth = 3480;
		m_nWindowHeight = 2160;
		break;
	case BTO_RESOLUTIONS::RES_CV_480x720_3x4_NTSC:
		m_nWindowWidth = 480;
		m_nWindowHeight = 720;
		break;
	case BTO_RESOLUTIONS::RES_CV_720x1280_9x16_HD:
		m_nWindowWidth = 720;
		m_nWindowHeight = 1280;
		break;
	case BTO_RESOLUTIONS::RES_CV_1080x1920_9x16_FULLHD:
		m_nWindowWidth = 1080;
		m_nWindowHeight = 1920;
		break;
	case BTO_RESOLUTIONS::RES_MV_480x640_3x4_VGA:
		m_nWindowWidth = 480;
		m_nWindowHeight = 640;
		break;
	case BTO_RESOLUTIONS::RES_MV_900x1600_9x16_WXGA:
		m_nWindowWidth = 900;
		m_nWindowHeight = 1600;
		break;
	case BTO_RESOLUTIONS::RES_MV_1200x1920_10x16_WUXGA:
		m_nWindowWidth = 1200;
		m_nWindowHeight = 1920;
		break;
	case BTO_RESOLUTIONS::RES_MV_1080x2560_9x21_UWUXGA:
		m_nWindowWidth = 1080;
		m_nWindowHeight = 2560;
		break;
	}
}

void BasicXSystem::SetWindowWidth(int nWidth)
{
	m_nWindowWidth = nWidth;
	if (m_nWindowWidth < 1)
		m_nWindowWidth = 1;
}

int BasicXSystem::GetWindowWidth(void) { return m_nWindowWidth; }
void BasicXSystem::SetWindowHeight(int nHeight)
{
	m_nWindowHeight = nHeight;
	if (m_nWindowHeight < 1)
		m_nWindowHeight = 1;
}

int BasicXSystem::GetWindowHeight(void){	return m_nWindowHeight;}
void BasicXSystem::SetWindowName(String a_sWindowName) { m_sWindowName = a_sWindowName; }
String BasicXSystem::GetWindowName(void){ return m_sWindowName;}

void BasicXSystem::SetThreaded(bool a_bMultithreaded){ m_bMultithreaded = a_bMultithreaded; }
bool BasicXSystem::GetThreaded(void){ return m_bMultithreaded; }

bool BasicXSystem::GetUsingConsole(void){ return m_bConsoleWindow; }
void BasicXSystem::SetUsingConsole(bool a_bUsing){ m_bConsoleWindow = a_bUsing; }

float BasicXSystem::GetWindowRatio(void) { return m_nWindowWidth / static_cast<float>(m_nWindowHeight); }
int BasicXSystem::GetFPS(void){	return m_nFPS; }

void BasicXSystem::Update()
{
	// Get FPS
	if( (GetTickCount() - m_dLastFPS) >= 1000 )	// When a Second has passed...
	{
		m_dLastFPS = GetTickCount();			// Refresh the value of frames
		m_nFPS = m_uFrameCount;						// save the number of frames that occurred in this second
		m_uFrameCount = 1;							// Reset the frames
		return;
	}
	m_uFrameCount++;								// Increment the frame count
	return;
}
void BasicXSystem::StartClock(unsigned int a_nClock)
{
	while (m_lClock.size() < a_nClock + 1)
		m_lClock.push_back(GetTickCount());
	m_lClock[a_nClock] = GetTickCount();
}
double BasicXSystem::LapClock(unsigned int a_nClock)
{
	while (m_lClock.size() < a_nClock + 1)
		m_lClock.push_back(GetTickCount());
	DWORD dCurrentTime = GetTickCount();
	double dTime = (dCurrentTime - m_lClock[a_nClock])/1000.0;
	m_lClock[a_nClock] = dCurrentTime;

	return dTime;
}
uint BasicXSystem::GenClock(void)
{
	uint nSize = m_lClock.size();
	LapClock(nSize);
	return nSize;
}
bool BasicXSystem::CountDown(float a_fTime, bool a_bRepeat)
{
	static bool bNew = true;
	static bool bGoneOff = false;
	static DWORD dTime = 0;
	static DWORD dStartTime = 0;
	if(bNew)
	{
		dStartTime = GetTickCount();
		dTime = static_cast<DWORD>(a_fTime * 1000);
		bNew = false;
	}
	bool bDone = false;
	DWORD dTimeDifference = GetTickCount() - dStartTime;
	if(dTimeDifference > dTime)
	{
		bDone = true;
		if(a_bRepeat)
		{
			bNew = true;
		}
	}
	
	return bDone;
}