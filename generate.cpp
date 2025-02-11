//Marisol Morales
//CECS 325 - 02
//Proj 4 - Threads
//Due Date: 10/31/2024
//
//I certify that this program is my own original work. I did not copy any part of this program from
//any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>

using namespace std;

int main(int argc, char *argv[]){
    srand(time(0));
    if (argc != 4){
    cout << "Error: Did not enter 3 parameters.\n";
    cout << "Please enter 3 parameters. Given the following guidelines.\n";
    cout << "Parameter 1: total amount of numbers you want.\n";
    cout << "Parameter 2: minimum value.\n";
    cout << "Parameter 3: maximum value.\n";
    cout << "Input the parameters in the following order on your terminal.\n";
    cout << "$ generate Parameter 1 Parameter 2 Parameter 3";
    exit(EXIT_FAILURE);
    }
    
    int COUNT = stoi(argv[1]);
    int MIN = stoi(argv[2]);
    int MAX = stoi(argv[3]);
    //we comment these out since we dont want this for project 4, these prints are more for project 3!
    //for(int i = 0; i < argc; i++){
     //   cout << "argv[" << i << "]:" << argv[i] <<endl;
    //}
    ofstream numFileOut;
    numFileOut.open("numbers.dat", ios::out);
    for(int i = 0; i < COUNT; i++){
        numFileOut << (rand() % (MAX - MIN + 1) + MIN) << endl;
    }
    numFileOut.close();
    return 0;
}
