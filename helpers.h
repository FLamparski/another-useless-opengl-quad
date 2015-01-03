#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <string.h>

// Shader utility functions

// Prints shader info log if any
int print_shader_log(GLuint shader);

// Prints program info log if any
int print_program_log(GLuint program);

// File loading functions
long load_file(const char* path, char** buffer);
GLuint shader_from_file(const char* path, GLenum shader_type);

// debug macros
#ifdef NODEBUG
  #define pdebug()
#else
  #define pdebug(M, ...) fprintf(stderr, "[%s (%s:%d)][debug] " M, __func__, __FILE__, __LINE__, ##__VA_ARGS__);
#endif

#define pinfo(M, ...) fprintf(stderr, "[%s (%s:%d)][info] " M, __func__, __FILE__, __LINE__, ##__VA_ARGS__);
#define pwarn(M, ...) fprintf(stderr, "[%s (%s:%d)][warn] " M, __func__, __FILE__, __LINE__, ##__VA_ARGS__);
#define perr(M, ...) fprintf(stderr, "[%s (%s:%d)][error] " M, __func__, __FILE__, __LINE__, ##__VA_ARGS__);
