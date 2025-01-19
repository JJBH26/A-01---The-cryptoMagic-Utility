#
#   FILE          : Makefile
#   PROJECT       : cryptoMagic - A1
#   PROGRAMMER    : Valentyn, Juan Jose, Lukas, Warren
#   FIRST VERSION : 01/15/2025
#   DESCRIPTION   :
#      TTis is the Makefile which puts all the source codes together
#		and compile it into the executable file
#

# FINAL BINARY Target
./bin/cryptoMagic : ./obj/cryptoMagic.o ./obj/encrypt.o ./obj/decrypt.o
	cc ./obj/cryptoMagic.o ./obj/encrypt.o ./obj/decrypt.o -o ./bin/cryptoMagic

# =======================================================
#                     Dependencies
# =======================================================
./obj/cryptoMagic.o : ./src/cryptoMagic.c ./inc/cryptoMagic.h
	cc -c ./src/cryptoMagic.c -o ./obj/cryptoMagic.o 

./obj/encrypt.o : ./src/encrypt.c ./inc/cryptoMagic.h
	cc -c ./src/encrypt.c -o ./obj/encrypt.o 

./obj/decrypt.o : ./src/decrypt.c ./inc/cryptoMagic.h
	cc -c ./src/decrypt.c -o ./obj/decrypt.o 

# =======================================================
# Other targets
# =======================================================
all : ./bin/cryptoMagic

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o