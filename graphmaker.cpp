#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "graphmaker.h"
using namespace std;

//This files is for graph making and utility functions


#ifndef DEBUG
#define DEBUG	false //false or true
#endif

#ifndef DEBUGQ //debugging queue
#define DEBUGQ	false //false or true
#endif

#ifndef DEBUGCOMBINE //debugging queue
#define DEBUGCOMBINE	false //false or true
#endif

int nodesExp(bool* visited, int size) {
    int counter = 0;
    for (int x = 0; x < size; x++) {
        if (visited[x]) counter++;
    }
    return counter;
}

void print_array(int* arr, int size)
{
    //cout << '\n';
    for (int x = 0; x < size - 1; x++) {
        printf("%d,", arr[x]);
    }
    printf("%d", arr[size - 1]);
    printf("\n");
}

void print_array(item* arr)
{
    int size = arr[0].arrSize;

    if (DEBUG) {
        printf("\n***DEBUG PRINT ARRAY******\n");
        printf("Array size     : %d\n", size);
    }

    for (int x = 0; x < size; x++) {

        printf("**************************\n");
        printf("Array index    : %d\n", x);
        printf("Leftshore      : %d,%d,%d\n", arr[x].leftShore[0], arr[x].leftShore[1], arr[x].leftShore[2]);
        printf("Rightshore     : %d,%d,%d\n", arr[x].rightShore[0], arr[x].rightShore[1], arr[x].rightShore[2]);
        printf("Prority number : %d\n", arr[x].priority);
        printf("Parent number  : %d\n", arr[x].parent);
        if (arr[x].arrSize > 0) { printf("Array Size     : %d\n", arr[x].arrSize); }
        printf("**************************\n");

    }
}

void print_item(item arr)
{
    //int size = arr[0].arrSize;

    if (DEBUG) {
        printf("\n***DEBUG PRINT ITEM******\n");
    }


    printf("**************************\n");
    printf("Leftshore      : %d,%d,%d\n", arr.leftShore[0], arr.leftShore[1], arr.leftShore[2]);
    printf("Rightshore     : %d,%d,%d\n", arr.rightShore[0], arr.rightShore[1], arr.rightShore[2]);
    printf("Prority number : %d\n", arr.priority);
    printf("Parent number  : %d\n", arr.parent);
    if(arr.arrSize > 0){ printf("Array Size     : %d\n", arr.arrSize); }
    printf("**************************\n");

    
}

bool compaireItem(item history, item newMove) {
    if (history.leftShore[0] == newMove.leftShore[0] &&
        history.leftShore[1] == newMove.leftShore[1] &&
        history.leftShore[2] == newMove.leftShore[2])
    {
       // printf("true");
        return true;

    }
    else
    {
        return false;
    }
}

//Rules**

// [0] == chicks [1] == wold [2] == boat 
bool twochick(item current) {
    if (current.leftShore[2] == 1) { //check if boat left or right : Left here
        if (current.leftShore[0] >= 2) { // if leftshore has 2 or more rabbit move legal.
            return true;
        }
    }
    else { //check if boat left or right : Right here
        if (current.rightShore[0] >= 2) { // if Rightshore has 2 or more rabbit move legal.
            return true;
        }
    }
    return false;
}
bool twowolf(item current) {
    if (current.leftShore[2] == 1) { //check if boat left or right : Left here
        if (current.leftShore[1] >= 2) { // if leftshore has 2 or more wolf move legal.
            return true;
        }
    }
    else { //check if boat left or right : Right here
        if (current.rightShore[1] >= 2) { // if Rightshore has 2 or more wolf move legal.
            return true;
        }
    }
    return false;

}
bool onewolf(item current) {
    if (current.leftShore[2] == 1) { //check if boat left or right : Left here
        if (current.leftShore[1] >= 1) { // if leftshore has 1 or more wolf move legal.
            return true;
        }
    }
    else { //check if boat left or right : Right here
        if (current.rightShore[1] >= 1) { // if Rightshore has 1 or more wolf move legal.
            return true;
        }
    }
    return false;
}
bool onechick(item current) {
    if (current.leftShore[2] == 1) { //check if boat left or right : Left here
        if (current.leftShore[0] >= 1) { // if leftshore has 1 or more rabbit move legal.
            return true;
        }
    }
    else { //check if boat left or right : Right here
    if (current.rightShore[0] >= 1) { // if Rightshore has 1 or more rabbit move legal.
        return true;
    }
    }
    return false;
}
bool chickandwolf(item current) {
    if (current.leftShore[2] == 1) { //check if boat left or right : Left here
        if (current.leftShore[1] >= 1 && current.leftShore[0] >= 1) { // if leftshore has 1 or more rabbit move legal.
            return true;
        }
    }
    else { //check if boat left or right : Right here
        if (current.rightShore[1] >= 1 && current.rightShore[0] >= 1) { // if Rightshore has 1 or more rabbit move legal.
            return true;
        }
    }
    return false;
}

