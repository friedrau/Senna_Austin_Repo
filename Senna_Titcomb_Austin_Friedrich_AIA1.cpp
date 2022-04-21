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
#define SKIPCHOICE	false //false or true
#endif

#ifndef DEBUG
#define DEBUG	false //false or true
#endif

#ifndef PRINTEND
#define PRINTEND	false //false or true
#endif

#ifndef PRINTFILE
#define PRINTFILE	true //false or true
#endif



void playerChoice(item* arr, string choiceAlg) {
    if(SKIPCHOICE){
        bfs(arr);
        dfs(arr);
        astar(arr);
        iddfs(arr);
        //exit(EXIT_SUCCESS);

    }
    
    if (!(SKIPCHOICE)) {
        std::string str1("bfs");
        std::string str2("dfs");
        std::string str3("astar");
        std::string str4("iddfs");

        if (choiceAlg.compare(str1) == 0) bfs(arr);
        if (choiceAlg.compare(str2) == 0) dfs(arr);
        if (choiceAlg.compare(str3) == 0) astar(arr);
        if (choiceAlg.compare(str4) == 0) iddfs(arr);
    }
}

int main(int argc,char* argv[])
{
    string choiceAlg = "no";
    string fileName = "no";
    string fileName2 = "no";
    string outputFile = "no";
    printf("\nFile name: %s\n",argv[0]);
    printf("\nFile start input: %s\n",argv[1]);
    printf("\nFile goal input: %s\n", argv[2]);
    printf("\nMode lowercase: bfs dfs iddfs astar: %s\n", argv[3]);
    printf("\nOutput File: %s\n", argv[4]);
    printf("\nNumber Of Arguments Passed: %d\n",argc);

    if(argc==0){
        printf("\nNO FILE");
        //exit(EXIT_FAILURE);
    }else if(argc == 5){
        //printf("\nName of program: %s",argv[0]);
        fileName = argv[1];
        fileName2 = argv[2];
        choiceAlg = argv[3];
        outputFile = argv[4];
        //printf("\nname of file: %s",argv[1]);
        printf("\nSuccess\n");
    }else if(argv[1] == NULL || argv[2] == NULL || argv[3] == NULL || argv[4] == NULL || argv[5] != NULL){
        printf("\nINVALID ARGUMENT AMOUNT: %d",argc);
        printf("\nREQUIRED 4 ARGUMENTS, < initial state file > < goal state file > < mode > < output file >\n");
        exit(EXIT_FAILURE);
    }else{
        printf("\nERROR UNKOWN");
        exit(EXIT_FAILURE);
    }

    //cout << fileName;

    int leftShore [] = {0,0,0};
    int rightShore [] = {0,0,0};

    int gLeftShore[] = { 0,0,0 };
    int gRightShore[] = { 0,0,0 };

    
    if (fileName != "no") {
        //Open file
        fstream newfile;

        /*
        newfile.open(fileName,ios::out);  // open a file to perform write operation using file object
        if(newfile.is_open()) //checking whether the file is open {
            newfile<<"Tutorials point \n"; //inserting text
            newfile.close(); //close the file object
        }
        */

        newfile.open(fileName, ios::in | ios::app | ios::binary); //open a file to perform read operation using file object
        if (newfile.is_open()) { //checking whether the file is open
            string tp;



            bool leftRightShoreToggle = 0;

            while (getline(newfile, tp)) { //read data from file object and put it into string.
                //cout <<"\nOUTPUT FILE : " << tp << "\n"; //print the data of the string

                size_t pos = 0;
                int counter = 0;
                string delimiter = ",";
                string token;
                while ((pos = tp.find(delimiter)) != std::string::npos) {

                    token = tp.substr(0, pos);
                    //cout << "\nTOKEN :"<<"\n" << token;

                    if (leftRightShoreToggle == 0) {
                        if (counter <= 1) {
                            leftShore[counter] = stoi(token);
                        }
                    }
                    else if (leftRightShoreToggle == 1) {
                        if (counter <= 1) {
                            rightShore[counter] = stoi(token);

                        }
                    }
                    counter++;
                    tp.erase(0, pos + delimiter.length());
                }
                if (leftRightShoreToggle == 0) {
                    leftRightShoreToggle = 1;
                    leftShore[2] = stoi(tp);
                }
                if (leftRightShoreToggle == 1) {
                    rightShore[2] = stoi(tp);

                }

                //cout << "\nTOKEN :"<<"\n" << tp;


            }


            newfile.close(); //close the file object.
        }
    }

    printf("initial state file ... FINISHED\n");

    if (fileName2 != "no") {
        //Open file
        fstream newfile;



        newfile.open(fileName2, ios::in | ios::app | ios::binary); //open a file to perform read operation using file object
        if (newfile.is_open()) { //checking whether the file is open
            string tp;
            bool leftRightShoreToggle = 0;
            while (getline(newfile, tp)) { //read data from file object and put it into string.
                size_t pos = 0;
                int counter = 0;
                string delimiter = ",";
                string token;
                while ((pos = tp.find(delimiter)) != std::string::npos) {
                    token = tp.substr(0, pos);
                    if (leftRightShoreToggle == 0) {
                        if (counter <= 1) {
                            gLeftShore[counter] = stoi(token);
                        }
                    }
                    else if (leftRightShoreToggle == 1) {
                        if (counter <= 1) {
                            gRightShore[counter] = stoi(token);

                        }
                    }
                    counter++;
                    tp.erase(0, pos + delimiter.length());
                }
                if (leftRightShoreToggle == 0) {
                    leftRightShoreToggle = 1;
                    gLeftShore[2] = stoi(tp);
                }
                if (leftRightShoreToggle == 1) {
                    gRightShore[2] = stoi(tp);

                }
            }
            newfile.close(); //close the file object.
        }
    }

    printf("goal state file ... FINISHED\n");
    if (DEBUG) {

    }




    printf("PRINTING TO %s \n", argv[4]);
    printf("Please wait, creating tree...\n");
    if (PRINTFILE) freopen(argv[4], "w", stdout);
    item* priorityGraph = graphmaker(rightShore, leftShore);
    if (PRINTEND)print_array(priorityGraph);
    printf("Tree Complete, Choose Search Algorithm.\n");
    playerChoice(priorityGraph, choiceAlg);
     //close the file object
    if (PRINTFILE) fclose(stdout);

    

    return 0;
    

}
