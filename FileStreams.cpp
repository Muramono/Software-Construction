/*
Chase Dumbacher
cdd0035
hw4_cdd0035.cpp
compile hww_cdd0035 then run, make sure input1.txt and input2.txt are inside same folder as cpp file
*/

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cassert>
using namespace std;

const int MAX_SIZE = 100;

//Prototypes
int readfile(int inputArray[], ifstream& inStream);

int sort(int inputArray1[], int inputArray1_size, int inputArray2[],
	int inputArray2_size, int outputArray[]);

void writefile(int outputArray[], int outputArray_size, string file);

//Test Drivers 
void test_readfile(void);

void test_sort(void);

void test_writefile(void);

//Beginning of main
int main() {
	ifstream inStream;
	int iArray1[MAX_SIZE];
	int iArray1_size;
	int iArray2[MAX_SIZE];
	int iArray2_size;
	string filename;
	int outputArray[MAX_SIZE];
	int outputArray_size;

	//Unit testing
	cout << "*** Unit Test Case ***\n";
	test_readfile();
	test_sort();
	test_writefile();
	cout << "**************** End of Testing ****************" << endl;
	//Get first file
	cout << "*** Start of Main Program ***\n" << endl;
	cout << "Enter the first input file name: " << endl;
	cin >> filename;
	inStream.open((char*)filename.c_str());
	iArray1_size = readfile(iArray1, inStream);
	inStream.close();
	if (iArray1_size != -1) {
		cout << "The list of " << iArray1_size << " numbers in file " << filename << " is:\n";
		for (int i = 0; i < iArray1_size; i++) {
			cout << iArray1[i] << endl;
		}
		cout << endl;
	}
	//Check for no file
	else {
		exit(1);
	}

	//Get second file
	cout << "Enter the second input file name: ";
	cin >> filename;
	inStream.open((char*)filename.c_str());
	iArray2_size = readfile(iArray2, inStream);
	inStream.close();
	if (iArray2_size != -1) {
		cout << "The list of " << iArray2_size << " numbers in file " << filename << " is:\n";
		for (int i = 0; i < iArray2_size; i++) {
			cout << iArray2[i] << endl;
		}
		cout << endl;
	}
	//Check for no file
	else {
		exit(1);
	}

	//Sort
	outputArray_size = sort(iArray1, iArray1_size, iArray2, iArray2_size, outputArray);
	//Error checking

	cout << "The sorted list of " << outputArray_size << " numbers is: ";
	for (int i = 0; i < outputArray_size; i++) {
		cout << outputArray[i] << " ";
	}
	cout << endl;
	if (outputArray_size == -1) {
		exit(1);
	}
	//Write file

	writefile(outputArray, outputArray_size, "output.txt");
	cout << "*** Please check the new file - " << "output.txt" << " ***\n";

}

// Function Definitions

int readfile(int inputArray[], ifstream& inStream) {
	int index = 0;
	//check file opened
	if (inStream.fail()) {
		cout << "\tInput file opening failed. \n";
		return -1;
	}
	else {
		inStream >> inputArray[index];
		while (!inStream.eof()) {
			//Make sure it is in bounds
			if (index >= MAX_SIZE - 1) {
				cout << "\tFile exceeds max size\n";
				return -1;
			}
			index++;
			inStream >> inputArray[index];
		}
		return index + 1; //Size is index +1 (index starts at 0).
	}
}

int sort(int inputArray1[], int inputArray1_size, int inputArray2[],
	int inputArray2_size, int outputArray[]) {
	//Beacuse arrays are already sorted no need to worry about sorting between files.
	bool done = false; 
	int j = 0; 
	int k = 0; 
	int outputSize = 0; //Counter for added items
	while (!done) {
		//Check for in range
		if (j < inputArray1_size && k < inputArray2_size) {
			//Array 1 value smaller
			if (inputArray1[j] < inputArray2[k]) {
				if (outputSize > 0) {
					//Checks for duplicates
					if (inputArray1[j] != outputArray[outputSize - 1]) {
						outputArray[outputSize] = inputArray1[j];
					}
				}
				else {
					outputArray[outputSize] = inputArray1[j];
				}
				j++;
			}
			//Array 2 value smaller
			else if (inputArray1[j] > inputArray2[k]) {
				if (outputSize > 0) {
					//Checks for duplicates
					if (inputArray2[k] != outputArray[outputSize - 1]) {
						outputArray[outputSize] = inputArray2[k];
					}
				}
				else {
					outputArray[outputSize] = inputArray2[k];
				}
				k++;
			}
			//Both are equal
			else {
				if (outputSize > 0) {
					//Check for duplicates
					if (inputArray1[j] != outputArray[outputSize - 1]) {
						outputArray[outputSize] = inputArray1[j];
					}
				}
				else {
					outputArray[outputSize] = inputArray1[j];
				}
				j++;
				k++;
			}
		}
		//Only input array 1 has values left
		else if (j < inputArray1_size) {
			if (outputSize > 0) {
				//checks repeated numbers
				if (inputArray1[j] != outputArray[outputSize - 1]) {
					outputArray[outputSize] = inputArray1[j];
				}
			}
			else {
				outputArray[outputSize] = inputArray1[j];
			}
			j++;
		}
		//Only input array 2 has values left
		else if (k < inputArray2_size) {
			//Checks repeated numbers
			if (outputSize > 0) {
				if (inputArray2[k] != outputArray[outputSize - 1]) {
					outputArray[outputSize] = inputArray2[k];
				}
			}
			else {
				outputArray[outputSize] = inputArray2[k];
			}
			k++;
		}
		//Finished sorting
		else {
			done = true;
			return outputSize;
		}
		outputSize++;
	}
	//Default fail check
	return -1;
}

