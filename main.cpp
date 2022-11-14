#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

#define UNASSIGNED_VALUE    0
#define BOARD_SIZE          9
#define DUMMY_TAB           "    "
#define DUMMY_TAB_1         "  "
#define PLAYER_HEADER       "\n\tYour name here\n\tCOURSE - Branch - Section\n\n\tSudoku Puzzle\n"

bool CanEnterNumber(int grid[BOARD_SIZE][BOARD_SIZE], int row, int col, int num); // early declaration for CanEnterNumber()
void PrintGrid(int grid[BOARD_SIZE][BOARD_SIZE]); // early declaration for PrintGrid()
void EnterNumber(int grid[BOARD_SIZE][BOARD_SIZE], int row, int col, int num); // early declaration for EnterNumber()
void StartGame(); // early declaration for StartGame() 

/**
 * Function: UsedInRow()
 * Params: 
 *        - grid
 *              - The entered board
 *        - row
 *              - The entered row
 *        - num
 *              - The entered number
 * 
 * Returns:
 *        - true
 *              - If the row and column matched the entered number.
 *        - false
 *              - If the row and column did not match the entered number.
 */
bool UsedInRow(int grid[BOARD_SIZE][BOARD_SIZE], int row, int num)
{
    for (int col = 0; col < BOARD_SIZE; col ++)
    {
        if (grid[row][col] == num)
        {
            return true;
        }
    }
    return false;
}

/**
 * Function: UsedInCol()
 * Params: 
 *        - grid
 *              - The entered board
 *        - col
 *              - The entered col
 *        - num
 *              - The entered number
 * 
 * Returns:
 *        - true
 *              - If the row and column matched the entered number.
 *        - false
 *              - If the row and column did not match the entered number.
 */
bool UsedInCol(int grid[BOARD_SIZE][BOARD_SIZE], int col, int num)
{
    for (int row = 0; row < BOARD_SIZE; row ++)
    {
        if (grid[row][col] == num)
        {
            return true;
        }
    }
    return false;
}

/**
 * Function: UsedInBox()
 * Params: 
 *        - grid
 *              - The entered board
 *        - boxStartRow
 *              - The starting row of the box
 *        - boxStartCol
 *              - The starting column of the box
 *        - num
 *              - The entered number
 * 
 * Returns:
 *        - true
 *              - If the number is already used in the box.
 *        - false
 *              - If the number is available for the box.
 */
bool UsedInBox(int grid[BOARD_SIZE][BOARD_SIZE], int boxStartRow, int boxStartCol, int num)
{
    for (int row = 0; row < 3; row ++)
    {
        for (int col = 0; col < 3; col ++)
        {
            if (grid[row + boxStartRow][col + boxStartCol] == num)
            {
                return true;
            }
        }
    }
    return false;
}

/**
 * Function: CanEnterNumber()
 * Params: 
 *        - grid
 *              - The entered board
 *        - row
 *              - The entered row
 *        - col
 *              - The entered column
 *        - num
 *              - The entered number
 * 
 * Returns:
 *        - true
 *              - If the number is available in row, column, box, and the value of field is equals to 0
 *        - false
 *              - If the number is not available in row, column, box, and the value of field is not equals to 0
 */
bool CanEnterNumber(int grid[BOARD_SIZE][BOARD_SIZE], int row, int col, int num)
{
    return !UsedInRow(grid, row, num) && !UsedInCol(grid, col, num) && !UsedInBox(grid, row - row % 3, col - col % 3, num) && grid[row][col] == UNASSIGNED_VALUE;
}

/**
 * Function: CountBlankSpaces()
 * Params: 
 *        - grid
 *              - The entered board
 * 
 * Returns:
 *        - Number of blank spaces.
 */
int CountBlankSpaces(int grid[BOARD_SIZE][BOARD_SIZE])
{
    int count = 0;
    
    for (int row = 0; row < BOARD_SIZE; row ++)
    {
        for (int col = 0; col < BOARD_SIZE; col ++)
        {
            if (grid[row][col] == UNASSIGNED_VALUE)
            {
                count ++;
            }
        }
    }
    return count;
}

/**
 * Function: IsValidNumber()
 * Params: 
 *        - num
 *              - The entered number
 * 
 * Returns:
 *        - true
 *              - If the entered number is valid
 *        - false
 *              - If the entered number is invalid
 */
