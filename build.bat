@echo off
setlocal
cd /d "%~dp0"
where em++ >nul 2>nul
if errorlevel 1 (
  echo Emscripten is not active. Run emsdk_env.bat in this Command Prompt first.
  exit /b 1
)
if not exist public mkdir public
call em++ source\main-web.cpp -std=c++17 -O2 -sASYNCIFY -sEXIT_RUNTIME=1 -sENVIRONMENT=web -sEXPORTED_RUNTIME_METHODS=stringToUTF8,lengthBytesUTF8,UTF8ToString -o public\supermarket.js
if errorlevel 1 exit /b 1
echo Build complete. Open public\index.html using VS Code Live Server.
