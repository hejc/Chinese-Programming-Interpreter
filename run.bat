@echo off
title [Chinese programming]

ChineseToPinYin_Release
PinYinToEnglish_Release    

echo Compiling...
gcc PinYinToEnglish.c -o output

echo Runing...
output

@echo off
rem ɾ���м��ļ�
del PinYinToEnglish.c
del ChineseToPinYin.c
rem del output.exe
rem �ȴ��س�
pause