item* incReturnArr(item* returnArr, item newItem) {

    int old_size = returnArr[0].arrSize;
    int new_size = returnArr[0].arrSize + 1;

    if (DEBUG) {
        printf("OLD SIZE ARRAY: %d\n", old_size);
        printf("\n** ADDING newItem LS: %d,%d,%d : newItem Rightshore %d,%d,%d\n",
            newItem.leftShore[0], newItem.leftShore[1], newItem.leftShore[2],
            newItem.rightShore[0], newItem.rightShore[1], newItem.rightShore[2]);
    }

    //copy files to new array
    item* newArr = new item[old_size + 1];
    if (DEBUG) printf("New SIZE ARRAY: %d\n", new_size);

    for (int x = 0; x < old_size; x++) {
        newArr[x] = returnArr[x];
    }

    newArr[old_size] = newItem;//add item
    newArr[0].arrSize = new_size; // inc arrsize
    delete[]returnArr;
    returnArr = newArr;
    newArr = NULL;//null pointer
    return returnArr;

}

item* combineItemArr(item* returnArr, item* newItem) {

    int old_size_1 = returnArr[0].arrSize;
    int old_size_2 = newItem[0].arrSize;
    int new_size = old_size_1 + old_size_2;

    if (DEBUGCOMBINE) {
        printf("OLD SIZE ARRAY 1: %d\n", old_size_1);
        printf("OLD SIZE ARRAY 1: %d\n", old_size_2);
    }

    //copy files to new array
    item* newArr = new item[new_size];
    
    //copy first half to new array
    if (DEBUGCOMBINE) printf("New SIZE ARRAY: %d\n", new_size);
    for (int x = 0; x < old_size_1; x++) {//add current array to front
        newArr[x] = returnArr[x];
        newArr[x].arrSize = 0; //resets old array numbers
    }
    


    if (DEBUGCOMBINE) {
        printf("COMBINING ARRAY PRINTING OLD:\n");
        print_array(newArr);
    }
    //copy last half to new array
    for (int x = old_size_1; x < new_size; x++) { //and new array to back
        newArr[x] = newItem[x - old_size_1];
        newArr[x].arrSize = 0;
    }

    //newArr[0].arrSize = new_size;//set new array size
    if (DEBUGCOMBINE) {
        printf("COMBINING ARRAY PRINTING COMPLETE:\n");
        print_array(newArr);
    }

    //newArr[old_size] = newItem;//add item
    newArr[0].arrSize = new_size; // inc arrsize
    if (DEBUGCOMBINE)printf("DELETING OLD ARRAYS");
    delete[]returnArr;
    delete[]newItem;
    returnArr = newArr;
    newArr = NULL;//null pointer
    if (DEBUGCOMBINE)printf("NEW ITEM == NULL");
    newItem = NULL;
    return returnArr;

}

