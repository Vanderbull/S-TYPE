; ///////////////////////////////////////////////////////////
; // Graphical Installer for Inno Setup                    //
; // Version 3.5.01 (Mirka)                            //
; // Copyright (c) 2011 - 2015 unSigned Softworks          //
; // http://www.graphical-installer.com                    //
; // info@unsigned-softworks.sk                            //
; // All rights reserved.                                  //
; ///////////////////////////////////////////////////////////
 
; *********************************************
; * This file contains setting for graphical  *
; * interface. Modify them freerly.           *
; ********************************************* 
 
; Script generated with Graphical Installer Wizard.
 
; UI file for Graphical Installer
#define public GraphicalInstallerUI "GraphicalInstallerUI"
 
; Texts colors
#define public TextsColor    "$FFFFFF"
#define public HeadersColor  "$FFFFFF"
#define public InversedColor "$FFFFFF"
 
; Buttons colors
#define public ButtonNormalColor   "$000000"
#define public ButtonFocusedColor  "$000000"
#define public ButtonPressedColor  "$000000"
#define public ButtonDisabledColor "$000000"
 
; Images - all files must be in the same directory as this .iss file!
#define public TopPicture    "369480-top-top.jpg"    ; 690x416 px
#define public InnerPicture  "369480-top-inner.jpg"  ; 413x237 px
#define public BottomPicture "369480-top-bottom.jpg" ; 690x83 px
#define public ButtonPicture "360_controller_svg.png" ; 80x136 px
 
; File with core functions and procedures
#include "compiler:Graphical Installer\GraphicalInstaller_functions.iss"
  
[Files]
; Pictures with skin 
Source: {#TopPicture};    Flags: dontcopy;
Source: {#InnerPicture};  Flags: dontcopy;
Source: {#BottomPicture}; Flags: dontcopy;
Source: {#ButtonPicture}; Flags: dontcopy;
; DLLs
Source: compiler:Graphical Installer\InnoCallback.dll; Flags: dontcopy;
Source: compiler:Graphical Installer\botva2.dll;       Flags: dontcopy;
 
; End of file (EOF)
