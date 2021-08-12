#ifndef RENDERER_HEADER
#define RENDERER_HEADER
#include "models/animation/AnimationState.hpp"

void initRenderer(int windowid);
void verticalShift(double dy);
void render();

static AnimationState animationState;

#endif
