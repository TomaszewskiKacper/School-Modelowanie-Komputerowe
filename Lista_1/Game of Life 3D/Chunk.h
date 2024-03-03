#pragma once
#include "Cube.h"
#include "ShaderProgram.h"
#include "CubePalette.h"
#include "Camera.h"
#include <stdlib.h>

#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <vector>

template <uint8_t Depth, uint8_t Width, uint8_t Height>
class Chunk {
	struct CubeData {
		Cube::Type m_type{ Cube::Type::None };
		bool m_isVisible{ true };
	};

	using FlattenData_t = std::array<CubeData, Depth * Width * Height>;
public:
	Chunk(const glm::vec2& origin, CubePalette& palette);


	void First();

	void Update();

	void Update_v2();

	void Draw(ShaderProgram& shader, glm::mat4 view) const;

private:
	size_t CoordsToIndex(size_t depth, size_t width, size_t height) const;
	void UpdateVisibility();

	//std::array<int, Depth* Width* Height> m_cells;
	int m_cells[Width][Depth][Height] = { 0 };
	CubePalette& m_palette;
	FlattenData_t m_data;
	glm::vec2 m_origin;
};

template<uint8_t Depth, uint8_t Width, uint8_t Height>
inline Chunk<Depth, Width, Height>::Chunk(const glm::vec2& origin, CubePalette& palette)
	:m_origin(origin),
	m_palette(palette){

}



template<uint8_t Depth, uint8_t Width, uint8_t Height>
inline void Chunk<Depth, Width, Height>::First() {

	for (size_t x = 0; x < Width; x++) {
		for (size_t y = 0; y < Height; y++) {
			for (size_t z = 0; z < Depth; z++) {
				if ((rand() % 10) < 5) {
					m_cells[x][z][y] = 1;
				}
				else {
					m_cells[x][z][y] = 0;
				}
			}
		}
	}

}

template<uint8_t Depth, uint8_t Width, uint8_t Height>
inline void Chunk<Depth, Width, Height>::Update() {
	int n_cells[Width][Depth][Height] = { 0 };
	//std::cout << "refreshed";
	for (size_t x = 0; x < Width; x++) {
		for (size_t y = 0; y < Height; y++) {
			for (size_t z = 0; z < Depth; z++) {
				int neighbours_alive = 0;

				//go over the neighbours
				int neighbours[6] = { 0 };
				if (x > 0)
					neighbours[0] = m_cells[x - 1][z][y];
				if (x < Width - 1)
					neighbours[1] = m_cells[x + 1][z][y];
				if (z > 0)
					neighbours[2] = m_cells[x][z - 1][y];
				if (z < Depth - 1)
					neighbours[3] = m_cells[x][z + 1][y];
				if (y > 0)
					neighbours[4] = m_cells[x][z][y - 1];
				if (y < Height - 1)
					neighbours[5] = m_cells[x][z][y + 1];

					for (int n : neighbours) {
						neighbours_alive += n;
					}
					if (neighbours_alive > 4 || neighbours_alive < 3)
						n_cells[x][z][y] = 0;
					else
						n_cells[x][z][y] = 1;
			}
		}
	}
	memcpy(m_cells, n_cells, sizeof(m_cells));
}

template<uint8_t Depth, uint8_t Width, uint8_t Height>
inline void Chunk<Depth, Width, Height>::Update_v2() {
	int n_cells[Width][Depth][Height] = { 0 };

	for (int x = 0; x < Width; x++) {//update each cell
		for (int y = 0; y < Height; y++) {
			for (int z = 0; z < Depth; z++) {
				int neighbours_alive = 0;
				for (int n_x = std::max(0, x - 1); n_x <= std::min(Width - 1, x + 1); n_x++) {
					for (int n_y = std::max(0, y - 1); n_y <= std::min(Width - 1, y + 1); n_y++) {
						for (int n_z = std::max(0, z - 1); n_z <= std::min(Width - 1, z + 1); n_z++) {
							if (n_x == x && n_y == y && n_z == z)	//if it's the cell, continue
								continue;
							else
								neighbours_alive += m_cells[n_x][n_z][n_y];
						}
					}
				}
				if (neighbours_alive > 18 || neighbours_alive < 10)
					n_cells[x][z][y] = 0;
				else
					n_cells[x][z][y] = 1;

			}
		}
	}
	memcpy(m_cells, n_cells, sizeof(m_cells));





}

template<uint8_t Depth, uint8_t Width, uint8_t Height>
inline void Chunk<Depth, Width, Height>::Draw(ShaderProgram& shader, glm::mat4 view) const {
	//define 2D chunk shift based on origin and dimension size
	glm::vec3 chunkShift(m_origin.x * Width, 0.0f, m_origin.y * Depth);

	//define transformation matrix
	glm::mat4 model = glm::translate(glm::mat4(1.0f), chunkShift);

	//activate shader
	shader.Use();

	//x,y,z in width, height, depth
	for (size_t x = 0; x < Width; x++) {
		for (size_t y = 0; y < Height; y++) {
			for (size_t z = 0; z < Depth; z++) {
				//check visibility
				if (m_cells[x][z][y]) {
					//calculate next transform
					glm::vec3 cubePosition(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
					glm::mat4 cubeModel = glm::translate(glm::mat4(1.0f), cubePosition);
					glm::mat4 finalModel = model * cubeModel;

					//glm::mat4 projection = glm::mat4(1.0f);
					//projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

					//glm::mat4 mvp = projection * view * finalModel;

					//pass transform to shader
					shader.SetMat4("model", finalModel);


					//draw cube
					Cube cube = m_palette.LookUp(Cube::Type::Alive);
					//std::cout << m_palette.LookUp(Cube::Type::Stone).Vao();
					glBindVertexArray(cube.Vao());
					glDrawArrays(GL_TRIANGLES, 0, 6 * 6);
				}
			}
		}
	}
}

template<uint8_t Depth, uint8_t Width, uint8_t Height>
inline size_t Chunk<Depth, Width, Height>::CoordsToIndex(size_t depth, size_t width, size_t height) const {
	return height * static_cast<size_t>(Depth) * static_cast<size_t>(Width)
		+ width * static_cast<size_t>(Depth)
		+ depth;
}

template<uint8_t Depth, uint8_t Width, uint8_t Height>
inline void Chunk<Depth, Width, Height>::UpdateVisibility() {
	//	x	y	z

	for (size_t x = 1; x < Width - 1; x++) {
		for (size_t z = 1; z < Depth - 1; z++) {
			for (size_t y = 1; y < Height - 1; y++) {
				//this cube
				size_t currCubeIndex = CoordsToIndex(z, x, y);
				//neighbours
				std::array<size_t, 6> neighbours = {
					CoordsToIndex(z,x-1,y),
					CoordsToIndex(z,x+1,y),
					CoordsToIndex(z,x,y-1),
					CoordsToIndex(z,x,y+1),
					CoordsToIndex(z-1,x,y),
					CoordsToIndex(z+1,x,y)
				};

				for(int n_x = x-1; n_x <= x+1; n_x++)
				m_data[currCubeIndex].m_isVisible = false;
				for (int i = 0; i < 6; i++) {
					if (m_data[neighbours[i]].m_type == Cube::Type::None) {
						m_data[currCubeIndex].m_isVisible = true;
						break;
					}
				}
			}
		}
	}
}
