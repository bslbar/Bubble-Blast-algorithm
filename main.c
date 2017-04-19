#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ROWS_NUM 5
#define COLS_NUM 6
#define BASEOFNUMBOUBLE 4
#define NAMEFILEGAME "bouble-blast-game.txt"

//define prototypes
void setupMatrix(int matrix[][COLS_NUM]);
void printMatrix(int matrix[][COLS_NUM]);

int generateRandomStateBouble();
int generateInsertNumberRows();
int generateInsertNumberColumns();
int maxNumberOfBouble();

void populateMatrix(int matrix[][COLS_NUM]);
void copyMatrix(void * destmat, void * sourcemat);
bool foundNotZeroElement(int matrix[][COLS_NUM]);

void addSingleLine();
void addDoubleLine();
void printHelloWorld();

void handleExplosion(int x, int y, int matrix[x][y]);
void shiftRight(int x, int y, int matrix[x][y]);
void shiftDown(int x, int y, int matrix[x][y]);
void shiftLeft(int x, int y, int matrix[x][y]);
void shiftUp(int x, int y, int matrix[x][y]);


int calculateRobotMove(int x, int y, int matrix[][y]);
void printResultGame(int matrix[][COLS_NUM]);

int main() {
    int matrix[ROWS_NUM][COLS_NUM], matrixHumanGame[ROWS_NUM][COLS_NUM];
    //variable for check end game
    char stopGame;
    //count move robot and human
    int countRobotMove = 0, countHumanMove = 0;

    //coordinate of human's choice
    bool  humanVictory = false;
    int humanX, humanY;


    printHelloWorld();

    do{

        setupMatrix(matrix);
        addSingleLine();

        populateMatrix(matrix);
        copyMatrix(matrixHumanGame,matrix);
        printMatrix(matrix);
//        printResultGame(matrix);

        addDoubleLine();
        countRobotMove = calculateRobotMove(ROWS_NUM, COLS_NUM, matrix);

        printf("Robot move:%d\n",countRobotMove);
        addDoubleLine();

        do{

            printf("Insert row\n");
            scanf("%d",&humanX);
            if(humanX>=0 && humanX<ROWS_NUM)
                printf("Okay for inserting number!\n");
            else
                printf("Error, You have wronged the insert number!\n");

            printf("Insert column:\n");
            scanf("%d",&humanY);
            if(humanY>=0 && humanY<COLS_NUM)
                printf("Okay for inserting number!\n");
            else
                printf("Error, You have wronged the insert number!\n");
                countHumanMove++;
            if(matrixHumanGame[humanX][humanY]==1){
                printf("Good call! Element found!It is a 1!\n");
                matrixHumanGame[humanX][humanY]--;

                handleExplosion(humanX, humanY, matrixHumanGame);

            }else if(matrixHumanGame[humanX][humanY]==2 || matrixHumanGame[humanX][humanY]==3){
                matrixHumanGame[humanX][humanY]--;
                printf("Good call! Element found! It is a 2 or 3!\n");
            }else{
                printf("Missed!\n");
            }

            printMatrix(matrixHumanGame);

            addSingleLine();

            printf("This is you %d move. You have only %d moves left\n",countHumanMove, countRobotMove-countHumanMove);
            humanVictory= foundNotZeroElement(matrixHumanGame);

        }while(humanVictory != true && countRobotMove-countHumanMove>0);

        if(humanVictory==true)
            printf("You are the winner!\n");
        else
            printf("You have lost against the robot\n");

        printf("Do you wanna stopping your session's game?Press y for yes for stopping the game!\n");
        scanf(" %c",&stopGame);
    }while(stopGame!='y');
    printf("End game");
    return 0;
}

//define functions

/*
 * Name:        setupMatrix
 * Output:      void
 * Function:    we call this function if we want to create a new matrix populated with zero state
 */
void setupMatrix(int matrix[ROWS_NUM][COLS_NUM]){
    for (int i = 0; i < ROWS_NUM; ++i) {
        for (int j = 0; j < COLS_NUM; ++j) {
            matrix[i][j] = 0;
        }
    }
}

/*
 * Name:        printMatrix
 * Output:      void
 * Function:    you can print our matrix
 */
void printMatrix(int matrix[ROWS_NUM][COLS_NUM]){
    for (int i = 0; i < ROWS_NUM; ++i) {
        for (int j = 0; j < COLS_NUM; ++j) {
            printf("%d",  matrix[i][j]);
        }
        printf("\n");
    }
}

