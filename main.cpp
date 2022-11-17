#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <unistd.h>
#include <cstdlib>
using namespace std;

#define UnassignedValue     0
#define BoardSize           9
#define DummyTab            "    "
#define DummyTab1           "  "

bool CanEnterNumber(int board[BoardSize][BoardSize], int row, int column, int num);
void PrintBoard(int board[BoardSize][BoardSize]);
void EnterNumberInBoard(int board[BoardSize][BoardSize], int row, int column, int num);
void StartSudokuGame();

bool UsedInRow(int board[BoardSize][BoardSize], int row, int num)
{
    for (int column = 0; column < BoardSize; column ++)
    {
        if (board[row][column] == num)
        {
            return true;
        }
    }
    return false;
}

bool UsedInColumn(int board[BoardSize][BoardSize], int column, int num)
{
    for (int row = 0; row < BoardSize; row ++)
    {
        if (board[row][column] == num)
        {
            return true;
        }
    }
    return false;
}

bool UsedInBox(int board[BoardSize][BoardSize], int BoxStartRow, int BoxStartColumn, int num)
{
    for (int row = 0; row < 3; row ++)
    {
        for (int column = 0; column < 3; column ++)
        {
            if (board[row + BoxStartRow][column + BoxStartColumn] == num)
            {
                return true;
            }
        }
    }
    return false;
}

bool CanEnterNumber(int board[BoardSize][BoardSize], int row, int column, int num)
{
    return !UsedInRow(board, row, num) && !UsedInColumn(board, column, num) && !UsedInBox(board, row - row % 3, column - column % 3, num) && board[row][column] == UnassignedValue;
}

int CountBlankSpaces(int board[BoardSize][BoardSize])
{
    int count = 0;

    for (int row = 0; row < BoardSize; row ++)
    {
        for (int column = 0; column < BoardSize; column ++)
        {
            if (board[row][column] == UnassignedValue)
            {
                count ++;
            }
        }
    }
    return count;
}

bool IsValidNumber(int num)
{
    int ValidNumber[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int ValidNumberLength = sizeof ValidNumber / sizeof ValidNumber[0];

    for (int i = 0; i < ValidNumberLength; i ++)
    {
        if (ValidNumber[i] == num)
        {
            return true;
        }
    }
    return false;
}

bool IsValidRow(int row)
{
    if (row < 0 || row > 8)
    {
        return false;
    }
    return true;
}

bool IsValidColumn(int column)
{
    if (column < 0 || column > 8)
    {
        return false;
    }
    return true;
}

void EnterNumberInBoard(int board[BoardSize][BoardSize], int row, int column, int num)
{
    if (CanEnterNumber(board, row, column, num) && IsValidNumber(num) == true && IsValidRow(row) == true && IsValidColumn(column) == true)
    {
        board[row][column] = num;
        PrintBoard(board);
    }
    else
    {
        if (UsedInRow(board, row, num) == true)
        {
            cout << "ERROR: The number " << num << " is used in row " << row + 1;
            
            sleep(2);
            
            PrintBoard(board);
        }
        else if (UsedInColumn(board, column, num) == true)
        {
            cout << "ERROR: The number " << num << " is used in column " << column + 1;

            sleep(2);
            
            PrintBoard(board);
        }
        else if (UsedInBox(board, row - row % 3, column - column % 3, num) == true)
        {
            cout << "ERROR: The num " << " is used in row " << (row - row % 3) + 1 << " and column " << (column - column % 3) + 1;

            sleep(2);

            PrintBoard(board);
        }
        else if (IsValidNumber(num) == false)
        {
            cout << "ERROR: The number " << num << " is invalid";

            sleep(2);

            PrintBoard(board);
        }
        else if (IsValidRow(row) == false)
        {
            cout << "ERROR: The row " << row + 1 << " is invalid";

            sleep(2);

            PrintBoard(board);
        }
        else if (IsValidColumn(column) == false)
        {
            cout << "ERROR: The column " << column + 1 << " is invalid";

            sleep(2);

            PrintBoard(board);
        }
        else
        {
            cout << "ERROR: Unknown error.";

            sleep(2);

            PrintBoard(board);
        }
    }
}

/**
 * 
 * Thanks for these links for different system clear commands.
 * - https://www.unix.com/programming/241672-system-clear-error.html
 * - https://stackoverflow.com/questions/15580179/how-do-i-find-the-name-of-an-operating-system
 */
void ClearConsole()
{
    #ifdef __WIN32
        system("cls");
    #elif __WIN64
        system("cls");
    #else
        system("clear");
    #endif
}

void PrintBoard(int board[BoardSize][BoardSize])
{
    ClearConsole();
    
    cout << DummyTab << "         C   O   L   U   M   N      \n";
    cout << DummyTab << "   1   2   3   4   5   6   7   8   9\n\n";

    int tab = 0;
    
    for (int row = 0; row < BoardSize; row ++)
    {
        tab ++;
        if (tab == 2)
        {
            cout << "R " << tab << DummyTab1 << "| ";
            
        }
        else if (tab == 4)
        {
            cout << "O " << tab << DummyTab1 << "| ";
        }
        else if (tab == 6)
        {
            cout << "W " << tab << DummyTab1 << "| ";
        }
        else if (tab == 8)
        {
            cout << "S " << tab << DummyTab1 << "| ";
        }
        else
        {
            cout << "  " << tab << DummyTab1 << "| ";
        }

        for (int column = 0; column < BoardSize; column ++)
        {
            if (board[row][column] == UnassignedValue)
            {
                cout << " ";
            }
            else
            {
                cout << board[row][column];
            }
            cout << " | ";
        }
        cout << endl;
    }

    if (CountBlankSpaces(board) != 0)
    {
        int row, column, num;

        cout << "\nSYSTEM: You still have " << CountBlankSpaces(board) << " blank field left." << endl;

        cout << "SYSTEM: Enter the row: ";
        cin >> row;

        cout << "SYSTEM: Enter the column: ";
        cin >> column;

        cout << "SYSTEM: Enter tthe number that you want to enter in row " << row << " and column " << column << ": ";
        cin >> num;

        EnterNumberInBoard(board, row - 1, column - 1, num);
    }
    else
    {
        char Option;

        cout << "\n\nSYSTEM: Congratulations! You have completed the Sudoku puzzle.\nWant to continue? (Y - Yes | N - No): ";
        cin >> Option;

        switch (Option)
        {
            case 'Y':
            {
                StartSudokuGame();
            }
            break;

            case 'N':
            {
                exit(0);
            }
            break;
        }
    }
}

void FillRandomBoxInBoard(int board[BoardSize][BoardSize])
{
    for (int row = 0; row < BoardSize; row ++)
    {
        for (int column = 0; column < BoardSize; column ++)
        {
            int num = (rand() % 9) + 0;

            if (CanEnterNumber(board, row, column, num))
            {
                board[row][column] = num;
            }
            else
            {
                board[row][column] = UnassignedValue;
            }
        }
    }
}

void StartSudokuGame()
{
    int board[BoardSize][BoardSize];

    FillRandomBoxInBoard(board);

    sleep(1);

    PrintBoard(board);
}

int main()
{
    srand(time(NULL));

    StartSudokuGame();

    return 0;
}