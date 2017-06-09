#include "AppClass.h"

ImGuiObject AppClass::gui;
void AppClass::DrawGUI(void)
{
	NewFrame();
	// 1. Show a simple window
	// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
	if (m_bGUI_Window_Main)
	{
		static float f = 0.0f;
		ImGui::SetNextWindowPos(ImVec2(1, 40), ImGuiSetCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(315, 91), ImGuiSetCond_FirstUseEver);
		ImGui::SetNextWindowCollapsed(true, ImGuiSetCond_FirstUseEver);
		ImGui::Begin(m_pSystem->GetAppName().c_str());
		ImGui::Text("FrameRate: %.2f [FPS] -> %.3f [ms/frame] ", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);
		ImGui::Text("RenderCalls: %d", m_uRenderCallCount);
		
		if (ImGui::Button("Credits")) 
			m_bGUI_Window_Secondary ^= 1;
		ImGui::SameLine();
		if (ImGui::Button("ImGui - Test Window")) 
			m_bGUI_Window_Test ^= 1;
		
		ImGui::End();
		
	}
	// 2. Show another simple window, this time using an explicit Begin/End pair
	if (m_bGUI_Window_Secondary)
	{
		ImGui::SetNextWindowPos(ImVec2(2, 635), ImGuiSetCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(315, 84), ImGuiSetCond_FirstUseEver);
		ImGui::SetNextWindowCollapsed(false, ImGuiSetCond_Always);
		String sAbout = m_pSystem->GetAppName() + " - About";
		ImGui::Begin(sAbout.c_str(), &m_bGUI_Window_Secondary);
		//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		//ImGui::Text("Programmer: \nAlberto Bobadilla - labigm@rit.edu");
		static ImVec4 v4ClearColor = ImColor(255, 0, 0);
		ImGui::TextColored(v4ClearColor, "Programmer: \nAlberto Bobadilla - labigm@rit.edu");
		ImGui::ColorEdit3("color", (float*)&v4ClearColor);
		ImGui::End(); 
	}
	// 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
	if (m_bGUI_Window_Test)
	{
		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
		ImGui::ShowTestWindow(&m_bGUI_Window_Test);
	}

	// Rendering
	ImGui::Render();
	ImDrawData* pData = ImGui::GetDrawData();
	RenderDrawLists(pData);
}
void AppClass::RenderDrawLists(ImDrawData* draw_data)
{
	// Avoid rendering when minimized, scale coordinates for retina displays (screen coordinates != framebuffer coordinates)
	ImGuiIO& io = ImGui::GetIO();
	int fb_width = (int)(io.DisplaySize.x * io.DisplayFramebufferScale.x);
	int fb_height = (int)(io.DisplaySize.y * io.DisplayFramebufferScale.y);
	if (fb_width == 0 || fb_height == 0)
		return;
	draw_data->ScaleClipRects(io.DisplayFramebufferScale);

	// Backup GL state
	GLint last_active_texture; glGetIntegerv(GL_ACTIVE_TEXTURE, &last_active_texture);
	glActiveTexture(GL_TEXTURE0);
	GLint last_program; glGetIntegerv(GL_CURRENT_PROGRAM, &last_program);
	GLint last_texture; glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
	GLint last_array_buffer; glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &last_array_buffer);
	GLint last_element_array_buffer; glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &last_element_array_buffer);
	GLint last_vertex_array; glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &last_vertex_array);
	GLint last_blend_src_rgb; glGetIntegerv(GL_BLEND_SRC_RGB, &last_blend_src_rgb);
	GLint last_blend_dst_rgb; glGetIntegerv(GL_BLEND_DST_RGB, &last_blend_dst_rgb);
	GLint last_blend_src_alpha; glGetIntegerv(GL_BLEND_SRC_ALPHA, &last_blend_src_alpha);
	GLint last_blend_dst_alpha; glGetIntegerv(GL_BLEND_DST_ALPHA, &last_blend_dst_alpha);
	GLint last_blend_equation_rgb; glGetIntegerv(GL_BLEND_EQUATION_RGB, &last_blend_equation_rgb);
	GLint last_blend_equation_alpha; glGetIntegerv(GL_BLEND_EQUATION_ALPHA, &last_blend_equation_alpha);
	GLint last_viewport[4]; glGetIntegerv(GL_VIEWPORT, last_viewport);
	GLint last_scissor_box[4]; glGetIntegerv(GL_SCISSOR_BOX, last_scissor_box);
	GLboolean last_enable_blend = glIsEnabled(GL_BLEND);
	GLboolean last_enable_cull_face = glIsEnabled(GL_CULL_FACE);
	GLboolean last_enable_depth_test = glIsEnabled(GL_DEPTH_TEST);
	GLboolean last_enable_scissor_test = glIsEnabled(GL_SCISSOR_TEST);

	// Setup render state: alpha-blending enabled, no face culling, no depth testing, scissor enabled
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);

	// Setup viewport, orthographic projection matrix
	glViewport(0, 0, (GLsizei)fb_width, (GLsizei)fb_height);
	const float ortho_projection[4][4] =
	{
		{ 2.0f / io.DisplaySize.x, 0.0f,                   0.0f, 0.0f },
		{ 0.0f,                  2.0f / -io.DisplaySize.y, 0.0f, 0.0f },
		{ 0.0f,                  0.0f,                  -1.0f, 0.0f },
		{ -1.0f,                  1.0f,                   0.0f, 1.0f },
	};
	glUseProgram(AppClass::gui.m_nShader);
	glUniform1i(AppClass::gui.m_nTex, 0);
	glUniformMatrix4fv(AppClass::gui.m_nProjMtx, 1, GL_FALSE, &ortho_projection[0][0]);
	glBindVertexArray(AppClass::gui.m_uVAO);

	for (int n = 0; n < draw_data->CmdListsCount; n++)
	{
		const ImDrawList* cmd_list = draw_data->CmdLists[n];
		const ImDrawIdx* idx_buffer_offset = 0;

		glBindBuffer(GL_ARRAY_BUFFER, AppClass::gui.m_uVBO);
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)cmd_list->VtxBuffer.Size * sizeof(ImDrawVert), (const GLvoid*)cmd_list->VtxBuffer.Data, GL_STREAM_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, AppClass::gui.m_uElements);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx), (const GLvoid*)cmd_list->IdxBuffer.Data, GL_STREAM_DRAW);

		for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++)
		{
			const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
			if (pcmd->UserCallback)
			{
				pcmd->UserCallback(cmd_list, pcmd);
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, (GLuint)(intptr_t)pcmd->TextureId);
				glScissor((int)pcmd->ClipRect.x, (int)(fb_height - pcmd->ClipRect.w), (int)(pcmd->ClipRect.z - pcmd->ClipRect.x), (int)(pcmd->ClipRect.w - pcmd->ClipRect.y));
				glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount, sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, idx_buffer_offset);
			}
			idx_buffer_offset += pcmd->ElemCount;
		}
	}

	// Restore modified GL state
	glUseProgram(last_program);
	glBindTexture(GL_TEXTURE_2D, last_texture);
	glActiveTexture(last_active_texture);
	glBindVertexArray(last_vertex_array);
	glBindBuffer(GL_ARRAY_BUFFER, last_array_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, last_element_array_buffer);
	glBlendEquationSeparate(last_blend_equation_rgb, last_blend_equation_alpha);
	glBlendFuncSeparate(last_blend_src_rgb, last_blend_dst_rgb, last_blend_src_alpha, last_blend_dst_alpha);
	if (last_enable_blend) glEnable(GL_BLEND); else glDisable(GL_BLEND);
	if (last_enable_cull_face) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);
	if (last_enable_depth_test) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
	if (last_enable_scissor_test) glEnable(GL_SCISSOR_TEST); else glDisable(GL_SCISSOR_TEST);
	glViewport(last_viewport[0], last_viewport[1], (GLsizei)last_viewport[2], (GLsizei)last_viewport[3]);
	glScissor(last_scissor_box[0], last_scissor_box[1], (GLsizei)last_scissor_box[2], (GLsizei)last_scissor_box[3]);
}
bool AppClass::CreateFontsTexture()
{
	// Build texture atlas
	ImGuiIO& io = ImGui::GetIO();
	unsigned char* pixels;
	int width, height;
	io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);   // Load as RGBA 32-bits (75% of the memory is wasted, but default font is so small) because it is more likely to be compatible with user's existing shaders. If your ImTextureId represent a higher-level concept than just a GL texture id, consider calling GetTexDataAsAlpha8() instead to save on GPU memory.

															  // Upload texture to graphics system
	GLint last_texture;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
	glGenTextures(1, &gui.m_uFontTexture);
	glBindTexture(GL_TEXTURE_2D, gui.m_uFontTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	// Store our identifier
	io.Fonts->TexID = (void *)(intptr_t)gui.m_uFontTexture;

	// Restore state
	glBindTexture(GL_TEXTURE_2D, last_texture);

	return true;
}
bool AppClass::CreateDeviceObjects()
{
	// Backup GL state
	GLint last_texture, last_array_buffer, last_vertex_array;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &last_array_buffer);
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &last_vertex_array);

	const GLchar *vertex_shader =
		"#version 330\n"
		"uniform mat4 ProjMtx;\n"
		"in vec2 Position;\n"
		"in vec2 UV;\n"
		"in vec4 Color;\n"
		"out vec2 Frag_UV;\n"
		"out vec4 Frag_Color;\n"
		"void main()\n"
		"{\n"
		"	Frag_UV = UV;\n"
		"	Frag_Color = Color;\n"
		"	gl_Position = ProjMtx * vec4(Position.xy,0,1);\n"
		"}\n";

	const GLchar* fragment_shader =
		"#version 330\n"
		"uniform sampler2D Texture;\n"
		"in vec2 Frag_UV;\n"
		"in vec4 Frag_Color;\n"
		"out vec4 Out_Color;\n"
		"void main()\n"
		"{\n"
		"	Out_Color = Frag_Color * texture( Texture, Frag_UV.st);\n"
		"}\n";

	gui.m_nShader = glCreateProgram();
	gui.m_nVertHandle = glCreateShader(GL_VERTEX_SHADER);
	gui.m_nFragHandle = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(gui.m_nVertHandle, 1, &vertex_shader, 0);
	glShaderSource(gui.m_nFragHandle, 1, &fragment_shader, 0);
	glCompileShader(gui.m_nVertHandle);
	glCompileShader(gui.m_nFragHandle);
	glAttachShader(gui.m_nShader, gui.m_nVertHandle);
	glAttachShader(gui.m_nShader, gui.m_nFragHandle);
	glLinkProgram(gui.m_nShader);

	gui.m_nTex = glGetUniformLocation(gui.m_nShader, "Texture");
	gui.m_nProjMtx = glGetUniformLocation(gui.m_nShader, "ProjMtx");
	gui.m_nPosition = glGetAttribLocation(gui.m_nShader, "Position");
	gui.m_nUV = glGetAttribLocation(gui.m_nShader, "UV");
	gui.m_nColor = glGetAttribLocation(gui.m_nShader, "Color");

	glGenBuffers(1, &gui.m_uVBO);
	glGenBuffers(1, &gui.m_uElements);

	glGenVertexArrays(1, &gui.m_uVAO);
	glBindVertexArray(gui.m_uVAO);
	glBindBuffer(GL_ARRAY_BUFFER, gui.m_uVBO);
	glEnableVertexAttribArray(gui.m_nPosition);
	glEnableVertexAttribArray(gui.m_nUV);
	glEnableVertexAttribArray(gui.m_nColor);