/*
 * Name:        foundNotZeroElement
 * Output:      boolean
 * Function:    searching an element inside our matrix different than 0.
 *              If we found, we will return true otherwise we will return false
 */
bool foundNotZeroElement(int matrix[ROWS_NUM][COLS_NUM]){
    bool notFound = true;
    for (int i = 0; i < ROWS_NUM; ++i) {
        for (int j = 0; j < COLS_NUM; ++j) {
            if(matrix[i][j]>0){
                notFound = false;
                break;
            }
        }
    }
    return notFound;
}

/*
 * Name:        generateRandomStateBouble
 * Output:      int
 * Function:    return a random number for generation
 *
 */
int generateRandomStateBouble(){
    srand((unsigned)time(NULL));
    return rand()%3+1;
}

/*
 * Name:        generateInsertNumberRows
 * Output:      int
 * Function:    return a random number for generation
 *
 */
int generateInsertNumberRows(){
    srand((unsigned)time(NULL));
    return rand()%ROWS_NUM;
}

/*
 * Name:        generateInsertNumberColumns
 * Output:      int
 * Function:    return a random number for generation
 *
 */
int generateInsertNumberColumns(){
    srand((unsigned)time(NULL));
    return rand()%COLS_NUM;
}

/*
 * Name:        maxNumberOfBouble
 * Output:      int
 * Function:    create a limit
 *              
 */
int maxNumberOfBouble(){
    return ROWS_NUM*COLS_NUM/BASEOFNUMBOUBLE;
}

/*
 * Name:        populateMatrix
 * Output:      void
 * Function:    insert a random number inside our matrix
 *
 */
void populateMatrix(int matrix[ROWS_NUM][COLS_NUM]){
    int remainedBouble = maxNumberOfBouble();
    do{
        int row = generateInsertNumberRows();
        int col = generateInsertNumberColumns();
        if(matrix[row][col] == 0){
            matrix[row][col] = generateRandomStateBouble();
            remainedBouble--;
        }
    }while(remainedBouble != 0);
}

/*
 * Name:        copyMatrix
 * Output:      void
 * Function:    create a new memory allocation with a new matrix.
 *              Its rows and columns will be like the matrix target
 */
void copyMatrix(void * destmat, void * sourcemat){
    memcpy(destmat,sourcemat, ROWS_NUM*COLS_NUM*sizeof(int));
}

/*
 * Name:        printHelloWorld
 * Output:      void
 * Function:    Print the rules of this game
 *
 */
void printHelloWorld(){
    printf("Hello world! Bouble blast");
    printf("Instructions:\n");
    printf("First rule: You have a limited moves. If you go over than robot moves you will loose but you will win if you will finish before robot moves.\n");
    printf("Second rule: You will see only one time the matrix so you have to image your moves if you want to win.\n");
    printf("Attention! You have to keep in mind rows and columns start from zero.\n");
}

/*
 * Name:        addSingleLine
 * Output:      void
 * Function:    add a single line for our program
 *
 */
void addSingleLine(){
    printf("\n");
}

/*
 * Name:        addDoubleLine
 * Output:      void
 * Function:    add a double line
 *
 */
void addDoubleLine(){
    printf("\n\n");
}

/*
 * Name:        calculateRobotMove
 * Output:      int
 * Function:    calculate a random number of playing.
 *              The logic behind it's to skim the matrix.
 *              When it finds a not zero number, it will reproduce a bomb attack that we will count as a new move.
 *              This logic will be reproduce until we will skim the matrix but we did not find a zero.
 *
 */
int calculateRobotMove(int x, int y, int matrix[ROWS_NUM][COLS_NUM]){

    int countMoveMachine = 0;
    bool conditionToContinue;
    do{
        conditionToContinue = true;
        for (int i = 0; i < x;i++) {
            for (int j = 0; j < y; ++j) {
                if (matrix[i][j] == 1){
                    matrix[i][j]--;
                    handleExplosion(x,y,matrix);
                    conditionToContinue = false;
                    countMoveMachine++;
                }else if(matrix[i][j]== 2 || matrix[i][j]== 3){
                    matrix[i][j]--;
                    conditionToContinue = false;
                    countMoveMachine++;
                }
            }
        }
    }while(conditionToContinue==false);
    return countMoveMachine;

}


/*
 * Name:        handleExplosion
 * Output:      void
 * Function:    this test show us if a cell inside matrix contains a number.
 *              If will find, we will handle the bomb
 *
 */