void writefile(int outputArray[], int outputArray_size, string file) {
	ofstream outStream;
	//Open/create file
	outStream.open((char*)file.c_str());
	if (outStream.fail()) {
		cout << "Could not write to file";
	}
	else {
		for (int i = 0; i < outputArray_size; i++) {
			outStream << outputArray[i] << endl;
		}
	}
	outStream.close();
}

//Test Cases


void test_readfile(void) {
	cout << "Unit Test Case 1: Function name - readfile()\n";
	ifstream inStream;
	int iArray[MAX_SIZE];
	int iArray_size;

	//Case 1: Normal file
	inStream.open("input1.txt");
	cout << "\tCase 1.1: Normal file (input1.txt)\n";
	iArray_size = readfile(iArray, inStream);
	inStream.close();
	assert(6 == iArray_size);
	assert(4 == iArray[0]);
	assert(13 == iArray[1]);
	assert(14 == iArray[2]);
	assert(17 == iArray[3]);
	assert(23 == iArray[4]);
	assert(89 == iArray[5]);
	cout << "\tCase 1.1 passed.\n";

	//Case 2: Normal file
	inStream.open("input2.txt");
	cout << "\tCase 1.2: Normal file (input2.txt)\n";
	iArray_size = readfile(iArray, inStream);
	inStream.close();
	assert(5 == iArray_size);
	assert(3 == iArray[0]);
	assert(7 == iArray[1]);
	assert(9 == iArray[2]);
	assert(14 == iArray[3]);
	assert(15 == iArray[4]);
	cout << "\tCase 1.1 passed.\n";

	//Case 3: invalid file
	cout << "\tCase 1.3: Invalid file\n";
	inStream.open("notafile.txt");
	iArray_size = readfile(iArray, inStream);
	inStream.close();
	assert(-1 == iArray_size);
	cout << "\tCase 1.3 passed.\n";

	//Case 4: More items than max_size
	cout << "\tCase 1.4: Too many items\n";
	inStream.open("toomany.txt");
	iArray_size = readfile(iArray, inStream);
	inStream.close();
	assert(-1 == iArray_size);
	cout << "\tCase 1.4 passed.\n";
}

//Implementation of test_sort()
void test_sort(void) {
	cout << "Unit Test Case 2: Function name - sort()\n";
	int arr1[MAX_SIZE] = { 4, 13, 14, 17, 23, 89 };
	int arr2[MAX_SIZE] = { 3, 7, 9, 10, 15 };
	int arr1_size = 6;
	int arr2_size = 5;
	int outArr[MAX_SIZE];
	int outArr_size;

	//Case 1: Normal
	cout << "\tCase 2.1: Normal scenario\n";
	outArr_size = sort(arr1, arr1_size, arr2, arr2_size, outArr);
	assert(11 == outArr_size);
	assert(3 == outArr[0]);
	assert(4 == outArr[1]);
	assert(7 == outArr[2]);
	assert(9 == outArr[3]);
	assert(10 == outArr[4]);
	assert(13 == outArr[5]);
	assert(14 == outArr[6]);
	assert(15 == outArr[7]);
	assert(17 == outArr[8]);
	assert(23 == outArr[9]);
	assert(89 == outArr[10]);
	cout << "\tCase 2.1 passed.\n";
}

//Implementation of test_writefile
void test_writefile(void) {
	cout << "Unit Test Case 3: Function name - writefile()\n";
	int outArr[MAX_SIZE] = { 3, 4, 7, 9, 10, 13, 14, 15, 17, 23, 89 };
	int outArr_size = 11;
	string file = "test.txt";
	ifstream inStream;
	int testArr[MAX_SIZE];
	int index = 0;

	//Case 1: Normal
	cout << "\tCase 3.1: Normal case";
	writefile(outArr, outArr_size, file);
	//Test by reopening file and checking it
	//Open and read file
	inStream.open("test.txt");
	inStream >> testArr[index];
	while (!inStream.eof()) {
		index++;
		inStream >> testArr[index];
	}
	inStream.close();
	assert(3 == testArr[0]);
	assert(4 == testArr[1]);
	assert(7 == testArr[2]);
	assert(9 == testArr[3]);
	assert(10 == testArr[4]);
	assert(13 == testArr[5]);
	assert(14 == testArr[6]);
	assert(15 == testArr[7]);
	assert(17 == testArr[8]);
	assert(23 == testArr[9]);
	assert(89 == testArr[10]);
	cout << "\tCase 3.1 passed.\n";
}
