
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <fstream>
#include "FilePasser.h"
#include <iostream>

using namespace sf;
using namespace std;


FilePasser::FilePasser()
{

	int Darray[36][64] = { { 0 },{ 0 } };

	ifstream inputFile("GrasslandsASCIImap.txt");

	// Go back to the start of the file
	inputFile.clear();
	inputFile.seekg(0, ios::beg);


	// Loop through the file and store all the values in the 2d array
	string row;
	int y = 0;
	while (inputFile >> row)
	{
		for (int x = 0; x < 64; x++) {

			const char val = row[x];
			Darray[y][x] = atoi(&val);
		}

		y++;
	}
	for (int i = 0; i < 36; i++)
	{

		for (int j = 0; j < 64; j++)
		{
			cout << Darray[i][j];




		}
		cout << endl;
	}



	// close the file
	inputFile.close();


}