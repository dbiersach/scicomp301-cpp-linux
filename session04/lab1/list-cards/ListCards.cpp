// ListCards.cpp

#include "stdafx.h"

using namespace std;

void InitDeck(vector<int>& deck)
{
	for (size_t i{}; i < deck.size(); ++i)
		deck.at(i) = i;
}

void DisplayCards(vector<int>& deck)
{
	const vector<string> suit{ "Clubs", "Diamonds",
							   "Hearts", "Spades" };

	const vector<string> rank{ "Deuce", "Three", "Four",
							   "Five", "Six", "Seven",
							   "Eight", "Nine", "Ten",
							   "Jack", "Queen", "King",
							   "Ace" };

	for (size_t i{}; i < deck.size();++i) {
		int card = deck.at(i);
		cout << "Card in position " << i
			<< " is the " << rank.at(0)
			<< " of " << suit.at(0) << endl;
	}
}

int main()
{
	vector<int> deck(52);

	InitDeck(deck);

	DisplayCards(deck);

	return 0;
}
