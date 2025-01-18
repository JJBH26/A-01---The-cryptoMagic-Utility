/*
*   FILE          : encrypt.c
*   PROJECT       : cryptoMagic - A1
*   PROGRAMMER    : Valentyn, Juan Jose, Lukas, Warren
*   FIRST VERSION : 01/15/2025
*   DESCRIPTION   :
*      This is the file where the logic and functionality for ecryption is implemented
*/
#include "cryptoMagic.h"


/*
 *  Function  : encryptFile()
 *  Summary   : Encrypts the content of the input file and writes the encrypted data to a new file with a ".crp" extension.
 *  Params    : 
 *     const char* inputFileName  - The name of the input file to encrypt.
 *  Return    :  
 *     none.
 */
void encryptFile(const char* inputFileName) {
    char outputFileName[256];
	replaceExtension(inputFileName, ".crp", outputFileName);        // the first step is to replace the extension of the file. CRP

	FILE* inputFile = fopen(inputFileName, "r");                    // open the file in read mode
    if (!inputFile) {
        perror("Error opening input file");                         // just checking we gotta make sure
        return;
    }

	FILE* outputFile = fopen(outputFileName, "w");				    // open the file in write mode we will write the encrypted data here
    if (!outputFile) {
		perror("Error creating output file");					   // just checking we gotta make sure AGAIN

		if (fclose(inputFile) != 0) {                              // if we cant close the file we will show an error
			perror("Error closing input file");
			exit(1);
		}
        return;
    }

	char line[121];                                                 // 120 characters + null terminator this is were the fun is going to happen
	while (fgets(line, sizeof(line), inputFile)) {                  // STEP 1: we are going to read the file line by line   
		for (int i = 0; line[i] != '\0'; i++) {					    // STEP 2: we are going to read the line character by character so we can encrypt each character
			char c = line[i];									    // STEP 3: we are going to store the character in a variable I prefer it this way
			if (c == '\t') {										// STEP 4: if the character is a tab we are going to write TT as specified
                fprintf(outputFile, "TT");
            }
			else if (c == '\n') {									// STEP 5: if the character is a new line we are going to write a new line in our encryption method, we can do something else if we want
                fputc('\n', outputFile);
            }
			else {													// STEP 6: if the character is not a tab or a new line we are going to encrypt it (OFC)
				int outChar = c - 16;                               // STEP 7: we are going to subtract 16 from the character in the ASCII value   
				if (outChar < 32) {								    // STEP 8: if the character is less than 32 we are going to add 144 to it so we have a standard ASCII encryption
					outChar = (outChar - 32) + 144;                 // We are making sure that the character is in the printable range so we dont have headaches later
                }
				fprintf(outputFile, "%02X", outChar);			    // STEP 9: we are going to print the character in hex format
            }
        }
    }

	if (fclose(inputFile) != 0) {                                   
		perror("Error closing input file");
		return;
	}
    
	if (fclose(outputFile) != 0) {
		perror("Error closing output file");
		return;
	}
	printf("Encryption complete: %s\n", outputFileName); 		     // STEP 10: Success message
}