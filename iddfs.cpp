#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "graphmaker.h"
#include "iddfs.h"

using namespace std;

#ifndef DEBUG
#define DEBUG	false //false or true
#endif

#ifndef TOPOFHEAP
#define TOPOFHEAP	false //false or true
#endif

#ifndef PLEASEWAIT
#define PLEASEWAIT	false //false or true
#endif

#ifndef CHECKLAST
#define CHECKLAST	false //false or true
#endif


void iddfs(item* graph) {
    if (DEBUG) {
        printf("\nSTARTING IDDFS\n");
        //print_array(currentQueue);
    }
    item* pq = copyGraph(graph); // make disposable graph for deconstructions priority que
    int pqSize = pq[0].arrSize; //the fist element in pq holds the size of the list since this is a pointer array.
    //if (DEBUG) { printf("\ncopyGraph BFS\n"); }
    //initilize array of values of visited and not visited. 
    bool* visited = new bool[pqSize];
    for (int i = 0; i < pqSize; i++) {
        visited[i] = false;
    }
    visited[0] = true; // have visited root node

    //if (DEBUG) { printf("\visited BFS\n"); }
    item* currentQueue = createQueue(pq, 0);//returns leaf nodes from a spcified parent

    bool winCon = false;
    int x = 0; //check position zero for current iteam on que.
    int counter = 0; //for please wait 
    int increment = 0; //for please wait
    int depthLimit = 5;//initial depth limit

    int depthMAX = distanceFromRoot(pq, pq[pqSize]); // if depthMax < depthLimit ignore depthlimit
    bool ignoreDepthLimit = false;

    bool* indexPastDepth = new bool[pqSize];//pointer to all flagged parrents.
    for (int i = 0; i < pqSize; i++) {
        indexPastDepth[i] = false;
    }

    while (winCon != true) { //for size of arr


           // print_array(currentQueue);

        if (currentQueue[0].arrSize == 0) {
            //indexPastDepth[currentQueue[0].priority] = true;
            //printf("made it");

            bool noSolution = true;

            //printf("LIST LIST BEFORE INCREMENT");
            //print_array(currentQueue);
            for (int c = 0; c < pqSize; c++) {
                if (indexPastDepth[c]) {
                    //visited[currentQueue[c].priority] = false; //if recorded here it has not been searched yet
                    noSolution = false;//there are still nodes to check
                    indexPastDepth[c] = false; //reset to false
                    item* nextLeafNodes = createQueue(pq, pq[c].priority); // get new leaf if this node was flagged.
                    currentQueue = combineItemArr(nextLeafNodes, currentQueue); //combine into queue
                }
            }
            
            if (noSolution) {
                //printf("ARRAY EMPTY NO SOLUTION\n");
                break;
            }
            else {
                //printf("NEW LIST AFTER INCREMENT");
                //print_array(currentQueue);
                depthLimit = depthLimit + 5;//increment depth
            }
            
        }
        /*
        //if both history and current queue empty then no solution.
        if (currentQueue[x].arrSize == 0 && history[x].arrSize == 0) {
            printf("ARRAY EMPTY NO SOLUTION\n");
            break;
        }
        */
        int depthofcurrent = distanceFromRoot(pq, currentQueue[0]);
       //printf("***********\n");
       //printf("DEPTH TO ROOT %d \n", depthofcurrent);
       //printf("depthLimit %d \n", depthLimit);
       //print_item(currentQueue[0]);
       //printf("***********\n");
        if (depthMAX < depthLimit) { //if the last element in the array has a depth value under depthLimit, ignore depthLimit.
            ignoreDepthLimit = true;
        }
        
        if (depthofcurrent - 1 < depthLimit || ignoreDepthLimit) {



            //make if visited
            if (visited[currentQueue[x].priority] != true) {
                visited[currentQueue[x].priority] = true;
                //printf("check %d\n", currentQueue[0].priority);

                if (winConLite(currentQueue[x])) {// check if winner
                    //solution found
                    //print solution and expanded nodes
                    printf("\n***SOLUTION FOUND IDDFS***\n");
                    int nodesExpanded = nodesExp(visited, pqSize);
                    printf("Nodes Expanded in search %d\n", nodesExpanded);
                    printf(": IDDFS SOLUTION :\n");
                    winConPrint(pq, currentQueue[x]);
                    printf(": END IDDFS SOLUTION :\n");
                    winCon = true;//set wincon

                }
                else {
                    //if not winnder then add tree leaf nodes to que for checking
                    item* nextLeafNodes = createQueue(pq, currentQueue[x].priority); // get new leaf
                    currentQueue = combineItemArr(nextLeafNodes, currentQueue); //Only change for DFS is to search Left hand side of graph first.

                    if (DEBUG) {
                        //printf("\nCOMPLETED LIST MERGE\n");
                       // print_array(currentQueue);
                    }

                    //remove the first item from queue
                    //currentQueue = removeFront(currentQueue); //pop top of que
                    if (TOPOFHEAP) {
                        printf("\nCurrent Top of Heap\n");
                        print_item(currentQueue[0]);
                    }


                    //debug counter and emergence exit
                    if (PLEASEWAIT) {//if i want to turn this off at some point
                        if (counter == 0) {
                            printf("\nPlease Wait for IDDFS\n");
                        }
                        counter++;
                        int newInc = counter % 10; // every 10 loops print "."
                        if (newInc > increment) {
                            printf(".");
                            increment = newInc;
                        }
                        if (winCon) {
                            printf("\nGraph Complete!\n");
                        }
                        if (increment > 100000) {
                            printf("\nEMERGENCY EXIT INC == 1000000\n");
                            winCon = true;
                            break;
                        }
                    }

                }

            }
            else {
                currentQueue = removeFront(currentQueue); //remove from stack pop top of stack
            }
        }
        else {
        //if (DEBUG) printf("DEPTH REACHED");
        indexPastDepth[currentQueue[0].priority] = true; //record parents not used.
        //visited[currentQueue[0].priority] = false;
        currentQueue = removeFront(currentQueue); //remove from stack pop top of stack
        }
        
    }


    //int counter


    //code here
}