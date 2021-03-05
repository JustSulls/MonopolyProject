#include "CSV.h"
CSV::CSV(string fname)
{
	file_name = fname;
}
void CSV::create()
{
	std::fstream myfile;
	myfile.open(file_name); // declare file stream: http://www.cplusplus.com/reference/iostream/ifstream/
	std::string value;
	
	while (myfile.good())
	{
		std::getline(myfile, value, ','); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
		std::cout << std::string(value) << std::endl; // display value removing the first and the last character from it
		holding.push_back(value);
	}

}
