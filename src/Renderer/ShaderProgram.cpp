#include"ShaderProgram.h"
namespace Renderer {
	ShaderProgram::ShaderProgram(const string& vertexShader,
		const string& fragmentShader) {
		GLuint vertexShaderID;
		if (!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID)) {
			cerr << "Error vertexShader isn't compile!\n";
			return;
		}
		GLuint fragmentShaderID;
		if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID)) {
			cerr << "Error FRAGMENT_SHADER isn't compile!\n";
			glDeleteShader(vertexShaderID);
			return;
		}
		m_ID = glCreateProgram();
		    glAttachShader(m_ID, vertexShaderID);
			glAttachShader(m_ID, fragmentShaderID);
			glLinkProgram(m_ID);
			GLint success;
			glGetProgramiv(m_ID,GL_LINK_STATUS,&success);
			if (!success) {
				GLchar infolog[1024];
				glGetProgramInfoLog(m_ID, 1024, nullptr, infolog);
				cerr << "Error!Shader::LinkTime-error\n" << infolog << endl;
			}
			else {
				m_isCompiled = true;
			}
			glDeleteShader(vertexShaderID);
			glDeleteShader(fragmentShaderID);
	}
	bool ShaderProgram::createShader(const string& source, const GLenum shaderType	, GLuint& shaderID) {
		shaderID = glCreateShader(shaderType);
		const char* code = source.c_str();
		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);

		GLint success;

		glGetShaderiv(shaderID,GL_COMPILE_STATUS,&success);
		if (!success) {
			GLchar infolog[1024];
			glGetProgramInfoLog(shaderID, 1024, nullptr, infolog);
			cerr << "Error!Shader::CompileTime-error\n" <<infolog<< endl;
			return false;
		}
		return true;
}
	
	ShaderProgram::~ShaderProgram() {
		glDeleteProgram(m_ID);
	}
	void ShaderProgram::use()const {
		glUseProgram(m_ID);
	}
	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept {
		glDeleteProgram(m_ID);
		m_ID = shaderProgram.m_ID;
		m_isCompiled = shaderProgram.m_isCompiled;
		shaderProgram.m_ID = 0;
		shaderProgram.m_isCompiled = false;
		return *this;
	}
	ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept {
		m_ID = shaderProgram.m_ID;
		m_isCompiled = shaderProgram.m_isCompiled;
		shaderProgram.m_ID = 0;
		shaderProgram.m_isCompiled = false;
		 }


}
