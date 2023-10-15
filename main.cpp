#include <iostream>
#include <random>
#include <list>

int getRandomNumber(int a, int b) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(a, b);
    return distribution(gen);
}

int montyhallgame(int willswitch)
{
    std::list<int> remainingDoors = {1, 2, 3};
    // 1. Monty sets up the doors
    int winningDoor = getRandomNumber(1, 3);
    int losingDoor1, losingDoor2;
    if (winningDoor == 1) {
        losingDoor1 = 2;
        losingDoor2 = 3;
    } else if (winningDoor == 2) {
        losingDoor1 = 1;
        losingDoor2 = 3;
    } else {
        losingDoor1 = 1;
        losingDoor2 = 2;
    }

    // 2. The player chooses one at random.
    int playerChoiceDoor = getRandomNumber(1, 3);
    // 3. An unchosen door with a goat is revealed.
    // If one goat is in the unchosen door, that door is revealed, obviously.
    int removedDoor;
    if (winningDoor != playerChoiceDoor)
    {
        for(int i = 1; i <= 3; i++)
        {
            if((winningDoor != i) && (playerChoiceDoor != i))
            {
                removedDoor = i;
            }

        }
    }
        // If both goats are behind the unchosen doors, one of the two doors is revealed at random.
    else
    {
        if (playerChoiceDoor == 1)
        {
            removedDoor = getRandomNumber(2, 3);
        }
        else if (playerChoiceDoor == 2)
        {
            removedDoor = getRandomNumber(1, 2);
            if (removedDoor == 2)
            {
                removedDoor = 3;
            }

        }
        else
        {
            removedDoor = getRandomNumber(1, 2);
        }
    }


    //4. The choice to switch or not is applied.
    if (willswitch == 1)
    {
        for(int i = 1; i <= 3; i++)
        {
            if (i != playerChoiceDoor && i != removedDoor)
            {
                playerChoiceDoor = i;
            }
        }
    }
    //5. Evaluated for win.
    if (playerChoiceDoor == winningDoor)
    {
        return(1);
    }
    else
    {
        return(0);
    }


}

void winrateSimulation(int totalgames)
{
    int switched = 0;
    int didnt_switch = 0;

    for(int i = 0; i < totalgames; i++)
    {
        switched = switched + montyhallgame(1);
        didnt_switch = didnt_switch + montyhallgame(0);
        std::cout << (double)i*100.0/(double)totalgames << "% Switch Winrate: " << (double)switched*100.0/(double)i << "% No Switch Winrate: " << (double)didnt_switch*100.0/(double)i <<"%       \r"<< std::flush;
    }

    double switched_winrate = (switched*100)/totalgames;
    double didntswitch_winrate = (didnt_switch*100)/totalgames;
    std::cout << "Switched Wins: " << switched << " Didn't Switch Wins: " << didnt_switch << std::endl;

    std::cout << "Switched Winrate: " << switched_winrate << " Didn't Switch: " << didntswitch_winrate << std::endl;
}

void machineLearning(int epochs, double learningrate)
{
    int wins = 0;
    int gamescount = 0;
    for(int i = 1; i <= epochs; i++)
    {

        if (i % 200000 == 0) {
            wins = 0;
            gamescount = 0;
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        double shouldswitch = distribution(gen);

        std::random_device rd2;
        std::mt19937 gen2(rd2());
        std::bernoulli_distribution distribution2(shouldswitch);

        int willswitch = distribution2(gen2);

        int result = montyhallgame(willswitch);
        gamescount++;

        if (result == 1) {
            wins++;
                if (willswitch == 0)shouldswitch += (-1)*learningrate;
                else if (willswitch == 1) shouldswitch += learningrate;
        }
        else
        {
            if (willswitch == 1)shouldswitch += (-1)*learningrate;
            else if (willswitch == 0) shouldswitch += learningrate;
        }

        double winrate = (double)wins*100.0/double(gamescount);
        if (i % 10000 == 0) std::cout << "Epoch: " << i << " shouldSwitch: " << shouldswitch << " Winrate: " << winrate << "  \r" << std::flush;
    }
}
int main() {

    machineLearning(99999999999, 0.000000001);

    return 0;
}
