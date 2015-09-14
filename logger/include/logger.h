#ifndef __LOGGER__H__
#define __LOGGER__H__
#include "config.h"

// Log Level Setup
#define NUM_LOG_LEVELS 4
typedef enum {
	ERROR,
	WARNING,
	DEBUG,
	INFO
} eLogLevel;

static const char* logLevelNames[NUM_LOG_LEVELS] = {
	[ERROR] = "Error",
    [WARNING] = "Warning",
	[DEBUG] = "Debug",
	[INFO] = "Info"
};

static const char logLevelCodes[NUM_LOG_LEVELS] = {
	[ERROR] = 'E',
	[WARNING] = 'W',
	[DEBUG] = 'D',
	[INFO] = 'I'
};

// Log function declarations
void logPrint(eLogSubsystem ss, eLogLevel lvl, const char *s);
#define logFunctionTime(ss, FXN) \
	logPrint(ss, INFO, "Start: " #FXN); \
	FXN; \
	logPrint(ss, INFO, "End: " #FXN);
#define logCount(ss, VAR) \
	logPrint(ss, INFO, #VAR "= ");
#define logRawData (ss, VAR)

struct logStuff {
	int x;
	double y;
	char c;
};

void printLogStuff(logStuff s);

void printRawData(int len, void *d);

void * getRawData(char *raw);


#endif
