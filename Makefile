#
#   FILE          : Makefile
#   PROJECT       : cryptoMagic - A1
#   PROGRAMMER    : Valentyn, Juan Jose, Lukas, Warren
#   FIRST VERSION : 01/15/2025
#   DESCRIPTION   :
#      TTis is the Makefile which puts all the source codes together
#		and compile it into the executable file
#
CC = gcc
CFLAGS = -Wall
OBJ = cryptoMagic.o decrypt.o encrypt.o
EXEC = cryptoMagic

# Default target
all: $(EXEC)

# Link object files into the executable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Compile cryptoMagic.c (main file)
cryptoMagic.o: cryptoMagic.c cryptoMagic.h
	$(CC) $(CFLAGS) -c cryptoMagic.c

# Compile decrypt.c
decrypt.o: decrypt.c cryptoMagic.h
	$(CC) $(CFLAGS) -c decrypt.c

# Compile encrypt.c
encrypt.o: encrypt.c cryptoMagic.h
	$(CC) $(CFLAGS) -c encrypt.c

# Clean rule
clean:
	rm -f $(OBJ) $(EXEC)