item* removeBack(item* returnArr) {

    int old_size = returnArr[0].arrSize;
    int new_size = returnArr[0].arrSize - 1;

    //copy files to new array
    item* newArr = new item[new_size];
    if (DEBUG) printf("New SIZE ARRAY: %d\n", new_size);

    for (int x = 0; x < new_size; x++) {
        newArr[x] = returnArr[x];
    }

    newArr[0].arrSize = new_size; // inc arrsize
    delete[]returnArr;
    returnArr = newArr;
    newArr = NULL;//null pointer
    return returnArr;

}

item* removeFront(item* returnArr) {

    int old_size = returnArr[0].arrSize;
    int new_size = returnArr[0].arrSize - 1;

    //copy files to new array
    item* newArr = new item[new_size];
    if (DEBUG) printf("New SIZE ARRAY: %d\n", new_size);

    for (int x = 0; x < new_size; x++) {
        newArr[x] = returnArr[x+1];
    }

    newArr[0].arrSize = new_size; // inc arrsize
    delete[]returnArr;
    returnArr = newArr;
    newArr = NULL;//null pointer
    return returnArr;

}


//used for cloning array
item* copyGraph(item* returnArr) {

    int old_size = returnArr[0].arrSize;

    //copy files to new array
    item* newArr = new item[old_size];
    if (DEBUG) printf("COPY SIZE ARRAY: %d\n", old_size);

    for (int x = 0; x < old_size; x++) {
        newArr[x] = returnArr[x];
    }
    return newArr;

}

//gets all children of current parent node.
//if it can't find a children it returns the parent.
item* createQueue(item* returnArr,int parent) {
    int old_size = returnArr[0].arrSize;

    //copy files to new array
    item* newArr = new item[1];
    newArr[0] = returnArr[parent];
    newArr[0].arrSize = 0;
    if (DEBUGQ) printf("\nPRINTING QUEUE: %d\n");

    for (int x = parent; x < old_size; x++) { //parent is priority node, so to save time we can start at parent because all child nodes will be larger

        if (parent == returnArr[x].parent) {
            if (returnArr[x].parent != returnArr[x].priority) {// checking for base node
                if (DEBUGQ) printf("\nQUEUE OLD LIST:\n");
                item holder = returnArr[x];
                //if (DEBUGQ) print_item(holder);

                if (newArr[0].arrSize == 0) { // get first item
                    newArr[0] = holder;
                    newArr[0].arrSize = 1;
                }
                else { //inc rest
                    newArr = incReturnArr(newArr, holder);
                }
                //newArr = incReturnArr(newArr, holder);
                if (DEBUGQ) printf("\nQUEUE NEW LIST:\n");
                if (DEBUGQ) print_array(newArr);
            }
        }           
    }
    return newArr;
}


//0 == chick
//1 == wolf
//2 == boat

bool isValid(item newMove) {
    //IF leftshore != 0 then check if leftshore Greater then right shore
    bool leftside = false;
    bool rightside = false;


    //if shore is not == 0 then check if valid
    if (newMove.leftShore[0] != 0) {
        if (newMove.leftShore[0] >= newMove.leftShore[1]) {
            leftside = true;
        }
        else {
            leftside = false;
        }
        
    }
    if (newMove.rightShore[0] != 0) {
        if (newMove.rightShore[0] >= newMove.rightShore[1]) {
            rightside = true;
        }
        else {
            rightside = false;
        }

    }
    //if leftshore is 0 check for valid right side.
    if (newMove.leftShore[0] == 0) {
        if (newMove.rightShore[0] >= newMove.rightShore[1]) {
            leftside = true;
            rightside = true;
        }
        else {
            rightside = false;
        }
    }
    //if rightshore is 0 check for valid left side.
    if (newMove.rightShore[0] == 0) {
        if (newMove.leftShore[0] >= newMove.leftShore[1]) {
            leftside = true;
            rightside = true;
        }
        else {
            leftside = false;
        }
    }

    bool finaly = false;

    //if left shore all == 0  then if you have parent 0 then but not priority 0 then you must be false.

    if (leftside && rightside) { //if left and right are true return true
        finaly = true;
    }
    return finaly;
}

