#include<stdio.h>

#include "logger.h"

void logPrint(eLogSubsystem ss, eLogLevel lvl, const char *s) {
	printf("%s/%s:\t%s\n", subsystemNames[ss], logLevelNames[lvl], s);
}
