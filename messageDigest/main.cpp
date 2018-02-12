/***
compile and run (in linux):
g++ sha256.cpp main.cpp -o sha256_example && ./sha256_example
Output:
sha256('grape'): 0f78fcc486f5315418fbf095e71c0675ee07d318e5ac4d150050cd8e57966496
**/

#include <iostream>
#include <fstream>
#include "sha256.h"
#include "BigIntegerLibrary.hh"

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
	std::cout << "\nthe content \n";

	string output01 = sha256(str);
 
	//convert the signature to a bigUnsigned
    cout << "sha256('"<< str << "'):" << output01 << endl;
	BigUnsigned sig01 = stringToBigUnsigned(output01);
	cout << "converted string to bigUnsigned \n";
	//import the private key and n
	std::ifstream privateKeyFile;
	privateKeyFile.open("d_n.txt");
	cout << "opened the d_n.txt file \n";
	string d_str, n_str;
	std::getline(privateKeyFile, d_str);
	std::getline(privateKeyFile, n_str);
	cout << "got the variables \n";
	BigUnsigned privateKey = stringToBigUnsigned(d_str);
	cout << "got the privateKey \n";
	BigUnsigned n = stringToBigUnsigned(n_str);
	cout << "got the n \n";
	//apply signature to output01
	BigUnsigned signature01 = modexp(sig01, privateKey, n);
	cout << "made it to modexp \n";
    return 0;
}
