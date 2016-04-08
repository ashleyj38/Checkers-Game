#include <iostream>
#include <math.h>
using namespace std;

//void initializeBoard(char (&array)[8][8]);

void initializeBoard(char[][8]);

void printBoard(char[][8]);

bool validatePiece(char[][8],char,int, int);

bool validateMove(char[][8], char, int, int, int, int);

int movePiece(char[][8], char, int, int, int, int);

int main() 

{
	char Board[8][8];
	int player = 1;
	char validPiece, opponent;
	int rowChoice, colChoice, moveRowChoice, moveColChoice;
	bool valid;
	int numRedPieces = 12, numBlkPieces = 12;
	int redScore = 0, blkScore = 0;
	int jump;

	//Initialize the Board
	initializeBoard(Board);

	do {
		//Print the Board
		printBoard(Board);

		if (player % 2 == 1)
		{
			validPiece = 'R';
			opponent = 'B';
			cout << "It's the red player's turn.\n";
		}
		else
		{
			validPiece = 'B';
			opponent = 'R';
			cout << "It's the black player's turn.\n";
		}

		//Red's turn

		//Choose the piece you would like to move. Must have the value of red. 
		cout << "Please enter the row number of the piece you would like to move: ";
		cin >> rowChoice;
		cout << "Please enter the column number of the piece you would like to move: ";
		cin >> colChoice;

		valid = validatePiece(Board, validPiece, rowChoice, colChoice);

		while (!valid)
		{
			cout << "You did not choose a valid piece to move. Please re-enter the row and column respectively: ";
			cin >> rowChoice >> colChoice;

			valid = validatePiece(Board, validPiece, rowChoice, colChoice);
		}
		//Choose the spot you would like to move it to. If the position is not free, ask the player to move to a different spot
		cout << "Please enter the row number where you would like to move your piece: ";
		cin >> moveRowChoice;
		cout << "Please enter the column number where you would like to move your piece: ";
		cin >> moveColChoice;

		valid = validateMove(Board, opponent, rowChoice, colChoice,moveRowChoice,moveColChoice);

		while (!valid)
		{
			cout << "You did not choose a valid space to move your piece to. Please re-enter the row and column respectively: ";
			cin >> moveRowChoice >> moveColChoice;

			valid = validatePiece(Board, validPiece, rowChoice, colChoice);
		}

		//"Move" the piece once an appropriate spot is chosen
		if (validPiece == 'R')
		{
			jump = movePiece(Board, validPiece, rowChoice, colChoice, moveRowChoice, moveColChoice);
			redScore += jump;
			numBlkPieces -= jump;
		}
		else
		{
			jump = movePiece(Board, validPiece, rowChoice, colChoice, moveRowChoice, moveColChoice);
			blkScore += jump;
			numRedPieces -= jump;
		}
		//Black's turn. (same rules)

		player++;

		/*if (player == 3)
			numBlkPieces = 0*/

		//printBoard(Board); //Delete this line after testing

		//Check if each player still has pieces. If so, loop again.
	} while (numRedPieces > 0 && numBlkPieces > 0);

	return 0;
}

/*void initializeBoard(char (&CheckerBoard)[8][8])
{

}*/

void initializeBoard(char CheckerBoard[][8])
{
	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			if (row == 0 || row == 1 || row == 2)
			{
				if ((row == 0 || row == 2) && (col % 2 == 1))
				{
					CheckerBoard[row][col] = 'R';
				}
				else if (row == 1 && col % 2 == 0)
				{
					CheckerBoard[row][col] = 'R';
				}
				else
				{
					CheckerBoard[row][col] = '0';
				}
			}
			else if (row == 5 || row == 6 || row == 7)
			{
				if ((row == 5 || row == 7) && (col % 2 == 0))
				{
					CheckerBoard[row][col] = 'B';
				}
				else if (row == 6 && col % 2 == 1)
				{
					CheckerBoard[row][col] = 'B';
				}
				else
				{
					CheckerBoard[row][col] = '0';
				}
			}
			else
			{
				CheckerBoard[row][col] = '0';
			}
		}
	}
}

