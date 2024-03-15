#include <iostream>
#include <random>
#include <fstream>
#include <cstdlib>

const int m_x = 300;
const int m_y = 300;
const int m_steps = 15000;
int board[m_x][m_y];


void Generate() {

	srand(time(NULL));	//random seed
	for (int x = 0; x < m_x; x++) {
		for (int y = 0; y < m_y; y++) {
			board[x][y] = rand() % 2;
		}
	}
}

void Next_Step() {

	int board_v2[m_x][m_y];
	for (int x = 0; x < m_x; x++) {	// go over all cells
		for (int y = 0; y < m_y; y++) {
			//go over the neighbours
			int neighbours = 0;
			for (int dx = -1; dx <= 1; dx++) {
				for (int dy = -1; dy <= 1; dy++) {
					if (x + dx >= 0 && x + dx < m_x && y + dy >= 0 && y + dy < m_y) {	//check border 
						neighbours += board[x + dx][y + dy];
					}
				}
			}

			//update cell based on neighbours alive
			if (neighbours < 4 || neighbours == 5) {
				board_v2[x][y] = 0;
			}
			else {
				board_v2[x][y] = 1;
			}
		}
	}

	//update board with next step
	for (int x = 0; x < m_x; x++) {
		for (int y = 0; y < m_y; y++) {
			board[x][y] = board_v2[x][y];
		}
	}
}

float Density() {
	float sum = 0;
	for (int x = 0; x < m_x; x++) {
		for (int y = 0; y < m_y; y++) {
			sum += board[x][y];
		}
	}
	return sum / (m_x * m_y);
}





int main() {
	int board[m_x][m_y];


	//Fill the board with random values
	Generate();

	//Open and write to file
	std::ofstream file("../Spots_graphing/Spots_Density_300x300_1.txt");

	for (int s = 0; s < m_steps; s++) {
		//system("cls");
		//std::cout << s << std::endl << "density: " << Density(board);
		Next_Step();
		file<<Density()<<" ";
	}

	file.close();
	std::cout << "fin";
	return 0;
}
