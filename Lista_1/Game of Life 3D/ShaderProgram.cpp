#include "ShaderProgram.h"
#include <iostream>
#include <assert.h>

const char* ShaderProgram::s_vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 inPosition;
    layout (location = 1) in vec2 inTexCoords;
    
    out vec2 outTexCoords;

    uniform mat4 mvp;
    uniform mat4 model;
    
    void main() {
        gl_Position = mvp * model * vec4(inPosition, 1.0);
        outTexCoords = inTexCoords;
    }
)";
 const char* ShaderProgram::s_fragmentShaderSource = 
    R"(
    #version 330 core
    out vec4 fragColor;
    in vec2 outTexCoords;
    
    uniform sampler2D texture1;

    void main() {
        fragColor = texture(texture1, outTexCoords);
    }
)";

GLuint CreateShader(const GLchar* shaderSource, GLenum shaderType) {
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
    const GLuint vertexShader = CreateShader(s_vertexShaderSource, GL_VERTEX_SHADER);
    glAttachShader(m_programId, vertexShader);

    const GLuint fragmentShader = CreateShader(s_fragmentShaderSource, GL_FRAGMENT_SHADER);
    glAttachShader(m_programId, fragmentShader);

    glLinkProgram(m_programId);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    Use();
    SetInt("texture1", 0);
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
