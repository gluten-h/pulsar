@ECHO OFF

git submodule update
if not exist vcpkg\vcpkg.exe call vcpkg\bootstrap-vcpkg.bat
call vcpkg\vcpkg.exe install directxtex:x64-windows
call vcpkg\vcpkg.exe install directxtk:x64-windows
call vcpkg\vcpkg.exe integrate install

if not exist build\ mkdir build\
call cmake -B build\
