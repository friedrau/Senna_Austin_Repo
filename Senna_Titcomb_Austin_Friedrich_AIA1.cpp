#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "bfs.h"
#include "dfs.h"
#include "iddfs.h"
#include "astar.h"
#include "graphmaker.cpp"
using namespace std;

#ifndef DEBUG
#define DEBUG	true //false or true
#endif


void print_array(int *arr,int size)
{
    //cout << '\n';
    for (int x = 0; x < size - 1; x++) {
        printf("%d,", arr[x]);
    }
    printf("%d", arr[size - 1]);
    cout << '\n';
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
        //cout<< "\nLEFTSHORE: "<<leftShore[0] << " " << leftShore[1] << " " << leftShore[2] << "\n";
        //cout<< "\nRIGHTSHORE: " <<rightShore[0] << " " <<rightShore[1] << " " << rightShore[2] << "\n";
        int i = *(&leftShore + 1) - leftShore;
        print_array( leftShore, i);
        i = *(&rightShore + 1) - rightShore;
        print_array( rightShore, i);


        item * history = graphmaker(rightShore,leftShore);


        bool test = haveVisited(history,rightShore,leftShore);
        
        if (DEBUG)  printf(test ? "true" : "false");
        }


        

    }

    
    //return 0;

}
