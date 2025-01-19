/*
*   FILE          : cryptoMagic.h
*   PROJECT       : cryptoMagic - A1
*   PROGRAMMER    : Valentyn, Juan Jose, Lukas, Warren
*   FIRST VERSION : 01/15/2025
*   DESCRIPTION   :
*      This is the header file where we put all the function prototypes, libraries
*      variable declaration, etc
*/
#ifndef CRYPTOMAGIC_H
#define CRYPTOMAGIC_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h> //This is the library that we need to include for the strtol function

#pragma warning(disable: 4996) //This is to disable the warning that we get from the fopen function

#define SUBTRACT 16
#define MIN 32
#define MAX 126
#define WRAP_OFFSET 144
#define MAX_LINE_LENGTH 121
#define MAX_FILE_PATH_LENGTH 256

//Insert Our prototypes here
void printfUsage();
void encryptFile(const char* inputFileName);
void decryptFile(const char* inputFileName);
void replaceExtension(const char* fileName, const char* newExtension, char* outputFileName);

#endif // CRYPTOMAGIC_H