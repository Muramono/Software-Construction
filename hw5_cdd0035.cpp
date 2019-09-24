#include <string>
#include <cstdlib>
#include <iostream>
#include <cassert>
//#define DEBUG
/*
Chase Dumbacher
CDD003
hw5_cdd0035
Extra Resources : 
*/
using namespace std;

int playPoints = 0; //Tracks Player Points 

//Triva Struct
struct TriviaNode {
	string answer;
	string question;
	int points;
};

class TriviaList {
public:
	//TriviaList(){}
	TriviaList(string question, string answer, int points, TriviaList* theLink) 
	{
		node.question = question, node.answer = answer, node.points = points, link = theLink;
	}
	TriviaList* getLink() { return link; }
	string getQuestion() { return node.question; }
	string getAnswer() { return node.answer; }
	int getPoints() { return node.points; }
	void setQuestion(string theQuestion) { node.question = theQuestion; }
	void setAnswer(string theAnswer) { node.answer = theAnswer; }
	void setPoints(int thePoints) { node.points = thePoints; }
	void setLink(TriviaList* pointer) { link = pointer; }
private:
	TriviaNode node;
	TriviaList* link;
};
typedef TriviaList* TriviaListPtr;

//Initialization Of Hard Coded Question
TriviaListPtr inItTrivia();

int askQuestion(TriviaListPtr List, int numberOfQuestions);

void tester();

TriviaListPtr getTrivia(TriviaListPtr list);

//Add New Node to List of Nodes
TriviaListPtr addNode(string question, string answer, int points, TriviaListPtr node);

int main() {
#ifdef DEBUG
	tester();
#else
	//Regular version
	TriviaListPtr head = NULL;
	cout << "*** Welcome to Chase's trivia quiz game ***\n";
	cout << "Would you like to enter your own trivia? (Yes/No): ";
	string ans;
	getline(cin, ans);
	//Get valid yes/no input
	while (ans != "Yes" && ans != "No") {
		cout << "Please enter valid input (Yes/No): ";
		getline(cin, ans);
	}
	//Get questions if they want to enter their own
	if (ans == "Yes") {
		string cont;
		do {
			//Get input
			head = getTrivia(head);
			//Prompt to add more
			cout << "Continue? (Yes/No): ";
			getline(cin, cont);
			//Get valid yes/no input
			while (cont != "Yes" && cont != "No") {
				cout << "Please enter valid input (Yes/No): ";
				getline(cin, cont);
			}
		} while (cont == "Yes");
	}
	//Initialize list with 3 hard-coded questions
	TriviaListPtr inItHead = inItTrivia();
	TriviaListPtr Tail = inItHead->getLink();
	Tail = Tail->getLink();
	Tail->setLink(head);
	

	cout << endl; //formatting.
	cout << "How many questions would you like to answer? ";
	int questions;
	cin >> questions;
	int test;
	test = askQuestion(inItHead, questions);
	//Be sure number is valid
	while (test == 1) {
		cout << "Enter a valid number: ";
		cin >> questions;
		test = askQuestion(inItHead, questions);
	}
	//Number was valid, has now answered questions... Game is now over.
	cout << "\n*** Thank you for playing the trivia quiz game. Goodbye! ***\n";
#endif
}

//Definition

int askQuestion(TriviaListPtr List, int numberOfQuestions) {

	TriviaListPtr head = List;
	TriviaListPtr next = List->getLink();
	int size = 1, numAnswered = 0;
	string PAnswer;

	if (numberOfQuestions <= 0) {
		cout << "Number of questions is invlaid please ask to answer at least 1 or more questions" << endl;
		return 1; //Failure
	}
	else if (List == NULL) {
		cout << "List of trivia is empty or invalid" << endl;
		return 1; //Failure
	}
	while (next != NULL) {
		size++;
		next = next->getLink();
	}
	if (size < numberOfQuestions) {
		cout << "You have asked to answer more questions then there are trivia" << endl;
		return 1; //Failure due to asking more questions then there are trivia
	}
	else {
		next = head;
		do {
			cout << "Questions : " << next->getQuestion() << endl;
			cout << "Answer : ";
			getline(cin, PAnswer);
			//Weird Problem of picking up previous answers spaces as input for next getline Source from online above
			if (PAnswer == "") {
				getline(cin, PAnswer);
			}
			if (PAnswer != next->getAnswer()) {
				cout << "Sorry that is incorrect \nThe correct answer is, " << next->getAnswer() << endl;
				cout << "Your total points : " << playPoints << endl;
			}
			else if (PAnswer == next->getAnswer()) {
				cout << "Correct answer, you have been awarded " << next->getPoints() << endl;
				playPoints += next->getPoints();
				cout << "Your total points : " << playPoints << endl;
			}
			next = next->getLink();
			numAnswered++;
			//Check to make sure list is neither empty or that the number of desired questions have been answered
		} while (next != NULL && numAnswered < numberOfQuestions);
		return 0; //Success
	}
}

