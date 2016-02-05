This a fully functional SDL on Windows 10
It uses Mingw
Should show a rotating image
However the screen position could be odd for other configurations
So... YMMV

|  | Windows 10 | Linux | 
| :---: |:---: | :---: |
| status | *working*  | *working* |
| branch | *linuxsdl*  | *master* |

This program uses SDL2 libraries and shows RGB solid colors and then a rotating image, 
It uses Mingw to compile with Eclipse, make on Windows is broken because of 
library structure (may be my fault by improper installation)


On linux it compiles with g++ and the Makefile using "make"


**Things we have learned** while trying to create a (Windows and Linux)+SDL2+OpenGL+GUI

* README.md (md) extension means "MarkDown"
* fork to contribute or copy (github only)
* send a pull request
* sync your fork
* git status
* git diff
* markdown language
* git remote -v
* git remote add origin 'url'
* git add [. || filename || * ]
* git commit -m "What this commit does"
* git log
* sync a fork, fetch, merge , push
* git remote add upstream "url"
* git fetch upstream <pass>
* git merge upstream/master 
* git push origin master <pass>
* http://gitref.org/
* git stash
* git reset HEAD --file
* git branch newbranch
* rejected when pushing and rejected pull requests

:+1: :shipit: (shipit) Some silly emoticons that can be used. **(NEW) Simian & Garflunker song** "We all come to look for emoticons"



There is an unusual compile problem ( on Linux) that involves adding -lz or zlib to link to make this work 
and that seems like a kludge as well as implying that the system is non-deterministic
and could change behavior by just changing some unrelated code or in a different machine environment
The crash happens on SDL_Quit or SDL_Image so it means there is some library interface problem I assume.

## github went nuts with emojis 
[http://emoji-cheat-sheet.com is EMOJI reference] (http://emoji-cheat-sheet.com)

I thought they should have an emoji that indicated this repo was a steaming pile of shit and lo and behold (poop) :poop:
and it has shit which is the same, however steaming pile of seems to be unrepresented

The naming is somewhat backward as the Windows 10 code was put under linuxsdl branch and the linux code is under master

# Things that have caused problems with cross platform code:
1. IDE and MinGW and cygwin as well as spaces in names and /\ path variations
2. SDL libraries vary between the different Operating Systems
3. OpenGL does not work the same on Windows as it does on Ubuntu Linux
4. Hardware varies between machines and thus speed as well as methods vary
5. The complexity of the IDE is different than Cmake or config or make
6. Code and library locations are not standardized on Windows
7. If files are --static they can hold onto security flaws
8. Dynamic link can create new problems
9. Visual Studio is a tar baby in the briar patch that should be avoided
10. Windows upgrades are not synchronous
11. Many more
12. nullptr and NULL resolves with compiler option **-std=c++0x** 
13. :pizza: is pizza on the list?

# This is no walk in the park
In fact it is more like being stranded in Central Park with no clothes or food , sleeping by day to avoid the semantics cops 
and working by night wandering aimlessly through complex APIs and drop down menus with no common structure.
Finally after you accept help from what appears to be a good samaritan and try Windows Visual Studio free trial 
and it works somewhat and then 30 days later when you are still trying to figure out how to use it effectively, they turn
around and mug you for money and steal your configuration and hold it for ransom.
The linux version works almost immediately and after wandering about in the dark running into trees that look like
solutions and turn out to be bears you happen upon a meadow where everything works and you think you are home but ...
the nagging question is: Is this some special place like a local minimum that works today at this time and will disappear 
at random and you will be left in the dark, naked and screaming that you wish you were doing something simpler, like brain surgery?

- [x] some done
- [ ] much more to do
