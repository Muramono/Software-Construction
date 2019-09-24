#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <assert.h>
using namespace std;
/* Author : Chase Dumbacher 
   ID : CDD0035
   filename hw3_cdd0035
   run and compile in g++
*/

const int totDuels = 10000;
const int ARate = 33;
const int BRate = 50;
const int CRate = 100;
int winsA1 = 0;
int winsA2 = 0;

//Prototypes
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive);
/* Input: A_alive indicateswhether Aaron is alive
 * B_alive indicateswhether Bob is alive 
 * C_alive indicateswhether Charlie is alive 
 * Return:true if at least two are alive 
 * otherwise return false */

void Aaron_shoots1(bool &B_alive, bool &C_alive);
/* Strategy 1: Use call by reference* Input: B_alive indicates whether Bob alive or dead 
 * C_alive indicates whether Charlie is alive or dead * Return: Change B_alive into false if Bob is killed.  
 * Change C_alive into false if Charlie is killed. */

void Bob_shoots(bool& A_alive, bool& C_alive);
/* Call by reference* Input: A_alive indicates ifAaronis alive or dead
 * C_alive indicates whether Charlie is alive or dead * Return: Change A_alive into falseif Aaronis killed.
 * Change C_alive into falseif Charlie is killed.
 */

void Charlie_shoots(bool& A_alive, bool& B_alive);
/* Call by reference* Input: A_alive indicatesifAaronis alive or dead
 * B_alive indicates whether Bobis alive or dead * Return: Change A_alive into falseif Aaronis killed.
 * Change B_alive into falseif Bobis killed. 
 */

void Aaron_shoots2(bool& B_alive, bool& C_alive);
/* Strategy 2: Use call by reference* Input: B_alive indicates whether Bob alive or dead
 * C_alive indicates whether Charlie is alive or dead * Return: Change B_alive into falseif Bob is killed.
 * Change C_alive into falseif Charlie is killed.
 */

void test_at_least_two_alive();
/* Unit test on to check if two of the three participants are alive */

void strat1();
/* Run the simulation 10,000 times with the first strat*/

void strat2();
/* Run the simulation 10,000 times with the second strat*/

int main() {
	srand(time(NULL));
	test_at_least_two_alive();
	cout << "Press Enter to continue...";
	cin.get(); //Pause Command for Linux Terminal
	cout << "Ready to test strategy 1 (run 10,000 times)" << endl;
	cout << "Press Enter to continue...";
	cin.get(); //Pause Command for Linux Terminal
	strat1();
	cout << "Ready to test strategy 2 (run 10,000 times)";
	cin.get();
	strat2();
	if (winsA2 > winsA1) cout << "Strategy 2 is better then strategy 1" << endl;
	return 0;
}

