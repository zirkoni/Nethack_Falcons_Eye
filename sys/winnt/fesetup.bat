@REM  SCCS Id: @(#)fesetup.bat    2001/05/24                
@REM  Copyright (c) NetHack PC Development Team 1993, 1996
@REM  NetHack may be freely redistributed.  See license for details. 
@REM  Win32 setup batch file for Falcon's Eye, see Install.nt 
@REM  for details
@REM
@echo off
echo Checking to see if directories are set up properly
if not exist ..\..\include\hack.h goto err_dir
if not exist ..\..\src\hack.c goto err_dir
if not exist ..\..\dat\wizard.des goto err_dir
if not exist ..\..\util\makedefs.c goto err_dir
if not exist ..\..\sys\winnt\winnt.c goto err_dir
if not exist ..\..\win\jtp\jtp_win.c goto err_dir
if not exist ..\..\win\jtp\gamedata\nethack.ico goto err_dir
if not exist ..\..\win\jtp\gamedata\config\jtp_opts.txt goto err_dir
if not exist ..\..\win\jtp\gamedata\graphics\jtp_nh_1.pcx goto err_dir
if not exist ..\..\win\jtp\gamedata\sound\nethack.mid goto err_dir
echo Directories look ok.

:do_rest
echo "Copying Makefile.mgw to ..\..\src\Makefile"
copy Makefile.mgw ..\..\src\Makefile >nul
echo Makefile copied ok.
echo Done!
echo Proceed with the next step documented in Install.nt
goto done

:err_dir
echo Your directories are not set up properly, please re-read the
echo documentation.
goto done
:done
