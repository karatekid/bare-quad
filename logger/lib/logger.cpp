#include<stdio.h>
#include<iostream>

#include "logger.h"

void logPrint(eLogSubsystem ss, eLogLevel lvl, const char *s) {
	printf("%s/%s:\t%s\n", subsystemNames[ss], logLevelNames[lvl], s);
}

void printLogStuff(logStuff s) {
	printf("x:%d,\ty:%f,\tc:%c\n",
			s.x,s.y,s.c);
}

void printRawData(int len, void *d) {
	for(int i = 0; i < sizeof(int); ++i) {
		std::cout.put(((char *)&len)[i]);
	}
	for(int i = 0; i < len; ++i) {
		std::cout.put(((char *)d)[i]);
	}
}

void * getRawData() {
	int len = 0;
	for(int i = 0; i < sizeof(int); ++i) {
		((char *)&len)[i] = (char) std::cin.get();
	}
	void *d = (void *) new char[len];
	for(int i = 0; i < len; ++i) {
		((char *)d)[i] = (char) std::cin.get();
	}
	return d;
}
