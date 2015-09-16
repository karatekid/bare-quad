/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : parser.cpp
 * Purpose : parse output from logger
 * Creation Date : 15-09-2015
 * Created By : Michael Christen
 _._._._._._._._._._._._._._._._._._._._._.*/

#include "parser.h"

void parseLog() {
	// Wait for start character
	while(readc() != LOG_START_CHAR);
	eLogLevel lvl = (eLogLevel) readc();
	eLogSubsystem ss = (eLogSubsystem) readc();
	eLogType type = (eLogType) readc();
	uint8_t len = (uint8_t) readc();
	char *payload = new char[len];
	for(uint8_t i = 0; i < len; ++i) {
		payload[i] = readc();
	}
	if(!filterLog(lvl, ss)) {
		printf("%s:%s(%s)\t",
				logLevelNames[lvl],
				logSubsystemNames[ss],
				logTypeNames[type]);
		parseFunctions[type](len, payload);
	}
	delete[] payload;
}

bool filterLog(eLogLevel lvl, eLogSubsystem ss) {
	return false;
}

const ParseFunctionPointer parseFunctions[NUM_TYPES] = {
	[T_TIME] = parseTimeLog,
	[T_COUNT] = parseCountLog,
	[T_VERSION] = parseVersionLog,
	[T_PRINT] = parsePrintLog,

	[T_LOGSTUFF] = parseLogStuff
};

void parseTimeLog(uint8_t len, const char *data) {
	bool start = (data[0] == 'b');
	uint32_t time;
	cpyRawValue(time, data + 1);
	char id[len - 5];
	strcpy(id, data + 5);
}

void parseCountLog(uint8_t len, const char *data) {
	uint32_t count;
	cpyRawValue(count, data);
	char id[len - 4];
	strcpy(id, data + 4);
}

void parseVersionLog(uint8_t len, const char *data) {
	uint8_t major, minor, build;
	major = data[0];
	minor = data[1];
	build = data[2];
}

void parsePrintLog(uint8_t len, const char *data) {
	char s[len];
	strcpy(s, data);
}

void parseLogStuff(uint8_t len, const char *data) {
	uint8_t data_len = data[0];
	logStuff stuff;
	cpyRawValue(stuff, data + 1);
	char id[len - data_len - 1];
	strcpy(id, data + 1 + data_len);
	printf("x:%d,y:%f,z:%c\n",stuff.x,stuff.y,stuff.c);
}
