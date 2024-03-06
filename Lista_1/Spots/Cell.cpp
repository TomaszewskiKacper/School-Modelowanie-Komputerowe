#include "Cell.h"

Cell::Cell() : 
	m_alive(true)
{
	m_vertices = { 0 };
}

Cell::Cell(size_t coord_x, size_t coord_y, size_t m_size_x, size_t m_size_y) : 
	m_alive(true)
{
	//Area on screen from -1 to 1
	//Convert [x][y] into coordinates on screen
	float x = ((coord_x * 2.0f) / m_size_x) - 1.0f;
	float y = ((coord_y * 2.0f) / m_size_y) - 1.0f;
	float m_cell_width = 2.0f / m_size_x;
	float m_cell_height = 2.0f / m_size_y;

	//Use converted coordinates to create vertices of 2 triangles that create the cell
	 m_vertices = {
		//	x	y	z
			x,					y,					0,	//top left
			x + m_cell_width,	y + m_cell_height,	0,	//bottom right
			x,					y + m_cell_height,	0,	//bottom left
			x,					y,					0,	//top left
			x + m_cell_width,	y,					0,	//top right
			x + m_cell_width,	y + m_cell_height,	0	//bottom left
	};


	 //Generate VBO, VAO
	 glGenVertexArrays(1, &m_vao);
	 glGenBuffers(1, &m_vbo);

	 glBindVertexArray(m_vao);

	 glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	 glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices.data(), GL_STATIC_DRAW);

	 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	 glEnableVertexAttribArray(0);

	 glBindBuffer(GL_ARRAY_BUFFER, 0);
	 glBindVertexArray(0);

}

Cell::~Cell()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
}

Cell& Cell::operator=(Cell&& rhs) noexcept {
	if (&rhs == this) {
		return *this;
	}

	m_vbo = std::exchange(rhs.m_vbo, 0);
	m_vao = std::exchange(rhs.m_vao, 0);

	return *this;
}

