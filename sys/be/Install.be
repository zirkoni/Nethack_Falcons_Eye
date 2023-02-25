            Instructions for installing the BeOS version of
                        NetHack - Falcon's Eye
            (NetHack 3.3.1 with the Falcon's Eye interface)
                =======================================

Please read this file before starting to install NetHack - 
Falcon's Eye on your BeOS system.

For help on playing NetHack with the Falcon's Eye interface, open 
the game manual (win/jtp/gamedata/manual/index.html) in a web 
browser.

Preliminaries
---------------
1.  Make sure all the NetHack files are in the appropriate directory
    structure.  You should have a main directory with subdirectories
    dat, doc, include, src, util, sys/share, sys/be, win/tty, and 
    win/jtp.  You may have other subdirectories under sys and win, 
    but they will not affect compilation for a BeOS system.  

    For a detailed explanation of the directory structure, see 
    'Files' in the top directory.

2.  You need the BeOS development tools (gcc), as well as version 
    1.2 of the SDL libraries. Download and install them if you don't 
    have them yet.

Compiling
----------------
3.  Your Makefiles may still be in sys/be with tags on the end of 
    them. If so, run setup.sh in that directory to distribute the 
    Makefiles to their proper places. 

4.  Go to the include subdirectory and edit config.h according to 
    the comments to match your system and desired set of features.  
    Similarly edit unixconf.h.  Please see the "Notes:" section, 
    below, for some configuration hints for particular systems.

    If you want, you can also look at system.h and topten.c in the 
    src subdirectory. You don't need to, however. 

Installing
----------------
4.  First, edit the top sections of the src and util Makefiles.  
    Then type 'touch makedefs.c' to make sure certain files get 
    remade. After that, type 'make' in src and go get a cup of 
    coffee or take a nap, depending on the speed of your system. 
    You should now have created the game executable.

7.  Go back to the top directory and edit that Makefile, explaining 
    where you want everything to be installed.

    Make sure that you follow the comments about setting GAMEDIR -- 
    any files under it will be considered debris and deleted. If you 
    want to spare them, install the game somewhere else, or comment 
    out the rm under the install target.

    In the makefile, there are commands CHOWN and CHGRP. They're 
    currently set to 'true', since BeOS doesn't really have groups.    

    Type 'make all' from the top directory to set up all the 
    auxiliary files the main executable will use.  Then type 
    'make install'. The game files will now be copied to the 
    subdirectory 'compiled'.

Configuring
-----------------
8.  Everything should now be set. The 'compiled' subdirectory 
    contains a complete installation of NetHack - Falcon's Eye. 
    The BeOS version supports all the game features, except
    for sound and music, which will be added in a later version.

    Please look at 'jtp_opts.txt' in the 'config' subdirectory. It
    has many important options that you can customize, like
    the game's graphics resolution.

    Read doc/recover.man or doc/recover.txt, and think about whether 
    and how you want to install the recover program. If you decide 
    to install it, type 'make recover' in the util directory and then 
    install recover by hand in your desired manner.

Notes
----------------
About lex/yacc:
    If your system does not have a lex/yacc or flex/bison combination
    capable of producing the dungeon and level compilers, lex and 
    yacc output from one of our development systems can be found in 
    sys/share.

    Unfortunately, this output is less portable than the rest of the 
    code, as it contains skeleton parsing code provided by the 
    specific vendor who has no particular incentive to make such 
    skeletons portable, but the output works on most systems. To try 
    it on yours, copy dgn_comp.h and lev_comp.h to include and 
    dgn_lex.c, dgn_yacc.c, lev_lex.c, and lev_yacc.c to util.

About this documentation:    
    This documentation is partly copied from the Unix install 
    documentation (sys/unix/Install.unx). It contains more notes on 
    various system-specific options, so if you get strange errors 
    or odd in-game behaviour, check the notes in the Unix 
    documentation.

If you have trouble compiling: 
    If you still have problems compiling, you can contact me 
    (Jaakko Peltonen, developer of Falcon's Eye) by e-mail me at 
    jaakko.peltonen@hut.fi .