//see if current win con is a valid win con
bool winConLite(item newMove) {
    if (
        newMove.rightShore[0] == 0 &&
        newMove.rightShore[1] == 0 &&
        newMove.rightShore[2] == 0
        ) {
        return true;
    }
    else {
        return false;
    }
}
//see if current win con is a valid win con
bool winCon(item* history, item newMove) {
    bool winCondition = false;
    int counter = 0;
    if (
        newMove.rightShore[0] == 0 &&
        newMove.rightShore[1] == 0 &&
        newMove.rightShore[2] == 0
        ) {
        
        int rows = history[0].arrSize;
        if (isValid(newMove)){
            if (DEBUG) printf("\nSTARTING WIN CONDITION\n");
            for (int i = 0; i < rows; i++) {
                
                if (newMove.parent == 0) { //if parent is root node then we have our solution
                    counter++;
                    newMove = history[0];
                    //ROOT NODE
                    if (DEBUG)  {
                        printf("\n***Returning True***\n");
                        printf("\nNUMBER OF NODES TO GET TO SOLUTION : %d\n", counter);
                        print_item(newMove);
                        printf("\n***Returning True***\n");
                    }
                    winCondition = true;
                    return true;
                }
                //if found previous parent.
                if (newMove.parent == history[i].priority) {
                    counter++;
                    if (DEBUG) {
                        printf("\nchild\n");
                        print_item(newMove);
                    }
                    newMove = history[i];
                    if (isValid(newMove)) {
                        i = 0;
                    }
                    else {
                        return false;
                    }
                    if (DEBUG) {
                        printf("\nPARENT\n");
                        print_item(newMove);
                    }
                }
            }
        }
    }else {
        return false;
    }
    return winCondition;
}
//see if current win con is a valid win con
void winConPrint(item* history, item newMove) {
    //bool winCondition = false;
    int counter = 0;
    if (
        newMove.rightShore[0] == 0 &&
        newMove.rightShore[1] == 0 &&
        newMove.rightShore[2] == 0
        ) {

        int rows = history[0].arrSize;
        if (isValid(newMove)) {
            for (int i = 0; i < rows; i++) {

                if (newMove.parent == 0) { //if parent is root node then we have our solution
                    counter++;
                    newMove = history[0];
                    //ROOT NODE
                    printf("\n***ROOT NODE***\n");
                    print_item(newMove);
                    printf("\n***ROOT NODE***\n");
                    printf("STEPS FROM ROOT TO SOLUTION : %d\n", counter);
                    break;
                }
                //if found previous parent.
                if (newMove.parent == history[i].priority) {
                    counter++;

                    
                    print_item(newMove);
                    //printf("\n**************************\n");
                    printf("\nCHILD ABOVE |*| PARENT BELOW\n");
                    newMove = history[i];
                    if (isValid(newMove)) {
                        i = 0;
                    }
                    else {
                        printf("\nERROR IN WINCONPRINT\n");
                    }
                }
            }
        }
    }
    else {
        printf("\nERROR IN WINCONPRINT 2\n");
    }
}

int distanceFromRoot(item* history, item newMove) {
    //bool winCondition = false;
    int counter = 0;
    
    int rows = history[0].arrSize;

    for (int i = 0; i < rows; i++) {

        if (newMove.parent == 0) { //if parent is root node then we have our solution
            counter++;
            newMove = history[0];
            //ROOT NODE
            break;
        }
        //if found previous parent.
        if (newMove.parent == history[i].priority) {
            counter++;
            newMove = history[i];
        }
    }
    return counter;
}

//If an element has the same value as a pervious element then that is the same element. So priority is == to the previous priority.
item graphCombo(item* history, item newMove) { //modifies item if items value is == to a previous value, 
    //if old ls == new ls 
    //if old rs == new rs
    //newitem.priority == old priority.
    int size = history[0].arrSize;
    for (int i = 0; i < size; i++) {
        if (compaireItem(history[i], newMove)) {
            newMove.priority = history[i].priority;
        }
    }
    return newMove;

}

