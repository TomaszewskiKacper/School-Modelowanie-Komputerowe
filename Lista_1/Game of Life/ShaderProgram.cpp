#include "ShaderProgram.h"
#include <iostream>
#include <assert.h>

const char* ShaderProgram::s_vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 position;
    
    void main() {
        gl_Position = vec4(position, 1.0);
    }
)";
 const char* ShaderProgram::s_fragmentShaderSource = R"(
    #version 330 core
    out vec4 fragmentColor;
    
    void main() {
        fragmentColor = vec4(0.0, 1.0, 1.0, 1.0);
    }
)";


GLuint CreateShaders(const GLchar* shaderSource, GLenum shaderType) {
    const GLuint shaderId = glCreateShader(shaderType);
    if (!shaderId) {
        return 0;
    }

    glShaderSource(shaderId, 1, &shaderSource, nullptr);
    glCompileShader(shaderId);

    return shaderId;
}

ShaderProgram::ShaderProgram()
    :m_programId(glCreateProgram())
{
    const GLuint vertexShader = CreateShaders(s_vertexShaderSource, GL_VERTEX_SHADER);
    glAttachShader(m_programId, vertexShader);

    const GLuint fragmentShader = CreateShaders(s_fragmentShaderSource, GL_FRAGMENT_SHADER);
    glAttachShader(m_programId, fragmentShader);

    glLinkProgram(m_programId);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    Use();
}

ShaderProgram::ShaderProgram(ShaderProgram&& rhs) noexcept
	: m_programId(std::exchange(rhs.m_programId, 0)) {
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& rhs) noexcept {
	if (&rhs == this) {
		return *this;
	}

	m_programId = std::exchange(rhs.m_programId, 0);

	return *this;
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::Use()
{
    glUseProgram(m_programId);
}

void ShaderProgram::SetInt(const std::string_view name, int value)
{
    glUniform1i(glGetUniformLocation(m_programId, name.data()), value);
}

void ShaderProgram::SetMat4(const std::string_view name, const glm::mat4& value)
{
    glUniformMatrix4fv(glGetUniformLocation(m_programId, name.data()), 1, GL_FALSE, glm::value_ptr(value));
}
