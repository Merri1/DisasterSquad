#ifndef HISCOREMANAGER_H
#define HISCOREMANAGER_H


class HiscoreManager
{
public:
	HiscoreManager();

	void parseFile();//Load file to data structure
	void writeFile();
	int	compareScore(int playerScore);
	void printScores();


protected:

};

#endif
