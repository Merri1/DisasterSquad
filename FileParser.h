#pragma once
#ifndef FILEPARSER_H
#define FILEPARSER_H
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

class FileParser
{
public:
	FileParser();
	void parseTextFile(int (&levelArray)[36][64], int level);
protected:

};
#endif
