/*
Daniel Louis
Algorithms
Project 1
Part Two
*/

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h> 
#include <ctime>
#include <fstream>
#include <string>
#include <sstream> 

// 'BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"
#include "sha256.h"

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


/*
function sign
*this will sign a document that is the filename and will generate a new document that is the signature
*precondition: this takes an argument of the filename to be signed as a string and needs to be the entire filename.extension
*postcondition: this will return nothing but will generate a document that will be filename.extension.signature
*/
void sign(std::string filename);

/*
function verify
*this will check if a file is the same as the signature that correlates with it
*precondition: has an argument of the filename.extension.signature as a string 
*postcondtion: will return nothing but will output a statement to standard output
** if the file was changed it will output saying they do not match
** if the file is the same it will say they matched 
*/
void verify(std::string sig);

/*
function main
*will take an argument after the call in order for the program to run
*so after the selection of the program call type in one of the following keys
** g : will generate new keys and will overwrite the old ones (may take a while)
** s : will call the sign function to sign a document
***this s should be followed by the filename.extension (needs the full file name)
** v : will call verify to verify if the document has been changed or not
***this v should be followed by the signature file which will be filename.extension.signature
*/
int main(int argc, char** argv)
{
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

  

   std::string ch = argv[1];

   if(ch == "g")
   {
      getKeys();
   }
   else if(ch == "v")
   {
      verify(argv[2]);
   }
   else if(ch == "s")
   {
      sign(argv[2]);
   }
   else
   {
      std::cout << "That was not an option; Please enter s for signature, v for verify, g to generate new keys \n";
      abort();
   }
}
void getKeys()
{
   BigInteger p = generateBigPrimeNum();
   BigInteger q = generateBigPrimeNum();

   std::ofstream primesOut;
   primesOut.open("p_q.txt");
   primesOut << p << '\n' << q;
   primesOut.close();

   BigInteger n = p * q;
   BigInteger phi = (p-1)*(q-1);

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

   //change a later!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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

void sign(std::string filename)
{
   std::ifstream fileIn;
   fileIn.open(filename);
   if(!fileIn)
   {
      std::cout << "file can not open \n";
      abort();
   }
   std::stringstream stream;
   stream << fileIn.rdbuf();
   std::string fileContent = stream.str();
   std::string sha = sha256(fileContent);
   fileIn.close();

   BigUnsigned sha16 = BigUnsignedInABase(sha, 16);

   std::ofstream out;
   out.open(filename + ".signature");

   fileIn.open("d_n.txt");
   std::string d , n;
   getline(fileIn, d, '\n');
   getline(fileIn, n);
   fileIn.close();
   BigInteger dBig = stringToBigInteger(d);
   BigInteger nBig = stringToBigInteger(n);
   //m^d %n = dycription = modular(file, d, n)
   BigInteger fileDec = modular(sha16, dBig, nBig);

   out << fileDec;

   out.close();
}

void verify(std::string sig)
{
   std::ifstream in;
   in.open(sig);
   if(!in)
   {
      std::cout << "file could not open\n";
      abort();
   }
   std::stringstream stream;
   stream << in.rdbuf();
   std::string signature = stream.str();
   in.close();

   std::ifstream fileIn;
   fileIn.open("e_n.txt");
   std::string e , n;
   getline(fileIn, e, '\n');
   getline(fileIn, n);
   fileIn.close();
   BigInteger eBig = stringToBigInteger(e);
   BigInteger nBig = stringToBigInteger(n);
   BigInteger signatureBig = stringToBigInteger(signature);

   //signature^e %n = none signature file = modulare(signature, e, n)
   BigInteger non = modular(signatureBig, eBig, nBig);

   sig.erase(sig.find(".signature"), sig.size());
   in.open(sig);

   std::stringstream fileContent;
   fileContent <<  in.rdbuf();
   std::string file = fileContent.str();
   std::string sha = sha256(file);

   BigUnsigned sha16 = BigUnsignedInABase(sha, 16);
   in.close();

   if(non == sha16)
   {
      std::cout << "The file matches the signature \n";
   }
   else
   {
      std::cout << "The file does not match the signature \n";
   }
}