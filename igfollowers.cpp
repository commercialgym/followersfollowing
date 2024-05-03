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

int createNamesList(std::string, std::string*);

int main(int argc, char* argv)
{
    //list for followers
    std::string* followerNameArr = new std::string[kMaxLines];

    //change hardcoded directory to argv
    std::string followersDir = "D:\\followers\\alexia.tu-followers.csv";

    int linesRead;
    linesRead = createNamesList(followersDir, followerNameArr);


    //list for following
    std::string* followingNameArr = new std::string[kMaxLines];

    std::string followingDir = "D:\\followers\\alexia.tu-following.csv";

    createNamesList(followingDir, followingNameArr);

    /*
    for (int i = 0; i < linesRead; i++)
    {
        std::cout << " Username: " << i + 1 << ": " << followerNameArr[i] << std::endl;
    }
    */

    //std::cout << "Hello World!\n";

    delete[] followerNameArr;
    delete[] followingNameArr;

    return 0;
}

int createNamesList(std::string followDir, std::string* userNameArr)
{
    //std::string* userNameArr = new std::string[kMaxLines];


    std::ifstream followFile(followDir);
    //error check to see if it can open, see if there is another way to error check in cpp
    if (!followFile)
    {
        std::cerr << "Failed to open." << std::endl;
        return 1;
    }

    int lineCount = 0;
    std::string line;

    while (getline(followFile, line))
    {
        //userName is the "token"
        std::string userName;

        std::stringstream inputString(line);

        //look into if this is the optimal way to parse for first token
        if (std::getline(inputString, userName, ','))
        {
            userNameArr[lineCount] = userName;
            if (lineCount >= kMaxLines)
            {
                //can specify for if limit was reached for followers/following later
                std::cerr << "List Limit Reached" << std::endl;
            }
        }

        lineCount++;

        line = "";
    }

    return lineCount;
}