#ifndef AF_UTIL_H
#define AF_UTIL_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

//Read the file from the string path and return a string text
char* AF_Util_ReadFile(const char* thisFilePath){
    char fileBuffer[1024];
    char textBuffer[1024];
    FILE* _file = fopen(thisFilePath, "r");
     // read the file
    while(!feof(_file)){
         if(fgets(fileBuffer, 1024, _file) != NULL) {
            if (_file) {
                fread(textBuffer, 1, 1024, _file);
                fclose(_file);
            }
         }
    }

    //std::string line,text;
    //std::ifstream in(thisFilePath);
    //while(std::getline(in, line))
    //{
    //   text += line + "\n";
   // }
    
    //return text;
    char * returnText = 0;
    return returnText;
}

#ifdef __cplusplus
}
#endif

#endif  // AF_UTIL_H
