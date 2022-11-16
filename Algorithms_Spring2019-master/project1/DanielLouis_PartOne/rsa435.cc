/*
Daniel Louis
Algorithms
Project 1
Part one
*/

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h> 
#include <ctime>
#include <fstream>
#include <string>


// 'BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"

/*
function FermatsPrimality
*this will check if a number is prime or not
*preconditions: takes a BigInteger argument that is the number that is to be checked if it is prime
*postcondition: will return true if it is a potential prime number and false otherwise
*/
bool FermatsPrimality(BigInteger n);

/*
function modular
*this function will find the multiplication and mod break down
*/
BigInteger modular(BigInteger x, BigInteger y, BigInteger m);

/*
function generateBigPrimeNum
*this will generate a four hundred digit prime number (it will take some time potentially) 
*precondition: This has no arguments
*postcondition: this will return a BigInteger that is a randomly generated prime number  
*/
BigInteger generateBigPrimeNum();

/*
function getKeys
*this function will generate the keys for encryption 
*precondition: takes no arguments
*postcontion: does not return anything 
**this will create 3 txt files that hold the different keys 
***first is p_q.txt which will have p and q on the first two lines
***second will be d_n.txt which will store d and n on first two lines
***finally will be e_n.txt which will store d and n on first two lines
**the n in both d_n.txt and e_n.txt will be the same number 
*/
void getKeys();

/*
function EuclidAlgorithm
*this will take two numbers and find their greatest common divisor (gcd) 
*precondition: this takes two BigIntegers that will find the gcd of the two
*postcondition: this will return a Biginteger that is the gcd of the two input
*/
BigInteger EuclidAlgorithm(BigInteger x, BigInteger y);

/*
function multiInverse
*this will return the inverse of e which will be d in the formula ((m^d)%n)^e%n
*precondition: this will take four arguments of all BigInteger for the gcd(a,b) = ax + by
*postcondition: will return d for encryption 
*/
BigInteger multiInverse(BigInteger a, BigInteger b, BigInteger &x, BigInteger &y);


int main(){
	/* The library throws 'const char *' error messages when things go
	 * wrong.  It's a good idea to catch them using a 'try' block like this
	 * one.  Your C++ compiler might need a command-line option to compile
	 * code that uses exceptions. */
	try {
		      
      /*std::cout << "a couple of test cases for 3460:435/535 Algorithms!!!\n";
      BigUnsigned big1 = BigUnsigned(1);
      for (int i=0;i<400;i++) {
         big1 = big1*10 +rand();
      }
      std::cout << "my big1 !!!\n";
      std::cout << big1;
      BigUnsigned big2 = BigUnsigned(1);
      for (int i=0;i<400;i++) {
         big2 = big2*10 +rand();
      }
      std::cout << "my big2 !!!\n";
      std::cout << big2;
      std::cout << "my big3 = big1*big2 !!!\n";
      BigUnsigned big3 = big1*big2;
      std::cout <<big3;
      std::cout << "my big3/big2 !!!\n";
      std::cout <<big3/big2;*/
      
	} catch(char const* err) {
		std::cout << "The library threw an exception:\n"
			<< err << std::endl;
	}
   
   getKeys();

	return 0;
}

void getKeys()
{
   //generates the two large prime numbers
   BigInteger p = generateBigPrimeNum();
   BigInteger q = generateBigPrimeNum();

   std::ofstream primesOut;
   primesOut.open("p_q.txt");
   primesOut << p << '\n' << q;
   primesOut.close();

   BigInteger n = p * q;
   BigInteger phi = (p-1)*(q-1);

   //e will start here and if it works than that will be the e 
   BigInteger e = 134542427;
   while(EuclidAlgorithm(phi, e) != 1)
   {
      e+=2;
   }
   primesOut.open("e_n.txt");
   primesOut << e << '\n' << n;
   primesOut.close();

   BigInteger x = 1, y = 1;
   BigInteger d = multiInverse(phi,e,x,y);

   primesOut.open("d_n.txt");
   primesOut << d << '\n' << n;
   primesOut.close();

   //if the e and d are wrong then p and q are wrong and we need to exit the program
   if((e*d) % ((p-1)*(q-1)) != 1)
      {abort();}


}

BigInteger EuclidAlgorithm(BigInteger x, BigInteger y)
{
   if(y == 0)
      {return x;}
   else
      {return EuclidAlgorithm(y, x % y);}
}

BigInteger generateBigPrimeNum()
{
   srand(time(NULL));
   BigInteger  big(1);
   while(!(FermatsPrimality(big)))
   {
      big = 1;
      for (int i=0;i<400;i++) 
      {
         big = big*10 +rand();
      }
      //have fermat's test run twice on a potential number to double check it
      if(!(FermatsPrimality(big)))
      {big = 1;}
   }
   return big;
}

bool FermatsPrimality(BigInteger n)
{
   //catch what is not prime but would work for the test
   if(n <= 1 || n == 4)
   {
      return false;
   }

   //a can be any number les than n and n-15 is less than n (this is not random and will alwyas be the same)
   BigInteger a = n - 15;

   if(modular(a, n-1 , n) == 1)
      {return true;}
   else
      {return false;}
}

BigInteger modular(BigInteger x, BigInteger y, BigInteger m)
{
   if(y == 0)
      {return 1;}
   else
   {
      BigInteger z = modular(x,y/2,m);
      if(y % 2 == 0)
         {return ((z*z) % m);}
      else
         {return ((x*z*z) % m);}
   }
}
BigInteger multiInverse(BigInteger a, BigInteger b, BigInteger &x, BigInteger &y)
{
   if(b == 0) {
       x = 1;
       y = 0;
       return a;
    }
    BigInteger p, q, gcd = multiInverse(b, a%b, p, q);
    x = q;
    y = p - (a / b) * q;
    return y;
}