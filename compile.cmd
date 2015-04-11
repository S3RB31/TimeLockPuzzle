@echo off
call "%VS120COMNTOOLS%"vsvars32.bat
cl  src\Crypt.cpp src\Puzzle.cpp /EHsc
del *.obj