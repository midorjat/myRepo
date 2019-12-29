// KnightMove.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

const int bSize = 40;
int chessPlace[bSize][bSize];
int finalChessPlace[bSize][bSize];
bool finish = false;

const int xMove[8] = { 2, 1, -1, -2, -2, -1,  1,  2 };
const int yMove[8] = { 1, 2,  2,  1, -1, -2, -2, -1 };

class Pos {
public:
	int x, y;
	int possibleMoves = 0;
	vector<Pos> nextMoves;
	Pos(int x=0, int y=0) 
	{	
		this->x = x; 
		this->y = y;
	}
	bool isSafe()
	{
		return (x >= 0 && y >= 0 && x < bSize && y < bSize && chessPlace[x][y]==-1);
	}
	void checkNextMoves()
	{
		for (int i = 0; i < 8; ++i)
		{
			Pos nextPos(x + xMove[i], y + yMove[i]);
			int temp = chessPlace[x][y];
			chessPlace[x][y] = 1;
			if (nextPos.isSafe())
			{
				++possibleMoves;
				nextMoves.push_back(nextPos);
			}
			try {
				chessPlace[x][y] = temp;
			}
			catch (...)
			{
				cout << "SomeThing here\n";
			}
		}
	}
};

void resetChessPlace()
{
	for (int i = 0; i < bSize; ++i)
	{
		for (int j = 0; j < bSize; ++j)
		{
			chessPlace[i][j] = -1;
		}
	}
}

bool isChessPlaceFilled()
{
	bool isFilled = true;
	for (int i = 0; i < bSize; ++i)
	{
		for (int j = 0; j < bSize; ++j)
		{
			isFilled = isFilled&&(chessPlace[i][j] == 1);
			if (!isFilled) return isFilled;
		}
	}
	return isFilled;
}

struct myclass {
	bool operator() (Pos& i, Pos& j) { return (i.possibleMoves < j.possibleMoves); }
} myobject;

void getPosibleMove(Pos& currentPos)
{
	for(auto it=currentPos.nextMoves.begin(); it!=currentPos.nextMoves.end(); ++it)
	{
		it->checkNextMoves();
	}
	if (currentPos.nextMoves.size() != 0)
	{
		try
		{
			sort(currentPos.nextMoves.begin(), currentPos.nextMoves.end(), myobject);
		}
		catch (...)
		{
			cout << "some exception happen" << endl;
		}
	}
}

bool findSolution(Pos currentPos, vector<Pos>& moveSteps, int lv)
{
	Pos nextPos;
	if (lv == (bSize * bSize)) return true;
	//vector<Pos> nextMoves = getPosibleMove(currentPos);
	getPosibleMove(currentPos);
	for (auto it = currentPos.nextMoves.begin(); it != currentPos.nextMoves.end(); ++it)
	{
		if (it->isSafe())
		{
			chessPlace[it->x][it->y] = lv;
			moveSteps.push_back(*it);
			if (findSolution(*it, moveSteps, lv + 1))
			{
				return true;
			}
			else
			{
				chessPlace[it->x][it->y] = -1;
				moveSteps.pop_back();
			}
		}
	}
	/*for (int i = 0; i < 8; ++i)
	{
		nextPos.x = currentPos.x + xMove[i];
		nextPos.y = currentPos.y + yMove[i];
		if (nextPos.isSafe() && chessPlace[nextPos.x][nextPos.y]==-1)
		{
			chessPlace[nextPos.x][nextPos.y] = lv;
			moveSteps.push_back(nextPos);
			if (findSolution(nextPos, moveSteps, lv + 1))
			{
				return true;
			}
			else
			{
				chessPlace[nextPos.x][nextPos.y] = -1;
				moveSteps.pop_back();
			}
		}
	}*/
	return false;
}

int main()
{
	resetChessPlace();
	Pos startPos(0, 0);
	startPos.checkNextMoves();
	vector<Pos> steps;
	chessPlace[0][0] = 0;
	bool isOk = findSolution(startPos, steps, 1);
	cout << "isOk " << isOk << endl;
	cout << "Dump all move" << endl;
	
	for (int i = 0; i < bSize; ++i)
	{
		for (int j = 0; j < bSize; ++j)
		{
			cout << setw(3);
			cout << chessPlace[j][i] << " | ";
		}
		cout << endl;
	}
	return 0;
}


