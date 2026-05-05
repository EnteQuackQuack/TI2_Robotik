# Changelog
## Changes to be compilable with simulator
- removed `#include "nnxt.h"` from event.cpp and timer.cpp
- added `#include "event.cpp"` and `#include "timer.cpp"` to main.cpp

## Bugfixes
- removed () out of `CreateAndStartTask(Taskname())`; only requires `CreateAndStartTask(Taskname);`

## General Changes
- renamed `GO_LEFT` to `EVENT_GO_LEFT`
- renamed `GO_RIGHT` to `EVENT_GO_RIGHT`
- removed some magic numbers 
