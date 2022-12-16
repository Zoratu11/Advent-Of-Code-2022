//DAY 1 PUUZLE 2 OF ADVENT OF CODE

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/*
--- Part Two ---

By the time you calculate the answer to the Elves' question, they've already realized that the Elf carrying the most Calories of food might eventually run out of snacks.

To avoid this unacceptable situation, the Elves would instead like to know the total Calories carried by the top three Elves carrying the most Calories. That way, even if one of 
those Elves runs out of snacks, they still have two backups.

In the example above, the top three Elves are the fourth Elf (with 24000 Calories), then the third Elf (with 11000 Calories), then the fifth Elf (with 10000 Calories). The sum of 
the Calories carried by these three elves is 45000.

Find the top three Elves carrying the most Calories. How many Calories are those Elves carrying in total?

*/

//This function returns the total calories from the top 3 elves
const int getTotalFromTop3Elves(const std::string& fileName);

//takes an elf file stream and splits it based on newline characters and adds the numbers in between the whitespace
const std::vector<int> splitAndAdd(std::ifstream& fileStream);

//input: vector<int> with more than 3 elements - output: vector<int> containing the 3 highest numbers from the original vector (returns empty vector if input is wrong)
const std::vector<int> getTop3(const std::vector<int>& vec);


int main()
{
    int calories = getTotalFromTop3Elves("input.txt");

    std::cout << "The total calories from the top 3 elves is: " << calories << std::endl;

}

const int getTotalFromTop3Elves(const std::string& fileName) {
    std::ifstream elfFileStream(fileName);

    //First split up the numbers based on a new line and add them
    std::vector<int> elves = splitAndAdd(elfFileStream);

    std::vector<int> top3 = getTop3(elves);

    int totalCalories = 0;
    //quickly total up the numbers from the top 3 elves
    for (auto const num : top3)
    {
        totalCalories += num;
    }
    return totalCalories;
}

const std::vector<int> splitAndAdd(std::ifstream& fileStream)
{
    std::vector<int> elves;
    char delimeter = '\n';
    std::string token;       //will hold number of food calories and empty strings when we get there

    int elfTotalCalories = 0;
    while (std::getline(fileStream, token, delimeter))
    {
        if (token == "")     //empty line so now we add elfTotal calories to vector and start over
        {
            elves.push_back(elfTotalCalories);
            elfTotalCalories = 0;
        }
        else
        {
            //add "food calories" to total
            elfTotalCalories += std::stoi(token);
        }
    }

    return elves;
}

//quick and dirty sort for top 3
void sort(std::vector<int>& top3)
{
    if (top3[0] > top3[2])
    {
        //swap 1 and 3
        int temp = top3[2];
        top3[2] = top3[0];
        top3[0] = temp;
    }

    if (top3[0] > top3[1])
    {
        //swap 1 and 2
        int temp = top3[1];
        top3[1] = top3[0];
        top3[0] = temp;
    }

    //Now the smallest element is the first one, just check 2 and 3 now
    if (top3[1] > top3[2])
    {
        //swap 2 and 3
        int temp = top3[2];
        top3[2] = top3[1];
        top3[1] = temp;
    }

}

const std::vector<int> getTop3(const std::vector<int>& vec)
{
    std::vector<int> top3;
    if (vec.size() < 3)
    {
        std::cout << "Sorry that vector is too small to get the top 3" << std::endl;
        return top3;
    }

    //insert first 3 elements into top3
    top3.push_back(vec[0]);
    top3.push_back(vec[1]);
    top3.push_back(vec[2]);

    //vector will always be smallest to largest to make things simple in the for loop
    sort(top3);

    //start at the fourth element because the first 3 are already stored in top3
    for (int i = 3; i < vec.size(); i++)
    {
        /*
        *In this for loop we start at the end of top3 and go down to 0 as we compare against vec
        *then if we replace an element with one from vec, we break so we dont keep replacing (if we are not at 0 yet, of course)
        */
        for (int j = 2; j >= 0; j--)
        {
            if (vec[i] > top3[j])
            {
                if (j == 2)
                {
                    //shift 3rd and 2nd number down one so we dont lose a number
                    int temp = top3[j - 1];
                    top3[j - 1] = top3[j];
                    top3[j - 2] = temp;
                }
                if (j == 1)
                {
                    //only shift 2nd number down one
                    top3[j - 1] = top3[j];
                }
                top3[j] = vec[i];
                break;
            }
        }
    }

    return top3;
}