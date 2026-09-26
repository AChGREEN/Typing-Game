Overview:
Since this is a command-line typing test, there is nowhere for me to host this and to run it, you will need to follow steps.

How to Run:
1. install typing_game_demo.exe
2. run: cd "file path"
        .\typing_game_demo.exe
        
Tech Stack:
C
GCC (MinGW-W64) ()
Code::Blocks
VS Code
Windows


AI Usage:
My windows computer didn't even have a C compiler installed, so nothing was gonna compile locally. I did try to install some vscode extentions and download some programs but it didn't work so I had copilot try to sort it out and it was kind of a mess honestly. The first attempt (installing MSYS2 through winget) just failed outright, then it tried a different mingw installer which also didn't really finish properly, so it went digging through folders trying to find where gcc.exe even ended up. Ended up having to install a third thing (a code::blocks bundle that comes with mingw baked in) before it actually found a working gcc