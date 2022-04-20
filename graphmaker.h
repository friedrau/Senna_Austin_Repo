#ifndef GRAPHMAKER_H
#define GRAPHMAKER_H
#include <vector> // #include directive
#include <string>

struct item {
public:
   int leftShore[3];
   int rightShore[3];
   int priority;
   int parent;
   int arrSize = 0;
};


item* graphmaker(int * arrStart,int * arrEnd);
//bool haveVisited(item* history, int* rightShore, int* leftShore);
void print_array(item* arr);// prints a item array
void print_array(int* arr, int size);//prints an arr of size
bool isValid(item newMove);//checks if move is a valid state
void print_item(item arr);//prints an item
item* createQueue(item* returnArr, int parent);//returns all children of parent
item* copyGraph(item* returnArr);//returns a copy of a graph
bool winCon(item* history, item newMove); //checks current node is winner then checks all parent nodes if valid moves.
bool winConLite(item newMove);//just checks if right shore == 0,0,0
item* combineItemArr(item* returnArr, item* newItem);//combines two list arrays
item* removeBack(item* returnArr);//removes item from back of array
item* removeFront(item* returnArr); //removes item from front of array
void winConPrint(item* history, item newMove);//prints winncon array solution
int nodesExp(bool* visited, int size);//gets every node explored #
int distanceFromRoot(item* history, item newMove);//gets distance from current node to root
item* incReturnArr(item* returnArr, item newItem);//increments array by one
bool compaireItem(item history, item newMove);//compaires two items



#endif
