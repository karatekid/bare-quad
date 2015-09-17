#ifndef __CONFIG__H__
#define __CONFIG__H__
#include<stdio.h>
#include<stdint.h>

// Processor dependent implementation of writec, readc, & getmicros
#ifdef ARDUINO
// On Arduino
#include "Arduino.h"
#define UINT16_MAX (65535U)
#define writec(c) Serial.write(c)
#define readc() \
    while(!Serial.available()); \
    Serial.read()
#define getmicros() micros()
#else
#include<iostream>
#include<cstring>
// On computer
#define writec(c) std::cout.put(c)
#define readc() (char) std::cin.get()
// TODO: get micros
#define getmicros() 43
#endif

// User libraries
#include "logstuff.h"

// General constants
#define LOG_START_CHAR '>'
#define LOG_CHECK_CHAR '@'

// Log Level Setup
#define NUM_LOG_LEVELS 5
enum eLogLevel{
    // Don't use this anywhere, specifiically for filtering out
    // everything
    IGNORE_SS,
    // IGNORE_SS must be first entry
    ERROR,
    WARNING,
    DEBUG,
    INFO
};
extern const char *const logLevelNames[NUM_LOG_LEVELS];


// Log Subsystem Setup
#define NUM_SUBSYSTEMS 2
enum eLogSubsystem{
    SS_MAIN,
    SS_PID
};
extern const char *const logSubsystemNames[NUM_SUBSYSTEMS];


//Log Type Setup
#define NUM_DEFAULT_TYPES 4
#define NUM_USER_TYPES 1
#define NUM_TYPES (NUM_DEFAULT_TYPES + NUM_USER_TYPES)
enum eLogType{
    // Default types
    T_TIME,
    T_COUNT,
    T_VERSION,
    T_PRINT,
    // User types
    T_LOGSTUFF
};
extern const char *const logTypeNames[NUM_TYPES];

typedef void(*ParseFunctionPointer)(uint16_t, const char *);

#endif
