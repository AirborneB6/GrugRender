#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>

#include "Renderer.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

//IMGUI SETUP
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Error %d: %s\n", error, description);
}


unsigned short WINDOW_WIDTH  = 640;
unsigned short WINDOW_HEIGHT = 480;

int main(void)
{
	glfwSetErrorCallback(glfw_error_callback);

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/*TEST DIFFERENT VERSIONS AND RUN MODE*/
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/*V-SYNC ENABLED?*/
	glfwSwapInterval(1);

	/*Initialize GLEW*/
	if (glewInit() != GLEW_OK)
	{
		/*IMPLEMENT ERROR REPORTS AS IN GRUG3D*/
		std::cout << "GLEW ERROR!\n";
	}
	std::cout << glGetString(GL_VERSION) << std::endl;

	// Setup ImGui binding
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls
	ImGui_ImplGlfwGL3_Init(window, true);

	// Setup style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	{
		//Actual app. Scope is used to call destructors before destroying window

		float trianglePositions[] =
		{
			0.0f   , 0.0f , 0.0f , 0.0f,
			100.0f , 0.0f , 1.0f , 0.0f,
			100.0f , 100.0f , 1.0f , 1.0f,
			0.0f   , 100.0f , 0.0f , 1.0f
		};

		unsigned int indices[] =
		{
			0,1,2,
			2,3,0
		};

		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glEnable(GL_BLEND));

		VertexBuffer vb(trianglePositions, 4 * 4 * sizeof(float));
		VertexArray va;
		va.bind();
		VertexBufferLayout layout;
		layout.push<float>(2, false);
		layout.push<float>(2, false);
		va.addBuffer(vb, layout);

		IndexBuffer ib(indices, 6);


		//MATHEMATICS ;)
		glm::mat4 proj = glm::ortho(0.0f , (float)WINDOW_WIDTH , 0.0f , (float)WINDOW_HEIGHT , -1.0f , 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));


		/*LOAD SHADER FROM SOURCE*/
		Shader shaderObj("res/shaders/Basic.shader");
		shaderObj.bind();

		va.unbind();
		shaderObj.unbind();
		ib.unbind();


		float r = 0.00f;
		float increment = 0.05f;

		//RENDERER TEST
		Renderer renderer;

		//TEXTURE TEST
		Texture texture("res/textures/texture.png");
		texture.bind();

		shaderObj.bind();
		shaderObj.setUniform1i("u_Texture", 0);


		//IMGUI TEST
		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		glm::vec3 translation1(200, 100, 0);
		glm::vec3 translation2(200, 100, 0);

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/*IMGUI Start Frame*/
			ImGui_ImplGlfwGL3_NewFrame();


			/* App-Render here */

			renderer.clear();
			shaderObj.bind();
			
			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), translation1);
				glm::mat4 mvp = proj * view * model;
				shaderObj.setUniformMat4f("u_MVP", mvp);

				renderer.draw(va, ib, shaderObj);
			}
			
			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), translation2);
				glm::mat4 mvp = proj * view * model;
				shaderObj.setUniformMat4f("u_MVP", mvp);

				renderer.draw(va, ib, shaderObj);
			}
			

			

			//shaderObj.setUniform4f("u_Color", r, 0.1f, 0.7f, 1.0f); //change color

			

			if (r > 1 || r < 0)
			{
				increment = -increment;
			}
			r += increment;

			{
				//IMGUI TEST WINDOW

				ImGui::SliderFloat("Model 1 X", &translation1[0], 0.0f, WINDOW_WIDTH);             // Edit 1 float using a slider from 0.0f to 1.0f    
				ImGui::SliderFloat("Model 1 Y", &translation1[1], 0.0f, WINDOW_HEIGHT);            // Edit 1 float using a slider from 0.0f to 1.0f    
				ImGui::SliderFloat("Model 2 X", &translation2[0], 0.0f, WINDOW_WIDTH);             // Edit 1 float using a slider from 0.0f to 1.0f    
				ImGui::SliderFloat("Model 2 Y", &translation2[1], 0.0f, WINDOW_HEIGHT);            // Edit 1 float using a slider from 0.0f to 1.0f    
				
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}

			/*IMGUI Render*/
			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
			/* Swap front and back buffers */
			glfwSwapBuffers(window);
			/* Poll for and process events */
			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;
}