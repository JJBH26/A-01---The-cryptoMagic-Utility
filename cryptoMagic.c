#include <stdio.h>
#include <string.h>
#include <stdlib.h> //This is the library that we need to include for the strtol function

#pragma warning(disable: 4996) //This is to disable the warning that we get from the fopen function

//Insert Our prototypes here
void printfUsage();
void encryptFile(const char* inputFileName);
void decryptFile(const char* inputFileName);
void replaceExtension(const char* fileName, const char* newExtension, char* outputFileName);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printfUsage();
        return 1;
    }


    int mode = 1;    // here I created a Flag so If the user doesnt enter 
    // neither encrypt or decrypt its set to encrypting
    char* fileName = NULL;

	if (argc == 2 && strcmp(argv[1], "--encrypt") != 0 && strcmp(argv[1], "--decrypt") != 0) {
        
        fileName = argv[1];
    }

    else if (argc == 3) {
        if (strcmp(argv[1], "--encrypt") == 0)
        {
            mode = 1; //This line doesnt really do anything its just there to clarify
        }
        else if (strcmp(argv[1], "--decrypt") == 0) {
            mode = 0; // This just puts it into the decrypting mode
        }
        else {
            printf("Error Invalid entry '%s'", argv[1]);
            printfUsage();
            return 1;
        }
        fileName = argv[2];
    }

    if (fileName == NULL) {
        printf("Error: No file name entered\n");
        printfUsage();
        return 1;
    }

    //Im just putting this for now but you guys have to add the logic
    if (mode == 1) {
		encryptFile(fileName);
    }
    else if (mode == 0) {
		decryptFile(fileName);
    }

	else {
		printf("Error Invalid entry '%s'", argv[1]);
		printfUsage();
		return 1;       //lets show user what he did wrong
	}
    return 0;
}

//This is just a function that I created so the user can see how he has to use the code
//its kind of a help command.
void printfUsage() {
    printf("How to use it: cryptoMagic [--encrypt or --decrypt] <filename>\n");
    printf("  --encrypt   Encrypt the input file (this would also be the default)\n");
    printf("  --decrypt   Decrypt the input file\n");
}


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





// Basically we just have to unfollow the steps we did in our encryption method
void decryptFile(const char* inputFileName) {
	char outputFileName[256];                                   // We are going to create a new file with the extension .txt
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

			int outChar = (int)strtol(hexPair, NULL, 16);	   // We are going to convert the hex pair to a decimal value


			// In this whole part we are just disconverting back what we did in the encryption method
			outChar += 16;
			if (outChar > 127) {
				outChar = (outChar - 144) + 32;
			}

			// Check if the character is printable If it is we are going to print it else we are going to ignore it
			if (outChar >= 32 && outChar <= 126) { // Printable ASCII range
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




//This is a function that I created to replace the extension of the file
void replaceExtension(const char* fileName, const char* newExtension, char* outputFileName) {
    char* dot = (char*)strrchr(fileName, '.');
    if (dot) {
        size_t baseLen = dot - fileName;
        strncpy(outputFileName, fileName, baseLen);
        outputFileName[baseLen] = '\0';
    }
    else {
        strcpy(outputFileName, fileName);
    }
    strcat(outputFileName, newExtension);
}
