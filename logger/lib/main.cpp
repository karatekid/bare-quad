/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : Main.cpp

 * Purpose :

 * Creation Date : 30-08-2015

 * Created By : Michael Christen

 _._._._._._._._._._._._._._._._._._._._._.*/
#include "logger.h"
#include "unistd.h"
#include<stdio.h>
int timePID(int x) {
	sleep(1);
	printf("%d\n",x);
	return x * 2;
}

int main(int argc, char *argv[]) {
	/*
	logPrint(SSMAIN, DEBUG, "Hello World!");
	int x;
	logFunctionTime(SSMAIN, x=timePID(3));
	printf("hey: %d\n", x);
	*/
	if(argc > 1) {
		// Parse
	} else {
		// Generate
		logStuff stuff;
		stuff.x = 4;
		stuff.y = 8.32;
		stuff.c = 'x';
		printLogStuff(stuff);
	}
	return 0;
}
