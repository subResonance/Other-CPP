#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct record {
	string precinct;
	string candidate;
	short votes;
};

struct Node {
	record data;
	struct Node *next;
};
struct candidate {
	string name;
	short numVotes = 0;
};

int main() {
	short recordCount = 0;
	ifstream fin;
	Node* head = new Node;
	recordCount++; // Increment after creation
	Node* nPtr = head;

	fin.open("votes.txt");

	for (int i = 0; i < 13; i++) {
		Node* n = new Node;
		recordCount++; // Increment after creation
		nPtr->next = n;
		fin >> nPtr->data.precinct;
		fin >> nPtr->data.candidate;
		fin >> nPtr->data.votes;
		nPtr = n;
	}
	nPtr->next = NULL; // Since this is the last node
	fin >> nPtr->data.precinct;
	fin >> nPtr->data.candidate;
	fin >> nPtr->data.votes;
	fin.close();

	short totalVotes = 0;
	candidate Jeff_Bezos, Satya_Nadella, Tim_Cook, Sundar_Pachai, Mark_Zuckerberg, Elon_Musk, Mary_Barra;
	Jeff_Bezos.name = "Jeff_Bezos"; Satya_Nadella.name = "Satya_Nadella"; Tim_Cook.name = "Tim_Cook"; Sundar_Pachai.name = "Sundar_Pachai";
	Mark_Zuckerberg.name = "Mark_Zuckerberg"; Elon_Musk.name = "Elon_Musk"; Mary_Barra.name = "Mary_Barra";

	Node *temp = new Node;
	temp = head;

	cout << "Election Results" << endl << "----------------" << endl;

	while (temp != NULL) {
		if (temp->data.candidate == "Jeff_Bezos") { Jeff_Bezos.numVotes += temp->data.votes; }
		else if (temp->data.candidate == "Satya_Nadella") { Satya_Nadella.numVotes += temp->data.votes; }
		else if (temp->data.candidate == "Tim_Cook") { Tim_Cook.numVotes += temp->data.votes; }
		else if (temp->data.candidate == "Sundar_Pachai") { Sundar_Pachai.numVotes += temp->data.votes; }
		else if (temp->data.candidate == "Mark_Zuckerberg") { Mark_Zuckerberg.numVotes += temp->data.votes; }
		else if (temp->data.candidate == "Elon_Musk") { Elon_Musk.numVotes += temp->data.votes; }
		else if (temp->data.candidate == "Mary_Barra") { Mary_Barra.numVotes += temp->data.votes; }

		totalVotes += temp->data.votes;
		cout << "     " << temp->data.precinct << " casts " << temp->data.votes << " votes for " << temp->data.candidate << endl;
		temp = temp->next;
	}

	cout << "\n" << recordCount << " records created" << endl;
	cout << totalVotes << " votes have been cast" << endl << endl;

	candidate resultsArr[7] = { Jeff_Bezos, Satya_Nadella, Tim_Cook, Sundar_Pachai, Mark_Zuckerberg, Elon_Musk, Mary_Barra };
	candidate mostVotes = Jeff_Bezos; // Arbitrary assignment to begin sorting

	for (int i = 0; i < 7; i++) {
		if (resultsArr[i].numVotes > mostVotes.numVotes) {
			mostVotes = resultsArr[i];
		}
	}

	cout << "The winner is " << mostVotes.name << " with " << mostVotes.numVotes << " votes" << endl;

}
