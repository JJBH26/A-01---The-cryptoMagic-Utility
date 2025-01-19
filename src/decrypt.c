/*
*   FILE          : decrypt.c
*   PROJECT       : cryptoMagic - A1
*   PROGRAMMER    : Valentyn, Juan Jose, Lukas, Warren
*   FIRST VERSION : 01/15/2025
*   DESCRIPTION   :
*      This is the file where the logic and functionality for decryption is implemented
*/

#include "cryptoMagic.h"


/*
 *  Function  : decryptFile()
 *  Summary   : Decrypts the content of the input file and writes the decrypted data to a new file with a ".txt" extension.
 *  Params    : 
 *     const char* inputFileName  - The name of the input file to decrypt.
 *  Return    :  
 *     none.
 */
void decryptFile(const char* inputFileName) {
	char outputFileName[MAX_FILE_PATH_LENGTH];                                   // We are going to create a new file with the extension .txt
	replaceExtension(inputFileName, ".txt", outputFileName);    // dont forget to replace the extension

    FILE* inputFile = fopen(inputFileName, "r");
    if (!inputFile) {
        perror("Error opening input file");
        return;
    }

    FILE* outputFile = fopen(outputFileName, "w");
    if (!outputFile) {
        perror("Error creating output file");
        fclose(inputFile);
        return;
    }


	char hexPair[3];                                            // We are going to store the hex pair in this variable (the hex pair is used to convert the hex to decimal)
	hexPair[2] = '\0';                                          // We are going to add a null terminator to the end of the string     
	int c;
	while ((c = fgetc(inputFile)) != EOF) {
		if (c == 'T' && fgetc(inputFile) == 'T') {
			fputc('\t', outputFile);                            // Translate 'TT' to tab just like we did before
		}
		else if (c == '\n') {
			fputc('\n', outputFile);                            // Leave newlines as is they dont change anything
		}
		else {
			hexPair[0] = c; 								    // We will read the first digit here                           
			hexPair[1] = fgetc(inputFile);                      // We will read the second digit here       

			if (hexPair[1] == EOF) {
				fprintf(stderr, "Error: Incomplete hex pair in input file\n"); // This means this file is either not encrypted, corrupted or was made using a different method
				break;
			}

			int outChar = (int)strtol(hexPair, NULL, SUBTRACT);	   // We are going to convert the hex pair to a decimal value


			// In this whole part we are just disconverting back what we did in the encryption method
			outChar += SUBTRACT;
			if (outChar > MAX) {
				outChar = (outChar - WRAP_OFFSET) + MIN;
			}

			// Check if the character is printable If it is we are going to print it else we are going to ignore it
			if (outChar >= MIN && outChar <= MAX) { // Printable ASCII range
				fputc(outChar, outputFile);
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

	printf("Decryption complete: %s\n", outputFileName);        // Success message
}

