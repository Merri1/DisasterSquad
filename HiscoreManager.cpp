#include "HiscoreManager.h"
#include <iostream>
#include <fstream>
#include <string>

int hiScore;

HiscoreManager::HiscoreManager()
{

}

void writeToFile()
{
    std::ifstream file;
    file.open("my_file.txt");

    if (!file) 
    {
        std::cout << "File not created!";
    }
    else 
    {
        std::cout << "File created successfully!";
        //file << playerScore;
        file.close();
    }
    

}

void parseFile()//Load file to data structure
{
    std::ifstream file("assets/Hiscore.txt");
    std::string str;
    std::string file_contents;
    while (std::getline(file, str))
    {
        file_contents += str;
        file_contents.push_back('\n');
    }
}

int	compareScore(int playerScore)
{
    if (playerScore >= hiScore)
    {
        hiScore = playerScore;
    }
}

void printScores()
{
    std::ofstream outputFile("assets/Hiscore.txt");
    outputFile << hiScore;
    outputFile.close();
}