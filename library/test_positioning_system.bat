@echo off

rem ---------------------------------------------------------------------
rem                     compile the file


call set_environment_variables.bat

call abuild.bat -r -c "positioning_system\examples\test_solver\test_solver.pde" 

call aupload.bat obj/test_solver.elf

