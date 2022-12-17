#include <iostream>
#include <string>
#include <fstream>
#include <map>

/*
--- Day 2: Rock Paper Scissors ---

The Elves begin to set up camp on the beach. To decide whose tent gets to be closest to the snack storage, a giant Rock Paper Scissors tournament is already in progress.

Rock Paper Scissors is a game between two players. Each game contains many rounds; in each round, the players each simultaneously choose one of Rock, Paper, or Scissors using a 
hand shape. Then, a winner for that round is selected: Rock defeats Scissors, Scissors defeats Paper, and Paper defeats Rock. If both players choose the same shape, the round 
instead ends in a draw.

Appreciative of your help yesterday, one Elf gives you an encrypted strategy guide (your puzzle input) that they say will be sure to help you win. "The first column is what 
your opponent is going to play: A for Rock, B for Paper, and C for Scissors. The second column--" Suddenly, the Elf is called away to help with someone's tent.

The second column, you reason, must be what you should play in response: X for Rock, Y for Paper, and Z for Scissors. Winning every time would be suspicious, so the responses 
must have been carefully chosen.

The winner of the whole tournament is the player with the highest score. Your total score is the sum of your scores for each round. The score for a single round is the 
score for the shape you selected (1 for Rock, 2 for Paper, and 3 for Scissors) plus the score for the outcome of the round (0 if you lost, 3 if the round was a draw, and 6 if you 
won).

Since you can't be sure if the Elf is trying to help you or trick you, you should calculate the score you would get if you were to follow the strategy guide.

For example, suppose you were given the following strategy guide:

A Y
B X
C Z

This strategy guide predicts and recommends the following:

    In the first round, your opponent will choose Rock (A), and you should choose Paper (Y). This ends in a win for you with a score of 8 (2 because you chose Paper + 6 
    because you won).
    In the second round, your opponent will choose Paper (B), and you should choose Rock (X). This ends in a loss for you with a score of 1 (1 + 0).
    The third round is a draw with both players choosing Scissors, giving you a score of 3 + 3 = 6.

In this example, if you were to follow the strategy guide, you would get a total score of 15 (8 + 1 + 6).

What would your total score be if everything goes exactly according to your strategy guide?

*/

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

    std::map<char, int> handMap{{'A', Rock}, {'B', Paper}, {'C', Scissors}, 
                                {'X', Rock}, {'Y', Paper}, {'Z', Scissors}};

    int score = 0;
    //opponent hand is the first element and your hand is the third element because they are seperated by a space
    char opponentHand = currentLine[0];
    char yourHand = currentLine[2];

    //get initial score from what hand you and opponent picked
    int opponentScore = handMap[opponentHand];
    int yourScore = handMap[yourHand];

    if(opponentScore == yourScore)
    {
        //it is a draw so return Drawscore + score
        return Draw + yourScore;
    }

    //algorithm I just thought of
    int total = yourScore + opponentScore;  //just used in algorithm, not total score
    switch(total)
    {
        case Scissors + Paper:
            if(yourScore == Scissors) 
            {
                //you won so return winscore + yourscore
                return Win + yourScore;
            }
            return Lose + yourScore;
        case Rock + Scissors:
            if(yourScore == Rock)
            {
                return Win + yourScore;
            }
            return Lose + yourScore;
        case Rock + Paper:
            if(yourScore == Paper)
            {
                return Win + yourScore;
            }
            return Lose + yourScore;
        
        default:
            std::cout << "if this gets run you are stupid" << std::endl;
            return 0;
    }

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