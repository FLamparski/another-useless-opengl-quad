#include "helpers.h"

int print_shader_log(GLuint shader) {
  int len;
  GLenum error;

  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
  error = glGetError();
  if (error) {
    switch (error) {
      case GL_INVALID_VALUE:
        fprintf(stderr, "Not a valid shader handle: %d\n", shader);
        break;
      case GL_INVALID_OPERATION:
        fprintf(stderr, "No shader compiler or not a valid shader handle.\n");
        break;
      default:
        fprintf(stderr, "Other GL error: %d\n", error);
        break;
    }
    return -1;
  }

  if (len) {
    // len includes the terminating NULL byte
    char* log = (char*) malloc(len);

    glGetShaderInfoLog(shader, len, &len, log);
    fprintf(stderr, "%s\n", log);

    free(log);
  } else {
    fprintf(stderr, "(No shader log present)\n");
  }

  return len;
}

int print_program_log(GLuint program) {
  int len;
  GLenum error;

  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
  error = glGetError();
  if (error) {
    switch (error) {
      case GL_INVALID_VALUE:
        perr("Not a valid program handle: %d\n", program);
        break;
      case GL_INVALID_OPERATION:
        perr("No shader compiler or not a valid program handle.\n");
        break;
      default:
        perr("Other GL error: %d\n", error);
        break;
    }
    return -1;
  }

  if (len) {
    // len includes the terminating NULL byte
    char* log = (char*) malloc(len);

    glGetProgramInfoLog(program, len, &len, log);
    fprintf(stderr, "%s\n", log);

    free(log);
  } else {
    fprintf(stderr, "(No shader log present)");
  }

  return len;
}

GLuint shader_from_file(const char* path, GLenum shader_type) {
  GLuint shader = 0;
  GLint length;

  shader = glCreateShader(shader_type);

  char* src = NULL;
  length = load_file(path, &src);
  if (length < 0) {
    perr("Could not load shader source file for %s.\n", path);
    return 0;
  }

  pinfo("Loading shader (id %d; %d bytes)\n", shader, length);

  const char** vertex_shader_src = (const char**) &src;
  glShaderSource(shader, 1, vertex_shader_src, &length);
  free(src);

  GLenum err = glGetError();
  pdebug("GL error: %d\n", err);

  return shader;
}

long load_file(const char* path, char** buf) {
  FILE* file;
  long length;

  if (*buf != NULL) {
    fprintf(stderr, "Buf should be null when reading a file.\n");
    return -1;
  }

  file = fopen(path, "rb");
  if (!file) {
    fprintf(stderr, "Could not read file %s.\n", path);
    return -1;
  }

  fseek(file, 0, SEEK_END); // Go to end of file so that we know how long it is
  if (errno == EBADF) {
    fprintf(stderr, "Could not find the length of %s.\n", path);
    return -1;
  }

  length = ftell(file);

  rewind(file); // Go back to start of the file for reading

  *buf = (char*)(calloc(length + 1, sizeof(char))); // Make space for the \0 terminator
  fread(*buf, length, 1, file);

  fclose(file); // Close the file and free the memory

  (*buf)[length] = '\0'; // Add the \0 terminator
  return length;
}
