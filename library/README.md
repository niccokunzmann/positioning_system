Testing
-------

edit `test_positioning_system.bat` to contain the COM-port, library path and arduino type and Arduino install directory.
then you can rum

    test_positioning_system.bat test1
    test_positioning_system.bat test2
    test_positioning_system.bat test3
    test_positioning_system.bat test4

And see the output of the examples in the examples folder.


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

So I changed that.

Furthemore
    
    nano328.name=Arduino Nano w/ ATmega328
    
    nano328.upload.protocol=arduino
    nano328.upload.maximum_size=30720
    nano328.upload.speed=57600
    
    nano328.bootloader.low_fuses=0xFF
    nano328.bootloader.high_fuses=0xDA
    nano328.bootloader.extended_fuses=0x05
    nano328.bootloader.path=atmega
    nano328.bootloader.file=ATmegaBOOT_168_atmega328.hex
    nano328.bootloader.unlock_bits=0x3F
    nano328.bootloader.lock_bits=0x0F
    
    nano328.build.mcu=atmega328p
    nano328.build.f_cpu=16000000L
    nano328.build.core=arduino
    nano328.build.variant=eightanaloginputs

Describes 

    nano328.build.core=arduino
    nano328.build.variant=eightanaloginputs

So 

	SET ARDUINO_MCU=atmega168
	SET ARDUINO_VARIANT=eightanaloginputs

must be set accordingly. This is done by `set_environment_variables.bat`.


Serial communication
--------------------

Downloaded `serialterm.exe` form http://www.comp.lancs.ac.uk/~albrecht/sw/terminal/index.html