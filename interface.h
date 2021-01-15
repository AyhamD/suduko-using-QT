#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTime>
#include <QTimer>
#include <QGridLayout>
#include <QLineEdit>
#include<stack>
#include<QRegExp>
#include<QRegExpValidator>
#include<QRadioButton>
#include<QGroupBox>
#include<string>
#include<QMessageBox>
#include <iostream>
#include <QApplication>
#include <QProcess>

#include "suduko.h"
/*!
 * \brief The cells class define the cells of the grid and it give every cell an ID
 */
class cells: public QLineEdit{
    Q_OBJECT;
public:
    /*!
     * \brief cells constructor
     * \param cellId the id that will give to every grid in the suduko game
     */
    cells(int cellId);
private:
    int cellId;
};
/*!
 * \brief The interface class define how the suduko will looks like and we arv QWidget
 */
class interface : public QWidget{
Q_OBJECT;
public:
    cells *cell[81];
    /*!
     * \brief interface constructor till calssen and it is the main window
     */
    interface();
    ~interface();
    void gameSet(int number);
public slots:
    void open();
    void solve();
    void soloutions();
private:
    QLabel* backgroundLabel ,*level,*backG,*wid, *lay;
    QPushButton *Generate, *slou, *undo, *solution;
    //QTime *time;
    //QTimer* timer;
    QWidget * widget;
    QGridLayout *grid;

    QRadioButton *L1,*L2,*L3,*L4;
    QVBoxLayout *vbox,*vl;
    QGroupBox * GB ;
    const int width= 9, lenght= 9;

    QPalette *palette;
    suduko s;

    bool gameIsRunning = false;
    bool isSolved();
};
#endif // INTERFACE_H
