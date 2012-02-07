=====
README
=====

Idea
=====

In multithreaded programs one needs to debug dangerous parts of code. This module will allow marking the danger zones, and easy logging of threads passing the zones.

Usage
=====

    DZ_ENTRY;
--or--
    DZ_ENTRY_MSG("message");

followed by
    DZ_MIDDLE;

ended with
    DZ_EXIT;
