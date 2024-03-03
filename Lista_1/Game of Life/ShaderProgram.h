#pragma once
#include <glad/glad.h>
#include <glm.hpp>
#include <ext.hpp>

#include <string>

class ShaderProgram {
public:
	ShaderProgram();
	ShaderProgram(const ShaderProgram&) = delete;
	ShaderProgram& operator=(const ShaderProgram&) = delete;
	ShaderProgram(ShaderProgram&& rhs) noexcept;
	ShaderProgram& operator=(ShaderProgram&& rhs) noexcept;
	~ShaderProgram();

	void Use();


	void SetInt(const std::string_view name, int value);
	void SetMat4(const std::string_view name, const glm::mat4& value);

private:
	GLuint m_programId;

	static const char* s_vertexShaderSource;
	static const char* s_fragmentShaderSource;
};