//adds item to graph, and preforms check
// 1.)check to see if move allready existed in list if so then change priority number to match old listing.
item* addNewItem(item* returnArray, item newMove, item currentMove, int counter) { //modifies item if items value is == to a previous value, 
    newMove.parent = currentMove.priority;
    newMove.priority = counter;//increment counter to keep track of prority
    newMove = graphCombo(returnArray,newMove); //check to see if move allready existed in list if so then change priority number to match old listing.
    if (DEBUG) printf("ADDING TWO CHICKS TO ARR\n");
    returnArray = incReturnArr(returnArray, newMove);//add new item to return array
    if (DEBUG) printf("ENDED ADDING\n");
    return returnArray;

}

//item* iddfs


//Graphmaker makes a graph with this the conditions set by the input file
//Makes graph and tree branches defined by rules set by chick wolf boat


item* graphmaker(int * arrStart,int * arrEnd) {

  //Set up fist array
  item startingValues;
  startingValues.leftShore[0] = arrEnd[0];
  startingValues.leftShore[1] = arrEnd[1];
  startingValues.leftShore[2] = arrEnd[2];
  startingValues.rightShore[0] = arrStart[0];
  startingValues.rightShore[1] = arrStart[1];
  startingValues.rightShore[2] = arrStart[2];
  startingValues.priority = 0;
  startingValues.parent = 0;
  startingValues.arrSize = 1;
  //end Set up fist array

  //item * history = new item[1];
  item * returnArray = new item[1];// return array
  returnArray[0] = startingValues;
 // history[0] = startingValues


  bool loop = true; //breaks loop if complete
  int counter = 1; // keeps track of Priority. starts at 1 because returnArray[0] is prority 0 
  int loopCounter = 0; //keeps track of returnArray index
  //this loop creates a min heap. where 0 is the top of the que and inc as the que grows
  bool winCondition = false;
  while(loop) {
      item currentMove = returnArray[loopCounter];
      int parent = currentMove.parent;
      int priority = currentMove.priority;
      currentMove.arrSize = 0; //change arraySize to zero because not first element
      //*********************twochick 
      if(twochick(currentMove)) {
          if (DEBUG) printf("SELECTING TWO CHICKS\n");
          //Make new move
          item newMove = currentMove;
          //if (DEBUG)  printf("\nPre change newMove new values in twochick is %d,%d\n", newMove.leftShore[0], newMove.rightShore[0]);
          if (newMove.leftShore[2] == 1) { //check if boat left or right : Left here
              //move animal
              newMove.leftShore[0] = (newMove.leftShore[0] - 2);
              newMove.rightShore[0] = (newMove.rightShore[0] + 2);
              //move boat
              newMove.rightShore[2] = 1;
              newMove.leftShore[2] = 0;
          }
          else { //check if boat left or right : Right here
              //move animal
              newMove.leftShore[0] = newMove.leftShore[0] + 2;
              newMove.rightShore[0] = newMove.rightShore[0] - 2;
              //move boat
              newMove.rightShore[2] = 0;
              newMove.leftShore[2] = 1;
          }
          if (isValid(newMove)) {
              returnArray = addNewItem(returnArray, newMove, currentMove, counter);
              counter++;
              winCondition = winCon(returnArray, returnArray[returnArray[0].arrSize]);//Checks win con from last added node.
          }
      }
      if (winCondition == true) {
          break;
      }

      //*********************onechick 
      if (onechick(currentMove)) {
          if (DEBUG) printf("SELECTING ONE CHICKS\n");
          //Make new move
          item newMove = currentMove;
          //if (DEBUG)  printf("\nPre change newMove new values in twochick is %d,%d\n", newMove.leftShore[0], newMove.rightShore[0]);
          if (newMove.leftShore[2] == 1) { //check if boat left or right : Left here
              //move animal
              newMove.leftShore[0] = (newMove.leftShore[0] - 1);
              newMove.rightShore[0] = (newMove.rightShore[0] + 1);
              //move boat
              newMove.rightShore[2] = 1;
              newMove.leftShore[2] = 0;
          }
          else { //check if boat left or right : Right here
              //move animal
              newMove.leftShore[0] = newMove.leftShore[0] + 1;
              newMove.rightShore[0] = newMove.rightShore[0] - 1;
              //move boat
              newMove.rightShore[2] = 0;
              newMove.leftShore[2] = 1;
          }
          if (isValid(newMove)) {
              returnArray = addNewItem(returnArray, newMove, currentMove, counter);
              counter++;
              winCondition = winCon(returnArray, returnArray[returnArray[0].arrSize]);//Checks win con from last added node.
          }
      }
      if (winCondition == true) {
          break;
      }
      //*********************twowolf 
      if (twowolf(currentMove)) {
          if (DEBUG) printf("SELECTING TWO WOLFS\n");
          //Make new move
          item newMove = currentMove;
          //if (DEBUG)  printf("\nPre change newMove new values in twochick is %d,%d\n", newMove.leftShore[0], newMove.rightShore[0]);
          if (newMove.leftShore[2] == 1) { //check if boat left or right : Left here
              //move animal
              newMove.leftShore[1] = (newMove.leftShore[1] - 2);
              newMove.rightShore[1] = (newMove.rightShore[1] + 2);
              //move boat
              newMove.rightShore[2] = 1;
              newMove.leftShore[2] = 0;
          }
          else { //check if boat left or right : Right here
              //move animal
              newMove.leftShore[1] = newMove.leftShore[1] + 2;
              newMove.rightShore[1] = newMove.rightShore[1] - 2;
              //move boat
              newMove.rightShore[2] = 0;
              newMove.leftShore[2] = 1;
          }
          if (isValid(newMove)) {
              returnArray = addNewItem(returnArray, newMove, currentMove, counter);
              counter++;
              winCondition = winCon(returnArray, returnArray[returnArray[0].arrSize]);//Checks win con from last added node.
          }
      }
      if (winCondition == true) {
          break;
      }
      //*********************onewolf 
      if (onewolf(currentMove)) {
          if (DEBUG) printf("SELECTING ONE WOLFS\n");
          //Make new move
          item newMove = currentMove;
          //if (DEBUG)  printf("\nPre change newMove new values in twochick is %d,%d\n", newMove.leftShore[0], newMove.rightShore[0]);
          if (newMove.leftShore[2] == 1) { //check if boat left or right : Left here
              //move animal
              newMove.leftShore[1] = (newMove.leftShore[1] - 1);
              newMove.rightShore[1] = (newMove.rightShore[1] + 1);
              //move boat
              newMove.rightShore[2] = 1;
              newMove.leftShore[2] = 0;
          }
          else { //check if boat left or right : Right here
              //move animal
              newMove.leftShore[1] = newMove.leftShore[1] + 1;
              newMove.rightShore[1] = newMove.rightShore[1] - 1;
              //move boat
              newMove.rightShore[2] = 0;
              newMove.leftShore[2] = 1;
          }
          if (isValid(newMove)) {
              returnArray = addNewItem(returnArray, newMove, currentMove, counter);
              counter++;
              winCondition = winCon(returnArray, returnArray[returnArray[0].arrSize]);//Checks win con from last added node.
          }

          //}
      }
      if (winCondition == true) {
          break;
      }


      //*********************chickandwolf 
      if (chickandwolf(currentMove)) {
          if (DEBUG) printf("SELECTING ONE WOLFS ONE CHICK\n");
          //Make new move
          item newMove = currentMove;
          //if (DEBUG)  printf("\nPre change newMove new values in twochick is %d,%d\n", newMove.leftShore[0], newMove.rightShore[0]);
          if (newMove.leftShore[2] == 1) { //check if boat left or right : Left here
              //move animal
              newMove.leftShore[1] = (newMove.leftShore[1] - 1);
              newMove.rightShore[1] = (newMove.rightShore[1] + 1);
              newMove.leftShore[0] = (newMove.leftShore[0] - 1);
              newMove.rightShore[0] = (newMove.rightShore[0] + 1);
              //move boat
              newMove.rightShore[2] = 1;
              newMove.leftShore[2] = 0;
          }
          else { //check if boat left or right : Right here
              //move animal
              newMove.leftShore[1] = newMove.leftShore[1] + 1;
              newMove.rightShore[1] = newMove.rightShore[1] - 1;
              newMove.leftShore[0] = newMove.leftShore[0] + 1;
              newMove.rightShore[0] = newMove.rightShore[0] - 1;
              //move boat
              newMove.rightShore[2] = 0;
              newMove.leftShore[2] = 1;
          }
          if (isValid(newMove)) {
              returnArray = addNewItem(returnArray, newMove, currentMove, counter);
              counter++;
              winCondition = winCon(returnArray, returnArray[returnArray[0].arrSize]);//Checks win con from last added node.
          }
      }


      if (winCondition == true) {
          break;
      }

      //loop breaker
      if (winCondition != true) { // if the arrsize and loop size dont equal keep looping.
          //if more loops need doing then set loop == true inc counter.
          loop = true;
          loopCounter++;
      }
      else {
          loop = false; // if all bools are false then tree is complete.
      }

      if (DEBUG) {
          //emergency end condition.
          if (loopCounter > 10000) {
              printf("10 counts met ending loop in failure.");
              loop = false;
          }
      }


      
      

    

  } // END OF WHILE LOOP

  
   return returnArray;
}


