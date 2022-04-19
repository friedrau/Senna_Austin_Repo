#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "graphmaker.h"
#include "bfs.h"

using namespace std;

#ifndef DEBUG
#define DEBUG	false //false or true
#endif

#ifndef TOPOFHEAP
#define TOPOFHEAP	false //false or true
#endif

#ifndef PLEASEWAIT
#define PLEASEWAIT	true //false or true
#endif


void bfs(item* graph) {
    if (DEBUG) {
        printf("\nSTARTING BFS\n");
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

    visited[0] = true;// fist node in list is explored
    //queue.push_back(s);
    bool winCon = false;
    int x = 0; //check position zero for current iteam on que.
    int counter = 0; //for please wait 
    int increment = 0; //for please wait
    while (winCon != true) { //for size of arr


           // print_array(currentQueue);
        

        //make if visited
        if (visited[currentQueue[x].priority] != true) {
            visited[currentQueue[x].priority] = true;

            if (winConLite(currentQueue[x])) {// check if winner
                //solution found
                //print solution and expanded nodes
                printf("\n***SOLUTION FOUND BFS***\n" );
                int nodesExpanded = nodesExp(visited, pqSize);
                printf("Nodes Expanded in search %d\n", nodesExpanded);
                printf(": BFS SOLUTION :\n");
                winConPrint(pq, currentQueue[x]);
                printf(": END BFS SOLUTION :\n");
                winCon = true;//set wincon

            }
            else {
                //if not winnder then add tree leaf nodes to que for checking
                item* nextLeafNodes = createQueue(pq, currentQueue[x].priority); // get new leaf
                currentQueue = combineItemArr(currentQueue, nextLeafNodes); //combine into queue
                if (DEBUG) {
                    //printf("\nCOMPLETED LIST MERGE\n");
                   // print_array(currentQueue);
                }
                
                //remove the first item from queue
                currentQueue = removeFront(currentQueue); //pop top of que
                if (TOPOFHEAP) {
                    printf("\nCurrent Top of Heap\n");
                    print_item(currentQueue[0]);
                }


                //debug counter and emergence exit
                if (PLEASEWAIT) {//if i want to turn this off at some point
                    if (counter == 0) {
                        printf("\nPlease Wait for BFS\n");
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




            //add

        } //mark visited

    }
    

    //int counter
        

    //code here
}

