#pragma once
#ifndef HUD_H
#define HUD_H
#include <string>

class HUD
{
public:
    HUD();
    std::string getLevel();
    std::string getMessage();
    std::string getTime();
    void setLevel(std::string);
    void setTime(std::string);

protected:

};
#endif