#include "Board.h"
#include <glad/glad.h>
#include<iostream>

Board::Board(size_t Size_x, size_t Size_y) :
	m_size_x(Size_x),
	m_size_y(Size_y),
	m_board(new Cell[m_size_x * m_size_y])
{
	//initialize every cell
	for (size_t x = 0; x < m_size_x; x++) {
		for (size_t y = 0; y < m_size_y; y++) {
			m_board[Coords_to_Index(x, y)] = Cell(x, y, m_size_x, m_size_y);
		}
	}

}

void Board::Generate()
{
	srand(time(NULL));	//random seed

	auto rng = []() {return (rand() % 2) == 1; };	//lambda to generate alive state

	for (size_t x = 0; x < m_size_x; x++) {	//set alive status for each cell
		for (size_t y = 0; y < m_size_y; y++) {
			m_board[Coords_to_Index(x, y)].Set_Alive(rng());
			//m_board[Coords_to_Index(x, y)].Set_Alive(true);
		}
	}
}

void Board::Next_step()
{
	bool* m_new_board = new bool[m_size_x * m_size_y];
	for (size_t x = 0; x < m_size_x; x++) {	//go through each cell
		for (size_t y = 0; y < m_size_y; y++) {
			//neighbours
			int neighbours_alive = 0;
			
			for (int dx = -1; dx <= 1; dx++) {
				for (int dy = -1; dy <= 1; dy++) {


					size_t n_x = x + dx;	//calculate neighbour coords
					size_t n_y = y + dy;

					if (n_x >= 0 && n_x < m_size_x && n_y >= 0 && n_y < m_size_y)	//check if neighbour is within bounds
						if (m_board[Coords_to_Index(n_x, n_y)].Is_Alive())	//If neighbour is alive
							neighbours_alive++;
				}
			}
			//std::cout << neighbours_alive << std::endl;


			//update based on number of alive neighbours
			if (neighbours_alive < 4 || neighbours_alive == 5)	//cell dies with 0,1,2,3,5 alive neighbours
				m_new_board[Coords_to_Index(x, y)] = false;
			else
				m_new_board[Coords_to_Index(x, y)] = true;	
															
		}
	}
	//override old alive state
	for (size_t i = 0; i < m_size_x * m_size_y; i++)
		m_board[i].Set_Alive(m_new_board[i]);

}

float Board::Density()
{
	float sum = 0;
	for (size_t i = 0; i < m_size_x * m_size_y; i++) {
		if (m_board[i].Is_Alive()) {
			sum++;
		}
	}
	return sum / (m_size_x * m_size_y);
}

void Board::Draw(ShaderProgram& shader)
{
	for (size_t x = 0; x < m_size_x; x++) {	//go through the board
		for (size_t y = 0; y < m_size_y; y++) {
			Cell& curr_cell = m_board[Coords_to_Index(x, y)];	//current cell
			if (curr_cell.Is_Alive()) {	//if is Alive
				
				//rendering
				shader.Use();
				glBindVertexArray(curr_cell.Vao());
				glDrawArrays(GL_TRIANGLES, 0, 6);
				glBindVertexArray(0);
			}
		}
	}
}



size_t Board::Coords_to_Index(size_t x, size_t y)
{
	return size_t((y * m_size_x) + x);
}

