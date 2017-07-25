@echo off
title [Chinese programming]

ChineseToPinYin_Release
PinYinToEnglish_Release    

echo Compiling...
gcc PinYinToEnglish.c -o output

echo Runing...
output

@echo off
rem 删除中间文件
del PinYinToEnglish.c
del ChineseToPinYin.c
rem del output.exe
rem 等待回车
pause