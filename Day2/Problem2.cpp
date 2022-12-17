#include <iostream>
#include <string>
#include <fstream>
#include <map>

/*
--- Part Two ---

The Elf finishes helping with the tent and sneaks back over to you. "Anyway, the second column says how the round needs to end: X means you need to lose, Y means you need to end 
the round in a draw, and Z means you need to win. Good luck!"

The total score is still calculated in the same way, but now you need to figure out what shape to choose so the round ends as indicated. The example above now goes like this:

    In the first round, your opponent will choose Rock (A), and you need the round to end in a draw (Y), so you also choose Rock. This gives you a score of 1 + 3 = 4.
    In the second round, your opponent will choose Paper (B), and you choose Rock so you lose (X) with a score of 1 + 0 = 1.
    In the third round, you will defeat your opponent's Scissors with Rock for a score of 1 + 6 = 7.

Now that you're correctly decrypting the ultra top secret strategy guide, you would get a total score of 12.

Following the Elf's instructions for the second column, what would your total score be if everything goes exactly according to your strategy guide?

*/

//a = 1 b = 2 scissors = 3

enum
{
    Lose = 0, Draw = 3, Win = 6, 
    Rock = 1, Paper = 2, Scissors = 3
};

//Gets Rock paper scissor score in current line
int getScore(std::string currentLine)
{
    //make sure string is longer than 3 otherwise our function will probably throw an error
    if(currentLine.length() < 3)
    {
        std::cout << "string is shorter than 3! returning 0" << std::endl;
        return 0;
    }

    std::map<char, int> handMap{{'A', Rock}, {'B', Paper}, {'C', Scissors}};
    std::map<char, int> outcomeMap{{'X', Lose}, {'Y', Draw}, {'Z', Win}};

    int score = 0;
    //opponent hand is the first element and your needed outcome is the third element because they are seperated by a space
    char opponentHand = currentLine[0];
    char neededOutcome = currentLine[2];

    //get initial score from what hand you and opponent picked
    int opponentScore = handMap[opponentHand];
    int outcome = outcomeMap[neededOutcome];

    if(outcome == Draw)
    {
        //you need a draw so return Drawscore + opponentScore because you also need to play the same thing
        return Draw + opponentScore;
    }

    
    switch(opponentScore)
    {
        case Rock:
            if(outcome == Win)
            {
                return outcome + Paper;
            }
            return outcome + Scissors;
        case Paper:
            if(outcome == Win)
            {
                return outcome + Scissors;
            }
            return outcome + Rock;
        case Scissors:
            if(outcome == Win)
            {
                return outcome + Rock;
            }
            return outcome + Paper;
    }
    //should never get here
    return 0;
}

int main()
{
    std::ifstream MyReadFile("input.txt");

    int totalScore = 0;
    std::string currentLine;
    while(std::getline(MyReadFile, currentLine))
    {
        totalScore += getScore(currentLine);
        std::cout << currentLine << "\n";
    }

    std::cout << "The total score if we follow the strategy is: " << totalScore << std::endl;

    return 0;
}