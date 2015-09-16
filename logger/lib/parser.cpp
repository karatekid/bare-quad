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
    uint16_t len  = (uint16_t) readc();
    len += ((uint16_t) readc()) << 8;
    char *payload = new char[len];
    for(uint16_t i = 0; i < len; ++i) {
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

void parseTimeLog(uint16_t len, const char *data) {
    bool start = (data[0] == 'b');
    uint32_t time;
    cpyRawValue(time, data + 1);
    char id[len - 5];
    strcpy(id, data + 5);
    printf("%s ", id);
    if(start) {
        printf("started");
    } else {
        printf("ended");
    }
    printf(" @ %d seconds\n", time);
}

void parseCountLog(uint16_t len, const char *data) {
    uint32_t count;
    cpyRawValue(count, data);
    char id[len - 4];
    strcpy(id, data + 4);
    printf("%s = %d\n", id, count);
}

void parseVersionLog(uint16_t len, const char *data) {
    uint8_t major, minor, build;
    major = data[0];
    minor = data[1];
    build = data[2];
    printf("%d.%d.%d\n", major, minor, build);
}

void parsePrintLog(uint16_t len, const char *data) {
    char s[len];
    strcpy(s, data);
    printf("%s\n",s);
}

void parseLogStuff(uint16_t len, const char *data) {
    uint16_t data_len;
    cpyRawValue(data_len, data);
    logStuff stuff;
    cpyRawValue(stuff, data + 2);
    char id[len - data_len - 2];
    strcpy(id, data + 2 + data_len);
    printf("x:%d,y:%f,z:%c\n",stuff.x,stuff.y,stuff.c);
}
