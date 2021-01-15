#include "suduko.h"

/*!
 * \brief suduko::fillValues suduko generator
 */
void suduko::fillValues()
{
    // Fill the diagonal of 3 x 3 matrices
    fillDiagonal();

    // Fill remaining blocks
    fillRemaining(0, SRN);

    // Remove Randomly K digits to make game
     removeKDigits();
}

/*!
 * \brief suduko::fillDiagonal Fill the diagonal SRN number of 3 x 3 matrices
 */
void suduko::fillDiagonal()
{
    for(int i=0;i<number;i=i+SRN){
        fillBox(i,i);
    }
}

/*!
 * \brief suduko::unUsedInBox
 * \param rowStart define row
 * \param colStart define column
 * \param num number will be checked
 * \return false if given 3 x 3 block contains num.
 */
bool suduko::unUsedInBox(int rowStart, int colStart, int num)
{
    for(int i= 0;i< SRN;i++){
        for(int j=0;j< SRN;j++){
            if(grid[rowStart + i][colStart + j] == num){
                return false;
            }
        }
    }
    return true;
}
//
/*!
 * \brief suduko::CheckIfSafe Check if safe to put in cell
 * \param i x
 * \param j y
 * \param num number will be checked
 * \return the true if it safe to use
 */
bool suduko::CheckIfSafe(int i, int j, int num)
{
    return(unUsedInRow(i,num)&& unUsedInCol(j,num) && unUsedInBox(i-i%SRN,j-j%SRN,num));
}

/*!
 * \brief suduko::unUsedInRow check in the row for existence
 * \param i row
 * \param num number will be checked
 * \return return false if it is existence and true if not
 */
bool suduko::unUsedInRow(int i, int num)
{
    for(int j = 0;j< number;j++){
        if(grid[i][j] == num){
            return false;
        }
    }
    return true;
}
//
/*!
 * \brief suduko::unUsedInCol check in the row for existence
 * \param j column
 * \param num number will be checked
 * \return return false if it is existence and true if not
 */
bool suduko::unUsedInCol(int j, int num)
{
    for(int i = 0;i< number;i++){
        if(grid[i][j] == num){
            return false;
        }
    }
    return true;
}

/*!
 * \brief suduko::fillBox Fill a 3 x 3 matrix.
 * \param row define row
 * \param col define column
 */
void suduko::fillBox(int row, int col)
{
    int num;
    for(int i=0; i<SRN; i++){
        for(int j=0; j<SRN; j++){
            do{
                num = GenrateRandom(number);
            }while(!unUsedInBox(row,col,num));
            grid[row + i][col + j] = num;
        }
    }
}

/*!
 * \brief suduko::GenrateRandom Random generator
 * \param a range of the number
 * \return a random number between 0 and a
 */
int suduko::GenrateRandom(int a)
{
    std::uniform_int_distribution<int> dist(0, a);
    return dist(generator);
}

/*!
 * \brief suduko::fillRemaining A recursive function to fill remaining matrix
 * \param i define row
 * \param j define x
 * \return true when all grid is not empty and if it is safe to do it
 */
bool suduko::fillRemaining(int i, int j)
{
    if(j>= number && i<number -1){
        i = i + 1;
        j = 0;
    }
    if(i>=number && j>= number){
        return true;
    }
    if(i<SRN){
        if(j<SRN){
            j = SRN;
        }
    }else if(i < number -SRN){
        if(j == (int)(i/SRN)*SRN){
            j = j + SRN;
        }
    }else{
        if(j == number -SRN){
            i = i +1;
            j = 0;
            if(i >=number){
                return true;
            }
        }
    }
    for(int num = 1; num <= number; num++){
        if(CheckIfSafe(i,j,num)){
            grid[i][j] = num;
            if(fillRemaining(i,j +1)){
                return true;
            }
            grid[i][j] = 0;
        }
    }
    return false;
}

/*!
 * \brief suduko::removeKDigits Remove the K no. of digits to complete game
 */
void suduko::removeKDigits()
{
    int count = K;
    while (count != 0){
        int cellID = GenrateRandom(number*number);
        int i = (cellID/number);
        int j = cellID%9;
        if(j!= 0){
            j =j -1;
        }
        //std::cerr << i << " "<< j;
        if(i == 9){
            i--;
        }
        if(grid[i][j] != 0){
            count--;
            grid[i][j]= 0;
        }
    }
}

/*!
 * \brief suduko::GetValue get the numbers
 * \param x row
 * \param y column
 * \return number from the vector in the specific row and column
 */
int suduko::GetValue(int x, int y)
{
    return grid[y][x];
}



