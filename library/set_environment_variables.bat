@echo off
@rem ---------------------------------------------------------------------
@rem                     set environment variables
@rem See http://playground.arduino.cc/Code/WindowsCommandLine
@rem you will need to edit this file
@rem where you installed Arduino on your computer (e.g. C:\ARDUINO-0011)
SET ARDUINO_PATH=C:\Program Files (x86)\Arduino

@rem the name of your microcontroller (e.g., atmega168)
@rem atmega168 atmega328
SET ARDUINO_MCU=atmega328p

@rem the variant of the arduino must be looked up in boards.txt 
@rem in !ARDUINO_PATH!\hardware\arduino\variants
SET ARDUINO_VARIANT=eightanaloginputs

@rem the name of the programmer you wish to use (usually stk500)
SET ARDUINO_PROGRAMMER=arduino

@rem the clock frequency of your microcontroller (usually 16000000 for atmega168)
SET ARDUINO_FCPU=16000000

@rem the port to which your programmer is connected (e.g. COM1, COM2, etc.)
SET ARDUINO_COMPORT=COM23

@rem the baud rate at which the download is to occur (19200 seems to be a good starting point)
rem according to http://arduino.cc/en/Serial/Begin these are possible baud rates
rem 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, or 115200
rem see baud rates here http://42bots.com/resources/arduino-program-sketch-upload-speeds/
SET ARDUINO_BURNRATE=57600

@rem The directory for user defined libraries
SET ARDUINO_USER_LIBRARIES=C:\Users\cheche\Documents\Arduino\libraries

@rem The maximum upload size of the arduino