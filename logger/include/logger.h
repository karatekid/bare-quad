#ifndef __LOGGER__H__
#define __LOGGER__H__
#include "config.h"

// Log function declarations

// Generic logging function used by all others
void logHead(eLogLevel lvl, eLogSubsystem ss, eLogType type, uint8_t len);

void logTimeRaw(eLogLevel lvl, eLogSubsystem ss, const char *id, bool start);
// A macro to wrap around functions
#define logFunctionTime(lvl, ss, FXN) \
	logTimeRaw(lvl, ss, #FXN, true); \
	FXN; \
	logTimeRaw(lvl, ss, #FXN, false)

void logCount(eLogLevel lvl, eLogSubsystem ss, uint32_t count, const char *id);
// A macro to wrap around variables
#define logVariableCount(lvl, ss, VAR) \
	logCount(lvl, ss, VAR, #VAR)

// Version is automatically only info log level
void logVersion(eLogSubsystem ss, uint8_t major, uint8_t minor, uint8_t build);

void logPrint(eLogLevel lvl, eLogSubsystem ss, const char *s);

void logRawData(eLogLevel lvl, eLogSubsystem ss, eLogType type, uint8_t length, const char *data, const char *id);
#define logRawVar(lvl, ss, type, VAR) \
	logRawData(lvl, ss, type, sizeof(VAR), (char *)&(VAR), #VAR)

// Helper that makes writing arbitrary data easy
void writeRawData(uint8_t len, void *d);
// A macro so you don't have to calculate len everytime
#define writeRawValue(v) \
	writeRawData(sizeof(v), (void *)&(v))

//void * getRawData();


#endif
