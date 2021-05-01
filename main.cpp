/******************************************************************************

Heap by Nabhan Abedin
This program creates a heap structure from either a console or file input.
5.1.2021

*******************************************************************************/
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <fstream>
#include <cmath>

using namespace std;

void parseInput(int*& parsed, char input[], int &counter);
void heapify(int*& arr, int n, int i);
void buildHeap(int*& arr, int n);
void printHeap(int* arr, int n);
void sortHeap(int* arr, int n);
void drawHeap(int* arr, int n);

int main() {
    //initialize variables
    int num;
    char fileName[20];
    char input[1000];
    int* parsed;
    int parsedSize;
    cout << endl << "Enter input type ('1' for console, '2' for file): " << endl;
    cin >> num;
    cin.clear();
    cin.ignore(1000000, '\n');
    
    if (num == 1) { //console input
        cout << endl << "Enter numbers separated by spaces:" << endl;
        cin.get(input, 1000);
        cin.clear();
        cin.ignore(1000000, '\n');
    } else if (num == 2) { //file input
        cout << endl << "Enter file name:" << endl;
        cin.get(fileName, 20);
        cin.clear();
        cin.ignore(1000000, '\n');
        streampos size;
        //retrieve file
        ifstream file(fileName, ios::in | ios::binary | ios::ate);
        if (file.is_open()) {
            size = file.tellg();
            file.seekg(0, ios::beg);
            file.read(input, size);
            file.close();
        }
    } else {
        return 0;
    }
    
    parseInput(parsed, input, parsedSize);
    
    buildHeap(parsed, parsedSize);
    cout << endl << "Heap in array form: ";
    printHeap(parsed, parsedSize);
    cout << endl << "Heap drawn out: " << endl;
    drawHeap(parsed, parsedSize);
    cout << "Sorted input (greatest to least): ";
    sortHeap(parsed, parsedSize);
    return 0;
}

void parseInput(int*& parsed, char input[], int &counter) {
    //remove spaces between chars
    int pointers[2];
    int value;
    int* temp;
    counter = 1;
    pointers[0] = -1;
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] == ' ') {
            pointers[1] = i;
            int j = 0;
            char* newArray = new char[pointers[1] - pointers[0]];
            for (int i = pointers[0] + 1; i < pointers[1]; i++) {
                newArray[j] = input[i];
                j = j + 1;
            }
            newArray[j] = '\0';
            temp = parsed;
            parsed = new int[counter];
            if (counter > 1) {
                for (int i = 0; i < counter - 1; i++) {
                  parsed[i] = temp[i];
                }
            }
            parsed[counter - 1] = atoi(newArray);
            counter = counter + 1;
            pointers[0] = pointers[1];
        }
    }
    char* newArray = new char[strlen(input) - pointers[0]];
    int j = 0;
    
    for (int i = pointers[0] + 1; i < strlen(input); i++) {
        newArray[j] = input[i];
        j = j + 1;
    }
    newArray[j] = '\0';
    temp = parsed;
    parsed = new int[counter];
    
    if (counter > 1) {
        for (int i = 0; i < counter - 1; i++) {
            parsed[i] = temp[i];
        }
    }
    parsed[counter - 1] = atoi(newArray);
}

void heapify(int*& arr, int n, int i) {
    //heapifying
    int largest = i; //set largest
    int l = 2 * i + 1; //left child
    int r = 2 * i + 2; //right child
    
    //if left is larger than root
    if (l < n && arr[l] > arr[largest]) {
        largest = l;
    }
    
    //if right is larger than root
    if (r < n && arr[r] > arr[largest]) {
        largest = r;
    }
    
    //set largest to root again
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void buildHeap(int*& arr, int n) {
    //construct heap
    int start = (n / 2) - 1;
    
    for (int i = start; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

void printHeap(int* arr, int n) {
    //print heap array
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void sortHeap(int* arr, int n) {
    //sort heap from greatest to least
    int counter = n;
    int* temp = arr;
    arr = new int[n];
    
    for (int i = 0; i < n; i++) {
        //taking the head of the array and adding it to the final array
        arr[i] = temp[0];
        
        //removing the head
        int* temp2 = new int[counter - 1];
        
        for (int j = 0; j < counter - 1; j++) {
          temp2[j] = temp[j + 1];
        }
        counter = counter - 1;
        temp = temp2;
        buildHeap(temp, counter);
    }
    printHeap(arr, n);
}

void drawHeap(int* parsed, int n) {
    //draw visual representation of heap
    int* temp = parsed;
    
    //moving indexes one spot over for calculatiosn
    parsed = new int[n + 1];
    
    for (int i = 0; i < n; i++) {
        parsed[i + 1] = temp[i];
    }
    
    int levels = ceil(log2(n)); //how many levels
    int index = 1;
    
    for (int i = 0; i < levels; i++) {
        int num = index;
        for (int j = 0; j < num; j++) {
          //the index of the first value of each level is the amount of numbers in that level
          if (index <= n) {
            cout << parsed[index] << " ";
            index = index + 1;
          }
        }
        cout << endl;
        if (i < levels - 1) {
          for (int k = 0; k < pow(2, i); k++) {
            //add slashes between each level except last
            cout << "/\\";
          }
          cout << endl;
        }
    }
    cout << endl;
}