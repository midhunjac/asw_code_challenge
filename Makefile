Challenge: i2c.o LIS3MDLTR.o main.o
	g++ -Wall i2c.o LIS3MDLTR.o main.o -o Challenge
i2c.o: ./i2c/i2c.c ./i2c/i2c.h
	g++ -c ./i2c/i2c.c
LIS3MDLTR.o: LIS3MDLTR.c LIS3MDLTR.h
	g++ -c LIS3MDLTR.c
main.o: main.c
	g++ -c main.c