TriviaListPtr addNode(string question, string answer, int points, TriviaListPtr node) {
	TriviaListPtr head = new TriviaList(question, answer, points, node);
	return head;
}

TriviaListPtr inItTrivia() {
	TriviaListPtr head;
	//Q3
	string q = "What is the best-selling video game of all time? (Hint: Minecraft or Tetris)";
	string a = "Tetris";
	int p = 20;
	head = new TriviaList(q, a, p, NULL);
	//Q2
	q = "What was Bank of America's original name? (Hint Bank of Italy or Bank of Germany)";
	a = "Bank of Italy";
	p = 50;
	head = new TriviaList(q, a, p, head);
	//Q1
	q = "How long was the shortest war on record? (Hint: how many minutes)";
	a = "38";
	p = 100;
	head = new TriviaList(q, a, p, head);

	return head;
}

void tester() {
	TriviaListPtr TriviaList = inItTrivia();
	int returnVal;
	cout << "*** this is a debug version ***" << endl;
	cout << "\nTest Case 1, Zero question with expected warning" << endl;
	returnVal = askQuestion(TriviaList, 0);
	cout << "\nTest Case 2.1, 1 question asked with correct answer " << endl;
	returnVal = askQuestion(TriviaList, 1);
	assert(100 == playPoints);
	cout << "Test case 2.1 Passed." << endl;
	cout << "\nTest Case 2.2, 1 question asked with incorrect answer" << endl;
	playPoints = 0; //reset points from previous test
	returnVal = askQuestion(TriviaList, 1);
	assert(0 == playPoints);
	cout << "Test Case 2.2 Passed." << endl;
	cout << "\nTest Case 3.1, 3 question asked with correct answer" << endl;
	playPoints = 0; //reset points from previous test
	returnVal = askQuestion(TriviaList, 3);
	assert(170 == playPoints);
	cout << "Test Case 3.1 Passed." << endl;
	cout << "\nTest Case 3.2, 3 question asked with correct answer" << endl;
	playPoints = 0; //reset points from previous test
	returnVal = askQuestion(TriviaList, 3);
	assert(0 == playPoints);
	cout << "Test Case 3.2 Passed." << endl;
	cout << "Test Case 4, Ask 5 question, exceeds trivia" << endl; 
	returnVal = askQuestion(TriviaList, 5);

	cout << "\n *** End of the Debug Version ***" << endl;
}

//Definition for getTrivia
TriviaListPtr getTrivia(TriviaListPtr list) {
	TriviaListPtr head = list;
	string question;
	string answer;
	int p;
	//Get input
	cout << "Enter a question: ";
	getline(cin, question);
	cout << "Enter an answer: ";
	getline(cin, answer);
	cout << "Enter award points: ";
	//Check to be sure points is valid (an integer > 0) 
	//Note, this specific check (while loop) was found on stack overflow.
	//Noting because outline says to note outside sources. Link in above comments.
	while (!(cin >> p) || p <= 0) {
		cout << "Points must be a number greater than 0. Try again: ";
		cin.clear(); //Clears error in cin
		cin.ignore(1000, '\n'); //Makes sure next cin is next line.
	}
	//Add to head of list
	head = addNode(question, answer, p, head);
	cin.clear();
	cin.ignore(1000, '\n'); //Moves to next line for next cin input
	return head;
}