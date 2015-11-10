# README #

Time Paradox - game where you should NOT face your previous self.

### Storyline ###

Imagine, that you are a tiny robot trapped in an old facility, which is filled(for some reason) with unsolvable puzzles and unreasonable constrictions. You have no other choice but to spend eternity in this building. 

However, one day you found your key to freedom: mysterious machine, that allows you to travel back and forwards in time. Now you at least stand a chance so reach your dream and leave this place.

DISCLAIMER: Changing observable past might cause The End of the World

### Controls ###

Use Up, Left, Right, Down to move

Use space to stop time, then press "-" to travel into the past, or "+" to visit your future

### How do I build this game ###

You need Microsoft Visual Studio 15 OR gcc 4.8+ for building solution.

1. Download pre-built binaries(Linux or Windows) of SFML from http://www.sfml-dev.org/download.php
2. Unpack them somewhere  
3. Linux:  
mkdir build  
cd build  
cmake .. -DCMAKE_BUILD_TYPE=Release -DSFML_ROOT=dir_where_lies_unpacked_sfml_lib  
make Game
3'. Windows:   
mkdir build  
cd build  
set path=C:\Program Files (x86)\CMake\bin  
cmake -G "Visual Studio 14 Win64" .. -DSFML_ROOT=dir_where_lies_unpacked_sfml_lib   
Then open TimeParadox.sln and build it in VisualStudio, do not forget change build type to Release
4. Place „resource“ folder near binary file.
5. For Windows you probably also need copy *.dll from SFML_ROOT/bin


### Known Bugs ###

- Platform still not working properly
- Main menu needs to be reworked
- Spurious crashes
- Animations