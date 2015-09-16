#ifndef __CONFIG__H__
#define __CONFIG__H__
#include<iostream>
#include<cstring>
#include<stdio.h>
#include<stdint.h>
// User libraries
#include "logstuff.h"

// General constants
#define LOG_START_CHAR '>'

// Log Level Setup
#define NUM_LOG_LEVELS 5
typedef enum {
	// Don't use this anywhere, specifiically for filtering out
	// everything
	IGNORE_SS,
	// IGNORE_SS must be first entry
	ERROR,
	WARNING,
	DEBUG,
	INFO
} eLogLevel;
extern const char *const logLevelNames[NUM_LOG_LEVELS];


// Log Subsystem Setup
#define NUM_SUBSYSTEMS 2
typedef enum {
	SS_MAIN,
	SS_PID
} eLogSubsystem;
extern const char *const logSubsystemNames[NUM_SUBSYSTEMS];


//Log Type Setup
#define NUM_DEFAULT_TYPES 4
#define NUM_USER_TYPES 1
#define NUM_TYPES (NUM_DEFAULT_TYPES + NUM_USER_TYPES)
typedef enum {
	// Default types
	T_TIME,
	T_COUNT,
	T_VERSION,
	T_PRINT,
	// User types
	T_LOGSTUFF
} eLogType;
extern const char *const logTypeNames[NUM_TYPES];

typedef void(*ParseFunctionPointer)(uint16_t, const char *);


// Processor dependent implementation of writec, readc, & getmicros
#ifdef ARDUINO
// On Arduino
#define writec(c) Serial.print(c)
#define readc() \
	while(!Serial.available()); \
	Serial.read()
#define getmicros() micros()
#else
// On computer
#define writec(c) std::cout.put(c)
#define readc() (char) std::cin.get()
// TODO: get micros
#define getmicros() 43
#endif



#endif