bool IsValidNumber(int num)
{
    int validNumber[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int validNumberLength = sizeof validNumber / sizeof validNumber[0];

    for (int i = 0; i < validNumberLength; i ++)
    {
        if (validNumber[i] == num)
        {
            return true;
        }
    }
    return false;
}

/**
 * Function: IsValidNumber()
 * Params: 
 *        - row
 *              - The entered row
 * 
 * Returns:
 *        - true
 *              - If the entered row is valid
 *        - false
 *              - If the entered row is invalid
 */
bool IsValidRow(int row)
{
    if (row < 0 || row > 8)
    {
        return false;
    }
    return true;
}

/**
 * Function: IsValidCol()
 * Params: 
 *        - col
 *              - The entered column
 * 
 * Returns:
 *        - true
 *              - If the entered column is valid
 *        - false
 *              - If the entered column is invalid
 */
bool IsValidCol(int col)
{
    if (col < 0 || col > 8)
    {
        return false;
    }
    return true;
}

/**
 * Function: EnterNumber()
 * Params: 
 *        - grid
 *              - The entered grid
 *        - row
 *              - The entered row
 *        - col
 *              - The entered column
 *        - num
 *              - The entered number
 * 
 * Returns:
 *        - none as it's a void function
 */
void EnterNumber(int grid[BOARD_SIZE][BOARD_SIZE], int row, int col, int num)
{
    if (CanEnterNumber(grid, row, col, num) && IsValidNumber(num) == true && IsValidRow(row) == true && IsValidCol(col) == true)
    {
        grid[row][col] = num;
        PrintGrid(grid);
    }
    else
    {
        if (UsedInRow(grid, row, num) == true)
        {
            cout << "The number " << num << " is used in row " << row + 1;
            sleep(1.5);
            PrintGrid(grid);
        }
        else if (UsedInCol(grid, col, num) == true)
        {
            cout << "The number " << num << " is used in column " << col + 1;
            sleep(1.5);
            PrintGrid(grid);
        }
        else if (UsedInBox(grid, row - row % 3, col - col % 3, num) == true)
        {
            cout << "The number " << num << " is used in row " << (row - row % 3) + 1 << " and column " << (col - col % 3) + 1;
            sleep(1.5);
            PrintGrid(grid);
        }
        else if (IsValidNumber(num) == false)
        {
            cout << "The number " << num << " is invalid";
            sleep(1.5);
            PrintGrid(grid);
        }
        else if (IsValidRow(row) == false)
        {
            cout << "The row " << row << " is invalid";
            sleep(1.5);
            PrintGrid(grid);
        }
        else if (IsValidCol(col) == false)
        {
            cout << "The column " << col << " is invalid";
            sleep(1.5);
            PrintGrid(grid);
        }
        else
        {
            cout << "Unknown error.";
            sleep(1.5);
            PrintGrid(grid);
        }
    }
}

/**
 * Function: ClearConsole()
 * Params: 
 *        - none
 * 
 * Returns:
 *        - none as it's a void function
 */
void ClearConsole()
{
    #ifdef __WIN32
        system("cls");
    #elif __WIN64
        system("cls");
    #elif __APPLE__ || __MACH__
        system("clear");
    #elif __linux__
        system("clear");
    #elif __FreeBSD__
        system("clear");
    #elif __unix || __unix__
        system("clear");
    #else
        system("clear");
    #endif
}

/**
 * Function: PrintGrid()
 * Params: 
 *        - grid
 *              - The entered grid         
 * 
 * Returns:
 *        - none as it's a void function
 */
void PrintGrid(int grid[BOARD_SIZE][BOARD_SIZE])
{
    ClearConsole();

    cout << PLAYER_HEADER << endl;

    cout << DUMMY_TAB << "         C   O   L   U   M   N      \n";
    cout << DUMMY_TAB << "   1   2   3   4   5   6   7   8   9\n\n";

    int tab = 0;
    
    for (int row = 0; row < BOARD_SIZE; row ++)
    {
        tab ++;
        if (tab == 2)
        {
            cout << "R " << tab << DUMMY_TAB_1 << "| ";
            
        }
        else if (tab == 4)
        {
            cout << "O " << tab << DUMMY_TAB_1 << "| ";
        }
        else if (tab == 6)
        {
            cout << "W " << tab << DUMMY_TAB_1 << "| ";
        }
        else if (tab == 8)
        {
            cout << "S " << tab << DUMMY_TAB_1 << "| ";
        }
        else
        {
            cout << "  " << tab << DUMMY_TAB_1 << "| ";
        }

        for (int col = 0; col < BOARD_SIZE; col ++)
        {
            if (grid[row][col] == UNASSIGNED_VALUE)
            {
                cout << " ";
            }
            else
            {
                cout << grid[row][col];
            }
            cout << " | ";
        }
        cout << endl;
    }

    int row, col, num;
    if (CountBlankSpaces(grid) != 0)
    {
        cout << "\nYou have " << CountBlankSpaces(grid) << " blank field left." << endl;

        cout << "Enter the row: ";
        cin >> row;

        cout << "Enter the column: ";
        cin >> col;

        cout << "Enter the number that you want to enter in specified row and column: ";
        cin >> num;
        EnterNumber(grid, row - 1, col - 1, num);
    }
    else
    {
        char Option;

        cout << "\n\nCongratulations! You completed the Sudoku puzzle.\nWant to continue? (Y - Yes | N - No): ";
        cin >> Option;

        switch (Option)
        {
            case 'Y':
            {
                StartGame();
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

/**
 * Function: FillRandom()
 * Params: 
 *        - grid
 *              - The entered grid         
 * 
 * Returns:
 *        - none as it's a void function
 */
void FillRandom(int grid[BOARD_SIZE][BOARD_SIZE])
{
    for (int row = 0; row < BOARD_SIZE; row ++)
    {
        for (int col = 0; col < BOARD_SIZE; col ++)
        {
            int num = (rand() % 9) + 0;

            if (CanEnterNumber(grid, row, col, num))
            {
                grid[row][col] = num;
            }
            else
            {
                grid[row][col] = UNASSIGNED_VALUE;
            }
        }
    }
}

/**
 * Function: FillRandom()
 * Params: 
 *        - none         
 * 
 * Returns:
 *        - none as it's a void function
 */
void StartGame()
{
    int grid[BOARD_SIZE][BOARD_SIZE];
    
    FillRandom(grid);

    cout << PLAYER_HEADER << endl;

    cout << "Preparing game, please wait..." << endl;

    sleep(1);

    PrintGrid(grid);
}

int main()
{
    srand(time(NULL));

    StartGame();

    return 0;
}