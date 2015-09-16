/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : Main.cpp

 * Purpose :

 * Creation Date : 30-08-2015

 * Created By : Michael Christen

 _._._._._._._._._._._._._._._._._._._._._.*/
#include "logger.h"
#include "unistd.h"
#include<stdio.h>
int timePID(int x) {
    sleep(1);
    //printf("%d\n",x);
    return x * 2;
}

int main(int argc, char *argv[]) {
    // Generate
    Logger *log = Logger::getLogger();
    logStuff stuff;
    stuff.x = 4;
    stuff.y = 8.32;
    stuff.c = 'x';
    log->rawVar(DEBUG, SS_MAIN, T_LOGSTUFF, stuff);
    log->timeRaw(INFO, SS_MAIN, "hey", true);
    log->variableCount(INFO, SS_MAIN, stuff.x);
    log->version(SS_MAIN, 0,0,1);
    log->off();
    log->print(ERROR, SS_MAIN, "OH NOO");
    log->on();
    log->setLevel(ERROR, SS_PID);
    log->functionTime(WARNING, SS_PID, timePID(2));
    return 0;
}
