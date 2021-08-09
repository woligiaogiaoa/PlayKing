#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <thread>

#include "stb_image.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>




void  frame_buffer_size_callback(GLFWwindow* window, const int width, const int height)
{
	glViewport(0, 0, width, height);
}

float factor = 0.2f;

void process_input(GLFWwindow* window)
{
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

			glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);

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
	unsigned char* data = stbi_load("cat.jpg", &width, &height, &nrChannels, 0);
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

	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f    // top left 
	};
	const char* textureVertextShader = "#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"layout(location = 1) in vec3 aColor;\n"
		"layout(location = 2) in vec2 aTexCoord;\n"
		"out vec3 ourColor;\n"
		"out vec2 TexCoord;\n"
		"uniform mat4 transform;\n"
		"void main()\n"
		"{\n"
		"gl_Position =transform *  vec4(aPos,1.0);\n"
		"ourColor = aColor;\n"
		"TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
		"}\n";

	unsigned int vShaderTexture = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShaderTexture, 1, &textureVertextShader, nullptr);
	glCompileShader(vShaderTexture);
	

	
	unsigned int fShaderTexture = glCreateShader(GL_FRAGMENT_SHADER);
	

	const char* textureFragmentShader = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec3 ourColor;\n"
		"in vec2 TexCoord;\n"
		"uniform sampler2D texture1;\n"
		"uniform sampler2D texture2;\n"
		"uniform float  factor;\n"
		"void main()\n"
		"{\n"
		//"FragColor = texture(ourTexture,TexCoord);\n"
		" FragColor = mix(texture(texture1,TexCoord), texture(texture2,TexCoord),0.0) * vec4(ourColor,1.0);\n"
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), static_cast<void*>(0));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(3* sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(6* sizeof(float)));
	glEnableVertexAttribArray(2);

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
	
	while (!glfwWindowShouldClose(window))
	{
		process_input(window);
		//rendering here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1);
		
		glUseProgram(textureProgram);


		//set a matrix

		glm::mat4 trans = glm::mat4(1.0f); //diagonal matrix
		trans = glm::translate(trans, glm::vec3(0.5f,-0.5f,0.0f));
		trans = glm::rotate(trans, static_cast<float>(sin(glfwGetTime())), glm::vec3(0.0f,0.0f,1.0f)); 
		
		
		
		
		// ReSharper disable once CppInconsistentNaming
		unsigned int transformLocation = glGetUniformLocation(textureProgram, "transform");

		glUniformMatrix4fv(transformLocation, 1, GL_FALSE,glm::value_ptr(trans) );
		
		glUniform1i(glGetUniformLocation(textureProgram, "texture1"), 0);
		glUniform1i(glGetUniformLocation(textureProgram, "texture2"), 1);
		glUniform1f(glGetUniformLocation(textureProgram, "factor"), factor);
		

		glBindVertexArray(vaoTexture);
		// ReSharper disable once CppZeroConstantCanBeReplacedWithNullptr
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}
