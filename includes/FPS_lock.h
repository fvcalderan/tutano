#ifndef _FPS_LOCK_H
#define _FPS_LOCK_H

#include <GL/gl.h>
#include <GL/glut.h>

#define FPS_before_execution() { \
    idle_currentClock = glutGet(GLUT_ELAPSED_TIME); \
    idle_deltaT = idle_currentClock - idle_previousClock; \
    if (idle_deltaT < 17) { \
        return; \
    } else { \
        idle_previousClock = idle_currentClock; \
    } \
} 

GLint  FPS;
GLint  FPS_func_frameCounter;         // frames averaged over 1000ms
GLuint FPS_func_currentClock;         // [milliSeconds]
GLuint FPS_func_previousClock;        // [milliSeconds]
GLuint FPS_func_nextClock;            // [milliSeconds]

GLuint idle_previousClock;
GLuint idle_currentClock;
GLfloat idle_deltaT;

void FPS_after_execution();
void FPS_init();

#endif
