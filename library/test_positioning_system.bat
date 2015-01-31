@echo off

rem ---------------------------------------------------------------------
rem                     compile the file


call set_environment_variables.bat "C:\Program Files (x86)\Arduino" C:\Users\cheche\Documents\Arduino nano328 COM23

call abuild.bat -r -c "positioning_system\examples\test_solver\test_solver.pde" 

FOR %%A IN (obj\*.elf) DO set elf_file_size=%%~zA

rem comparing http://stackoverflow.com/questions/9278614/if-greater-than-batch-files
if %elf_file_size% LEQ  %ARDUINO_MAXIMUM_UPLOAD_SIZE% (
  call aupload.bat obj/test_solver.elf
) else (
  echo %elf_file_size% is too big for the arduino. 30720 is allowed.
)

