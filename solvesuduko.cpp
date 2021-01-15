#include "suduko.h"

// UNASSIGNED is used for empty
// cells in sudoku grid
#define UNALIGNED 0

/*!
 * \brief suduko::SolveSudoku takes a partially filled-in grid and attempts to assign values to all unssigned locations in such a way to meet the requirements for Suduko solution
 * (non-duplication across rows, cols, and boxes)
 * \return true if there is no unassigned location so we are done
 * true if it sucess solving suduko. if not it it make umake and the run again
 * and return false if it triggers backtracking
 */
bool suduko::SolveSudoku(){
    int row , cols;
    if(!FindUnassignedLocation(row,cols)){
        return true;
    }
    for(int i = 1; i<= number ; i++){
        if(isSafe(row,cols,i)){
            grid[row][cols] = i;
            if(SolveSudoku()){
                return true;
            }
            grid[row][cols]= UNALIGNED;
        }
    }
    return false;
}
/*!
 * \brief suduko::FindUnassignedLocation search the grid to find en entry that is still unassigned
 * \param row define the column
 * \param col define the row
 * \return it return if found the reference parameters row, col will is returned.if no unnassigned entiries remain,false is returned
 */
bool suduko::FindUnassignedLocation(int& row, int& col){
    for(row = 0;row< 9;row++){
        for(col= 0;col< 9; col++){
            if(grid[row][col] == UNALIGNED){
                return true;
            }
        }
    }
    return false;
}
/*!
 * \brief suduko::UsedInRow
 * \param row define the row
 * \param num the number that will be checked
 * \return a boolean which indicates whether an assigned entry in the specified row matches the given number
 */
bool suduko::UsedInRow( int row, int num){
    for (int col = 0; col < 9; col++){
        if (grid[row][col] == num){
            return true;
        }
    }
    return false;
}
/*!
 * \brief suduko::UsedInCol
 * \param col define the column
 * \param num the number that will be checked
 * \return a boolean which indicates whether an assigned entry in the specified column matches the given number.
 */
bool suduko::UsedInCol( int col, int num){
    for (int row = 0; row < 9; row++){
        if (grid[row][col] == num){
            return true;
        }
    }
    return false;
}
/*!
 * \brief suduko::UsedInBox
 * \param boxStartRow
 * \param boxStartCol
 * \param num the number have been checked
 * \return a boolean which indicates whether an assigned entry within the specified 3x3 box matches the given number
 */
bool suduko::UsedInBox( int boxStartRow,int boxStartCol, int num){
    for (int row = 0; row < 3; row++){
        for (int col = 0; col < 3; col++){
            if (grid[row + boxStartRow][col + boxStartCol] == num){
                return true;
            }
        }
    }
    return false;
}
/*!
 * \brief suduko::isSafe
 * \param row define the row
 * \param col define the column
 * \param num the number have been checked
 * \return a boolean which indicates whether it will be legal to assign num to the given row, col location.
 */
bool suduko::isSafe( int row,int col, int num){
    return !UsedInRow( row, num)
              && !UsedInCol( col, num)
              && !UsedInBox( row - row % 3, col - col % 3, num)
              && grid[row][col] == UNALIGNED;
}
/*!
 * \brief suduko::getSolve
 * \param i define x
 * \param j define y
 * \return vector with x and y if the suduko is solved
 * false if not solved
 */
int suduko::getSolve(int i, int j)
{
    if(SolveSudoku() == true){
        return grid[i][j];
    }
    return false;
}
