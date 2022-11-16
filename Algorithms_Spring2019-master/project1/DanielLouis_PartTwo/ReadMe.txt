Daniel Louis
Algorithms
Project One
Prat Two
                                        Signature of a file
This program will generate encryption keys and a signed encrypted file for a file that the user specifies. The program file needs arguments to run and without them it will through a char exception. 


To generate the keys enter a g after the program call from the consol. Such as “./sign g” entered to the command line.  This will generate two prime numbers that are very large to act as p and q and will also generate n which is p times q, will generate d and e which are  partially prime numbers to each other. These numbers will be saved in corresponding text files each number on one line. The numbers will also allow for the signature of a document to be secure and give the ability to verify if the signature is the same one on both files. 


To sign the file enter the key s after the program call followed by the filename with its extension. Such as “./sign s filename.extension” entered into the command line. The signing process will take the continents of the file and convert it into an integer which will then be placed into the sha256 hash function so the file will be an integer that is exactly 256 bits. This integer should be holly unique to the file that was converted in this way. Then to decrypt the file a simple mathematical function is applied with sha256 integer is raised to the d power and then taken the mod of n from that. This new integer from that function will be the encryption and will not be able to be repeated by anyone without the knowledge of what d is. So, for this to work properly keep d secrete, but, n and e should be public so people can run the verify function on it. 


To verify the file was not tampered with enter the key v after the function call. Such as “./sign v filename.extension.signature” entered into the command line. The filename should be the signature file not the original filename without signature at the end. Both the signature and the original document that needs to be tested for similarity must be present in the folder that the program is running in. To verify the document it will raise the signature to the power of e and take the mod n of that so that the original sha256 integer is output. Then the program will once again create the sha256 of the original file to be tested and if both of these files has the same sh256 integer then the document was not modified. If the two sha256 numbers do not match then the file being tested has been altered in some way since it has been put through the signing process.