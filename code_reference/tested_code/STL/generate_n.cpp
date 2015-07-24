/* ===========================================
			WHAT IS ILLUSTRATED HERE

	Example taken from the Rogue Wave User guide
	Illustrate generate_n

	
	generate_n calls a generator function a specified number of 
	times and fills a sequence using an inserting iterator

	
	the advantage of having the generator function as class is
	that the member_variables act as static variables (retain
	their value in successive calls). In this example e.g., 
	each call to DeckGen::operator() will result in a different
	Card object.

	The function returns the Card object by value and it is then
	inserted in a value based container.

* =========================================== */


/* -- *
*

  The following example is a complete program that creates
  a deck of cards and shuffles it.
  The purpose of the example is to show how the Tools.h++ 
  template collections can be used in conjunction with the 
  Standard C++ Library. See your Standard C++ Library documentation
  for more information on the features used in the example.
*
* -- */

/* Note: This example requires the C++ Standard Library */

#include <iostream.h>
#include <algorithm>
#include <rw/tvordvec.h>

struct Card {
	char  rank;
	char  suit;
	
	bool operator==(const Card& c) const
	{ return rank == c.rank && suit == c.suit; }
	
	Card() { }
	Card(char r, char s) : rank(r), suit(s) { }
	
	// print card: e.g. '3-C' = three of clubs, 'A-S' = ace of spades
	friend ostream& operator<<(ostream& ostr, const Card& c)
	{ return (ostr << c.rank << "-" << c.suit << "  "); }
};

/*
* A generator class - return Cards in sequence
*/
class DeckGen {
	int rankIdx;  // indexes into static arrays below
	int suitIdx;
	static const char Ranks[13];
	static const char Suits[4];
public:
	DeckGen() : rankIdx(-1), suitIdx(-1) { }
	
	// generate the next Card
	Card operator()() {
		rankIdx = (rankIdx + 1) % 13;
		if (rankIdx == 0)
			// cycled through ranks, move on to next suit:
			suitIdx = (suitIdx + 1) % 4;
		return Card(Ranks[rankIdx], Suits[suitIdx]);
	}
};

const char DeckGen::Suits[4]  = {'S', 'H', 'D', 'C' };
const char DeckGen::Ranks[13] = {'A', '2', '3', '4',
'5', '6', '7', '8',
'9', 'T', 'J', 'Q', 'K' };

int main(){
	// Tools.h++ collection:
	RWTValOrderedVector<Card> deck;
	RWTValOrderedVector<Card>::size_type pos;
	
	Card aceOfSpades('A','S');
	Card firstCard;
	
	// Use standard library algorithm to generate deck:
	generate_n(back_inserter(deck.std()), 52, DeckGen());
	cout << endl << "The deck has been created" << endl;
	
	// Use Tools.h++ member function to find card:
	pos = deck.index(aceOfSpades);
	cout << "The Ace of Spades is at position " << pos+1 << endl;
	
	// Use standard library algorithm to shuffle deck:
	random_shuffle(deck.begin(), deck.end());
	cout << endl << "The deck has been shuffled" << endl;
	
	// Use Tools.h++ member functions:
	pos = deck.index(aceOfSpades);
	firstCard = deck.first();
	
	cout << "Now the Ace of Spades is at position " << pos+1
		<< endl << "and the first card is " << firstCard << endl;
}


/* Output (will vary because of the shuffle):

  The deck has been created
  The Ace of Spades is at position 1
  
	The deck has been shuffled
	Now the Ace of Spades is at position 37
	and the first card is Q-D  
	
*/