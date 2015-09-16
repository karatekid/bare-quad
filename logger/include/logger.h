#ifndef __LOGGER__H__
#define __LOGGER__H__
#include "config.h"

class Logger {
    public:
        // Gets singleton
        static Logger *getLogger();
        void on();
        void off();
        //Sets which level the subsystem must reach to get logged
        void setLevel(eLogLevel lvl, eLogSubsystem ss);
        void timeRaw(eLogLevel lvl, eLogSubsystem ss, const char *id, bool start);
        // A macro to wrap around functions
        #define functionTime(lvl, ss, FXN) \
            timeRaw(lvl, ss, #FXN, true); \
            FXN; \
            Logger::getLogger()->timeRaw(lvl, ss, #FXN, false)
        void count(eLogLevel lvl, eLogSubsystem ss, uint32_t count, const char *id);
        // A macro to wrap around variables
        #define variableCount(lvl, ss, VAR) \
            count(lvl, ss, VAR, #VAR)
        // Version is automatically only info log level
        void version(eLogSubsystem ss, uint8_t major, uint8_t minor, uint8_t build);

        void print(eLogLevel lvl, eLogSubsystem ss, const char *s);

        void rawData(eLogLevel lvl, eLogSubsystem ss, eLogType type, uint32_t len, const char *data, const char *id);
        #define rawVar(lvl, ss, type, VAR) \
            rawData(lvl, ss, type, sizeof(VAR), (char *)&(VAR), #VAR)

    protected:
        Logger();
    private:
        // Generic logging function used by all others
        void logHead(eLogLevel lvl, eLogSubsystem ss, eLogType type, uint32_t len);
        // Helper that makes writing arbitrary data easy
        void writeRawData(uint16_t len, const char *d);
        // A macro so you don't have to calculate len everytime
        #define writeRawValue(v) \
            writeRawData(sizeof(v), (char *)&(v))

        // Helper to filter out those calls that have been quieted
        bool filter(eLogLevel lvl, eLogSubsystem ss);

        bool logOn;
        eLogLevel logLevels[NUM_SUBSYSTEMS];
        static Logger* logger;
};

#endif
