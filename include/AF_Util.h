#ifndef AF_UTIL_H
#define AF_UTIL_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "AF_Log.h"

#ifdef __cplusplus
extern "C" {
#endif

static inline char* AF_Util_ReadFile(const char* thisFilePath) {
    FILE* _file = fopen(thisFilePath, "r");
    if (_file == NULL) {
        fprintf(stderr, "AF_Util: Read File: Failed to read file \n%s \nCheck file exists\n\n", thisFilePath);
        return NULL;
    }

    size_t textBufferSize = 1024;
    size_t totalLength = 0;
    char* textBuffer = (char*)malloc(textBufferSize);
    if (!textBuffer) {
        fprintf(stderr, "AF_Util: Read File: Memory allocation failed\n");
        fclose(_file);
        return NULL;
    }

    char line[1024];
    while (fgets(line, sizeof(line), _file) != NULL) {
        size_t lineLength = strlen(line);
        if (totalLength + lineLength + 1 > textBufferSize) {
            textBufferSize *= 2;
            char* tempBuffer = (char*)realloc(textBuffer, textBufferSize);
            if (!tempBuffer) {
                fprintf(stderr, "AF_Util: Read File: Memory reallocation failed\n");
                free(textBuffer);
                fclose(_file);
                return NULL;
            }
            textBuffer = tempBuffer;
        }
        strcpy(textBuffer + totalLength, line);
        totalLength += lineLength;
    }

    if (ferror(_file)) {
        fprintf(stderr, "AF_Util: Read File: Error reading file \n%s\n", thisFilePath);
        free(textBuffer);
        fclose(_file);
        return NULL;
    }

    fclose(_file);

    if (totalLength == 0) {
        free(textBuffer);
        return NULL;
    } else {
        return textBuffer;
    }
}


/*
====================
AF_STRING_EMPTY
Check if a const char* is empty
Return 1 if string is empty
REturn 0 if string is not empty
====================
*/
static inline uint32_t AF_STRING_IS_EMPTY(const char* _string){
    // null check the const char*, then see if the first element is a end of line
    if ((_string != NULL) && (_string[0] == '\0')) {
        return 1;
    }else {
        return 0;
    }
}

#ifdef __cplusplus
}
#endif

#endif  // AF_UTIL_H
