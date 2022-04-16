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