//#include <iostream>
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//#include <thread>
//#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>
//#include <gtc/type_ptr.hpp>
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//
//void  frame_buffer_size_callback(GLFWwindow * window , const int width, const int height )
//{
//	glViewport(0, 0, width, height);
//}
//
//void process_input(GLFWwindow* window)
//{
//	if(glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS)
//	{
//		glfwSetWindowShouldClose(window, true);
//	}
//}
//
//
//// ReSharper disable once IdentifierTypo
//bool usev1 = true;
//
//float vertices2[] = {
//		-1.0f,0.5f,0.0f,
//		1.0f,0.5f,0.0f,
//		0.0f,-1.0f,0.0f
//};
//
//
//int main()
//{
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	GLFWwindow* window = glfwCreateWindow(800, 600, "open_gl", nullptr, nullptr);
//	if(window==nullptr)
//	{
//		std::cout << " window init failed" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
//	{
//		std::cout << "glad init fail" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glViewport(0, 0, 800, 600);
//	
//
//
//
//	
//	// ReSharper disable once CppInconsistentNaming
//	const char* vertexShaderSource = "#version 330 core\n"
//		"layout (location = 0) in vec3 aPos;\n"
//		"out vec4 colorFromVertex;\n"
//		"void main()\n"
//		"{\n"
//		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//		"   colorFromVertex=vec4(0.1f,0.1f,0.3f,1.0f);\n"
//		"}\0";
//
//	// ReSharper disable once CppInconsistentNaming
//	const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//
//	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
//
//	glCompileShader(vertexShader);
//
//	int success;
//	char infoLog[512];
//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//	if(!success)
//	{
//		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
//		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//        glfwTerminate();
//		return -1;
//		
//	}
//
//	const char * fragmentShaderSource ="#version 330 core\n"
//		"out vec4 FragColor;\n"
//		"void main()\n"
//		"{\n"
//		"   FragColor= vec4(1.0f,0.5f,0.2f,1.0f);\n"
//		"}\0";
//	
//	// ReSharper disable once CppInconsistentNaming
//	// ReSharper disable once CppLocalVariableMayBeConst
//	//---------------------------------compile colorfulshader link program
//	float verticesColorful[] = {
//		// positions                         // colors
//		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
//		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
//		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
//	};
//
//	int newProgram = glCreateProgram();
//
//	// ReSharper disable once IdentifierTypo
//	const char* fragmentColorfulShaderSource = "#version 330 core\n"
//		"out vec4 FragColor;\n"
//		"in vec3 colorFromVertexShader;\n"
//		"void main()\n"
//		"{\n"
//		"   FragColor= vec4(colorFromVertexShader,1.0f);\n"
//		"}\0";
//
//
//	unsigned int colorShader = glCreateShader(GL_FRAGMENT_SHADER);
//
//	glShaderSource(colorShader, 1, &fragmentColorfulShaderSource, nullptr);
//
//	glCompileShader(colorShader);
//
//	const char* twoAttriShader =  "#version 330 core\n"
//		"layout (location = 0) in vec3 aPos;\n"
//		"layout (location = 1) in vec3 aColor;\n"
//		"out vec3 colorFromVertexShader;\n"
//	
//		"void main()\n"
//		"{\n"
//		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//		"   colorFromVertexShader=vec3(aColor);\n"
//		"}\0";
//
//	unsigned int colorShader1 = glCreateShader(GL_VERTEX_SHADER);
//
//	glShaderSource(colorShader1, 1, &twoAttriShader, nullptr);
//
//	glCompileShader(colorShader1);
//
//	glAttachShader(newProgram, colorShader1);
//	glAttachShader(newProgram, colorShader);
//	glLinkProgram(newProgram);
//
//	unsigned int vao2, vbo2;
//
//	glGenBuffers(1, &vbo2);
//	glGenVertexArrays(1, &vao2); 
//
//	glBindVertexArray(vao2);
//	glBindBuffer(GL_ARRAY_BUFFER,vbo2);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesColorful), verticesColorful, GL_STATIC_DRAW);
//	// ReSharper disable once CppZeroConstantCanBeReplacedWithNullptr
//	glVertexAttribPointer(0,  3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), static_cast<void*>(0) );
//	glEnableVertexAttribArray(0);
//
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0); 
//
//	
//	
//
//
//
//
//
//	//-------------------------------------end
//	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//
//
//	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
//
//
//	glCompileShader(fragmentShader);
//
//	int fragmentShaderSuccess;
//		
//	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentShaderSuccess);
//	
//	if(!fragmentShaderSuccess)
//	{
//		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
//		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//
//	// ReSharper disable once CppLocalVariableMayBeConst
//	unsigned int program = glCreateProgram();
//	glAttachShader(program, vertexShader);
//	glAttachShader(program, fragmentShader);
//	glLinkProgram(program);
//	glGetProgramiv(program, GL_LINK_STATUS, &success);
//	if(!success)
//	{
//		glGetProgramInfoLog(program, 512, nullptr, infoLog);
//		glfwTerminate();
//		std::cout << "ERROR::LINKER::PROGRAM\n" << infoLog << std::endl;
//		return -1;
//	}
//
//	const unsigned int program_yell = glCreateProgram();
//	
//	glAttachShader(program_yell, vertexShader);
//
//	const char* fragmentShaderSource1= "#version 330 core\n"
//		"out vec4 FragColor;\n"
//		"in vec4 colorFromVertex;\n"
//		"uniform vec4 colorUniform;\n"
//		"void main()\n"
//		"{\n"
//	/*	"   FragColor= vec4(0.4f,0.25f,0.72f,1.0f);\n"*/
//		/*"   FragColor= vec4(colorFromVertex);\n"*/
//	
//		"   FragColor= vec4(colorUniform);\n"
//		"}\0";
//
//	const unsigned int shader_yell = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(shader_yell, 1, &fragmentShaderSource1, nullptr);
//	glCompileShader(shader_yell);
//
//	glGetShaderiv(shader_yell, GL_COMPILE_STATUS, &fragmentShaderSuccess);
//
//	if (!fragmentShaderSuccess)
//	{
//		glGetShaderInfoLog(shader_yell, 512, nullptr, infoLog);
//		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//
//	glAttachShader(program_yell, shader_yell);
//	glLinkProgram(program_yell);
//
//	glDeleteShader(shader_yell);
//	
//	
//	
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//
//	float vertices[] = {
//		 0.5f,  0.5f, 0.0f,  // top right
//		 0.5f, -0.5f, 0.0f,  // bottom right
//		-0.5f, -0.5f, 0.0f,  // bottom left
//		-0.5f,  0.5f, 0.0f   // top left 
//	};
//	unsigned int indices[] = {  // note that we start from 0!
//		0, 1, 3,   // first triangle
//		1, 2, 3    // second triangle
//	};
//
//	// ReSharper disable once CppInconsistentNaming
//	unsigned int VBO;
//
//	// ReSharper disable once CppInconsistentNaming
//	unsigned int VAO;
//
//	glGenVertexArrays(1, &VAO); 
//
//	glGenBuffers(1, &VBO);
//
//
//
//
//	unsigned int ebo;
//
//	glGenBuffers(1, &ebo);
//
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//
//	// ReSharper disable once CppZeroConstantCanBeReplacedWithNullptr
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(0));
//	
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	glEnableVertexAttribArray(0);
//
//	//unbind vbo
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//
//	//unbinf vao
//	glBindVertexArray(0);
//
//	unsigned int vao1,vbo1;
//
//	glGenVertexArrays(1,&vao1);
//
//	glGenBuffers(1, &vbo1);
//
//	glBindVertexArray(vao1);
//
//	glBindBuffer(GL_ARRAY_BUFFER, vbo1);
//
//	float vertices1 [] = {
//		-1.0f,0.5f,0.0f,
//		1.0f,0.5f,0.0f,
//		0.0f,1.0f,0.0f
//	}; 
//	
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
//
//	// ReSharper disable once CppZeroConstantCanBeReplacedWithNullptr
//	//glVertexAttribIPointer(0, 3, GL_FLOAT,  GL_FALSE, 3*sizeof(float),  static_cast<void*>(0));
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),  static_cast<void*>(0));
//
//	glEnableVertexAttribArray(0);
//
//	//unbind vao1 vbo1
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	
//	glBindVertexArray(0);
//
//
//	glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);
//	while(!glfwWindowShouldClose(window))
//	{
//		process_input(window);
//		//rendering here
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//		
//
//		//data ready draw data
//
//		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
//
//		glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
//		glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
//
//		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
//		glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
//
//		glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
//
//		const float radius = 10.0f;
//		float camX = sin(glfwGetTime()) * radius;
//		float camZ = cos(glfwGetTime()) * radius;
//		glm::mat4 view;
//		view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
//
//	
//		
//
//		glUseProgram(program);
//
//		glBindVertexArray(VAO);
//
//		//glDrawArrays(GL_TRIANGLES, 0, 3);
//		// ReSharper disable once CppZeroConstantCanBeReplacedWithNullptr
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//		
//
//
//		glUseProgram(program_yell);
//		//set uniform here
//		//
//		// NOLINT(bugprone-narrowing-conversions)
//		const float time = glfwGetTime();  
//		
//		// ReSharper disable once CppLocalVariableMayBeConst
//		float timeColor = (sin(time) / 2.0f) + 0.5f;   // 0-1f
//
//		// ReSharper disable once CppLocalVariableMayBeConst
//		int uniformColorLocation = glGetUniformLocation(program_yell, "colorUniform");
//
//		glUniform4f(uniformColorLocation, 0.0f, timeColor, 0.0f, 1.0f);
//		
//
//		//avo1 init with up data 
//		if(usev1)
//		{
//			glBindVertexArray(vao1);
//			glBindBuffer(GL_ARRAY_BUFFER, vbo1);
//			float vertices1New[] = {
//		-1.0f,0.5f,timeColor,
//		1.0f,0.5f,timeColor,
//		0.0f,1.0f,timeColor
//			};
//			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1New), vertices1New, GL_STATIC_DRAW);
//
//			// ReSharper disable once CppZeroConstantCanBeReplacedWithNullptr
//			//glVertexAttribIPointer(0, 3, GL_FLOAT,  GL_FALSE, 3*sizeof(float),  static_cast<void*>(0));
//
//			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(0));
//			glEnableVertexAttribArray(0);
//			//unbind vbo
//			glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//
//			//unbinf vao
//			glBindVertexArray(0);
//			
//			
//			
//		}else
//		{
//			glBindVertexArray(vao1);
//			glBindBuffer(GL_ARRAY_BUFFER, vbo1);
//			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
//
//			// ReSharper disable once CppZeroConstantCanBeReplacedWithNullptr
//			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(0));
//			glEnableVertexAttribArray(0);
//			//unbind vbo to prevent data from being modified again
//			glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//
//			//also unbind vao here 
//			glBindVertexArray(0);
//
//
//		}
//		usev1 = !usev1;
//
//		
//		glBindVertexArray(vao1);
//		
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//
//
//		//draw here a new---------------------start
//		
//		glUseProgram(newProgram);
//		glBindVertexArray(vao2);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//
//
//		//------------------------------------------end
//
//		//draw a texture
//		unsigned int texture;
//		glGenTextures(1, &texture);
//		glBindTexture(GL_TEXTURE_2D, texture);
//		// set the texture wrapping/filtering options (on the currently bound texture object)
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//		// load and generate the texture
//		int width, height, nrChannels;
//		unsigned char* data = stbi_load("resources/container.jpg", &width, &height, &nrChannels, 0);
//		if (data)
//		{
//			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//			glGenerateMipmap(GL_TEXTURE_2D);
//		}
//		else
//		{
//			std::cout << "Failed to load texture" << std::endl;
//		}
//		stbi_image_free(data);
//
//
//		float verticesTexture[] = {
//			// positions          // colors           // texture coords
//			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
//			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
//			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
//			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
//		};
//
//		const char* textureVertextShader = "#version 330 core\n"
//			"layout(location = 0) in vec3 aPos;\n"
//			"layout(location = 1) in vec3 aColor;\n"
//			"layout(location = 2) in vec2 aTexCoord;\n"
//			"out vec3 ourColor;\n"
//			"out vec2 TexCoord;\n"
//			"void main()\n"
//			"{\n"
//			"gl_Position = vec4(aPos, 1.0);\n"
//			"ourColor = aColor;\n"
//			"TexCoord = aTexCoord;\n"
//			"}\n";
//
//		unsigned int vShaderTexture, fShaderTexture;
//
//		vShaderTexture=glCreateShader(GL_VERTEX_SHADER); 
//		fShaderTexture=glCreateShader(GL_FRAGMENT_SHADER);
//		glShaderSource(vShaderTexture, 1, &textureVertextShader, nullptr);
//
//		const char* textureFragmentShader = "#version 330 core\n"
//			"out vec4 FragColor;\n"
//			"in vec3 ourColor;\n"
//			"in vec2 TexCoord;\n"
//			"uniform sampler2D ourTexture;\n"
//			"void main()\n"
//			"{\n"
//			"FragColor = texture(ourTexture, TexCoord);\n"
//			"}\n";
//
//		fShaderTexture=glCreateShader(GL_FRAGMENT_SHADER);
//		glShaderSource(fShaderTexture, 1, &textureFragmentShader, nullptr);
//		glCompileShader(fShaderTexture);
//		glCompileShader(vShaderTexture);
//		unsigned textureProgram = glCreateProgram();
//		glAttachShader(textureProgram, vShaderTexture);
//		glAttachShader(textureProgram, fShaderTexture);
//
//		unsigned int vboTexture, vaoTexture;
//		glGenBuffers(1, &vboTexture);
//		glGenVertexArrays(1, &vaoTexture);
//		glBindVertexArray(vaoTexture);
//		glBindBuffer(GL_ARRAY_BUFFER, vboTexture);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTexture), verticesTexture, GL_STATIC_DRAW);
//
//		unsigned int ebo1;
//		glGenBuffers(1, &ebo1); 
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo1);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//		/// float verticesTexture[] = {
//		//	// positions          // colors           // texture coords
//		//	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
//		//	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
//		//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
//		//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
//		//};
//
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), static_cast<void*>(0));
//		glEnableVertexAttribArray(0);
//
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(3));
//		glEnableVertexAttribArray(1);
//
//		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(6));
//		glEnableVertexAttribArray(2);
//
//		glBindTexture(GL_TEXTURE_2D, texture);
//		glBindVertexArray(vaoTexture);
//		glUseProgram(textureProgram);
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//		
//
//		/// <summary>
//		/// </summary>
//		/// <returns></returns>
//		
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//
//	glBindVertexArray(VAO);
//	
//	//unbind ebo bound in vao before
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//	//unbind VAO
//	glBindVertexArray(0);
//
//	glDeleteProgram(program);
//	glDeleteBuffers(1, &VBO);
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteProgram(program_yell);
//	glDeleteBuffers(1, &vbo1);
//	glDeleteVertexArrays(1, &vao1);
//
//	
//	glDeleteShader(colorShader);
//	glDeleteShader(colorShader1);
//	glDeleteProgram(newProgram);
//	glDeleteBuffers(1, &vbo2);
//	glDeleteVertexArrays(1, &vbo2);
//	
//	
//
//	glfwTerminate();
//	return  0;
//	
//	
//}
