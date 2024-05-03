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

const int kMaxLines = 3000;

int createNamesList(std::string, std::string*);

int main(int argc, char* argv[])
{

    if (argc < 3)
    {
        std::cerr << "Not enough command line arguments" << std::endl; 
    }
    //list for followers
    std::string* followerNameArr = new std::string[kMaxLines];

    //change hardcoded directory to argv
    std::string followersDir;
    followersDir = argv[1];

    int linesRead;
    linesRead = createNamesList(followersDir, followerNameArr);


    //list for following
    std::string* followingNameArr = new std::string[kMaxLines];

    std::string followingDir;
    followingDir = argv[2];

    int totalLines;
    totalLines = createNamesList(followingDir, followingNameArr);

    //now to compare

    //if element from following not found in followers, print to screen or add to array

    // < = ?
    int followsBack;

    std::cout << "The people who don't follow you back are: " << std:: endl; 

    //totalLines is the number of lines read from who you follow
    for (int i = 0; i < totalLines; i++)
    {
        followsBack = 0;
        //linesRead is the number of lines from those who follow you
        for (int j = 0; j < linesRead; j++)
        {
            //if there is a match in usernames that means that they follow back and 
            //there is no need to keep searching
            if (followingNameArr[i].compare(followerNameArr[j]) == 0)
            {
                followsBack = 1;
                break;
            }
        }

        if (followsBack == 0)
        {
            std::cout << followingNameArr[i] << std:: endl;
        }

    }

    //print the index of following that does not exist in followers


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