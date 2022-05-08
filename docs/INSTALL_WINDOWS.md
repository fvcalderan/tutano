# Install Tutano (Windows)

Compile Tutano on Windows is a more cumbersome procedure. First, install
MSYS2 using winget inside an powershell (with administrator privileges):
```powershell
winget install msys2.msys2 --source winget
```
Then, open MSYS2 MSYS and run the following commands to install the GNU C
Compiler (gcc) and the required libraries:
```bash
pacman -Syu
pacman -S mingw-w64-x86_64-toolchain
pacman -S mingw-w64-x86_64-freeglut
pacman -S mingw-w64-x86_64-glew
pacman -S make
```
After everything has been installed, copy Tutano's source code to any folder
MSYS2 has access to. After that, make the following changes to the files:

**makefile**
```diff
- LDFLAGS = -lm -lGL -lGLU -lglut
+ LDFLAGS = -lm -lopengl32 -lglu32 -lfreeglut
```

**includes/texloader.c**
```diff
- glEnable(GL_RESCALE_NORMAL);
+ // glEnable(GL_RESCALE_NORMAL);
```
Run `make` inside Tutano's root folder. The game should compile with some
warnings, but do not worry about them.

At this point, the game is fully compiled but won't run if you try to execute
Tutano.exe, because libfreeglut.dll isn't in the same folder as Tutano.exe.
To fix this, first we need to find where the missing file is.
```bash
ldd Tutano.exe | grep libfreeglut.dll
```
This should return a path to libfreeglut.dll. Copy this file to where
Tutano.exe is located. Now you should be good to go:
```bash
./Tutano.exe
```

Have fun!
