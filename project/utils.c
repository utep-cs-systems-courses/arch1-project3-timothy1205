#include "utils.h"

#define CONVERGE_TIME 5 // Converge in 5 seconds

short calc_velocity(short start, short end)
{
  // vel = dist / time
  return (end - start) / CONVERGE_TIME;
}

