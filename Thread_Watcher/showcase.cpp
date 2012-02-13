#include <iostream>
#include <fstream>
#include "dz_watch.hpp"
#include <ctime>

int main()
{
  clock_t end = clock() + 1.4*CLOCKS_PER_SEC;
  DZ_ENTRY_MSG("MAIN THREAD");
  while (clock() < end)
  {
  }
  DZ_PROCESS;
  end = clock() + 5.2*CLOCKS_PER_SEC;
  while (clock() < end)
  {
    int a = 5;
    //NOP
  }
  DZ_EXIT;
  return 0;
}