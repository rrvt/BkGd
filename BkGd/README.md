# BkGd -- Screen Background

Windows provides for an application to place pictures on the screen as a background.
Their in house version of a slide show will only place pictures on the background from
one directory. Furthermore there does not seem to be a way to determine the path to the
current picture on the screen.

BkGd attempts to extend the capability of the wallpaper background slide show by providing
these services:

  o Initiates during the login of a user
  o Uses every picture file in a tree of directories given by a single root directory specified by the user
  o Allows the user to discover the path to the current picture
  o Allows the user to specify the interval between changing the background picutre (n minutes)
  o Allows the user to specify that the pictures are selected randomly or linerly
  o Allows the user to halt the changing of the wallpaper

The interval and picture directory may be changed at any time. The pictures are
randomly or linerly selected.

## Getting Started

This version was created with Visual Studion 2022 (VS22).  It was compiled with the following properties:
  o Windows SDK Version: 10.0.xxxxx (latest)
  o Platfor Toolset: visual Studio 2022
  o MFC: Use MFC in a Shared DLL
  o Character Set:  Use Unicode Character Set
  o Precompiled Header:  Not Using Precompiled Headers
  o Linker/Additional Dependencies:  Htmlhelp.lib

The HTML Help Workshop (HHW), Version 4.74.8702.0 (the last one produced) was used to prepare the help
file (WixApp.chm).  It is
copied into the Release directory.  I used Dreamweaver (DW) to do most of the content production of the
help files that the HTML Help Workshop produces (i.e. HHW is used to produce the pages/files needed
and DW is used to fill in the content).

Wix is used to create the &lt;AppName&gt;.msi file.  WixApp (one of my applications, see git) was used
to produce the product.wxs file.

Note:  In order to avoid hickups during the compilation/link process make sure the VS22 dependencies are
set so the projects are produced in the proper order.

## Prerequisites

Windows 11 or above.  visual Studio 2022 or above.  The WiX Toolset must be installed in Visual Studio.
The "HTML Help Workshop" (google it) must be installed on the PC.

### Installing

## Authors

Robert R. Van Tuyl

Contact:  romeo romeo victor tango alpha tango sam whisky delta echo dot charlie oscar mike

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

