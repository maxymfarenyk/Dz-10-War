#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

const int MAXSTEPS = 5000; // maximum number of steps
const int NCARDS = 36; // number of cards
const int NSUITS = 4; // number of suits
const int SUITVALUES = 9; // size of suit
char values[] = "6789TJQKA";
char suits[] = "cdhs";
ifstream inFile("war.txt");


int rank_card(char value, char suit)
{
	for (int i = 0; i < SUITVALUES; i++){
		if (values[i] == value){
			for (int j = 0; j < NSUITS; j++){
				if (suits[j] == suit)
					return(i * NSUITS+j);
			}
		}
	}
	
}

int value(int card)
{
	return((card) / NSUITS);
}


void war(queue<int> d1, queue<int> d2)
{
	int steps = 0; 
	int x, y;
	queue<int> warDeck;
	while (!d1.empty() && !d2.empty() && steps < MAXSTEPS)
	{

		x = d1.front();
		d1.pop();
		y = d2.front();
		d2.pop();

		cout << value(x) << " and ";
		cout << value(y) << endl;

		warDeck.push(x);
		warDeck.push(y);

		if (value(x) > value(y))
			{
				if (value(x) != 8 && value(y) != 0){
				while (!warDeck.empty())
				{
					int card = warDeck.front();
					warDeck.pop();
					d1.push(card);
				}
				}
				else if (value(x) == 8 && value(y) == 0) {
					while (!warDeck.empty())
					{
						int card = warDeck.front();
						warDeck.pop();
						d2.push(card);
					}
				}

			}
		else if (value(x) < value(y))
		{
				if (value(x) != 0 && value(y) != 8) {
				while (!warDeck.empty())
				{
					int card = warDeck.front();
					warDeck.pop();
					d2.push(card);
				}
				}
				else if (value(x) == 0 && value(y) == 8) {
					while (!warDeck.empty())
					{
						int card = warDeck.front();
						warDeck.pop();
						d1.push(card);
					}
				}
	
		}
		else if (value(x) == value(y)) {
			while (!warDeck.empty())
			{
				int card = warDeck.front();
				warDeck.pop();
			}
		}


		steps++;
	}
		if (!d1.empty() && d2.empty())
			cout << "deck 1 wins in " << steps << " steps" << endl;
		else if (d1.empty() && !d2.empty())
			cout << "deck 2 wins in " << steps << " steps" << endl;
		else
			cout << "game tied after " << steps << " steps, deck 1 has " << d1.size()
			<< " cards while deck 2 has " << d2.size() << " cards" << endl;
}
void clear(queue<int>& d)
{
	while (!d.empty())
		d.pop();
}

int main()
{
	queue<int> decks[2]; 
	char val, suit;

		for (int i = 0; i < 2; i++)
		{
			val = inFile.get();
			while (val != '\n' && val != EOF)
			{
				if (val != ' ')
				{
					suit = inFile.get();
					decks[i].push(rank_card(val, suit));
					cout << decks[i].back() << " ";
				}
				val = inFile.get();
				
			}
			cout << endl;
		}

		war(decks[0], decks[1]);
		clear(decks[0]);
		clear(decks[1]);

	return 0;
}