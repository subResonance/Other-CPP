#include <iostream>
#include <time.h>

/* Places the outlier "coin" at a random position within
	our coins after initialization. 
	normal_coin represented as (false) : outlier_coin is (true) */
bool* initializeCoins(const int numCoins) {
	srand(time(NULL));
	bool* coins = new bool[numCoins];
	const int randIndex = (rand() % numCoins);
	std::cout << "   There are " << numCoins << " coins presented\n";

	for (int i = 0; i < numCoins; i++) { *(coins + i) = false; } // Initialization
	*(coins + randIndex) = true;
	std::cout << "   Outlier coin was placed at index: " << randIndex << "\n\n";

	return coins;
}


/* RECALL: All coins are of the same weight except for the
	outlier coin, which is of heavier weight */
/* RETURNS:
	0 if left scale contains the heavier coin
	1 if right scale contains the heavier coin
	2 if the heavier coin is not present on either side */
const int performWeigh(const bool* left, const bool* right, const int subset_size) {
	for (int i = 0; i < subset_size; i++) {
		if (*(left + i)) { return 0; }
	}
	for (int i = 0; i < subset_size;  i++) {
		if (*(right + i)) { return 1; }
	}
	return 2;
}


/* DIVIDE AND CONQUER: Recursive function that locates the
	index of the outlier_coin. */
/* RECALL: Our initial input size is constrained to the subspace of values 3^n */

/* Initial indexing of our subsets is lost with each array subdivison.
	EX: Final base case is of size 3 with indices (0,2) relative to itself, but we 
	do not know which slice of the initial array these final 3 coins are from.
	Therefore an offset value is updated after each subcall in the form:
		[subcall_numCoins - (subset_size * the subset value)]
	Alowing us to maintain indexing relative to the ORIGINAL array */
const int findCoin(const bool* coins, const int subcall_numCoins, const int initial_numCoins, int indexOffset) {
	const int subset_size = subcall_numCoins / 3;
	const bool* subsets[3] = { coins, (coins + subset_size), (coins + (2 * subset_size)) };
	const int weighResult = performWeigh(subsets[0], subsets[1], subset_size);
	
	if (subcall_numCoins == 3) { return weighResult + indexOffset; } // Base case

	else {
		int subcall_offset;

		if (weighResult > 0) {
			subcall_offset = subcall_numCoins;
			if (weighResult == 1) { subcall_offset -= (subset_size * 2); }
			else { subcall_offset -= subset_size; }
		}
		/* If subsets[0] is selected from performWeigh, no offset is needed at all
			(it is the leftmost section of the array so indexing never changed) */
		else { subcall_offset = 0; }
		indexOffset += subcall_offset;

		findCoin(subsets[weighResult], subset_size, initial_numCoins, indexOffset); // Recursive function call
	}
}


int main(){
	// Enter an input size with a value of 3^n
	const int INPUT_SIZE = 14348907;

	if (INPUT_SIZE % 3 != 0) { 
		std::cout << "INVALID INPUT SIZE\n"; 
		exit(EXIT_FAILURE);
	}

	std::cout << "Coin Detection\n--------------\n";
	std::cout << "Outlier Coin was found at index: " << findCoin(initializeCoins(INPUT_SIZE), INPUT_SIZE, INPUT_SIZE, 0);
}