void handleExplosion(int x, int y, int matrix[ROWS_NUM][COLS_NUM]){

    shiftRight(x,y, matrix);
    shiftDown(x, y, matrix);
    shiftLeft(x, y, matrix);
    shiftUp(x, y, matrix);
    return;
}

/*
 * Name:        shiftRight
 * Output:      void
 * Function:    handle a right shift.
 *              We will skim matrix until, we will find a number.
 *              If we do not find a number, we will return nothing.
 */
void shiftRight(int x, int y, int matrix[ROWS_NUM][COLS_NUM]){
    bool end = false;

    if(y<COLS_NUM-1){
        y++; //added one for skimming to right
        do{
            if(matrix[x][y]!=0){
                //handle explosion
                end = true;
                if (matrix[x][y]  == 1){
                    matrix[x][y]--;
                    handleExplosion(x,y--,matrix);
                }else{
                    //matrix[x][y] == 3 || matrix[x][y] == 2
                    matrix[x][y]--;
                }
            }else{
                y++;
                if(y==COLS_NUM)
                    end = true;
            }
        }while(end != true);
    }

    return;
}

/*
 * Name:        shiftDown
 * Output:      void
 * Function:    handle a down shift.
 *              We will skim matrix until, we will find a number.
 *              If we do not find a number, we will return nothing.
 */
void shiftDown(int x, int y, int matrix[ROWS_NUM][COLS_NUM]){
    bool end = false;

    if (x<ROWS_NUM-1){
        x++; //added one for skimming to down
        do{
            if(matrix[x][y]!=0){
                //handle explosion
                end = true;
                if (matrix[x][y]  == 1){
                    matrix[x][y]--;
                    handleExplosion(x--,y,matrix);
                }else{
                    //matrix[x][y] == 3 || matrix[x][y] == 2
                    matrix[x][y]--;
                }
            }else{
                x++;
                if (x==ROWS_NUM)
                    end =true;
            }
        }while(end != true);
    }

    return;
}

/*
 * Name:        shiftLeft
 * Output:      void
 * Function:    handle a left shift.
 *              We will skim matrix until, we will find a number.
 *              If we do not find a number, we will return nothing.
 */
void shiftLeft(int x, int y, int matrix[ROWS_NUM][COLS_NUM]){
    bool end = false;

    if(y>0){
        y--; //added one for skimming to left
        do{
            if(matrix[x][y]!=0){
                //handle explosion
                end = true;
                if (matrix[x][y]  == 1){
                    matrix[x][y]--;
                    handleExplosion(x,y++,matrix);
                }else{
                    //matrix[x][y] == 3 || matrix[x][y] == 2
                    matrix[x][y]--;
                }
            }else{
                y--;
                if ( y <0)
                    end = true;
            }
        }while(end != true);
    }else{
        return;
    }

    return;

}

/*
 * Name:        shiftUp
 * Output:      void
 * Function:    handle an up shift.
 *              We will skim matrix until, we will find a number.
 *              If we do not find a number, we will return nothing.
 */
void shiftUp(int x, int y, int matrix[ROWS_NUM][COLS_NUM]){
    bool end = false;

    if(x > 0){
        x--; //added one for skimming to up
        do{
            if( matrix[x][y]!=0){
                //handle explosion
                end = true;
                if ( matrix[x][y]  == 1){
                    matrix[x][y]--;
                    handleExplosion(x++,y,matrix);
                }else{
                    //matrix[x][y] == 3 || matrix[x][y] == 2
                    matrix[x][y]--;
                }
            }else{
                x--;
                if( x <= 0)
                    end =true;
            }
        }while(end != true);
    }else{
        return;
    }

    return;
}

/*
 * Name:        printResultGame
 * Output:      void
 * Function:    handle i/o files.
 *              It will handle the creation of a new text file.
 *              a+ represent Opens a text file for writing in appending mode.
 *              If it does not exist, then a new file is created.
 */
void printResultGame(int matrix[ROWS_NUM][COLS_NUM]){
    FILE *file_results;
    file_results = fopen(NAMEFILEGAME, "a+");

    if (file_results == NULL) {
        printf("I cannot write inside the file %s\n", NAMEFILEGAME);
        exit(-1);
    }

    fprintf(file_results, "Set-up matrix:\n");
    for (int i = 0; i < ROWS_NUM; ++i) {
        for (int j = 0; j < COLS_NUM; ++j) {
            fprintf(file_results, "%d", matrix[i][j]);
        }
        fprintf(file_results, "\n");
    }

    fprintf(file_results, "\n");

    fclose(file_results);

}

