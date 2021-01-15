#include "suduko.h"
/*!
 * \brief suduko::isInRange Function to check if all elements of the vector store value in the range[1, 9]
 * \return false if vector in the range and true if not
 */
bool suduko::isInRange()
{
    for(int i = 0; i<number;i++){
        for(int j = 0;j<number;j++){
            if(grid[i][j] <= 0 || grid[i][j] > 9){
                return false;
            }
        }
    }
    return true;
}

/*!
 * \brief suduko::isValidSudoku Function to check if the solution of sudoku puzzle is valid or not
 * \return false if it is in the vector
 * false if current column have duplicate values
 * fasle if current block have duplicte value
 * true if all conditions satisfied
 */
bool suduko::isValidSudoku()
{
    if(isInRange() ==false){
        return false;
    }
    bool unique[number + 1];//store unique value from 1-number
    for(int i= 0;i<number;i++){
        memset(unique,false,sizeof (unique));
        for(int j=0;j < number;j++){
            int grids = grid[i][j];
            if(unique[grids]){
                return false;
            }
            unique[grids]=true;
        }
    }
    for(int i = 0;i < number ; i++){
        memset(unique,false,sizeof (unique));//Sets the first num bytes of the block of memory pointed by ptr to the specified value
        for (int j = 0; j < number;j++) {
            int grids = grid[j][i];
            // Initiliaze unique[]
            // array to false
            if (unique[grids]) {
                return false;
            }
            unique[grids] = true;
        }
    }
    for(int i = 0;i  < number -2; i +=3){
        for(int j = 0; j < number -2;j =+3){
            memset(unique,false,sizeof (unique));
            for(int k = 0; k < 3; k++){
                for(int l = 0; l < 3; l++){
                    int X = i + k;
                    int Y = k + l;
                    int Z = grid[X][Y];
                    if(unique[Z]){
                        return false;
                    }
                    unique[Z] = true;
                }
            }
        }
    }
    return true;
}



