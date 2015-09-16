#include "logger.h"

void logHead(eLogLevel lvl, eLogSubsystem ss, eLogType type, uint32_t len) {
	writec(LOG_START_CHAR);
	writec(lvl);
	writec(ss);
	writec(type);
	// This is where the majority of length checking happens
	if(len > UINT16_MAX) {
		throw "Length of log message too large";
	}
	uint16_t sLen = (uint16_t) len;
	writeRawValue(sLen);
}

void logTimeRaw(eLogLevel lvl, eLogSubsystem ss, const char *id, bool start) {
	uint32_t id_len = strlen(id);
	logHead(lvl, ss, T_TIME, 5 + id_len);
	writec(start ? 'b' : 'e');
	uint32_t time = getmicros();
	writeRawValue(time);
	writeRawData(id_len, id);
}

void logCount(eLogLevel lvl, eLogSubsystem ss, uint32_t count, const char *id) {
	uint32_t id_len = strlen(id);
	logHead(lvl, ss, T_COUNT, 4 + id_len);
	writeRawValue(count);
	writeRawData(id_len, id);
}

void logVersion(eLogSubsystem ss, uint8_t major, uint8_t minor, uint8_t build) {
	logHead(INFO, ss, T_VERSION, 3);
	writec(major);
	writec(minor);
	writec(build);
}

void logPrint(eLogLevel lvl, eLogSubsystem ss, const char *s) {
	uint32_t s_len = strlen(s);
	logHead(lvl, ss, T_PRINT, s_len);
	writeRawData(s_len, s);
}

void logRawData(eLogLevel lvl, eLogSubsystem ss, eLogType type, uint32_t len, const char *data, const char *id) {
	uint32_t len_id = strlen(id);
	logHead(lvl, ss, type, 1 + len_id + len);
	// Length of the raw data
	uint16_t sLen = (uint16_t) len;
	writeRawValue(sLen);
	writeRawData(len, data);
	writeRawData(len_id, id);
}

void writeRawData(uint16_t len, const char *d) {
	for(uint16_t i = 0; i < len; ++i) {
		writec(d[i]);
	}
}
