#ifndef __CCGL_H__
#define __CCGL_H__

#define glClearDepth                glClearDepthf
#define glDeleteVertexArrays        glDeleteVertexArraysOES
#define glGenVertexArrays           glGenVertexArraysOES
#define glBindVertexArray           glBindVertexArrayOES

#ifdef Q_OS_SYMBIAN
#define GL_DEPTH24_STENCIL8_OES 0x88F0
#endif

#define GL_DEPTH24_STENCIL8      GL_DEPTH24_STENCIL8_OES

#include <GLES2/gl2platform.h>

#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES 1
#endif

// normal process
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

typedef char GLchar;

#endif // __CCGL_H__
