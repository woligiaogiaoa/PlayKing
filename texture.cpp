#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <thread>

#include "stb_image.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


float lastX = 400, lastY = 300;
float yaw = -90.0f, pitch = 0.0f;

glm::vec3 direction;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

	if (firstMouse) // initially set to true
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
	lastX = xpos;
	lastY = ypos;

	const float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}

float fov = 45.0f;
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	// ReSharper disable once CppCStyleCast
	fov -= (float)(yoffset);
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;
}


float cubeVertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame


	
void  frame_buffer_size_callback(GLFWwindow* window, const int width, const int height)
{
	glViewport(0, 0, width, height);
}

float factor = 0.2f;


float cameraSpeed = 0.01f; // adjust accordingly



void process_input(GLFWwindow* window)
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	cameraSpeed = 2.5f * deltaTime;
	
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		factor += 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
		if (factor >= 1.0f)
			factor = 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		factor -= 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
		if (factor <= 0.0f)
			factor = 0.0f;
	}
	
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}




int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "open_gl", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << " window init failed" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cout << "glad init fail" << std::endl;
		glfwTerminate();
		return -1;
	}
	glViewport(0, 0, 800, 600);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);

	glfwSetScrollCallback(window, scroll_callback);

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	 int width, height, nrChannels;
	 stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("catok.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
			
	unsigned int texture1;
	glGenTextures(1, &texture1);	
	glBindTexture(GL_TEXTURE_2D, texture1);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	unsigned char* data1 = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
	if (data1)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture1" << std::endl;
	}
	stbi_image_free(data1);


	

	//- ------------------------data and program-----------------------

	float	vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};
	const char* textureVertextShader = "#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		//"layout(location = 1) in vec3 aColor;\n"
		"layout(location = 1) in vec2 aTexCoord;\n"
		//"out vec3 ourColor;\n"
		"out vec2 TexCoord;\n"
		"uniform mat4 model;\n"
		"uniform mat4 view;\n"	
		"uniform mat4 projection;\n"
		"void main()\n"
		"{\n"
		"gl_Position =projection * view *model *  vec4(aPos,1.0); \n"
		//"ourColor = aColor;\n"
		"TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
		"}\n";

	unsigned int vShaderTexture = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShaderTexture, 1, &textureVertextShader, nullptr);
	glCompileShader(vShaderTexture);
	

	
	unsigned int fShaderTexture = glCreateShader(GL_FRAGMENT_SHADER);
	

	const char* textureFragmentShader = "#version 330 core\n"
		"out vec4 FragColor;\n"
		//"in vec3 ourColor;\n"
		"in vec2 TexCoord;\n"
		"uniform sampler2D texture1;\n"
		"uniform sampler2D texture2;\n"
		"uniform float  factor;\n"
		"void main()\n"
		"{\n"
		//"FragColor = texture(ourTexture,TexCoord);\n"
		" FragColor = mix(texture(texture1,TexCoord), texture(texture2,TexCoord),0.0) ;\n"
	   // "FragColor =vec4(ourColor ,1.0f);\n"
		"}\n";

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	

	glShaderSource(fShaderTexture, 1, &textureFragmentShader, nullptr);
	glCompileShader(fShaderTexture);
	
	unsigned textureProgram = glCreateProgram();
	glAttachShader(textureProgram, vShaderTexture);
	glAttachShader(textureProgram, fShaderTexture);
	glLinkProgram(textureProgram);

	unsigned int vboTexture, vaoTexture;
	glGenBuffers(1, &vboTexture);
	glGenVertexArrays(1, &vaoTexture);
	glBindVertexArray(vaoTexture);
	glBindBuffer(GL_ARRAY_BUFFER, vboTexture);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5* sizeof(float), static_cast<void*>(0));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(3* sizeof(float)));
	glEnableVertexAttribArray(1);

	/*glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(6* sizeof(float)));
	glEnableVertexAttribArray(2);*/

	// position attribute
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);
	//// color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	//// texture coord attribute
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//glEnableVertexAttribArray(2);

	unsigned int ebo1;
	glGenBuffers(1, &ebo1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	
	
	//-------------------------------end--------------------------------

	glEnable(GL_DEPTH_TEST);
	
	while (!glfwWindowShouldClose(window))
	{
		process_input(window);
		//rendering here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glUniform1i(glGetUniformLocation(textureProgram, "texture1"), 0);
		glUniform1i(glGetUniformLocation(textureProgram, "texture2"), 1);
		glUniform1f(glGetUniformLocation(textureProgram, "factor"), factor);
		
		glUseProgram(textureProgram);

		glBindVertexArray(vaoTexture);


		//set a matrix

		glm::mat4 model = glm::mat4(1.0f); //diagonal matrix

		glm::mat4 view = glm::mat4(1.0f);

		glm::mat4 projection = glm::mat4(1.0f);

		

		glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		// ReSharper disable once CppInconsistentNaming

		//we are looking at a fixed position
		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		//projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);
		std::cout<<"perspective angle: "<<fov<<std::endl;
		unsigned int viewLocation = glGetUniformLocation(textureProgram, "view");
		//

		unsigned int modelLocation = glGetUniformLocation(textureProgram, "model");
	

		unsigned int projectionLocation = glGetUniformLocation(textureProgram, "projection");
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

	
		// model = glm::rotate(model, static_cast<float>(glfwGetTime()) *glm::radians(-55.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		
		

		float time = glfwGetTime();

		const float radius = 10.0f;
		float camX = sin(time) * radius;
		float camZ = cos(time) * radius;	
		//	"gl_Position =projection * view *model *  vec4(aPos,1.0); \n"
		
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);


		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
		
		for(unsigned int i=0;i<10;i++)
		{
			glm::mat4 model1 = glm::mat4(1.0f);
			//chapter1 : we translate and rotate it
			model1 = glm::translate(model1, cubePositions[i]);
			const float angle = static_cast<float>(i) * 20.0f; //½Ç¶È
			model1 = glm::rotate(model1, ((glm::radians(angle) + time) * 0.3f), glm::vec3(1.0f, 0.3f, 0.5f));

			


		
			// this time we want to use look at matrix
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model1));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		

		
	
		

		
		// ReSharper disable once CppZeroConstantCanBeReplacedWithNullptr
		//glDrawArrays(GL_TRIANGLES, 0,36);
		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}
