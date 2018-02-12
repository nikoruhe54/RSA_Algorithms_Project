/***
compile and run (in linux):
g++ sha256.cpp main.cpp -o sha256_example && ./sha256_example
Output:
sha256('grape'): 0f78fcc486f5315418fbf095e71c0675ee07d318e5ac4d150050cd8e57966496
**/

#include <iostream>
#include <fstream>
#include "sha256.h"

using std::string;
using std::cout;
using std::endl;
 
int main(int argc, char *argv[])
{
	std::string filename = "test.txt"; //test.jpg test.png etc.
	std::ifstream myfile(filename.c_str(), std::ios::binary);
	std::streampos begin, end;
	begin = myfile.tellg();
	myfile.seekg(0, std::ios::end);
	end = myfile.tellg();
	std::streampos size = end - begin; //size of the file in bytes   
	myfile.seekg(0, std::ios::beg);

	char * memblock = new char[size];
	myfile.read(memblock, size); //read the entire file
	memblock[size] = '\0'; //add a terminator
	myfile.close();

	//check what's in the block
	string str(memblock);
	std::cout << str;
	std::cout << "\nthe content ";

    string input = "grapeJuice    sha256('grapeJuice'):0f78fcc486f5315418fbf095e71c0675ee07d318e5ac4d150050cd8e57966496";
    string output1 = sha256(input);
 
    cout << "sha256('"<< input << "'):" << output1 << endl;
    return 0;
}
