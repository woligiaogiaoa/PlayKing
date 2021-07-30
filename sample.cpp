#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <thread>

void  frame_buffer_size_callback(GLFWwindow * window , const int width, const int height )
{
	glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window)
{
	if(glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}


// ReSharper disable once IdentifierTypo
bool usev1 = true;

float vertices2[] = {
		-1.0f,0.5f,0.0f,
		1.0f,0.5f,0.0f,
		0.0f,-1.0f,0.0f
};


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "open_gl", nullptr, nullptr);
	if(window==nullptr)
	{
		std::cout << " window init failed" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cout << "glad init fail" << std::endl;
		glfwTerminate();
		return -1;
	}
	glViewport(0, 0, 800, 600);
	



	
	// ReSharper disable once CppInconsistentNaming
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	// ReSharper disable once CppInconsistentNaming
	const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);

	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        glfwTerminate();
		return -1;
		
	}

	const char * fragmentShaderSource ="#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor= vec4(1.0f,0.5f,0.2f,1.0f);\n"
		"}\0";
	
	// ReSharper disable once CppInconsistentNaming
	// ReSharper disable once CppLocalVariableMayBeConst
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);


	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);

	glCompileShader(fragmentShader);

	int fragmentShaderSuccess;
		
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentShaderSuccess);
	
	if(!fragmentShaderSuccess)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		glfwTerminate();
		return -1;
	}

	// ReSharper disable once CppLocalVariableMayBeConst
	unsigned int program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(program, 512, nullptr, infoLog);
		glfwTerminate();
		std::cout << "ERROR::LINKER::PROGRAM\n" << infoLog << std::endl;
		return -1;
	}

	const unsigned int program_yell = glCreateProgram();
	
	glAttachShader(program_yell, vertexShader);

	const char* fragmentShaderSource1= "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor= vec4(0.4f,0.25f,0.72f,1.0f);\n"
		"}\0";

	const unsigned int shader_yell = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shader_yell, 1, &fragmentShaderSource1, nullptr);
	glCompileShader(shader_yell);

	glGetShaderiv(shader_yell, GL_COMPILE_STATUS, &fragmentShaderSuccess);

	if (!fragmentShaderSuccess)
	{
		glGetShaderInfoLog(shader_yell, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		glfwTerminate();
		return -1;
	}

	glAttachShader(program_yell, shader_yell);
	glLinkProgram(program_yell);

	glDeleteShader(shader_yell);
	
	
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	// ReSharper disable once CppInconsistentNaming
	unsigned int VBO;

	// ReSharper disable once CppInconsistentNaming
	unsigned int VAO;

	glGenVertexArrays(1, &VAO); 

	glGenBuffers(1, &VBO);


	int now = 3; 
	int max = 10;

	unsigned int ebo;

	glGenBuffers(1, &ebo);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	// ReSharper disable once CppZeroConstantCanBeReplacedWithNullptr
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(0));
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	//unbind vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	//unbinf vao
	glBindVertexArray(0);

	unsigned int vao1,vbo1;

	glGenVertexArrays(1,&vao1);

	glGenBuffers(1, &vbo1);

	glBindVertexArray(vao1);

	glBindBuffer(GL_ARRAY_BUFFER, vbo1);

	float vertices1 [] = {
		-1.0f,0.5f,0.0f,
		1.0f,0.5f,0.0f,
		0.0f,1.0f,0.0f
	}; 
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

	// ReSharper disable once CppZeroConstantCanBeReplacedWithNullptr
	//glVertexAttribIPointer(0, 3, GL_FLOAT,  GL_FALSE, 3*sizeof(float),  static_cast<void*>(0));

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),  static_cast<void*>(0));

	glEnableVertexAttribArray(0);

	//unbind vao1 vbo1
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindVertexArray(0);


	glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);
	while(!glfwWindowShouldClose(window))
	{
		process_input(window);
		//rendering here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		

		//data ready draw data

	
		

		glUseProgram(program);

		glBindVertexArray(VAO);

		//glDrawArrays(GL_TRIANGLES, 0, 3);
		// ReSharper disable once CppZeroConstantCanBeReplacedWithNullptr
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		glUseProgram(program_yell);

		//avo1 init with up data 
		if(usev1)
		{
			glBindVertexArray(vao1);
			glBindBuffer(GL_ARRAY_BUFFER, vbo1);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

			// ReSharper disable once CppZeroConstantCanBeReplacedWithNullptr
			//glVertexAttribIPointer(0, 3, GL_FLOAT,  GL_FALSE, 3*sizeof(float),  static_cast<void*>(0));

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(0));
			glEnableVertexAttribArray(0);
			//unbind vbo
			glBindBuffer(GL_ARRAY_BUFFER, 0);


			//unbinf vao
			glBindVertexArray(0);
			
			
			
		}else
		{
			glBindVertexArray(vao1);
			glBindBuffer(GL_ARRAY_BUFFER, vbo1);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

			// ReSharper disable once CppZeroConstantCanBeReplacedWithNullptr
			//glVertexAttribIPointer(0, 3, GL_FLOAT,  GL_FALSE, 3*sizeof(float),  static_cast<void*>(0));

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(0));
			glEnableVertexAttribArray(0);
			//unbind vbo
			glBindBuffer(GL_ARRAY_BUFFER, 0);


			//unbinf vao
			glBindVertexArray(0);


		}
		usev1 = !usev1;

		
		glBindVertexArray(vao1);
		
		glDrawArrays(GL_TRIANGLES, 0, 3);

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glBindVertexArray(VAO);
	
	//unbind ebo bound in vao before
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//unbind VAO
	glBindVertexArray(0);



	
	
	glDeleteProgram(program);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteProgram(program_yell);
	glDeleteBuffers(1, &vbo1);
	glDeleteVertexArrays(1, &vao1);
	

	glfwTerminate();
	return  0;
	
	
}
