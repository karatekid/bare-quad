#ifndef __PARSER__H__
#define __PARSER__H__
#include "config.h"
// Parses one log object
void parseLog(); 

// Parsing functions
typedef void(*ParseFunctionPointer)(uint16_t, const char *);
extern const ParseFunctionPointer parseFunctions[NUM_TYPES];
// Default functions
void parseTimeLog(uint16_t len, const char *data);
void parseCountLog(uint16_t len, const char *data);
void parseVersionLog(uint16_t len, const char *data);
void parsePrintLog(uint16_t len, const char *data);
// User functions
void parseLogStuff(uint16_t len, const char *data);

// Enum string lookups
extern const char *const logLevelNames[NUM_LOG_LEVELS];
extern const char *const logSubsystemNames[NUM_SUBSYSTEMS];
extern const char *const logTypeNames[NUM_TYPES];

#define cpyRawValue(d, o) \
    memcpy((void *)&(d), (void *)(o), sizeof(d))

#endif
