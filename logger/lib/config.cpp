/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : config.cpp

 * Purpose :

 * Creation Date : 30-08-2015

 * Created By : Michael Christen

 _._._._._._._._._._._._._._._._._._._._._.*/
#include "config.h"

const char *const logLevelNames[NUM_LOG_LEVELS] = {
	[IGNORE_SS]   = "IGNORE",
	[ERROR]       = "Error",
    [WARNING]     = "Warning",
	[DEBUG]       = "Debug",
	[INFO]        = "Info"
};

const char *const logSubsystemNames[NUM_SUBSYSTEMS] = {
	[SS_MAIN] = "Main",
    [SS_PID]  = "PID"
};

const char *const logTypeNames[NUM_TYPES] = {
	[T_TIME]     = "Time",
	[T_COUNT]    = "Count",
	[T_VERSION]  = "Version",
	[T_PRINT]    = "Print",

	[T_LOGSTUFF] = "Log Stuff"
};
