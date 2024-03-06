#pragma once
#include <array>
#include <glad/glad.h>

class Cell
{
public:
	Cell();
	Cell(size_t coord_x, size_t coord_y, size_t Width, size_t Height);
	~Cell();

	Cell& operator=(const Cell&) = delete;
	Cell& operator=(Cell&&) noexcept;
	//Cell(Cell&&) noexcept;

	GLuint Vbo() const { return m_vbo; }
	GLuint Vao() const { return m_vao; }
	bool Is_Alive() { return m_alive; }

	void Set_Alive(bool state) { m_alive = state; }

private:
	GLuint m_vbo{ 0 };
	GLuint m_vao{ 0 };
	bool m_alive;
	std::array<float, 6 * 3> m_vertices;
};