//unused code
/*
* 
* 
* 
* //Function tracts location and compares current location to all known locations, 
//Function stoped the array from duplicating array states but this lead to a no completable array states.

bool haveVisited(item* history, item newMove){
    //if in histroy right and left shore ==  histroy[x],[y]
    //left shore is Y 
    //Right shore is X
    //History tracks pairs of shores
    int rows = history[0].arrSize;
    //int rows = *(&history + 1) - history;
    //if (DEBUG)  fprintf(stderr, "FNC **haveVisited** rows: %d\n", rows);
    bool ifVisited = false;
    for (int i = 0; i < rows; i++) {
        if(
            history[i].rightShore[0] == newMove.rightShore[0] &&
            history[i].rightShore[1] == newMove.rightShore[1] &&
            history[i].rightShore[2] == newMove.rightShore[2] &&
            history[i].leftShore[0] == newMove.leftShore[0] &&
            history[i].leftShore[1] == newMove.leftShore[1] &&
            history[i].leftShore[2] == newMove.leftShore[1]
        ){
            ifVisited = true;
            break;
        }else{
            break;
        }
    }
    return ifVisited;
}

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
        cout << "\n";
    }
  }
  */



/*

int** historyInc(int** historyArr, int* rightShore, int* leftShore, int sizeold){

    if (DEBUG)  fprintf(stderr, "check 1\n");
    int sizeOfHistory;

    if (DEBUG)  fprintf(stderr, "HISTORY ARRAY values: R:%d , R:%d , R:%d , L:%d L:%d , L:%d \n", historyArr[0][0],historyArr[0][1],historyArr[0][2],historyArr[1][0],historyArr[1][1],historyArr[1][2]);


    //IF this is first iteration set size to zero to capture fist
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
     if (DEBUG)  fprintf(stderr, "the size of returned array is %d\n", m);
   /*
      //Delete the array created
      for(int i=0;i<m;i++)    //To delete the inner arrays
      delete [] a[i];
      delete [] a;              //To delete the outer array
    //which contained the pointers
    //of all the inner arrays

    if (DEBUG)  fprintf(stderr, "check 6\n");

    if (DEBUG)
    {
        item testarray[1];
        testarray->leftShore[0] = 0;
        testarray->leftShore[1] = 0;
        testarray->leftShore[2] = 0;
        testarray->rightShore[0] = 3;
        testarray->rightShore[1] = 3;
        testarray->rightShore[2] = 1;
        testarray->priority = 1;

        bool test = haveVisited(testarray, a[0], a[1]);
        if (DEBUG)  printf("Should return true: ");
        if (DEBUG)  printf(test ? "true" : "false");
        if (DEBUG)  printf("\n");
    }

    return a;

}

*/