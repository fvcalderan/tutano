#include "FPS_lock.h"

void FPS_after_execution()
{
    ++FPS_func_frameCounter;

    //has limited resolution, so average over 1000mS
    FPS_func_currentClock = glutGet(GLUT_ELAPSED_TIME); 

    if ( FPS_func_currentClock < FPS_func_nextClock ) {
        return;
    }

    // store the averaged number of frames per second
    FPS = FPS_func_frameCounter/1; 

    FPS_func_previousClock = FPS_func_currentClock;

    // set the next clock to aim for as 1 second in the future (1000 ms)
    FPS_func_nextClock = FPS_func_currentClock + 1000;
    FPS_func_frameCounter=0;
}

void FPS_init()
{
    FPS = 0;
    FPS_func_frameCounter = 0;         // frames averaged over 1000mS
    FPS_func_previousClock = 0;        // [milliSeconds]
    FPS_func_nextClock = 0;            // [milliSeconds]
    idle_previousClock = glutGet(GLUT_ELAPSED_TIME);
    idle_currentClock = glutGet(GLUT_ELAPSED_TIME);
}
