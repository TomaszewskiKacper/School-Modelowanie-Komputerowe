#include "Cube.h"
#include <iostream>
#include <SFML/Graphics.hpp>

std::array<float, 6 * 6 * 5> Cube::s_vertices = {
       //x       y     z       u     v
		//+z
        -0.5f, -0.5f, -0.5f,  0.25f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.5f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.5f, 1.0f/3.0f,
		 0.5f,  0.5f, -0.5f,  0.5f, 1.0f/3.0f,
		-0.5f,  0.5f, -0.5f,  0.25f, 1.0f/3.0f,
		-0.5f, -0.5f, -0.5f,  0.25f, 0.0f,
		
		//-z
        -0.5f, -0.5f,  0.5f,  0.25f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.5f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.5f, 2.0f/3.0f,
		 0.5f,  0.5f,  0.5f,  0.5f, 2.0f/3.0f,
		-0.5f,  0.5f,  0.5f,  0.25f, 2.0f/3.0f,
		-0.5f, -0.5f,  0.5f,  0.25f, 1.0f,
		
		//-x
        -0.5f,  0.5f,  0.5f,  0.25f, 2.0f / 3.0f,
		-0.5f,  0.5f, -0.5f,  0.25f, 1.0f / 3.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f / 3.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f / 3.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 2.0f / 3.0f,
		-0.5f,  0.5f,  0.5f,  0.25f, 2.0f / 3.0f,
		
		//+x
         0.5f,  0.5f,  0.5f,  0.5f, 2.0f / 3.0f,
		 0.5f,  0.5f, -0.5f,  0.5f, 1.0f / 3.0f,
		 0.5f, -0.5f, -0.5f,  0.75f, 1.0f / 3.0f,
		 0.5f, -0.5f, -0.5f,  0.75f, 1.0f / 3.0f,
		 0.5f, -0.5f,  0.5f,  0.75f, 2.0f / 3.0f,
		 0.5f,  0.5f,  0.5f,  0.5f, 2.0f / 3.0f,
		 
		 //bottom
        -0.5f, -0.5f, -0.5f,  0.75f, 1.0f/3.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f / 3.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 2.0f / 3.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 2.0f / 3.0f,
		-0.5f, -0.5f,  0.5f,  0.75f, 2.0f / 3.0f,
		-0.5f, -0.5f, -0.5f,  0.75f, 1.0f / 3.0f,

		//top
        -0.5f,  0.5f, -0.5f,  0.25f, 1.0f/3.0f,
         0.5f,  0.5f, -0.5f,  0.5f, 1.0f / 3.0f,
         0.5f,  0.5f,  0.5f,  0.5f, 2.0f / 3.0f,
         0.5f,  0.5f,  0.5f,  0.5f, 2.0f / 3.0f,
        -0.5f,  0.5f,  0.5f,  0.25f, 2.0f / 3.0f,
        -0.5f,  0.5f, -0.5f,  0.25f, 1.0f / 3.0f
		
};


GLuint CreateTexture(const std::string& path) {
	//std::cout << path;
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	sf::Image image;
	if (image.loadFromFile(path)) {
		image.flipVertically();
		const sf::Vector2u size = image.getSize();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	return texture;
}



Cube::Cube(const std::string& texturePath)
{
	m_texture = CreateTexture(texturePath);
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(s_vertices), s_vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

Cube::Cube(const Cube& other)
{
	//std::cout<<"other : "<<other.Texture();
	m_texture = other.Texture();


	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(s_vertices), s_vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, m_texture);
}

Cube::Cube(Cube&& rhs) noexcept
	: m_vbo(std::exchange(rhs.m_vbo, 0))
	, m_vao(std::exchange(rhs.m_vao, 0))
	, m_texture(std::exchange(rhs.m_texture, 0)) {
}

Cube& Cube::operator=(Cube&& rhs) noexcept {
	if (&rhs == this) {
		return *this;
	}

	m_vbo = std::exchange(rhs.m_vbo, 0);
	m_vao = std::exchange(rhs.m_vao, 0);
	m_texture = std::exchange(rhs.m_texture, 0);

	return *this;
}

Cube::~Cube()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
}

