#ifndef SUDUKO_H
#define SUDUKO_H

#include <vector>
#include <QObject>
#include <random>

using Matrix = std::vector<std::vector<int>>;
/*!
 * \brief The suduko class it is how to set up the game
 */
class suduko : public QObject{
Q_OBJECT;
public:
    suduko() = default;
    //copy assign
    suduko(const suduko& rhs);
    suduko& operator = (const suduko& rhs);
    ~suduko();
    //solve suduko
    bool SolveSudoku();
    bool UsedInCol( int col, int num);
    bool UsedInRow( int row, int num);
    bool UsedInBox( int boxStartRow,int boxStartCol, int num);
    bool FindUnassignedLocation(int& row, int& col);
    bool isSafe( int row,int col, int num);
    int getSolve(int i,int j);
    //generate suduku
    suduko(int K);
    void fillDiagonal();
    bool unUsedInBox(int rowStart, int colStart, int num);
    bool CheckIfSafe(int i,int j,int num);
    bool unUsedInRow(int i,int num);
    bool unUsedInCol(int j,int num);
    void fillBox(int row,int col) ;
    int GenrateRandom(int a);
    bool fillRemaining(int i, int j);
    void removeKDigits();
    void fillValues();
    int GetValue(int x , int y);
    //check if it is correct
    bool isInRange();
    bool isValidSudoku();
private:
    std::random_device device;
    std::mt19937 generator {device()};
    static constexpr const int number = 9;// number of columns/rows.
    Matrix grid{9,std::vector<int>(9)};
    const int SRN = 3;
    int K;// No. Of missing digits
};
#endif // SUDUKO_H
