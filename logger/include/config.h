#ifndef __CONFIG__H__
#define __CONFIG__H__

#define NUM_SUBSYSTEMS 2
typedef enum {
	SSMAIN,
	SSPID
} eLogSubsystem;

static const char* subsystemNames [NUM_SUBSYSTEMS] = {
	[SSMAIN] = "Main",
    [SSPID] = "PID"
};


#endif
