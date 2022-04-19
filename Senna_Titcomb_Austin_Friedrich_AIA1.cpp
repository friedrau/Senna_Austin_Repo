#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "graphmaker.h"
#include "bfs.h"
#include "dfs.h"
#include "iddfs.h"
#include "astar.h"

using namespace std;

#ifndef SKIPCHOICE
#define SKIPCHOICE	true //false or true
#endif

#ifndef DEBUG
#define DEBUG	false //false or true
#endif

#ifndef PRINTEND
#define PRINTEND	false //false or true
#endif


void playerChoice(item* arr) {
    bool gameLoop = true;
    if(SKIPCHOICE){
        //bfs(arr);
        dfs(arr);
        //A*
        //iddfs
        exit(EXIT_SUCCESS);

    }
    //if not debug let user choose.
    if (!(SKIPCHOICE)) {
        while (gameLoop) {
            int choice = 0;
            printf(" ENTER 1 BFS\n ENTER 2 DFS\n ENTER 3 A*\n ENTER 4 IDDFS\n ENTER 5 QUIT\n ENTER INT :");
            cin >> choice;
            if (cin.fail()) {
                choice = 0;
                cin.clear();
                cin.ignore();
                printf("Incorrect entry. Try again: \n");
            }
            if (choice > 0 && choice < 6)
            {
                if (choice == 1) { bfs(arr); }
                if (choice == 2) { bfs(arr); }
                if (choice == 3) { bfs(arr); }
                if (choice == 4) { bfs(arr); }
                if (choice == 5) { gameLoop = false; }
                //printf("Incorrect entry. Try again: ");
            }

        }
    }
}

int main(int argc,char* argv[])
{
    
    string fileName = "no";
    printf("\nFile name: %s\n",argv[0]);
    printf("\nFile input: %s\n",argv[1]);
    printf("\nNumber Of Arguments Passed: %d",argc);
    if(argc==0){
        printf("\nNO FILE");
        //exit(EXIT_FAILURE);
    }else if(argc == 2){
        //printf("\nName of program: %s",argv[0]);
        fileName = argv[1];
        //printf("\nname of file: %s",argv[1]);
        printf("\nSuccess\n");
    }else if(argv[1] == NULL || argv[2] != NULL ){
        printf("\nINVALID ARGUMENT AMOUNT: %d",argc);
        exit(EXIT_FAILURE);
    }else{
        printf("\nERROR UNKOWN");
        exit(EXIT_FAILURE);
    }

    //cout << fileName;

    int leftShore [] = {0,0,0};
    int rightShore [] = {0,0,0};

    
    if(fileName != "no"){
            //Open file
        fstream newfile;

        /*
        newfile.open(fileName,ios::out);  // open a file to perform write operation using file object
        if(newfile.is_open()) //checking whether the file is open {
            newfile<<"Tutorials point \n"; //inserting text
            newfile.close(); //close the file object
        }
        */

        newfile.open(fileName,ios::in | ios::app | ios::binary); //open a file to perform read operation using file object
        if (newfile.is_open()){ //checking whether the file is open
            string tp;



            bool leftRightShoreToggle = 0;

            while(getline(newfile, tp)){ //read data from file object and put it into string.
                //cout <<"\nOUTPUT FILE : " << tp << "\n"; //print the data of the string

                size_t pos = 0;
                int counter = 0;
                string delimiter = ",";
                string token;
                while ((pos = tp.find(delimiter)) != std::string::npos) {

                    token = tp.substr(0, pos);
                    //cout << "\nTOKEN :"<<"\n" << token;

                    if(leftRightShoreToggle == 0){
                        if(counter <= 1){
                            leftShore[counter] = stoi(token);
                        }
                    } else if (leftRightShoreToggle == 1){
                        if(counter <= 1){
                            rightShore[counter] = stoi(token);
                            
                        }                        
                    }
                    counter++;
                    tp.erase(0, pos + delimiter.length());
                }
                if(leftRightShoreToggle == 0){
                    leftRightShoreToggle = 1;
                    leftShore[2] = stoi(tp);
                }
                if(leftRightShoreToggle == 1){
                    rightShore[2] = stoi(tp);
                    
                }                

                //cout << "\nTOKEN :"<<"\n" << tp;

            
            }


            newfile.close(); //close the file object.
        }

        if (DEBUG)  {
            
        }
        printf("Please wait, creating tree...\n");
        item* priorityGraph = graphmaker(rightShore, leftShore);
        if (PRINTEND)print_array(priorityGraph);
        printf("Tree Complete, Choose Search Algorithm.\n");
        playerChoice(priorityGraph);


        

    }

    
    return 0;

}
