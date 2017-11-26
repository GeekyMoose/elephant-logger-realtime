# Elephant Logger
![LittleElephant](https://i.imgur.com/zXS7zHs.png)
[Made by Marie-Pier Bouffard](https://www.artstation.com/mariepierbouffard)

> Your code

```
LOG_WTF(0, "1. TEST ERROR");
LOG_ERROR(0, "1. TEST ERROR");
LOG_WARNING(0, "2. TEST WARNING");
LOG_CONFIG(0, "3. TEST CONFIG");
LOG_INFO(0, "4. TEST INFO");
LOG_TRACE(0, "5. TEST TRACE");
LOG_DEBUG(0, "6. TEST DEBUG");

LOG_DEBUG(0, "Integer value: %d", 42);
LOG_DEBUG(0, "Float value: %f", 31.9);
LOG_DEBUG(0, "Bool value (true): %d", true);
LOG_DEBUG(0, "NULL (Using d): %d", NULL);
LOG_DEBUG(0, "NULL (Using s): %s", NULL);

LOG_DEBUG(0, "String: %s / Integer: %d / Float: %f / Char: %c", "Hello", 2, 7.1, 'c');

for(int counter = 1; counter < 4; ++counter) {
    LOG_DEBUG(0, "Log in loop (counter: %d)", counter);
}
```

> Execution

![Screenshot - Example](https://i.imgur.com/OJKpjmW.png)


# Work in progress
> Work in progress. Important change may still happened.
> This doc may be not at the last up to date state.


# Description
This project is a C++ logger designed for Realtime softwares.
Realtime doesn't mean here that logs are displayed in realtime.
Instead, the goal is that logging shouldn't affect the programme execution time.
(The least we can).
Inside the software thread (Your running programme), logs call only queue the message.
The logger is started on its own thread which then process the logs, print them, write in files etc...


# Dependencies
- Standalone library: no dependencies.


# Build requirement
- C++11
- experimental/filesystem support (stdc++fs)
- thread (pthread)
- pragma support (pragma once)


# Build on GNU/Linux (CMake)
- [CMake](https://cmake.org/)

```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j4
```
> DCMAKE_BUILD_TYPE options: Debug / Release / RelWithDebInfo / MinSizeRel


# Execute examples on GNU/Linux (CMake)
- Set CMake option "EXAMPLE" to ON (Already ON by default)
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j4
make ex1
```
> DCMAKE_BUILD_TYPE options: Debug / Release / RelWithDebInfo / MinSizeRel

> Start example 1. For other, change '1' by example number.


# Build / Run on Windows
TODO (Not supported yet. Coming soon)


# Features
- Simple logging calls with log levels
    - LOG_WTF
    - LOG_ERROR
    - LOG_WARNING
    - LOG_CONFIG
    - LOG_INFO
    - LOG_TRACE
    - LOG_DEBUG
- Printf like log format
    - Log message works like printf message format.
- Outputs
    - File output: logs are written in a file
    - Cout: logs are written in std::cout
    - VS: logs are written in Visual Studio console (Or std::cout if not supported)
- Channels
    - Channels are set to write in specific outputs.
    - Flexible configuration to set each Channels.
- Logging options
    - Log Level (Bypass all logs with lower critique level)
    - Save log file
    - Reset log file at start


# Example
```
#include "elephant.h"

#include <chrono>
#include <thread>


// A simple test
int main(int argc, char** argv) {

    elephant::init();

    LOG_WTF(0, "1. TEST ERROR");
    LOG_ERROR(0, "1. TEST ERROR");
    LOG_WARNING(0, "2. TEST WARNING");
    LOG_CONFIG(0, "3. TEST CONFIG");
    LOG_INFO(0, "4. TEST INFO");
    LOG_TRACE(0, "5. TEST TRACE");
    LOG_DEBUG(0, "6. TEST DEBUG");

    LOG_DEBUG(0, "Integer value: %d", 42);
    LOG_DEBUG(0, "Float value: %f", 31.9);
    LOG_DEBUG(0, "Bool value (true): %d", true);
    LOG_DEBUG(0, "NULL (Using d): %d", NULL);
    LOG_DEBUG(0, "NULL (Using s): %s", NULL);

    LOG_DEBUG(0, "String: %s / Integer: %d / Float: %f / Char: %c", "Hello", 2, 7.1, 'c');

    int counter = 0;
    while(true) {
        counter++;
        LOG_DEBUG(0, "Log in loop (counter: %d)", counter);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    return 0;
}
```


# Generate Doxygen documentation
- `doxygen Doxyfile`
- Documentation generated in build-doxygen folder.


# Author
Constantin Masson ([constantinmasson.com](http://constantinmasson.com/))
