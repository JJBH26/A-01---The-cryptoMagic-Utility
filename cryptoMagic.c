#include <stdio.h>
#include <string.h>

//Insert Our prototypes here
void printfUsage();

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
        //here is where teh encrypting code goes
		printf("Encrypting %s\n", fileName);
    }
    else if (mode == 0) {
        //here is where the decrypting code goes
		printf("Decrypting %s\n", fileName);
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
