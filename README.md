# Overview:
A command-line typing speed test written in C. It gives you a sentence, times how long you take to type it, and tells you your WPM and accuracy. I made this as a small project to get more comfortable with C, and it ended up being a good excuse to mess with timing, string handling, and file I/O.

## Features
- Three difficulty levels (easy, medium, hard) with different sentence lengths and word complexity
- Times you precisely and accurately
- Calculates your WPM and accuracy
- Colored character-by-character breakdown of what you typed (green = correct, red = wrong)
- Saves your best WPM to highscore.txt so you can see your progress
- Made for Windows but may work on Linux or Mac; not optimised for it.
<img width="1766" height="800" alt="image" src="https://github.com/user-attachments/assets/5ee4ed74-4cb5-4b8c-97fa-d1065273f358" />

# How to Run:
1. **download the executable file** from the latest release
2. run the **typing_game.exe** file
3. have fun typing :D
   
# Tech Stack:
1. C
2. GCC (MinGW-W64) ()
3. Code::Blocks
4. VS Code
5. Windows

# AI Usage:
My windows computer didn't have a C compiler installed, so nothing was gonna compile locally. I did try to install some vscode extentions and download some programs but it didn't work so I had copilot try to sort it out and it was kind of a mess honestly. The first attempt (installing MSYS2 through winget) just failed outright, then it tried a different mingw installer which also didn't really finish properly, so it went digging through folders trying to find where gcc.exe even ended up. Ended up having to install a third thing (a code::blocks bundle that comes with mingw baked in) before it actually found a working gcc
