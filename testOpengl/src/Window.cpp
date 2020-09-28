#include "./ImGui/imgui.h"
#include "./ImGui/imgui_impl_glfw_gl3.h"
#include <stdio.h>
#include <GL/glew.h>    // This example is using gl3w to access OpenGL functions (because it is small). You may use glew/glad/glLoadGen/etc. whatever already works for you.
#include <GLFW/glfw3.h>
#include "Window.h"
#include <iostream>
#include <Windows.h>
#include "GameObject.h"
#include "ImGuiStyle.h"
static void MainMenuBar();
static void CreateGameObject();
static void RemoveGameObject();
static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Error %d: %s\n", error, description);
}

bool main_window = true;
bool objects_window = false;
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
	StyleImGui::Style;
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
			ImGui::Begin("Scene objects", &objects_window);
			for(int i = 0; i < 120; i++)
				ImGui::Text("Hello from another window!");
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
			if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Window"))
		{
			ImGui::MenuItem("Scene object", "CTRL+SHIFT+L", &objects_window);
			ImGui::MenuItem("Color Window", "CTRL+SHIFT+Y", &color_window);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("GameObjects"))
		{
			if (ImGui::MenuItem("Create GameObject"))
				CreateGameObject();

			if (ImGui::MenuItem("Remove GameObject"))
				RemoveGameObject();

			ImGui::EndMenu();
		}

		ImGui::Text("| FPS: %d", (int)ImGui::GetIO().Framerate);
		ImGui::EndMainMenuBar();
	}
}

static void CreateGameObject()
{
	GameObject::CreateGameObject();
}

static void RemoveGameObject()
{
	GameObject::RemoveGameObject();
}