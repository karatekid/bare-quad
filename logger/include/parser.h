#ifndef __PARSER__H__
#define __PARSER__H__
#include "config.h"
// Parses one log object
void parseLog(); 
// Return true if don't want it (filter it)
bool filterLog(eLogLevel lvl, eLogSubsystem ss);

// Parsing functions
extern const ParseFunctionPointer parseFunctions[NUM_TYPES];
// Default functions
void parseTimeLog(uint8_t len, const char *data);
void parseCountLog(uint8_t len, const char *data);
void parseVersionLog(uint8_t len, const char *data);
void parsePrintLog(uint8_t len, const char *data);
// User functions
void parseLogStuff(uint8_t len, const char *data);

#define cpyRawValue(d, o) \
	memcpy((void *)&(d), (void *)(o), sizeof(d))

#endif
