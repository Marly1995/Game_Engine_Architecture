TITLE GeaMakeFile

ECHO build started!

ECHO off

MD build
CD build

conan install ..
cmake .. -G "Visual Studio 14 Win64"
cmake --build . --config Debug

pause