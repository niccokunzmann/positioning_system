Setup Hacks
-----------

got the output 
    
    C:\Users\cheche\Documents\programmiertes\positioning_system\library>abuild.bat positioning_system\test_positioning_system.cpp
    The system cannot find the path specified.
    positioning_system\test_positioning_system.cpp:5:21: error: Arduino.h: No such file or directory
    In file included from positioning_system\/positioning_system.h:19,
     from positioning_system\test_positioning_system.cpp:6:
    positioning_system\/test.h:10: error: 'boolean' does not name a type
    positioning_system\/test.h:11: error: 'boolean' does not name a type
    positioning_system\test_positioning_system.cpp: In function 'void setup()':
    positioning_system\test_positioning_system.cpp:10: error: 'Serial' was not declared in this scope
    positioning_system\test_positioning_system.cpp:13: error: 'test_success' was not declared in this scope
    abuild.bat: *** ERROR: cannot compile positioning_system\test_positioning_system.cpp using command:
    abuild.bat: *** ERROR: avr-g++ -c -g -Os "-IC:\Program Files (x86)\Arduino\hardware\cores\arduino"  -I"C:\Users\cheche\Documents\programmiertes\positioning_system\library\obj" -I"C:\Users\cheche\Docum
    ents\programmiertes\positioning_system\library\positioning_system" -mmcu=atmega328p -DF_CPU=16000000 -DABUILD_BATCH=1 -fno-exceptions positioning_system\test_positioning_system.cpp -o.\obj\test_positi
    oning_system.cpp.o

So it is expecting a library here: `C:\Program Files (x86)\Arduino\hardware\cores\arduino`  
But the library is there: `C:\Program Files (x86)\Arduino\hardware\arduino\cores\arduino`

So I ran

    mklink /J "C:\Program Files (x86)\Arduino\hardware\cores" "C:\Program Files (x86)\Arduino\hardware\arduino\cores"