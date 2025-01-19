/*
*   FILE          : cryptoMagic.c
*   PROJECT       : cryptoMagic - A1
*   PROGRAMMER    : Valentyn, Juan Jose, Lukas, Warren
*   FIRST VERSION : 01/15/2025
*   DESCRIPTION   :
*      This is the file which acts as a main file. The program starts here
*	   and it controls the flow of the program
*/
#include "cryptoMagic.h"


int main(int argc, char* argv[]) {
    if (argc < 2) {
        printfUsage();
        return 1;
    }


    int mode = 1;    // here I created a Flag so If the user doesnt enter 
    // neither encrypt or decrypt its set to encrypting
    char* fileName = NULL;

	if (argc == 2 && strcmp(argv[1], "-encrypt") != 0 && strcmp(argv[1], "-decrypt") != 0) {
        
        fileName = argv[1];
    }

    else if (argc == 3) {
        if (strcmp(argv[1], "-encrypt") == 0)
        {
            mode = 1; //This line doesnt really do anything its just there to clarify
        }
        else if (strcmp(argv[1], "-decrypt") == 0) {
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

/*
 *  Function  : printfUsage()
 *  Summary   : Displays usage instructions for the cryptoMagic utility.
 *  Params    : 
 *     none.
 *  Return    :  
 *     none.
 */
void printfUsage() {
    printf("How to use it: cryptoMagic [-encrypt or -decrypt] <filename>\n");
    printf("  -encrypt   Encrypt the input file (this would also be the default)\n");
    printf("  -decrypt   Decrypt the input file\n");
}


/*
 *  Function  : replaceExtension()
 *  Summary   : Replaces the file extension of the given file name with a new extension.
 *  Params    : 
 *     const char* fileName       - The original file name.
 *     const char* newExtension   - The new extension to append to the file name.
 *     char* outputFileName       - The output file name with the new extension.
 *  Return    :  
 *     none.
 */
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
