#include <iostream>

int CheckWin(char _cBoard[3][3]);
void PrintBoard(char _cBoard[3][3]);
struct nMove MinMaxMove(char _cBoard[3][3], char _cPlayer);

struct nMove
{
	nMove() {};
	nMove(int _iScore) {iScore = _iScore;};
	int iRow;
	int iCol;
	int iScore;
	char cFill;
};

int main()
{
	char cBoard[3][3];
	memset(cBoard, NULL, 9);
	bool bWin = false;
	bool bX = true;
	char cPlayer = 120;
	nMove mTurn;
	int iRow;
	int iCol;
	char cFill;

	while(bWin == false)
	{
		if(CheckWin(cBoard) != -1)
		{
			bWin = true;
			PrintBoard(cBoard);
		}
		else
		{
			mTurn = MinMaxMove(cBoard, cPlayer);
			cBoard[mTurn.iRow][mTurn.iCol] = mTurn.cFill;

			/*PrintBoard(cBoard);

			std::cin >> iRow;
			std::cin >> iCol;
			std::cin >> cFill;

			cBoard[iRow][iCol] = cFill;*/

			if(bX == true)
			{
				cPlayer = 111;
				bX = false;
			}
			else
			{
				cPlayer = 120;
				bX = true;
			}

			PrintBoard(cBoard);
		}
	}

	return 0;
}

int CheckWin(char _cBoard[3][3])
{
	bool bWin = false;
	char cWinner = NULL;
	for(int i = 0; i < 3; i++)
	{
		if((_cBoard[i][0] == _cBoard[i][1]) && (_cBoard[i][0] == _cBoard[i][2]) && (_cBoard[i][0] != NULL))
		{
			bWin = true;
			cWinner = _cBoard[i][0];
		}
		if((_cBoard[0][i] == _cBoard[1][i]) && (_cBoard[0][i] == _cBoard[2][i]) && (_cBoard[0][i] != NULL))
		{
			bWin = true;
			cWinner = _cBoard[0][i];
		}
	}

	if((_cBoard[0][0] == _cBoard[1][1]) && (_cBoard[0][0] == _cBoard[2][2]) && (_cBoard[0][0] != NULL))
	{
		bWin = true;
		cWinner = _cBoard[1][1];
	}
	if((_cBoard[0][2] == _cBoard[1][1]) && (_cBoard[0][2] == _cBoard[2][0]) && (_cBoard[0][2] != NULL))
	{
		bWin = true;
		cWinner = _cBoard[1][1];
	}

	if(bWin == true)
	{
		if(cWinner == 120)
		{
			return 10;
		}
		else
		{
			return -10;
		}
	}
	else
	{
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				if(_cBoard[i][j] == 0)
				{
					return -1;
				}
			}
		}
		return 0;
	}
}

nMove MinMaxMove(char _cBoard[3][3], char _cPlayer)
{
	int moveScore = CheckWin(_cBoard);
	nMove mBest;

	if(moveScore != -1)
	{
		nMove mWin(moveScore);
		return mWin;
	}

	if(_cPlayer == 120)
	{
		int iMax = -1000;
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				if(_cBoard[i][j] == 0)
				{
					_cBoard[i][j] = 120;
					nMove mRecur = MinMaxMove(_cBoard, _cPlayer = 111);
					mRecur.iRow = i;
					mRecur.iCol = j;
					if(iMax < mRecur.iScore)
					{
						iMax = mRecur.iScore;
						mBest.iScore = mRecur.iScore + moveScore;
						mBest.iCol = mRecur.iCol;
						mBest.iRow = mRecur.iRow;
						mBest.cFill = 120;
					}
					_cBoard[i][j] = 0;
				}
			}
		}
		return mBest;
	}
	else
	{
		int iMin = 1000;
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				if(_cBoard[i][j] == NULL)
				{
					_cBoard[i][j] = 111;
					nMove mRecur = MinMaxMove(_cBoard, _cPlayer = 120);
					mRecur.iRow = i;
					mRecur.iCol = j;
					if(iMin > mRecur.iScore)
					{
						iMin = mRecur.iScore;
						mBest.iScore = mRecur.iScore + moveScore;
						mBest.iCol = mRecur.iCol;
						mBest.iRow = mRecur.iRow;
						mBest.cFill = 111;
					}
					_cBoard[i][j] = NULL;
				}
			}
		}
		return mBest;
	}
	return 0;
}

void PrintBoard(char _cBoard[3][3])
{
	for(int i = 0; i < 3; i++)
	{
		std::cout<< "\n";
		for(int j = 0; j < 3; j++)
		{
			std::cout << _cBoard[i][j];
		}
	}
	std::cout<< std::endl;
}