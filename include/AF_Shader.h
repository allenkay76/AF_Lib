#ifndef AF_SHADER_H
#define AF_SHADER_H
#include "AF_Util.h"

#ifdef __cplusplus
extern "C" {    
#endif

inline int AF_Shader_GL_Load(const char* _vertexShaderPath, const char* _fragmentShaderPath, int* _shaderProgram){
    char* _vertexShaderSource = AF_Util_ReadFile(_vertexShaderPath);
    char* _fragmentShaderSource = AF_Util_ReadFile(_fragmentShaderPath);
    printf("AF_Shader_GL_Load: TOOD: %s %s %i\n", _vertexShaderSource, _fragmentShaderSource, *_shaderProgram);
    return 1;
}

/*
//constructor
GL_Shader::GL_Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	{
        bool success = true;
        //Check if path is empty
        if (vertexShaderPath.empty() || fragmentShaderPath.empty()) {
            LogManager::Log("Unable to load shader as path is missing %s %s\n", vertexShaderPath.c_str(), fragmentShaderPath.c_str());
            success = false;
        }

        //Read vertex shader file
        std::string vertexShaderSource = readFile(vertexShaderPath);
        if (vertexShaderSource.empty()) {
            LogManager::Log("Unable to read vertex shader file %s\n", vertexShaderPath.c_str());
            success = false;
        }
        
        //Read fragment shader file
        std::string fragmentShaderSource = readFile(fragmentShaderPath);
        if (fragmentShaderSource.empty()) {
            LogManager::Log("Unable to read fragment shader file %s\n", fragmentShaderPath.c_str());
            success = false;
        }
        
    //If no errors, create program
    if (success){
        //Create program
        setProgramID(glCreateProgram());
        //Create vertex shader
        unsigned int vertexShader = glCreateShader( GL_VERTEX_SHADER );

        //Set vertex source
        const char* vertexShaderSourcePtr = vertexShaderSource.c_str();
        //Set vertex source
        glShaderSource(vertexShader, 1, &vertexShaderSourcePtr, NULL);

        //Compile vertex source
        glCompileShader(vertexShader);

        //check vertex shader for errors
        int vShaderCompiled = GL_FALSE;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
        if(vShaderCompiled != GL_TRUE){
            LogManager::Log("Unable to compile vertex shader %s!\n", vertexShaderPath.c_str());
            printShaderLog(vertexShader);
            success = false;
        }
        else{
            //Attach vertex shader to program
            glAttachShader(getProgramID(), vertexShader);

            //Create fragment shader
            unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

            //Set fragment source
            const GLchar* fragmentShaderSourcePtr = fragmentShaderSource.c_str();
            glShaderSource(fragmentShader, 1, &fragmentShaderSourcePtr, NULL);

            //Compile fragment source
            glCompileShader(fragmentShader);

            //Check fragment shader for errors
            if(checkCompileErrors(fragmentShader, "SHADER") == false){
                LogManager::Log("Unable to compile fragment shader ",fragmentShaderPath.c_str());;
                printShaderLog(fragmentShader);
                success = false;
            }else{

                //Attach fragment shader to program
                glAttachShader(getProgramID(), fragmentShader);

                //Link program
                glLinkProgram(getProgramID());
                
                //Check for errors
                GLint programSuccess = GL_TRUE;
                glGetProgramiv(getProgramID(), GL_LINK_STATUS, &programSuccess);
                if(programSuccess != GL_TRUE){
                    LogManager::Log("\nError linking program %d!\n", getProgramID());
                    printProgramLog(getProgramID());
                    success = false;
                }
            }
        }
    }
}
*/

#ifdef __cplusplus
}
#endif

#endif //SHADER_H
