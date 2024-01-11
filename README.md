## Overview
Distributed Tracer is a C++ project designed to track and log function calls in distributed systems.
The output is compatible with chrome://tracing and perfetto (https://ui.perfetto.dev/)

### Requirements
spdlog library
C++17 compiler
Optional: MPI

### Usage
Initialize the trace manager at the start of your program with INIT_TRACE_MANAGER().
Use TRACE_FUNC() within functions to log their execution.
If linking to MPI, all functions will get their rank from the COMM_WORLD
If no MPI is available, the macros must take an integer to indicate their rank
The log is written on a per-process basis, so unique ranks are important or the processes will interfere with each other.

Example:

```cpp
#include "Tracer.h"

void myFunction() {
    TRACE_FUNC();
    // Function logic
}
```

### Log Merging

The provided Python script logMerger.py can be used to merge individual trace files into a single JSON file.
This is useful for analyzing the overall program execution across multiple processes.
The script accepts the -d option to indicate the location of the files, by default it will search in ./
The merged file will be generated to the same location