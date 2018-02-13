// You need to complete this program for a part of your first project.
//
// Niko Ruhe
// RSA Project 1 Part 1
// Dr. Duan
// Algorithms Class
// Spring2018
// 02/14/2018

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h> 
#include <fstream>


// `BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"

// checks to see if fermat test results in a likely prime number
bool fermat(BigUnsigned maybePrime, BigInteger a1, BigInteger a2) {
	// use this test to determine if the number is prime
	BigUnsigned answer = modexp(a1, maybePrime - 1, maybePrime);
	if (answer == 1) {
		answer = modexp(a2, maybePrime- 1, maybePrime);
		if (answer == 1) {
			return true;
		}
	}
	return false;
}

BigUnsigned checkE(BigUnsigned phi, BigUnsigned e) {
	//make sure the gcd of the public key and the totient is 1
	if (e == 0) {
		return phi;
	}
	else if(phi == 0){
		return 0;
	}
	return checkE(e, phi % e);
}

int main() {
	/* The library throws `const char *' error messages when things go
	 * wrong.  It's a good idea to catch them using a `try' block like this
	 * one.  Your C++ compiler might need a command-line option to compile
	 * code that uses exceptions. */
	try {
		      
      std::cout << "a couple of test cases for 3460:435/535 Algorithms!!!\n";
      BigUnsigned big1 = BigUnsigned(1);
	  BigInteger a1 = 2, a2 = 7;
	  while (1) {
		  //use 278 digits to get a number at least 1024 bits
		  for (int i = 0; i < 278; i++) {
			  big1 = big1 * 10 + (rand() % 10);
		  }
		  //force the number to end in 7 (more likely to hit primes, and reduce search time)
		  big1 = (big1 * 10) + 7;

		  if (fermat(big1, a1, a2)) {
			  //big1 is prime, move on
			  break;
		  }
		  else {
			  big1 = BigUnsigned(1);
		  }
	  }
	  //test case
	  //big1 = 11;
      std::cout << "my big1 !!!\n";
      std::cout << big1;
	  std::cout << "\n";
      BigUnsigned big2 = BigUnsigned(1);
	   while (1) {
		   //use 278 digits to get a number at least 1024 bits
		  for (int i = 0; i < 278; i++) {
			  big2 = big2 * 10 + (rand() % 10);
		  }
		  //force the number to end in 7 (more likely to hit primes, and reduce search time)
		  big2 = (big2 * 10) + 7;
		  if (fermat(big2, a1, a2)) {
			  //big2 is prime, move on
			  break;
		  }
		  else {
			  big2 = BigUnsigned(1);
		  }
	  }
	  //test case
	  //big2 = 5;
      std::cout << "my big2 !!!\n";
      std::cout << big2;
	  std::cout << "\n"; 
	  std::cout << "The two numbers are both prime \n";

	  std::ofstream outfile("p_q.txt");
	  outfile << big1 << std::endl;
	  outfile << big2 << std::endl;
	  outfile.close();

	  BigUnsigned a = (big1 - 1) * (big2 - 1);
	  std::cout << "The totient is a = (big1 - 1) * (big2 - 1) \n";
	  std::cout << a << std::endl;
	  //test case
	  //a = 40;
      std::cout << "n = big1*big2 !!!\n";
      BigUnsigned n = big1*big2;
	  //test case
	  //n = 55;
      std::cout << n;
	  std::cout << std::endl;
	  
	  //I use a common public key of 65537. It is relatively prime to the totient
	  //I check that later to confirm with my checkE function
	  BigUnsigned e = 65537; //prime number stored as public key
	  
	  //test case
	  //e = 7;

	  //check to see if e is relatively prime to a (the totient)
	  if (checkE(a, e) == 1) {
		  std::cout << "Good Public Key \n";
	  }
	  else {
	          std::cout << "Bad Public Key \n";
	  }

	  //calculate the private key by using modinv and extended euclidean of public key and totient
	  BigUnsigned d = modinv(e, a);

	  std::cout << "The private key is: \n";
	  std::cout << d;

	  //output the public key
	  std::ofstream outfile2("e_n.txt");
	  outfile2 << e << std::endl;
	  outfile2 << n << std::endl;
	  outfile2.close();

	  //output the private key
	  std::ofstream outfile3("d_n.txt");
	  outfile3 << d << std::endl;
	  outfile3 << n << std::endl;
	  outfile3.close();
      
	} catch(char const* err) {
		std::cout << "The library threw an exception:\n"
			<< err << std::endl;
	}

	return 0;
}