#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))
	glVertexAttribPointer(gui.m_nPosition, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, pos));
	glVertexAttribPointer(gui.m_nUV, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, uv));
	glVertexAttribPointer(gui.m_nColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, col));
#undef OFFSETOF

	CreateFontsTexture();

	// Restore modified GL state
	glBindTexture(GL_TEXTURE_2D, last_texture);
	glBindBuffer(GL_ARRAY_BUFFER, last_array_buffer);
	glBindVertexArray(last_vertex_array);

	return true;
}
void AppClass::NewFrame()
{
	if (!gui.m_uFontTexture)
		CreateDeviceObjects();

	ImGuiIO& io = ImGui::GetIO();

	// Setup display size (every frame to accommodate for window resizing)
	float width = static_cast<float>(m_pWindow->GetWidth());
	float height = static_cast<float>(m_pWindow->GetHeight());
	io.DisplaySize = ImVec2(width, height);
	GLint m_viewport[4];
	glGetIntegerv(GL_VIEWPORT, m_viewport);
	io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
	/*
	io.DisplayFramebufferScale =
		ImVec2(	width > 0 ? ((float)m_viewport[2] / width) : 0,
				height > 0 ? ((float)m_viewport[3] / height) : 0);
	*/
	// Setup time step
	double dDelta = m_pSystem->GetDeltaTime(gui.m_nClock);
	io.DeltaTime = static_cast<float>(dDelta);
	gui.m_dTimeTotal += dDelta;

	//Calculate the position of the mouse and store it
	vector3 v3Mouse = m_pWindow->GetMouseCoordinates();
	v3Mouse += vector3(-9.0f,7.0f,0.0f);
	io.MousePos = ImVec2(v3Mouse.x, v3Mouse.y);
	/*
	POINT pt;
	GetCursorPos(&pt);
	int window_x, window_y;
	m_pWindow->GetPosition(&window_x, &window_y);
	*/
	
	//io.MousePos = ImVec2(static_cast<float>(pt.x - window_x - 9), static_cast<float>(pt.y - window_y + 7));
	//io.MousePos = ImVec2(static_cast<float>(pt.x - window_x - 9), static_cast<float>(pt.y - window_y));

	// Start the frame
	ImGui::NewFrame();
}
void AppClass::InitIMGUI(void)
{
	ImGuiIO& io = ImGui::GetIO();
	
	io.KeyMap[ImGuiKey_Tab] = VK_TAB;                       // Keyboard mapping. ImGui will use those indices to peek into the io.KeyDown[] array that we will update during the application lifetime.
	io.KeyMap[ImGuiKey_LeftArrow] = VK_LEFT;
	io.KeyMap[ImGuiKey_RightArrow] = VK_RIGHT;
	io.KeyMap[ImGuiKey_UpArrow] = VK_UP;
	io.KeyMap[ImGuiKey_DownArrow] = VK_DOWN;
	io.KeyMap[ImGuiKey_PageUp] = VK_PRIOR;
	io.KeyMap[ImGuiKey_PageDown] = VK_NEXT;
	io.KeyMap[ImGuiKey_Home] = VK_HOME;
	io.KeyMap[ImGuiKey_End] = VK_END;
	io.KeyMap[ImGuiKey_Delete] = VK_DELETE;
	io.KeyMap[ImGuiKey_Backspace] = VK_BACK;
	io.KeyMap[ImGuiKey_Enter] = VK_RETURN;
	io.KeyMap[ImGuiKey_Escape] = VK_ESCAPE;
	io.KeyMap[ImGuiKey_A] = 'A';
	io.KeyMap[ImGuiKey_C] = 'C';
	io.KeyMap[ImGuiKey_V] = 'V';
	io.KeyMap[ImGuiKey_X] = 'X';
	io.KeyMap[ImGuiKey_Y] = 'Y';
	io.KeyMap[ImGuiKey_Z] = 'Z';
	
	//gui.io.RenderDrawListsFn = RenderDrawListsFunction;       // Alternatively you can set this to NULL and call ImGui::GetDrawData() after ImGui::Render() to get the same ImDrawData pointer.
	io.RenderDrawListsFn = NULL;
	io.SetClipboardTextFn = NULL;
	io.GetClipboardTextFn = NULL;
	io.ClipboardUserData = NULL;
	io.ImeWindowHandle = m_pWindow->GetHandler();

	gui.m_nClock = m_pSystem->GenClock();
	m_pSystem->StartClock(gui.m_nClock);
}
void AppClass::ShutdownGUI(void)
{
	if (gui.m_uVAO) glDeleteVertexArrays(1, &gui.m_uVAO);
	if (gui.m_uVBO) glDeleteBuffers(1, &gui.m_uVBO);
	if (gui.m_uElements) glDeleteBuffers(1, &gui.m_uElements);
	gui.m_uVAO = gui.m_uVBO = gui.m_uElements = 0;

	if (gui.m_nShader && gui.m_nVertHandle) glDetachShader(gui.m_nShader, gui.m_nVertHandle);
	if (gui.m_nVertHandle) glDeleteShader(gui.m_nVertHandle);
	gui.m_nVertHandle = 0;

	if (gui.m_nShader && gui.m_nFragHandle) glDetachShader(gui.m_nShader, gui.m_nFragHandle);
	if (gui.m_nFragHandle) glDeleteShader(gui.m_nFragHandle);
	gui.m_nFragHandle = 0;

	if (gui.m_nShader) glDeleteProgram(gui.m_nShader);
	gui.m_nShader = 0;

	if (gui.m_uFontTexture)
	{
		glDeleteTextures(1, &gui.m_uFontTexture);
		ImGui::GetIO().Fonts->TexID = 0;
		gui.m_uFontTexture = 0;
	}

	ImGui::Shutdown();
}