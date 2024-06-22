#ifndef AF_LOG_H
#define AF_LOG_H
#include <stdio.h>
#include <stdarg.h>

#ifdef DEBGUG
#define LOG_TO_CONSOLE = 1
#else
#define LOG_TO_CONSOLE = 0
#endif

// ANSI escape codes for colors
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_CYAN    "\033[36m"

#ifdef __cplusplus
extern "C" {
#endif
/*
inline static void AFSaveLog(const char* _message, const char* _format, __va_list_tag* _args){
    FILE* log_file = fopen("log.txt", "a");
    if (log_file) {
        vfprintf(log_file, _format, _args);
        fprintf(log_file, "\n");
        fclose(log_file);
    }

}
*/
// If debug
static inline void AF_Log(const char* _message,...){
    printf(COLOR_GREEN);  // Set color to cyan for regular logs
    va_list args;
    va_start(args, _message);
    vfprintf(stdout, _message, args);
    //AFSaveLog(_message, "LOG: ", args);
    va_end(args);
}

static inline void AF_Game_Log(const char* _message,...){
    printf(COLOR_CYAN);  // Set color to cyan for regular logs
    va_list args;
    va_start(args, _message);
    vfprintf(stdout, _message, args);
    //AFSaveLog(_message, "LOG: ", args);
    va_end(args);
}


static inline void AF_Log_Warning(const char* _message,...){
    printf(COLOR_YELLOW "Warning: ");  // Set color to yellow for warnings
    va_list args;
    va_start(args, _message);
    vfprintf(stdout, _message, args);
    va_end(args);
}

static inline void AF_Log_Error(const char* _message,...){    
    fprintf(stderr, COLOR_RED "Error: ");  // Set color to red for errors
    va_list args;
    va_start(args, _message);
    vfprintf(stderr, _message, args);
    va_end(args);
}

#ifdef __cplusplus
}
#endif

// Send to console
// Store to log file


// if release
// don't send ot console, but store to log file.

#endif
