#include "HiscoreManager.h"

using namespace std;

HiscoreManager::HiscoreManager()
{}

void HiscoreManager::readTextFile()
{
    m_scoreVector.clear();

    ifstream inputFile("../assets/text_files/scores.txt");

    string name;
    int score;

    while (inputFile >> name >> score)
    {
        m_scoreVector.push_back(make_pair(name, score));
    }

    inputFile.close();
}

bool HiscoreManager::compareScores(int score)
{
    m_playerScore = score;

    if (m_scoreVector.size() == 0 || m_scoreVector.size() < 10)
    {
        m_newHiscore = true;
    }
    else
    {
        for (int i = 0; i < m_scoreVector.size(); i++)
        {
            if (m_scoreVector[i].second < score)
            {
                m_newHiscore = true;
            }
        }
    }

    return m_newHiscore;
}

void HiscoreManager::writeTextFile()
{
    ofstream newScoreFile("../assets/text_files/scores.txt");

    int count = 0;

    for (int i = 0; i < m_scoreVector.size(); i++)
    {
        newScoreFile << m_scoreVector[i].first << " " << m_scoreVector[i].second << endl;

        count++;

        if (count >= MAX_SCORES)
        {
            break;
        }
    }

    newScoreFile.close();
}

bool HiscoreManager::sortScoreDesc(pair<string, int>& firstPair, pair<string, int>& secondPair)
{
    return (firstPair.second > secondPair.second);
}

string HiscoreManager::scoreToString(string player)
{
    m_playerName = player;

    if (m_newHiscore)
    {
        m_scoreVector.push_back(make_pair(m_playerName, m_playerScore));
        m_newHiscore = false;
    }

    sort(m_scoreVector.begin(), m_scoreVector.end(), sortScoreDesc);

    stringstream ss;

    ss << "TOP SCORES:  ";

    for (int i = 0; i < m_scoreVector.size(); i++)
    {
        if (i >= 1)
        {
            ss << " \t\t\t";
        }

        ss << left << setw(3) << i+1 << setw(12) << m_scoreVector[i].first << " " << setw(5) << m_scoreVector[i].second << "\n";

        // Only show the top 10 scores
        if (i == MAX_SCORES - 1)
        {
            i = m_scoreVector.size() - 1;
        }
    }

    // Write to file
    writeTextFile();

    // Return string of top 10 scores
    return ss.str();
}

