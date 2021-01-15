#include "interface.h"


cells::cells(int cellId):cellId(cellId)
{
    //cellId = 0;//save the position of the cell
    //everytime we use QLineEdit every time the value will change and the slot recive the signel
    //connect(this,SIGNAL(textChanged(QString)),this,SLOT());
}

interface::interface():QWidget()
{
    setFixedSize(800,600);//size of window dimensions
    setWindowTitle("Sudoku"); //set title
    //set backgound window
    backgroundLabel = new QLabel(this);
    backgroundLabel->setGeometry(QRect(0,0,800,600));//setGeometry is funktion from Qwidget and it set the widget grapgics effect and QRect is to define that it is rectangle and with the (x,y,width,hight)
    backgroundLabel->lower();//Lowers the widget to the bottom of the parent widget's stack.

    //Generate button
    Generate = new QPushButton("New Game",this);//create button to create new puzzle
    Generate->setGeometry(QRect(200,550,110,30));
    Generate->setToolTip("Generate a Sudoku grid according to the level selected");
    Generate->setCheckable(true);
    //solve puzzle

    solution = new QPushButton("Solution",this);
    solution->setGeometry(QRect(480,550,110,30));
    solution->setToolTip("the Solution");
    //restart puzzle button
    slou = new QPushButton("Solve",this);
    slou->setGeometry(QRect(340,550,110,30));
    slou->setToolTip("to check if your solution is correct");
    //Undo button
    /*undo = new QPushButton("Undo", this);
    undo->setGeometry(QRect(410, 550,110,30));
    undo->setToolTip("Undo");*/
    //create time
    /*time = new QTime();
    time->setHMS(0,0,0,0);//start time
    timer= new QTimer(this);//start the timer
    timer->start(0);
    //create it in the window
    elaps = new QLabel("Elapsed Time:  ",this);
    //elaps->setText(timer);

    elaps->setGeometry(10,16,350,30);
    elaps->setStyleSheet(QLatin1String("font: 75 16pt \"Arial\";"));*/

    //create to level number
    level = new QLabel("Stage: " ,this);
    level->setGeometry(QRect(20,60,200,30));
    level->setStyleSheet(QLatin1String("font:75 16pt \"Arial\";"));

    //widget = new QWidget();
    //widget->setGeometry(QRect(10,50,460,460));
    wid = new QLabel(this);
    wid->setGeometry(300,50,45*9,45*9);
    grid = new QGridLayout(wid);

    //level
    backG = new QLabel(this);
    backG->setGeometry(QRect(20,250,200,150));
    L1= new QRadioButton("Easy");
    L2=new QRadioButton("Medium");
    L3=new QRadioButton("Hard");
    L4=new QRadioButton("Evil");
    vbox = new QVBoxLayout();
    vbox->addWidget(L1);
    vbox->addWidget(L2);
    vbox->addWidget(L3);
    vbox->addWidget(L4);
    GB = new QGroupBox();
    GB->setTitle("choose a level");
    GB->setLayout(vbox);
    vl= new QVBoxLayout(backG);
    vl->addWidget(GB);

    //connection
    connect(Generate,SIGNAL(toggled(bool)),this,SLOT(open()));
    connect(slou,SIGNAL(clicked()),this,SLOT(soloutions()));

    //creating cells
    //we have 81 cells so we create 2 for loop with the size of 9
    for(int i = 0;i< width;i++){
        for(int j = 0;j < lenght;j++){
            int value = i*width+j;
            cell[value]= new cells(value);

            cell[value]->setFixedSize(45,45);
            cell[value]->setFrame(true);//to make border
            QRegExp r("^[1-9]$");//exeptions to write only 1-9
            QRegExpValidator *val=new QRegExpValidator(r,cell[value]);
            cell[value]->setValidator(val);//apply validator
            cell[value]->setGeometry(QRect(0,0,200,30));
            grid->addWidget(cell[value],j,i);

            if(value<3 ||(value>5 && value<12) || (value>14 && value<21) ||(value>23 && value<27)||(value>53 && value<57)||(value>59 && value<66)||(value>68 && value<75) ||value>77 || (value>29 && value<33) || (value>38 && value<42) ||(value>47 && value<51)){
                cell[value]->setStyleSheet(QLatin1String("background-color: white;\n font: 75 16pt \"Arial\";"));
            }else
                cell[value]->setStyleSheet(QLatin1String("background-color: green;\n""font: 75 16pt \"Arial\";"));
            }
     }
}
interface::~interface()
{
    delete backgroundLabel;
    delete level;
    delete backG;
    delete lay;
    delete Generate;
    delete slou;
    delete undo;
    delete solution;
    delete widget;
    delete grid;
    delete L1;
    delete L2;
    delete L3;
    delete L4;
    delete vbox;
    delete vl;
    delete GB ;
}
void interface::gameSet(int number)
{
    gameIsRunning = true;
    suduko se(number);
    s = se;
    s.fillValues();
    for(int i = 0;i< width ; i++){
        for(int j=0;j< lenght;j++){
            int index = i*width +j;
            int value = s.GetValue(j,i);
            if(value == 0){
                cell[index]->setEnabled(true);
                cell[index]->setText("");
            }else{
                cell[index]->setEnabled(false);
                cell[index]->setText(std::to_string(value).c_str());
                connect(solution,SIGNAL(clicked()),this,SLOT(solve()));
            }
        }
    }
}
/*!
 * \brief interface::open it is a slots function that are connected with start button and with it will start a new game
 */
