



#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <windows.h>
#include "includes/Shader.h"
void glfw_onError(int error, const char* description)
{
	// print message in Windows popup dialog box
	MessageBox(NULL, description, "GLFW error", MB_OK);
}
#define  GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
/*
//Ins and outs en shaders

const char* vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 aPos; // position has attribute position 0\n"
"out vec4 vertexColor; // specify a color output to the fragment shader\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos, 1.0); // we give a vec3 to vec4’s constructor\n"
"vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // output variable to dark-red\n"
"}\n\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 vertexColor; // input variable from vs (same name and type)\n"
"void main()\n"
"{\n"
" FragColor = vertexColor;\n"
"}\n\0";

*/

/*
//Uniforms shaders
const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor; // we set this variable in the OpenGL code.\n"
"void main()\n"
"{\n"
" FragColor = ourColor;\n"
"}\n\0";

//Uniforms shaders
const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor; // we set this variable in the OpenGL code.\n"
"void main()\n"
"{\n"
" FragColor = ourColor;\n"
"}\n\0";*/
/*
//Uniforms shaders
const char* vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 aPos; // position has attribute position 0\n"
"layout(location = 1) in vec3 aColor; // color has attribute position 1\n"
"out vec3 ourColor; // output a color to the fragment shader\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos, 1.0)\n;"
"ourColor = aColor; // set ourColor to input color from the vertex data\n"
"}\n\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
" FragColor = vec4(ourColor, 1.0);\n"
"}\n\0";
*/
/*
//Vertices del triángulo
float vertices[] = {
-0.5f, -0.5f, 0.0f,
0.5f, -0.5f, 0.0f,
0.0f, 0.5f, 0.0f
};
*/


float vertices[] = {
	// positions // colors
	0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
	-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
	0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f // top
};
unsigned int VBO, VAO;




void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void render()
{

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);



	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);



	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	Shader ourShader("./src/shaders/Shader1.vs", "./src/shaders/Shader2.fs");

	//Creación de polígono con VBO y VAO

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); //Triangulo Simple
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //Doble Triángulo Shader
	glEnableVertexAttribArray(0);


	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); //Doble Triángulo Shader
	glEnableVertexAttribArray(1);// Configuración para Doble Triángulo Shader

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);



	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
	
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);


		render();
		/*
		// update the uniform color
		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram,
			"ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		//
		*/
		ourShader.use();
		ourShader.setFloat("someUniform", 1.0f);
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;

}

