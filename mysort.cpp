//Marisol Morales
//CECS 325 - 02
//Proj 4 - Threads
//Due Date: 10/31/2024
//
//I certify that this program is my own original work. I did not copy any part of this program from
//any other source. I further certify that I typed each and every line of code in this program.

#include <thread>
#include <iostream>
#include <fstream> 
#include <string>

using namespace std;

#include <mutex>

unsigned long long totalSwaps = 0; // total number for swaps
mutex swappingMutex; //mutux to make sure threads are synchronized

//const ints that will be important while running the program!
int maxNum = 1000000; 
const int threadCount = 16;
//const int sectionSize = 62500; //we get this number from basically doing maxNum / threadCount
const int testMaxNum = 10000; // this will be used when we use "-test" in our parameters in main!

void bubbleSort(int A[], int size, const string& num_process){

    unsigned long long processSwaps = 0; // swaps done within a thread!, we will then add this number later to totalSwaps
    for (int i = 0; i < (size - 1); ++i){
        for (int j = 0; j < (size - i - 1); ++j){
            if(A[j] > A[j + 1]){
                int temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
                processSwaps++;

            }
        }
    }
    swappingMutex.lock();
    totalSwaps += processSwaps;
    cout << "Process " << num_process << " swap count: " << processSwaps << endl;
    swappingMutex.unlock();
}

void merge(int a1[], int s1, int a2[], int s2){

    int *temp = new int[s1 + s2];

    int i = 0;
    int j = 0;
    int k = 0;

    while ( i < s1 && j < s2){

        if (a1[i] < a2[j]){
            temp[k++] = a1[i++];

        }else{
            temp[k++] = a2[j++];
        }
    }

    while (i < s1){
        temp[k++] = a1[i++];
    }

    while (j < s2){
        temp[k++] = a2[j++];

    }
    // copying all nums from temp back to orinigal array (can think of this as nums)
    //this is done after merging
    for (int m = 0; m < (s1 + s2); ++m){
        a1[m] = temp[m];
    }
    //since done merging and using our dynamic array we much clear our allocated memory from array temp!
    delete[] temp;

}

int main(int argc, char *argv[]){

    if(argc == 4 && string(argv[3]) == "-test"){ //checking for if it is the optional "-test" choice which makes ur maxNum be only 10,000
        maxNum = testMaxNum;

    }else if(argc < 3){
        cout << "Error: Did not enter 2 parameters.\n";
        cout << "Please enter 2 parameters. Given the following guidelines.\n";
        cout << "Parameter 1: input file.\n";
        cout << "Parameter 2: output file.\n";
        cout << "Input the parameters in the following order on your terminal.\n";
        cout << "$ mysort Parameter 1  Parameter 2";

        exit(EXIT_FAILURE); //exiting program due to error(same as doing return 1;)
    }

    ofstream outputFile;
    ifstream inputFile;
    int *numsA = new int[maxNum];
    int count = 0;

    inputFile.open(argv[1]);
    outputFile.open(argv[2]);

    while(inputFile >> numsA[count]){
        count++;
    }
    //since we are now done with reading and using our input file we need to close the file!
    inputFile.close();

    //now we start using our threads and bubble sort!
    thread threads[threadCount];
    int sectionSize = maxNum / threadCount;
    //bubble sort using threads
    for (int i = 0; i < threadCount; ++i){
        threads[i] = thread(bubbleSort, numsA + i *sectionSize, sectionSize, "Thread " + to_string(i + 1));
    }
    //waiting for bubblesorted sections to join back
    for (int i = 0; i < threadCount; ++i){
        threads[i].join();
    }
    //now we merge our sorted threads

    //use global varaibles to define new varaibles that will be helpful with merging, we do this because we can't modify const int global varaibles
    int merging_threadCount = threadCount;
    int merging_sectionSize = sectionSize;

    while(merging_threadCount > 1){
        for(int i = 0; i < (merging_threadCount / 2); ++i){
            merge(numsA + i*2*merging_sectionSize, merging_sectionSize, numsA + (i*2+1)*merging_sectionSize, merging_sectionSize);

        }
        merging_threadCount = (merging_threadCount / 2); // by doing this we are now reducing the number of threads we have 16 
                                                        // 16 -> 8 -> 4 -> 2 -> 1
        merging_sectionSize = (merging_sectionSize * 2);// by doing this we are expanding our size for each array
                                                        // 62,500 -> 125,000 -> 250,000 -> 500,000 -> 1,000,000
                                                        //this will change depending on what our section size become based on maxNum
    }

    //now write our sorted numbers into our output file, note: we already opened our file!
    for(int i = 0; i < count; i++){
        outputFile << numsA[i] << endl;
    }
    //down with writing our sorted numbers so now we close the file!
    outputFile.close();
    //now make sure to free our allocated memory from numsA array!
    delete[] numsA;
    //make sure to cout our total number of swaps!
    cout << "Total swaps: " << totalSwaps << endl;
    //now we can return 0!
    return 0;
}