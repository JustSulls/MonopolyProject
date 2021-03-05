#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream> 
#include <stdio.h>
using namespace std;
class CSV
{
public:
	CSV(string fname="C:/Users/jsul2/Documents/monopoly cards.csv");
	void create();
	void create_data();
	std::vector<std::string> holding;

	string file_name;
};

