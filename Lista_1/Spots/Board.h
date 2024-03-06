#pragma once
#include "ShaderProgram.h"
#include "cell.h"
#include <random>


class Board{
public:
	Board(size_t Size_x, size_t Size_y);
	~Board() { delete[] m_board; }


	void Generate();	//Generate first iteration of the board
	void Next_step();	//Update the board with next step
	float Density();		//Get density of live population in [%]
	void Draw(ShaderProgram& shaderProgram);	//Draw the board




private:
	size_t Coords_to_Index(size_t x, size_t y);	//convert coordinate [x][y] to index in board

	const int m_size_x;
	const int m_size_y;
	Cell *m_board;	// true = Alive
};

