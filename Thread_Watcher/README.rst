=====
README
=====

Idea
=====

In multi-threaded programs one needs to debug dangerous parts of code. This module will allow marking the danger zones, and easy logging of threads passing the zones.

Usage
=====

    DZ_ENTRY;

or

    DZ_ENTRY_MSG("message");

followed by

    DZ_PROCESS;

ended with

    DZ_EXIT;

Prerequisites
=============

For output uses the Logger snippet, "log <<" syntax. Thus must be used with logger lib.

