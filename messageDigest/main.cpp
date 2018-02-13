/***
Nikolai Ruhe
Algorithms Class
RSA Project 1 Part 2
Project Based on source code by Oliver Gay
Dr. Duan
02/14/2018
**/

#include <iostream>
#include <fstream>
#include "sha256.h"
#include "BigIntegerLibrary.hh"

using std::string;
using std::cout;
using std::endl;

void sign(const char* fileName) {
	//import the message file as a binary stream
	std::ifstream inFile(fileName, std::ios::binary);
	std::string data((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
	if (data.empty()) {
		throw("the file entered is either Null or invalid");
	}
	inFile.close();
	
	//run the sha256 hash algorithm on the message
	string output01 = sha256(data);
	cout << output01 << endl;
	
	//convert the sha256 signature from base16 string to base10 bigUnsigned
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

	//apply signature using modexp
	BigUnsigned signature01 = modexp(sig01, privateKey, n);
	cout << "here is the big signature \n";
	cout << signature01 << endl;

	//save the signature to a file
	std::ofstream signatureOutFile("file.txt.signature");
	signatureOutFile << signature01 << std::endl;
	signatureOutFile.close();

	cout << "------------------------------------------------------------\n";
	cout << "------------------End of sign()-----------------------------\n";
	cout << "------------------------------------------------------------\n";
}

bool verify(const char* inputFileName, const char* signatureFileName) {
	//import the "MOST DEFINITELY AUTHENTIC message file" as a binary stream
	std::ifstream inFile(inputFileName, std::ios::binary);
	std::string data((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
	inFile.close();

	//run the sha256 hashing algorithm on the data
	string output01 = sha256(data);
	cout << output01 << endl;

	//convert the base 16 sha256 output to a base 10 bigUnsigned
	BigUnsigned sig01 = stringToBigUnsigned16(output01);
	cout << "the Sha256(M) after converted to bigUnsigned is: \n";
	cout << sig01 << endl;

	//import the signature file made with the private key
	std::ifstream sigImportFile;
	sigImportFile.open(signatureFileName);

	//get the signature into a mem register
	string signatureStr;
	std::getline(sigImportFile, signatureStr);
	cout << "here is the imported signature after conversion to bigunsigned \n";

	//convert the full signature to a base 10 bigUnsigned
	BigUnsigned Signature = stringToBigUnsigned10(signatureStr);
	cout << Signature << endl;
	sigImportFile.close();

	//import e_n.txt (the public key)
	std::ifstream publicKeyFile;
	publicKeyFile.open("e_n.txt");
	string pubKeyStr, nStr;
	std::getline(publicKeyFile, pubKeyStr);
	std::getline(publicKeyFile, nStr);

	//convert the public key to a base 10 bigUnsigned
	BigUnsigned publicKey = stringToBigUnsigned10(pubKeyStr);
	BigUnsigned n = stringToBigUnsigned10(nStr);
	publicKeyFile.close();

	//see if the message is authentic using modexp to do:
	// (sig(M)^e)%n == sha256(M)
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
	try {
		if (*argv[1] == 's') {
			sign(argv[2]);
		}

		if (*argv[1] == 'v') {
			if (verify(argv[2], argv[3])) {
				cout << "------------------------------\n";
				cout << "the file is authentic \n";
				cout << "------------------------------\n";
			}
			else {
				cout << "------------------------------\n";
				cout << "the file has been modified \n";
				cout << "------------------------------\n";
			}
		}
	}
	catch (string errorMsg) {
		cout << errorMsg << endl;
	}

	return 0;
}
