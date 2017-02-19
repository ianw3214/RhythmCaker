@echo off
doskey a = atom $*
doskey ls = dir $*
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall"
echo on
