@echo off

rem ---------------------------------------------------------------------
rem                     compile the file


call set_environment_variables.bat "C:\Program Files (x86)\Arduino" C:\Users\cheche\Documents\Arduino nano328 COM23

call abuild.bat -r -c "positioning_system\examples\test_solver\test_solver.pde" 

FOR %%A IN (obj\*.hex) DO set elf_file_size=%%~zA

rem does not work:
rem echo Binary Sketchsize: %elf_file_size% bytes (out of a maximum of %ARDUINO_MAXIMUM_UPLOAD_SIZE% bytes)

call aupload.bat obj/test_solver.hex

rem http://serverfault.com/questions/432322/how-to-sleep-in-a-batch-file#432323
rem timeout /t 5 /nobreak

rem http://stackoverflow.com/questions/11775185/open-a-com-port-in-c-with-number-higher-that-9
..\serialterm\serialterm.exe \\.\%ARDUINO_COMPORT% 9600