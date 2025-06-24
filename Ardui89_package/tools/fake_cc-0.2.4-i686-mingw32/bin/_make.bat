@echo off
@set path=%path%;C:\mingw\bin;C:\mingw\msys\1.0\bin;
@rem path=%path%;C:\cygwin\bin;
@rem windres main.rc mainrc.o
mkdir c:\users\crossover\Temp

set FAKE_VERSION=_FAKE_VERSION_=\"0.2.4\"
set SDCC_VERSION=_SDCC_VERSION_=\"4.4.0\"

rem set SRC_PATH=../../fake_cc-0.2.0-x86_64-apple-darwin12/bin

set SRC_PATH=.

rm -f fake.exe fake_cpp.exe fake_ld.exe fake_objcopy.exe fake_size.exe fake_sdar.exe
    
gcc -o fake.exe %SRC_PATH%/fake.c -D%FAKE_VERSION% -D%SDCC_VERSION%

gcc -o fake_cpp.exe %SRC_PATH%/fake_cpp.c -D%FAKE_VERSION% -D%SDCC_VERSION%

gcc -o fake_ld.exe %SRC_PATH%/fake_ld.c -D%FAKE_VERSION% -D%SDCC_VERSION%

gcc -o fake_objcopy.exe %SRC_PATH%/fake_objcopy.c -D%FAKE_VERSION% -D%SDCC_VERSION%
    
gcc -o fake_size.exe %SRC_PATH%/fake_size.c -D%FAKE_VERSION% -D%SDCC_VERSION%

gcc -o fake_sdar.exe %SRC_PATH%/fake_sdar.c -D%FAKE_VERSION% -D%SDCC_VERSION%

echo fake version : %FAKE_VERSION%
echo sdcc version : %SDCC_VERSION%
