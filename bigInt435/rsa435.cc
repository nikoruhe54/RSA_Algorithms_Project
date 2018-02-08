// You need to complete this program for a part of your first project.
//
// Niko Ruhe
// RSA Project Part I
// Dr. Duan
// Algorithms Class
// Spring2018
//
// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h> 
#include <fstream>


// `BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"

bool fermat(BigUnsigned maybePrime, BigInteger a1, BigInteger a2) {
	/* use this test to determine if the number is prime */
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
	if (e == 0) {
		return phi;
	}
	return checkE(e, phi % e);
}

BigUnsigned createPrivateKey(BigUnsigned e, BigUnsigned phi) {
	BigUnsigned i = 1, x;
	while (1) {
		x = (e * i - 1) % phi;
		if (x == 0) {
			return i;
			break;
		}
		i++;
	}
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
	  /* while (1) {
		  for (int i = 0; i < 278; i++) {
			  big1 = big1 * 10 + (rand() % 10);
		  }
		  big1 = (big1 * 10) + 7;

		  if (fermat(big1, a1, a2)) {
			  //big1 is prime, move on
			  break;
		  }
		  else {
			  big1 = BigUnsigned(1);
		  }
	  }
	  */
	  BigUnsigned big1 = 37;
      std::cout << "my big1 !!!\n";
      std::cout << big1;
	  std::cout << "\n";
      BigUnsigned big2 = BigUnsigned(1);
	  /* while (1) {
		  for (int i = 0; i < 278; i++) {
			  big2 = big2 * 10 + (rand() % 10);
		  }
		  big2 = (big2 * 10) + 7;
		  if (fermat(big2, a1, a2)) {
			  //big2 is prime, move on
			  break;
		  }
		  else {
			  big2 = BigUnsigned(1);
		  }
	  }
	  */
	  BigUnsigned big2 = 17;
      std::cout << "my big2 !!!\n";
      std::cout << big2;
	  std::cout << "\n";
	  std::cout << "The two numbers are both prime \n";

	  std::ofstream outfile("p_q.txt");
	  outfile << big1 << std::endl;
	  outfile << big2 << std::endl;
	  outfile.close();

	  BigUnsigned a = (big1 - 1) * (big2 - 1);
	  
      std::cout << "n = big1*big2 !!!\n";
      BigUnsigned n = big1*big2;
      std::cout << n;
	  std::cout << std::endl;

	  //BigUnsigned e = 65537; //prime number stored as public key
	  BigUnsigned e = 7;
	  if (checkE(a, e) == 1) {
		  std::cout << "Good Public Key \n";
	  }

	  BigUnsigned d = createPrivateKey(e, a);

	  std::cout << "The private key is: \n";
	  std::cout << d;

	  std::ofstream outfile2("e_n.txt");
	  outfile2 << e << std::endl;
	  outfile2.close();

	  std::ofstream outfile3("d_n.txt");
	  outfile3 << d << std::endl;
	  outfile3.close();

	  /*
      std::cout << "my big3/big2 !!!\n";
      std::cout <<big3/big2;
	  */
      
	} catch(char const* err) {
		std::cout << "The library threw an exception:\n"
			<< err << std::endl;
	}

	return 0;
}


