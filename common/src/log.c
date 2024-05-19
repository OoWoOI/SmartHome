/*************************************************************************
	> File Name: Log.c
	> Author: 
	> Mail: 
	> Created Time: Tue 14 May 2024 05:38:18 PM CST
 ************************************************************************/

#include "../include/head.h"

void log_event(const char *logfile, const int level, const char *msg) {
    time_t now = time(NULL);

    char *level_str;
    FILE *fp;

    switch (level) {
        case LOG_LEVEL_NORMAL: {
            level_str = "INFO";
        } break;

        case LOG_LEVEL_WARNING : {
            level_str = "WARNING";
        } break;

        case LOG_LEVEL_ERROR : {
            level_str = "ERROR";
        } break;

        default: {
            level_str = "UNKNOWN";
        } break;
    }


    if ((fp = fopen(logfile, "a")) == NULL) {
        DBG("%s : FILE_NOT_EXIST\n", logfile);
        return ;
    }
    
    fprintf(fp, "%s [%s] : %s\n", ctime(&now), level_str, msg);
    fclose(fp);
    return ;
}
