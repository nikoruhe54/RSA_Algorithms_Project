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

void testImage() {
	std::ifstream fin("test.txt", std::ios::binary);
	std::string data((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
	fin.close();
	string output01 = sha256(data);
	cout << output01 << endl;

	BigUnsigned sig01 = stringToBigUnsigned16(output01);
	cout << "convert to BigUnsigned: \n";
	cout << sig01 << endl;

	//import the private key and n
	std::ifstream privateKeyFile;
	privateKeyFile.open("d_n.txt");

	//format d and n in mem registers to generate a signature
	string d_str, n_str;
	std::getline(privateKeyFile, d_str);
	std::getline(privateKeyFile, n_str);
	BigUnsigned privateKey = stringToBigUnsigned10(d_str);
	BigUnsigned n = stringToBigUnsigned10(n_str);

	//apply signature to output01
	BigUnsigned signature01 = modexp(sig01, privateKey, n);
	cout << "here is the big signature \n";
	cout << signature01 << endl;

	//save the signature to a file
	std::ofstream signatureOutFile("file.txt.signature");
	signatureOutFile << signature01 << std::endl;
	signatureOutFile.close();

	cout << "------------------------------------------------------------\n";
	cout << "-------------------End of s()-------------------------------\n";
	cout << "------------------------------------------------------------\n";
}

bool testImageV() {
	std::ifstream fin("test.txt", std::ios::binary);
	std::string data((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
	fin.close();
	string output01 = sha256(data);
	cout << output01 << endl;

	//convert the SHA256 to a bigUnsigned
	BigUnsigned sig01 = stringToBigUnsigned16(output01);
	cout << "the Sha256(M) after converted to bigUnsigned is: \n";
	cout << sig01 << endl;

	//import the signature file made with the private key
	std::ifstream sigImportFile;
	sigImportFile.open("file.txt.signature");

	//get the signature into a mem register
	string signatureStr;
	std::getline(sigImportFile, signatureStr);
	cout << "here is the imported signature string: \n";
	cout << signatureStr << endl;
	cout << "here is the imported signature after conversion to bigunsigned \n";
	BigUnsigned Signature = stringToBigUnsigned10(signatureStr);
	cout << Signature << endl;
	sigImportFile.close();

	//import e_n.txt
	std::ifstream publicKeyFile;
	publicKeyFile.open("e_n.txt");
	string pubKeyStr, nStr;
	std::getline(publicKeyFile, pubKeyStr);
	std::getline(publicKeyFile, nStr);
	cout << "here is the privateKey string: \n";
	cout << pubKeyStr << endl;
	cout << "here is the nStr string: \n";
	cout << nStr << endl;
	BigUnsigned publicKey = stringToBigUnsigned10(pubKeyStr);
	BigUnsigned n = stringToBigUnsigned10(nStr);
	cout << "here is the privateKey after conversion to bigunsigned: \n";
	cout << publicKey << endl;
	cout << "here is the n after converstion to bigunsigned: \n";
	cout << n << endl;
	publicKeyFile.close();

	BigUnsigned decrypt = modexp(Signature, publicKey, n);
	cout << "here's the decrypt: " << endl;
	cout << decrypt << endl;

	if (decrypt == sig01) {
		return true;
	}
	else {
		return false;
	}
}

void s() {
	std::string filename = "test03.jpg";
	//std::string filename = "test.txt"; //test.jpg test.png etc.
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
	cout << "sha256('" << str << "'):" << output01 << endl;
	BigUnsigned sig01 = stringToBigUnsigned16(output01);
	cout << "convert to BigUnsigned: \n";
	cout << sig01 << endl;

	//import the private key and n
	std::ifstream privateKeyFile;
	privateKeyFile.open("d_n.txt");

	//format d and n in mem registers to generate a signature
	string d_str, n_str;
	std::getline(privateKeyFile, d_str);
	std::getline(privateKeyFile, n_str);
	BigUnsigned privateKey = stringToBigUnsigned10(d_str);
	BigUnsigned n = stringToBigUnsigned10(n_str);

	//apply signature to output01
	BigUnsigned signature01 = modexp(sig01, privateKey, n);
	cout << "here is the big signature \n";
	cout << signature01 << endl;

	//save the signature to a file
	std::ofstream signatureOutFile("file.txt.signature");
	signatureOutFile << signature01 << std::endl;
	signatureOutFile.close();

	cout << "------------------------------------------------------------\n";
	cout << "-------------------End of s()-------------------------------\n";
	cout << "------------------------------------------------------------\n";
}

bool v() {
	std::string filename = "test.png";
	//std::string filename = "test.txt"; //test.jpg test.png etc.
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
	cout << "sha256('" << str << "'):" << output01 << endl;

	//convert the SHA256 to a bigUnsigned
	BigUnsigned sig01 = stringToBigUnsigned16(output01);
	cout << "the Sha256(M) after converted to bigUnsigned is: \n";
	cout << sig01 << endl;

	//import the signature file made with the private key
	std::ifstream sigImportFile;
	sigImportFile.open("file.txt.signature");

	//get the signature into a mem register
	string signatureStr;
	std::getline(sigImportFile, signatureStr);
	cout << "here is the imported signature string: \n";
	cout << signatureStr << endl;
	cout << "here is the imported signature after conversion to bigunsigned \n";
	BigUnsigned Signature = stringToBigUnsigned10(signatureStr);
	cout << Signature << endl;
	sigImportFile.close();

	//import e_n.txt
	std::ifstream publicKeyFile;
	publicKeyFile.open("e_n.txt");
	string pubKeyStr, nStr;
	std::getline(publicKeyFile, pubKeyStr);
	std::getline(publicKeyFile, nStr);
	cout << "here is the privateKey string: \n";
	cout << pubKeyStr << endl;
	cout << "here is the nStr string: \n";
	cout << nStr << endl;
	BigUnsigned publicKey = stringToBigUnsigned10(pubKeyStr);
	BigUnsigned n = stringToBigUnsigned10(nStr);
	cout << "here is the privateKey after conversion to bigunsigned: \n";
	cout << publicKey << endl;
	cout << "here is the n after converstion to bigunsigned: \n";
	cout << n << endl;
	publicKeyFile.close();

	BigUnsigned decrypt = modexp(Signature, publicKey, n);
	cout << "here's the decrypt: " << endl;
	cout << decrypt << endl;

	if (decrypt == sig01) {
		return true;
	}
	else {
		return false;
	}
}

int main(int argc, char *argv[])
{
	/*
	s();
	if (v()) {
		cout << "------------------------------\n";
		cout << "the file has been unmodified \n";
		cout << "------------------------------\n";
	}
	else {
		cout << "------------------------------\n";
		cout << "the file has been modified \n";
		cout << "------------------------------\n";
	}
	*/
	testImage();
	if (testImageV()) {
		cout << "------------------------------\n";
		cout << "the file has been unmodified \n";
		cout << "------------------------------\n";
	}
	else {
		cout << "------------------------------\n";
		cout << "the file has been modified \n";
		cout << "------------------------------\n";
	}
	return 0;
}
