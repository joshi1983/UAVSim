#ifndef RENDERER_HEADER
#define RENDERER_HEADER
#include "models/animation/AnimationState.hpp"

void initRenderer(const char * programPath, int windowid);
void verticalShift(double dy);
void render();

static AnimationState animationState;

#endif
