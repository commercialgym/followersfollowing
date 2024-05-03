/*
* Project Name: Compare Followers/Following
* Programmer: Alexia Tu
* Date: 05-03-2024
* Description: Exporting followers and following from a profile to a csv file and then reading that
* file and putting the usernames into an array. Then comparing the usernames of the followers to following
* to see if there are people you follow who don't follow you back.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

const int kMaxLines = 2000;

int main(int argc, char* argv)
{
    std::string* followerNameArr = new std::string[kMaxLines];
    int lineCount = 0;

    //change hardcoded directory to argv
    std::string followersDir = "D:\\followers\\alexia.tu-followers.csv";

    std::ifstream followersFile(followersDir);
    //error check to see if it can open, see if there is another way to error check in cpp
    if (!followersFile)
    {
        std::cerr << "Failed to open." << std::endl;
        return 1;
    }

    std::string line;

    while (getline(followersFile, line))
    {
        //userName is the "token"
        std::string userName;

        std::stringstream inputString(line);

        //look into if this is the optimal way to parse for first token
        if (std::getline(inputString, userName, ',')) 
        {
            followerNameArr[lineCount] = userName;
            if (lineCount >= kMaxLines)
            {
                std::cerr << "List Limit Reached for followers" << std::endl;
            }
        }

        lineCount++;

        line = "";
    }

    /*
    for (int i = 0; i < lineCount; i++)
    {
        std::cout << " Username: " << i + 1 << ": " << followerNameArr[i] << std::endl;
    }
    */

    std::cout << "Hello World!\n";

    delete[] followerNameArr;

    return 0;
}

