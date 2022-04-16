#include "graphmaker.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
using namespace std;
#ifndef DEBUG
#define DEBUG	true //false or true
#endif





/*
int * makearray(int arrOld[], ){

  int size;

  std::cin >> size;

  int *array = new int[size];

  delete [] array;

  return 0;
}
*/

int** historyInc(int** historyArr, int* rightShore, int* leftShore, int sizeold){

    if (DEBUG)  fprintf(stderr, "check 1\n");
    int sizeOfHistory;

    if (DEBUG)  fprintf(stderr, "HISTORY ARRAY values: R:%d , R:%d , R:%d , L:%d L:%d , L:%d \n", historyArr[0][0],historyArr[0][1],historyArr[0][2],historyArr[1][0],historyArr[1][1],historyArr[1][2]);

    if (historyArr[0][0]== 0 && historyArr[0][1]== 0 && historyArr[0][2]== 0 
    && historyArr[1][0]== 0 && historyArr[1][1]== 0 && historyArr[1][2]== 0){
        sizeOfHistory = 0;
    }else{
        sizeOfHistory = *(&historyArr + 1) - historyArr; 
    }
    //int sizeOfHistory = *(&historyArr + 1) - historyArr;
    if (DEBUG)  fprintf(stderr, "HISTORY ARRAY SIZE: %d\n", sizeOfHistory);


    // Dimensions of the 2D array
    int m = 2+sizeold;
    int n = 3; 
 
     int** a = new int*[m];
    if (DEBUG)  fprintf(stderr, "check 2\n");
 
    for (int i = 0; i < m; i++) {
 
        // Declare a memory block
        // of size n
        a[i] = new int[n];
    }
    if (DEBUG)  fprintf(stderr, "check 3\n");
    // Traverse the 2D array
   // int counter = 0;

    for (int i = 0; i < m; i++) {
        if(i < sizeOfHistory){
            a[i] = historyArr[i];  
        }else{
            a[i] = rightShore;
            a[i+1] = leftShore;
            break;
        }
    }
     if (DEBUG)  fprintf(stderr, "check 4\n");
 
  if (DEBUG){
 //DEBUG TIME!!
    // Traverse the 2D array
    int counter2 = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if(counter2 != i){
                cout << "\n";
                counter2++;
            }
            // Print the values of
            // memory blocks created
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
  }
     if (DEBUG)  fprintf(stderr, "check 5\n");
   /*
      //Delete the array created
      for(int i=0;i<m;i++)    //To delete the inner arrays
      delete [] a[i];   
      delete [] a;              //To delete the outer array
    //which contained the pointers
    //of all the inner arrays
    */
    if (DEBUG)  fprintf(stderr, "check 6\n");
    return a;

}

bool haveVisited(item* history, int* rightShore, int* leftShore){
    //if in histroy right and left shore ==  histroy[x],[y]
    //left shore is Y 
    //Right shore is X
    //History tracks pairs of shores
    int rows =  sizeof (history) / sizeof (history[0]);
    if (DEBUG)  fprintf(stderr, "FNC **haveVisited** rows: %d\n", rows);
    for (int i = 0; i < rows; i + 2) {
        if(
            history[i].rightShore[0] == rightShore[0] &&
            history[i].rightShore[1] == rightShore[1] &&
            history[i].rightShore[2] == rightShore[2] &&
            history[i+1].leftShore[0] == leftShore[0] &&
            history[i+1].leftShore[1] == leftShore[1] &&
            history[i+1].leftShore[2] == leftShore[1] 
        ){
            return false;
        }else{
            return true;
        }
    }
}

item* graphmaker(int * arrStart,int * arrEnd) {


    //create first array
    int** ARR = new int*[2];
    for(int i = 0; i < 2; ++i){
        ARR[i] = new int[3];
        ARR[i][0] = 0;
        ARR[i][1] = 0;
        ARR[i][2] = 0;
    }
    //int sizeOfHistory = *(&historyArr + 1) - historyArr;
    if (DEBUG)  fprintf(stderr, "HISTORY ARRAY =: %d\n", **ARR);

    int ** history = historyInc(ARR,arrStart,arrEnd,0); // start history

    //clean up array
    for(int i = 0; i < 2; ++i) {
    delete [] ARR[i];
    }
    delete [] ARR;

   // int sizeOfHistory = *(&history + 1) - history;
    
  if (DEBUG){
    cout << "afterHistory\n";
 //DEBUG TIME!!
    // Traverse the 2D array
    int counter2 = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            if(counter2 != i){
                cout << "\n";
                counter2++;
            }
            // Print the values of
            // memory blocks created
            cout << history[i][j] << " ";
        }
        cout << endl;
    }
  }

    /*rules
    Two chicks
    One chick
    Two Wolf
    One Wolf
    chick and wolf

    1 animal on board at all times
    */
  //code here
  /*
    while(arrStart[0]!= 0,arrStart[1]!= 0,arrStart[2]!= 0){ //while arrStart is not empty
        if(arrStart[0]!= 0,arrStart[1]!= 0,arrStart[2]!= 0);

    }
    */
   return history;
}