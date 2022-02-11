#ifndef HISCOREMANAGER_H
#define HISCOREMANAGER_H
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

class HiscoreManager
{
public:
    HiscoreManager();
    void readTextFile();
    bool compareScores(int score);
    void writeTextFile();
    string scoreToString(string player);
    static bool sortScoreDesc(pair<string, int>& firstPair, pair<string, int>& secondPair);

protected:
    const int MAX_SCORES = 10;
    string m_playerName;
    int m_playerScore;
    bool m_newHiscore;
    vector<pair<string, int>> m_scoreVector;
};
#endif