#include "./ImGui/imgui.h"
#include "./ImGui/imgui_impl_glfw_gl3.h"
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Window.h"
#include <iostream>
#include <Windows.h>
#include <cstdio>
#include "GameObjects.h"
static void MainMenuBar();
static void CreateGameObject(char* name);
static void RemoveGameObject();
static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Error %d: %s\n", error, description);
}

bool main_window = true;
bool objects_window = false;
bool script_window = false;
bool color_window = false;

bool Window::Render()
{
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return false;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	GLFWwindow* window = glfwCreateWindow(1280, 720, "ImRender", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glewInit();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfwGL3_Init(window, true);
	//io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Verdana.ttf", 12);
	//io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Verdana.ttf", 10);
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Verdana.ttf", 14);
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Verdana.ttf", 18);
	ImGui::StyleColorsDark();
	ImGuiStyle * style = &ImGui::GetStyle();

	//style->WindowPadding = ImVec2(15, 15);
	style->WindowRounding = 5.0f;
	style->FramePadding = ImVec2(5, 5);
	style->FrameRounding = 4.0f;
	style->ItemSpacing = ImVec2(12, 8);
	style->ItemInnerSpacing = ImVec2(8, 6);
	style->IndentSpacing = 25.0f;
	style->ScrollbarSize = 15.0f;
	style->ScrollbarRounding = 9.0f;
	style->GrabMinSize = 5.0f;
	style->GrabRounding = 3.0f;

	style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	//style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
	//style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.23f, 0.23f, 0.23f, 0.75f);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.26f, 0.26f, 0.28f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.26f, 0.28f, 1.00f);
	style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.23f, 0.23f, 0.23f, 0.75f);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.26f, 0.28f, 1.00f);
	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	while (!glfwWindowShouldClose(window))
	{
		ImGui_ImplGlfwGL3_NewFrame();
		if (main_window)
		{
			MainMenuBar();
		}
		if (objects_window)
		{
			ImGui::SetNextWindowSize(ImVec2(230, 120), ImGuiCond_FirstUseEver);
			ImGui::Begin("GameObjects List", &objects_window);
			for (GameObjects::GameObject object : GameObjects::getGameObjects()) {
				ImGui::Text(object.name);
				printf("new object: %s\n", object.name);
			}
			printf("\n-\n");
			ImGui::End();
		}
		if (script_window)
		{
			ImGui::SetNextWindowSize(ImVec2(230, 120), ImGuiCond_FirstUseEver);
			ImGui::Begin("Scripts", &objects_window);
			ImGui::End();
		}
		if (color_window)
		{
			ImGui::SetNextWindowSize(ImVec2(230, 120), ImGuiCond_FirstUseEver);
			ImGui::Begin("Change ClearColor", &color_window);
			ImGui::ColorEdit3("clear color", (float*)&clear_color);
			ImGui::End();
		}
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// Cleanup
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();

	return true;
}

static void MainMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New project")) {}
			if (ImGui::MenuItem("Open project")) {}
			if (ImGui::MenuItem("Save project")) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Window"))
		{
			ImGui::MenuItem("GameObjects List", NULL, &objects_window);
			ImGui::MenuItem("Clear color", NULL, &color_window);
			ImGui::MenuItem("Project scripts", NULL, &script_window);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("GameObjects"))
		{
			static char name[128] = "";
			ImGui::InputText("name", name, IM_ARRAYSIZE(name));
			if (ImGui::MenuItem("Create new GameObject")) {
				int id = GameObjects::getGameObjects().size() + 1;
				GameObjects::CreateGameObject(name, id);
			}

			ImGui::EndMenu();
		}

		ImGui::Text("| FPS: %d", (int)ImGui::GetIO().Framerate);
		ImGui::EndMainMenuBar();
	}
} 
static void CreateGameObject(char* name)
{
	int id = GameObjects::getGameObjects().size() + 1;
	GameObjects::CreateGameObject(name, id);
}

static void RemoveGameObject()
{
	GameObjects::RemoveGameObject();
}