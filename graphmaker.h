#pragma once
#include <vector> // #include directive
#include <string>
struct item {
   int leftShore[3];
   int rightShore[3];
   int priority;
};


item* graphmaker(int * arrStart,int * arrEnd)