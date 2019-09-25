#include <iostream>
#include <cstring>
#include <ctime>

using namespace std;

string sushi = "WWIII";

void randomizeSushi(){ // Performs swaps at every index to randomize string
    int n = 0;
    int numSushi = sushi.length();
    
    while (n < numSushi){
        int r = rand() % numSushi;
        
        char temp = sushi[n];
        sushi[n] = sushi[r];
        sushi[r] = temp;
        n++;
    }
}

int main()
{
    const int NUM_SIMULATIONS = 10;
    const int NUM_TRIALS = 1000000;
    float PAB = 0.0;
    int eventA, eventB, numSushi, pickSushi;
    char firstSushi;

    srand(time(NULL)); // Uses the time to seed the random number generation

    int count = 0; // Number of simulations that have been performed

    while (count < NUM_SIMULATIONS){
        int trials = 0;
        eventA = 0;
        eventB = 0;

        while (trials < NUM_TRIALS){
            sushi = "WWIII";
            numSushi = sushi.size();
            firstSushi = ' ';

            randomizeSushi();
            pickSushi = rand() % numSushi;

            if(sushi[pickSushi] == 'W'){ // If the randomly selected sushi is wasabi, increment eventA and test for eventB
                firstSushi = 'W';
                eventA++;
                
                while (pickSushi < numSushi - 1){
                    sushi[pickSushi] = sushi[pickSushi + 1];
                    pickSushi++;
                }
                
                numSushi--;
                pickSushi = rand() % numSushi;
                
                if(sushi[pickSushi] == 'W' && firstSushi == 'W'){ // If a wasabi is picked twice in a row, increment eventB
                    eventB++;
                }
            }
            // If a wasabi isn't chosen on pick 1, eventB isn't possible, move onto next trial
            trials++;

        }

        cout << "Trial#\t" << count + 1 << "\tA = " << eventA<< "\tB = " << eventB
        << "\tP(A and B): " << (100.0 * eventB / NUM_TRIALS) << "\%\n"; // P(A and B) for the current simulation is calculated
        
        PAB += (100.0 * eventB / NUM_TRIALS); // P(A and B) incremented for all simulations
        count++;
        
    } 

    cout << "On average, P(A and B) = " << PAB / NUM_SIMULATIONS << "\%\n";
    return 0;
    
} // Closes main