void interface::open()
{
    if(gameIsRunning ){
        qApp->quit();
        QProcess::startDetached(qApp->arguments()[0],qApp->arguments());
    }
    int x = 0;

    if(L1->isChecked()){//if the user use easy level
        Generate->setText("Give up");
        L2->setEnabled(false);
        L3->setEnabled(false);
        L4->setEnabled(false);
        x =1;
        level->setText("Level: Easy");
        gameSet(20);
    }else if(L2->isChecked()){
        Generate->setText("Give up");
        L1->setEnabled(false);
        L3->setEnabled(false);
        L4->setEnabled(false);
        x = 2;
        level->setText("Level: Medium");
        gameSet(40);
    }else if(L3->isChecked()){
        Generate->setText("Give up");
        L1->setEnabled(false);
        L2->setEnabled(false);
        L4->setEnabled(false);
        x = 3;
        level->setText("Level: Hard");
        gameSet(50);
    }else if(L4->isChecked()){
        Generate->setText("Give up");
        L1->setEnabled(false);
        L2->setEnabled(false);
        L3->setEnabled(false);
        x = 4;
        level->setText("Level: Evil");
        gameSet(60);
    }

    if(x ==0){//if the user didnot choose lvl
        QMessageBox::warning(this,"Level","Please select a level");
    }else if(x == 1 || x == 2){
        std::cerr << "";

    }
}
/*!
 * \brief interface::soloutions it connected with soloution button and it will solve sodoku
 */
void interface::soloutions()
{
    if(isSolved()){
        if(s.isValidSudoku()){
            int reps = QMessageBox::warning(this,"Good Job", "you have solved this sududo good job \n Would you like to start a new game?\n",QMessageBox::Yes,QMessageBox::No);
            if(reps == QMessageBox::Yes){
                if(gameIsRunning ){
                    qApp->quit();
                    QProcess::startDetached(qApp->arguments()[0],qApp->arguments());
                }
            }else if(reps == QMessageBox::No){
                QApplication::quit();
            }
        }else{
            int rep=QMessageBox::warning(this,"Error","You've made this Puzzle Unsolvable ! \n\n Would you like to Solve it or start a new game ?\n",QMessageBox::Yes,QMessageBox::No);
            if(rep == QMessageBox::Yes){
                solve();
            }else if(rep == QMessageBox::No){
                if(gameIsRunning ){
                    qApp->quit();
                    QProcess::startDetached(qApp->arguments()[0],qApp->arguments());
                }
            }
        }
    }else{
        QMessageBox::warning(this,"Wait", "you did not fill all boxes");
    }

}
/*!
 * \brief interface::isSolved check if it is empty
 * \return false if a it true and if it not empty and fasle if it is empty
 */
bool interface::isSolved()
{
    for(int i = 0; i< width;i++){
        for(int j = 0;j< lenght; j++){
            int index = i*width +j;
            auto a =cell[index]->displayText().isEmpty();
            if(a){
                return false;
            }
        }
    }
    return true;
}
/*!
 * \brief interface::solve to solve the puzzel
 */
void interface::solve()
{
    for(int i = 0;i< width ; i++){
        for(int j=0;j< lenght;j++){
            int index = i*width +j;
            cell[index]->setText(std::to_string(s.getSolve(i,j)).c_str());
            slou->setEnabled(false);
            solution->setEnabled(false);
        }
    }
}