void printBoard(char CheckerBoard[][8])
{
	cout << " 1 2 3 4 5 6 7 8";

	for (int row = 0; row < 8; row++)
	{
		cout << endl << (row + 1);
		for (int col = 0; col < 8; col++)
		{
			 cout << " "<< CheckerBoard[row][col];
		}
	}

	cout << endl;
}

bool validatePiece(char CheckerBoard[][8],char validPiece, int row, int col)
{
	if (row > 8 || row < 1 || col > 8 || col < 1)
		return false;
	else if (CheckerBoard[row - 1][col - 1] != validPiece)
		return false;
	else
		return true;
}

bool validateMove(char CheckerBoard[][8], char opponent, int row, int col, int moveRow, int moveCol)
{
	if (moveRow > 8 || moveRow < 1 || moveCol > 8 || moveRow < 1)
		return false;
	else if (CheckerBoard[moveRow - 1][moveCol - 1] != '0')
	{
		cout << "REASON: Not an open space.\n\n";
		return false;
	}
	else if ((moveRow < row && opponent == 'B') || (moveRow > row && opponent == 'R'))
	{
		cout << "REASON: Wrong direction.\n\n";
		return false;
	}
	else if (abs((col - moveCol) / (row - moveRow)) == 1 && abs(col - moveCol) == 1 && abs(row - moveRow) == 1)
	{
		cout << "REASON: Single move\n\n";
		return true;
	}
	else if (abs((col - moveCol) / (row - moveRow)) == 1 && abs(col - moveCol) == 2 && abs(row - moveRow) == 2 && CheckerBoard[moveRow + (moveRow - row)/(-2) - 1][moveCol + (moveCol - col)/(-2) - 1] == opponent)
	{
		cout << "REASON: Hop\n\n";
		return true;
	}
	else
	{
		cout << "abs(col - moveCol): " << abs(col - moveCol) << "\tabs(row - moveRow == 2): " << abs(row - moveRow) << "\tabs((col - moveCol) / (row - moveRow)): " << abs((col - moveCol) / (row - moveRow)) << endl;
		cout << "Row checked: " << (moveRow + (moveRow - row) / (-2) - 1) << endl;
		cout << "Column checked: " << (moveCol + (moveCol - col) / (-2) - 1) << endl;
		cout << CheckerBoard[moveRow + (moveRow - row) / (-2) - 1][moveCol + (moveCol - col) / (-2) - 1] << endl << endl;
		cout << "Opponent: " << opponent << endl;
		cout << "REASON: Hop not over opponent\n\n.";
		return false;
	}
}

int movePiece(char CheckerBoard[][8], char piece, int begRow, int begCol, int finalRow, int finalCol)
{
	char temp;
	int slope;
	
	CheckerBoard[begRow - 1][begCol - 1] = '0';

	if (abs(begCol - finalCol) == 2 && abs(begRow - finalRow) == 2)
	{
		if (begRow > finalRow && begCol > finalCol)
		{
			CheckerBoard[begRow-2][begCol-2] = '0';
			CheckerBoard[finalRow - 1][finalCol - 1] = piece;

		}
		else if (begRow < finalRow && begCol < finalCol)
		{
			CheckerBoard[finalRow - 2][finalCol - 2] = '0';
			CheckerBoard[finalRow - 1][finalCol - 1] = piece;
		}
		else if (begRow > finalRow && begCol < finalCol)
		{
			CheckerBoard[begRow - 2][begCol + 2] = '0';
			CheckerBoard[finalRow - 1][finalCol - 1] = piece;
		}
		else
		{
			CheckerBoard[begRow + 2][begCol - 2] = '0';
			CheckerBoard[finalRow - 1][finalCol - 1] = piece;
		}
		return 1;
	}
	else
	{
		CheckerBoard[finalRow - 1][finalCol - 1] = piece;
		return 0;
	}
}
