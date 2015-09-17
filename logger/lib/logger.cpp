#include "logger.h"

Logger* Logger::logger = NULL;

Logger::Logger() {
    logOn = true;
    // Set all to be active
    for(int i = 0; i < NUM_SUBSYSTEMS; ++i) {
        logLevels[i] = INFO;
    }
#ifdef ARDUINO
    // Initialize Serial
    // TODO: let this be configurable
    Serial.begin(9600);
#endif
}

Logger* Logger::getLogger() {
    if(!logger) {
        logger = new Logger();
    }
    return logger;
}

void Logger::on() {
    logOn = true;
}

void Logger::off() {
    logOn = false;
}

void Logger::setLevel(eLogLevel lvl, eLogSubsystem ss) {
    logLevels[ss] = lvl;
}

void Logger::logHead(
        eLogLevel lvl,
        eLogSubsystem ss,
        eLogType type,
        uint32_t len) {
    if(filter(lvl, ss)) return;
    writec(LOG_START_CHAR);
    writec(lvl);
    writec(ss);
    writec(type);
    writec(LOG_CHECK_CHAR);
    // This is where the majority of length checking happens
    if(len > UINT16_MAX) {
#ifndef ARDUINO
        throw "Length of log message too large";
#endif
    }
    uint16_t sLen = (uint16_t) len;
    writeRawValue(sLen);
}

void Logger::timeRaw(
        eLogLevel lvl,
        eLogSubsystem ss,
        const char *id,
        bool start) {
    if(filter(lvl, ss)) return;
    uint32_t id_len = strlen(id);
    logHead(lvl, ss, T_TIME, 5 + id_len);
    writec(start ? 'b' : 'e');
    uint32_t time = getmicros();
    writeRawValue(time);
    writeRawData(id_len, id);
}

void Logger::count(
        eLogLevel lvl,
        eLogSubsystem ss,
        uint32_t count,
        const char *id) {
    if(filter(lvl, ss)) return;
    uint32_t id_len = strlen(id);
    logHead(lvl, ss, T_COUNT, 4 + id_len);
    writeRawValue(count);
    writeRawData(id_len, id);
}

void Logger::version(
        eLogSubsystem ss,
        uint8_t major,
        uint8_t minor,
        uint8_t build) {
    if(filter(INFO, ss)) return;
    logHead(INFO, ss, T_VERSION, 3);
    writec(major);
    writec(minor);
    writec(build);
}

void Logger::print(
        eLogLevel lvl,
        eLogSubsystem ss,
        const char *s) {
    if(filter(lvl, ss)) return;
    uint32_t s_len = strlen(s);
    logHead(lvl, ss, T_PRINT, s_len);
    writeRawData(s_len, s);
}

void Logger::rawData(
        eLogLevel lvl,
        eLogSubsystem ss,
        eLogType type,
        uint32_t len,
        const char *data,
        const char *id) {
    if(filter(lvl, ss)) return;
    uint32_t len_id = strlen(id);
    logHead(lvl, ss, type, 1 + len_id + len);
    // Length of the raw data
    uint16_t sLen = (uint16_t) len;
    writeRawValue(sLen);
    writeRawData(len, data);
    writeRawData(len_id, id);
}

void Logger::writeRawData(
        uint16_t len,
        const char *d) {
    for(uint16_t i = 0; i < len; ++i) {
        writec(d[i]);
    }
}

bool Logger::filter(eLogLevel lvl, eLogSubsystem ss) {
    return (!logOn || (lvl > logLevels[ss]));
}
