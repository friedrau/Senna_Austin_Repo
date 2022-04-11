#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
using namespace std;

int main(int argc,char* argv[])
{
    string fileName = "no";
    printf("File name: %s\n",argv[0]);
    if(argc==0)
        printf("\nNO FILE");
    if(argc==1)
        printf("\nNumber Of Arguments Passed: %d",argc);
        printf("\nName of program: %s",argv[0]);
        fileName = argv[1];
        printf("\nname of file: %s",argv[1]);

    if(argv[2]!= NULL)
    {
        printf("\nTo many arguments!: %s",argv[2]);
        exit(EXIT_FAILURE);
    }
    //cout << fileName;
    
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


            while(getline(newfile, tp)){ //read data from file object and put it into string.
                cout << tp << "\n"; //print the data of the string
            }


            newfile.close(); //close the file object.
        }

    }

    
    //return 0;

}