#pragma once
#include<iostream>
#include<string>
#include<glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;
namespace Renderer {
	class ShaderProgram {
	public:
		ShaderProgram(const string& vertexShader,
			const string& fragmentShader);
		 ~ShaderProgram();
		 bool isCompiled()const { return m_isCompiled; }
		 void use()const;
		 ShaderProgram() = delete;
		 ShaderProgram(ShaderProgram&) = delete;
		 ShaderProgram& operator=(const ShaderProgram&) = delete;
		 ShaderProgram& operator =(ShaderProgram&& shaderProgram)noexcept;//move constructor
		 ShaderProgram(ShaderProgram&& shaderProgram)noexcept;//move constructor
		
		 

	private:
		bool createShader(const string& source, const GLenum shaderType, GLuint& shaderID);
		bool m_isCompiled = false;
		GLuint m_ID = 0 ;

	};
}
