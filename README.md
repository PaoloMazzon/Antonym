Antonym
=======
Antonym is a 2D twin-stick arena shooter with a focus on ridiculous weaponry.

Building
========
Clone this repo and all of its submodules then use `CMakeLists.txt` to generate your
build system. To update the assets run the command

    JamUtil/GenHeader.py "-o=include/Nym/Assets.h" "-dir=data" -recursive "-map=data/Sprites.ini" -var=ASSETS -struct=NymAssets

On a terminal with Python 3+ installed. 