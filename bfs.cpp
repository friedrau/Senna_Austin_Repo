#include "bfs.h"
using namespace std;

struct Node{
 int chicLeftBank,
     chicRightBank,
     wolfLeftBank,
     wolfRightBank;
  bool boatOnLeftBank;    //true boat is on left bank -- false boat on right bank;
  struct Node *twoChic;
  struct Node *oneChic;
  struct Node *chicPlusWolf;
  struct Node *oneWolf;
  struct Node *twoWolf;
  struct Node *prev;
};

//move is invalid if there are more wolves than chickens on one side.
//BoatTree.h
class BoatTree{
  public:
  BoatTree();
  BoatTree(int lc, int rc, int lw, int rw, bool boatLeft);
  
  ~BoatTree();
  
  void buildGoal(int lc, int rc, int lw, int rw);
  bool isEqual(struct Node *other);
  bool buildTreeBreathFirst();
  private:
  struct Node *root;
  struct Node *ActiveParent;
  struct Node goal;
  bool isMoveLegal(struct *Node test);
  
  
}


//BaotTree.cpp
void  BoatTree::buildGoal(int lc, int rc, int lw, int rw){
 
  goal.chicLeftBank= lc;
  goal.chicRightBank=rc;
  goal.wolfLeftBank=lw;
  goal.wolfRightBank=rw;
  goal.twochic=nullptr;
  goal.oneChic= nullptr;
}


bool BoatTree::isEqual(struct Node *other){
 bool result = false; 
  if(goal.chicLeftBank == other->chicLeftBank && goal.chicRightBank == other->chicRightBank && goal.wolfLeftBank == other->wolfLeftBank && goal.wolfRightBank == other->wolfRightBank){
    result = true;
  }
  return result;
}

list<list<int>> BoatTree::bfsSolution() {
    list<list<int>> solution; // use to keep track of solution
    list<list<int>> explored // use to keep track of the possible next states
    bool done = false;

    explored.push_back(//initial state)

    while (!explored.empty()) {
      solution.push_back(explored.front());
      explored.pop_front();

      /*
      if goal state reached:
        return solution
      
      if Put one chicken in the boat doesn't create a state in solution:
        explored.push_back(new state)

      if Put two chickens in the boat doesn't create a state in solution:
        explored.push_back(new state)

      if Put one wolf in the boat doesn't create a state in solution:
        explored.push_back(new state)

      if Put one wolf and one chicken in the boat doesn't create a state in solution:
        explored.push_back(new state)

      if Put two wolves in the boat doesn't create a state in solution:
        explored.push_back(new state)
      */
    }

    // return fail
}

// solution for depth first search
void BoatTree::dfsSolution(//current state) {
    //before this function is called create a private variable that keeps track of the states/solution
    //call the variable "solution"

    list<list<int>> options;

    //add current state to solution

    /*
    if goal state not reached:    
      if Put one chicken in the boat doesn't create a state in solution:
        options.push_back(new state)
        dfsSolution(new state)

      if Put two chickens in the boat doesn't create a state in solution:
        options.push_back(new state)
        dfsSolution(new state)

      if Put one wolf in the boat doesn't create a state in solution:
        options.push_back(new state)
        dfsSolution(new state)

      if Put one wolf and one chicken in the boat doesn't create a state in solution:
        options.push_back(new state)
        dfsSolution(new state)

      if Put two wolves in the boat doesn't create a state in solution:
        options.push_back(new state)
        dfsSolution(new state)
    */

    //go to where this function was called.
    //if solution doesn't contain the goal state then say it failed
}