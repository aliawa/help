
#include <iostream>
#include <iomanip>
#include <stdio.h>

using namespace std;

#define COLS 3
#define ROWS 4


// -----------------------------

void printrow(int row[])
{
    for (int i=0; i<COLS; ++i) {
        cout << row[i] << "  " ;
    }
    cout << endl << endl;
}


// -----------------------------

void printArray(char*** arr, int rows, int cols)
{
    for (int r=0; r<rows; ++r){
        for (int c=0; c<cols; ++c) {
            cout << arr[r][c] << " : " ;
        }
        cout << endl;
    }
}



// -----------------------------


void populateArray(char*** arr, int rows, int cols)
{
    for (int r=0; r<rows; ++r){
        for (int c=0; c<cols; ++c) {
            char* buff = new char[10];
            snprintf(buff, 5, "r%dc%d", r, c);
            arr[r][c] = buff;
        }
    }
}


// -----------------------------


int main(int argc, char** argv)
{
    int array[ROWS][COLS]= {1,2,3,
                            10,20,30,
                            100,200,300,
                            1000,2000,3000};

    for (int row=0; row<ROWS; ++row){
        for (int col=0; col < COLS; ++col){
            cout << setw(4) << array[row][col] << " ";
        }
        cout << endl ;
    }
    cout << endl;


    // treating it as one dimensional array
    for (int i=0; i<COLS*ROWS; ++i) {
        cout << array[0][i] << "  " ;
    }
    cout << endl;


    // passing a single row to a function that takes
    // one dimensional array as argument
    printrow(array[2]);


    // Dynamic array (NEW)
    int y = 5;
    int arry[y];


    // myArr is a pointer to an array of char**
    char**(*myArr) = new char**[5];
    // Now allocate columns
    for (int i=0; i<5; ++i) {
        myArr[i]= new char*[4];
    }

    populateArray(myArr, 5,4);
    printArray(myArr,5,4);

    // Deallocate array
    // first delete columns
    for (int i=0; i<5; ++i){
        for (int j=0; j<4; j++) {
            delete[] myArr[i][j];
        }
        delete[] myArr[i];
    }
    delete[] myArr;

}



