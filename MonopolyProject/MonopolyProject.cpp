// MonopolyProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include<iterator> // for iterators
#include<vector> // for vectors
#include "Monopoly.h"
#include "Logger.h"

using namespace std;
int main()
{
 Monopoly m;
 m.play_game();
 system("pause");
 return 0;
}