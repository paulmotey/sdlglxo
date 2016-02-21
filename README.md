Changes in this version (0.51) 2-20-2016
added SDL2 sound,mouse handler,keys and started separating headers and modules plus the usual typo-allergenic problems

Fixed lots of interesting bugs and now the rest of the code can be ported easily. It is about a million lines of code and so the next big push will be a complete application.

Changes in this version (0.4) 2-17-2016
tested 3D BOX, lines, points, textured quads 
Included diagnostic to console to view PERSPECTIVE matrix
Oddly the Linux version has a different matrix when context is created
Also the texture copy feature operates differently and changes blend characteristics

Changes in this version (0.3) 2-16-2016
Added ttf (true type font) text as texture
Added **SDL2_ttf** as library for Linux or TTF does not work properly

##STAGE 1

This a fully functional SDL on Windows 10

It is also fully functional on Linux

##STAGE 2

###WEB page added for all projects

http://paulmotey.github.io/

- [x] Move includes to header file
- [x] Separate OPENGL graphics to a module (graphics)
- [x] Create a keyboard command interface for modes
- [ ] Create WebGL and Application personalities
- [x] Create mouse command interface
- [ ] Port modules for buttons and menus
- [ ] Port all test modules
- [ ] Identify capabilities and operate within them
- [ ] Use international language interface

###QUESTIONS
- [x] can markdown be converted to HTML **YES pandoc -f markdown_github x.md > x.html**
- [X] can assimp operate in Windows OS? **YES**
- [ ] how does QT work across platforms
- [x] what fonts are available
- [x] how to open sound interfaces
- [ ] how to open camera interfaces
- [ ] signal fault handler and debug
- [ ] opencv
- [ ] python
- [ ] language detection 

##STAGE 3

- [ ] 3D to matter interface for printers
- [ ] 4D to action interface for printers
- [ ] AI integration
- [ ] Temporal engineering code


##Windows only problems

It is bizarre that the **BSD** still exists in Windows 10

It is a symptom of a poorly designed OS. You would think that all that money they made that at least 1% would be put to improving the design to a point that it was a **REAL** operating system and not an accident waiting to happen.
 

This uses MinGW

Should show a rotating image

However the screen position could be odd for other configurations

So... YMMV

This may have been more complicated than it should have been as I dived into this without taking a stepwise approach to the new complexities.
What is new is:


1. Windows 10 and the strange locations of files
2. SDL2 on Windows
3. OpenGL on Windows
4. Eclipse
5. Visual Studio
6. Git bash
7. github
8. cygwin
9. c++ on Windows
10. Windows GUI
11. MinGW
12. SSH and keys
13. markdown
14. and all the strange interactions
15. Notepad ++ (GREAT PROGRAM) I recommend this
16. Odd Windows location of configuration for almost everything
17. **pandoc** is very handy for markdown to html or other formats
18. Still learning new uses of pandoc and markdown


| example | how to |
| ---|---:|
|__underscore?__ |__|
|_underscore?_ |_|
|*italics*      |*|
|**bold**       |**|
|--strikethrough?-- |--|


This CSS *could* be added to enhance pandoc to html

```
<style type="text/css">
table {
    margin-left: auto;
    margin-right: auto;
    margin-bottom: 24px;
    border-spacing: 0;
    border-bottom: 2px solid black;
    border-top: 2px solid black;
}
table th {
    padding: 3px 10px;
    background-color: white;
    border-top: none;
    border-left: none;
    border-right: none;
    border-bottom: 1px solid black;
}
table td {
    padding: 3px 10px;
    border-top: none;
    border-left: none;
    border-bottom: none;
    border-right: none;
}
</style>
```

As a result I have learned a lot, but it has been very confusing to have so many things to learn at once when I am familiar with Linux and the available tools that do not translate perfectly to pseudo Linux development mode.
So it was a very painful week and then a month before I could look at it again and fix all the messes that came with the confusion.
It now runs and compiles on both platforms consistently and this is the core that I needed to transport a very large OpenGL code base from Linux to be a cross platform utility that could run as an application on Android, WebGL, and as a stand alone program on Linux and Windows.

|  | Windows 10 | Linux | 
| :---: |:---: | :---: |
| status | *working*  | *working* |
| branch | *linuxsdl*  | *master* |

This program uses SDL2 libraries and shows RGB solid colors and then a rotating image, 
It uses MinGW to compile with Eclipse, make on Windows is broken because of 
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
The Linux version works almost immediately and after wandering about in the dark running into trees that look like
solutions and turn out to be bears you happen upon a meadow where everything works and you think you are home but ...
the obvious question is: Is this some special place like a local minimum that works today at this time and will disappear 
at random and you will be left in the dark, naked and screaming that you wish you were doing something simpler, like brain surgery?

- [x] some done
- [ ] much more to do
