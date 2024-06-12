# Terminal Warfare (II Edition)

![Static Badge](https://img.shields.io/badge/Category-Game-black)
![Static Badge](https://img.shields.io/badge/Status-WIP-lightyellow)
![Static Badge](https://img.shields.io/badge/Made_with-C%2B%2B-blue)
![Static Badge](https://img.shields.io/badge/Build-CMake-red)
![Static Badge](https://img.shields.io/badge/Platform-Universal-white)

## About
A game about controlling armies and winning battles against AI or your friends directly from the terminal. Through a graphical interface, the experience of a strategy game can be fully enjoyed, whiel also running from any machine with a command line. Also includes a complete set of tools to build your own maps, units and scenarios, allowing for modding the game to a whole another level. Be it from Windows, Linux, or many others, you will surelly enjoy this game.

## Instalation
   Clone the repository with:
      
      git clone https://github.com/CostaCesar/Terminal_Warfare_2.git
   
   Next, enter the directory and run CMake configuration:

      cmake -G "MinGW Makefiles" Cmakelists.tx
   
   And finnaly, build the project with:

      cmake --build .
   
   In the future, a release build will be provided for easier setup

## But why II Edition?
This was, innitialy, just a rewrite of the original game I made, Terminal War, which is now abandoned as a public archive (link). It was made more in a learning experience than a fun project, lacking in portability (Windows only), code readability, overall performance and many others.

Thus, I decided to start from scratch, now using C++ for the added tools it provides, as well as a proper code structure standart with CMake. Also, is written from the start with cross-platforming in mind, unlike the orginal.

However, this is also a sequence to that project because it expands on the core concepts and adds new features. Buildings, LAN multiplayer, tutorials, and others will be included into the final version.
