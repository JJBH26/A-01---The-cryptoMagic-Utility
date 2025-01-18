#
#   FILE          : Makefile
#   PROJECT       : cryptoMagic - A1
#   PROGRAMMER    : Valentyn, Juan Jose, Lukas, Warren
#   FIRST VERSION : 01/15/2025
#   DESCRIPTION   :
#      TTis is the Makefile which puts all the source codes together
#		and compile it into the executable file
#
# Compiler and flags
CC = gcc
CFLAGS = -Wall -Iinc  # Include the inc directory for header files

# Directories
OBJDIR = obj
SRCDIR = src
INCDIR = inc
BINDIR = bin

# Object files
OBJ = $(OBJDIR)/cryptoMagic.o $(OBJDIR)/decrypt.o $(OBJDIR)/encrypt.o
EXEC = $(BINDIR)/cryptoMagic

# Default target
all: $(EXEC)

# Link object files into the executable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Compile cryptoMagic.c (main file)
$(OBJDIR)/cryptoMagic.o: $(SRCDIR)/cryptoMagic.c $(INCDIR)/cryptoMagic.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/cryptoMagic.c -o $(OBJDIR)/cryptoMagic.o

# Compile decrypt.c
$(OBJDIR)/decrypt.o: $(SRCDIR)/decrypt.c $(INCDIR)/cryptoMagic.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/decrypt.c -o $(OBJDIR)/decrypt.o

# Compile encrypt.c
$(OBJDIR)/encrypt.o: $(SRCDIR)/encrypt.c $(INCDIR)/cryptoMagic.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/encrypt.c -o $(OBJDIR)/encrypt.o

# Clean rule
clean:
	rm -f $(OBJ) $(EXEC)