void strat1() {
	bool A_alive = true;
	bool B_alive = true;
	bool C_alive = true;
	int  winsB = 0, winsC = 0;

	for (int i = 0; i < totDuels; i++) {
		A_alive = true;
		B_alive = true;
		C_alive = true;
		while (at_least_two_alive(A_alive, B_alive, C_alive)) {
			if (A_alive) { Aaron_shoots1(B_alive, C_alive); }
			if (B_alive) { Bob_shoots(A_alive, C_alive); }
			if (C_alive) { Charlie_shoots(A_alive, B_alive); }
		}
		if (A_alive) {
			winsA1++;
		}
		else if (B_alive) {
			winsB++;
		}
		else if (C_alive) {
			winsC++;
		}
	}
	cout << "Aaron won " << winsA1 << "/10000 duels or " << (double)(100 * (winsA1 / 10000.0)) << "%" << endl;
	cout << "Bob won " << winsB << "/10000 duels or " << (double)(100 * (winsB / 10000.0)) << "%" << endl;
	cout << "Charlie won " << winsC << "/10000 duels of " << (double)(100 * (winsC / 10000.0)) << "%" << endl;
}
void strat2()
{
	bool A_alive = true;
	bool B_alive = true;
	bool C_alive = true;
	int winsB = 0, winsC = 0;

	for (int i = 0; i < totDuels; i++) {
		A_alive = true;
		B_alive = true;
		C_alive = true;
		while (at_least_two_alive(A_alive, B_alive, C_alive)) {
			if (A_alive) { Aaron_shoots2(B_alive, C_alive); }
			if (B_alive) { Bob_shoots(A_alive, C_alive); }
			if (C_alive) { Charlie_shoots(A_alive, B_alive); }
		}
		if (A_alive) {
			winsA2++;
		}
		else if (B_alive) {
			winsB++;
		}
		else if (C_alive) {
			winsC++;
		}
	}
	cout << "Aaron won " << winsA2 << "/10000 duels or " << (double)(100 * (winsA2 / 10000.0)) << "%" << endl;
	cout << "Bob won " << winsB << "/10000 duels or " << (double)(100 * (winsB / 10000.0)) << "%" << endl;
	cout << "Charlie won " << winsC << "/10000 duels of " << (double)(100 * (winsC / 10000.0)) << "%" << endl;
}
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive) {
	int numOfAlive = 0;
	bool twoPlusAlive = false;
	if (A_alive) numOfAlive++;
	if (B_alive) numOfAlive++;
	if (C_alive) numOfAlive++;
	if (numOfAlive >= 2) twoPlusAlive = true;
	return twoPlusAlive;
}

void test_at_least_two_alive() {
	cout << "Unit Testing 1: Function –at_least_two_alive()\n";
	cout << "Case 1: Aaron alive, Bob alive, Charlie alive\n";
	assert(true == at_least_two_alive(true, true, true));
	cout << "Case passed ...\n";
	cout << "Case 2: Aaron dead, Bob alive, Charlie alive\n";
	assert(true == at_least_two_alive(false, true, true));
	cout << "Case passed ...\n";
	cout << "Case 3: Aaron alive, Bob dead, Charlie alive\n";
	assert(true == at_least_two_alive(true, false, true));
	cout << "Case passed ...\n";
	cout << "Case 4: Aaron alive, Bob alive, Charlie dead\n";
	assert(true == at_least_two_alive(true, true, false));
	cout << "Case passed ...\n";
	cout << "Case 5: Aaron dead, Bob dead, Charlie alive\n";
	assert(false == at_least_two_alive(false, false, true));
	cout << "Case passed ...\n";
	cout << "Case 6: Aaron alive, Bob alive, Charlie dead\n";
	assert(true == at_least_two_alive(true, true, false));
	cout << "Case passed ...\n";
	cout << "Case 7: Aaron alive, Bob dead, Charlie dead\n";
	assert(false == at_least_two_alive(true, false, false));
	cout << "Case passed ...\n";
	cout << "Case 8: Aaron dead, Bob dead, Charlie dead\n";
	assert(false == at_least_two_alive(false, false, false));
	cout << "Case passed ...\n";
}

void Aaron_shoots1(bool &B_alive, bool &C_alive) {
	if (rand() % 100 < ARate) {
		//cout << "Hit the target, by Aaron" << endl;
		if (C_alive) C_alive = false;
		else if (B_alive) B_alive = false;
	}
}

void Charlie_shoots(bool & A_alive, bool & B_alive)
{
	if (rand() % 100 < CRate) {
		//cout << "Hit the target, by Charlie" << endl;
		if (B_alive) B_alive = false;
		else if (A_alive) A_alive = false;
	}
}

void Aaron_shoots2(bool & B_alive, bool & C_alive)
{
	if (!(B_alive && C_alive)) {
		if (rand() % 100 < ARate) {
			if (C_alive) C_alive = false;
			else if (B_alive) B_alive = false;
		}
	}
}

void Bob_shoots(bool &A_alive, bool &C_alive) {
	if (rand() % 100 < BRate) {
		//cout << "Hit the target, by Bob" << endl;
		if (C_alive) C_alive = false;
		else if (A_alive) A_alive = false;
	}
}


