#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "window.h"

//Conversion 
const float toRadians = 3.14159265f / 180.0f;

window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;

// Vertex Shader code
static const char* vShader = "Shaders/shader.vert";

// Fragment Shader
static const char* fShader = "Shaders/shader.frag";

void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	float vertices[] = {
		-1.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	
	Mesh *mesh = new Mesh();
	mesh->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(mesh);

	Mesh* mesh2 = new Mesh();
	mesh2->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(mesh2);
}


void CreateShaders()
{
	Shader* shader = new Shader;
	shader->CreateFromFiles(vShader, fShader);
	shaderList.push_back(shader);
}

int main()
{
	mainWindow = window(800, 600);
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	unsigned int uniformProjection = 0, uniformModel = 0;

	glm::mat4 projection = glm::perspective(45.0f, mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	// Loop until window closed
	while (!mainWindow.getShouldClose())
	{
		// Get + Handle user input events
		glfwPollEvents();

		// Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0]->UseShader();
		uniformModel = shaderList[0]->GetModelLocation();
		uniformProjection = shaderList[0]->GetProjectionLocation();

		//Triangle 1
		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//Triangle 2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		mainWindow.SwapBuffer();
	}

	return 0;
}