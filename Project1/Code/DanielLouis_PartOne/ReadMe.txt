Daniel Louis
Project One
Part One 
                                                Generating keys


This program will generate the keys needed for encryption of a signed document to prove that is came from a specific person and has not been tampered with. This starts this process by generating two random large prime numbers (both being 155 bits or greater) and naming them p and q.These prime numbers are generated at random then checked for primality with Fermat’s test. Then once it fidds p and q it will start to generate the actual numbers from there function to sign the document. These numbers are d, e, and n. To generate n it will just multiply p and q together and will be half of both private and public keys. Then it will find e which is relatively prime to (p-1)(q-1) and is found by taking the gcd of both e and (p-1)(q-1). Once e has been found the function will find d by taking the multiple inverse of e by doing euclidean algebra to find their gcd and set that to be the private number d. Finding these numbers may all take a long time for the machine to process since the prime numbers in question are being found by taking extremely large numbers. 


After this program finds these integer it outputs them into corresponding text file holding the numbers on one line each with no white space. Thus far this is all the program does and will only generate the integers necessary for the program to sign the document but will not sign it as of right now.