#pragma once
class Board
{
public:
	Board(const int X, const int Y);

	int CoordsToIndex(int x, int y);
	float Density();
	void Generate();
	void Next_Step();

private:
	bool *m_board;
	int m_x;
	int m_y;
};
