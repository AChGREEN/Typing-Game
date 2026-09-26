Overview:
This is a simple command line game made in C which is played by typing the prompt shown. It shows your accuracy, WPM and time taken with sentence diffculty levels ranging for easy, medium and hard.

How to Run:
Since this is a command-line typing test, there is nowhere for me to host this and to run it, you will need to follow steps.

1. download the release; source code zip file
3. extract the zip file
4. open the terminal of you choice
5. run: cd "file path"
        .\typing_game_demo.exe
6. have fun typing :D

Tech Stack:
C
GCC (MinGW-W64) ()
Code::Blocks
VS Code
Windows

AI Usage:
My windows computer didn't have a C compiler installed, so nothing was gonna compile locally. I did try to install some vscode extentions and download some programs but it didn't work so I had copilot try to sort it out and it was kind of a mess honestly. The first attempt (installing MSYS2 through winget) just failed outright, then it tried a different mingw installer which also didn't really finish properly, so it went digging through folders trying to find where gcc.exe even ended up. Ended up having to install a third thing (a code::blocks bundle that comes with mingw baked in) before it actually found a working gcc