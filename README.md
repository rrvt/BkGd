# BkGd -- Screen Background

Windows provides for an application to place pictures on the screen as a background.
Their in house version of a slide show will only place pictures on the background from
one directory. Furthermore there does not seem to be a way to determine the path to the
current picture on the screen.

BkGd attempts to extend the capability of the wallpaper background slide show by providing
these services:

  - Initiates during the login of a user when enabled
  - Uses every picture file in a tree of directories given by a single root directory specified by the user
  - Allows the user to discover the path to the current picture
  - Allows the user to specify the interval between changing the background picutre (n minutes)
  - Allows the user to specify that the pictures are selected randomly or linerly
  - Allows the user to halt the changing of the wallpaper

The interval and picture directory may be changed at any time. The pictures are
randomly or linerly selected.

## Installing

Install the applications using the msi file.  However there are two additional steps.

Step 1 is to use the Windows Settings to allow a background picture to be used as wallpaper.
The procedure is something like this:

  - Select "Settings"
  - Select "Personalization"
  - Select "Background"
  - Select "Picture" in the "Personalize your background" drop down menu
  - Select "Fit" in the "Choose a fit for your desktop image" drop down menu

Step 2 is to enable the Wallpaper Changer, BkGdEx.  Here are those steps:

  - Start BkGd application
  - Select the "Tool" drop down menu
  - Select the "Enable Wallpaper Process" menu item
  - Select the "Tree" toolbar command (cascade green squares) or the "File/Select Root Path"
  - A Choose Directory Dialog Box will appear.  Select a directory containing pictures
  - Select the interval button on the toolbar (a clock face with a curved arrow).  Supply the
number of minutes between changes
  - Select the mode button next to the interval button.  Press it twice to see what happens.  Leave it
the way you want it.

Enabling the wallpaper changer process and choosing the root path need only be done once.  The other
options may be done as desired by the user...

## Getting Started

This version was created with Visual Studion 2022 (VS22).  It was compiled with the following properties:
  - Windows SDK Version: 10.0.xxxxx (latest)
  - Platfor Toolset: visual Studio 2022
  - MFC: Use MFC in a Shared DLL
  - Character Set:  Use Unicode Character Set
  - Precompiled Header:  Not Using Precompiled Headers
  - Linker/Additional Dependencies:  Htmlhelp.lib

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

## Updates

### Update 9/5/22

Corrected the initialization logic.  Added logic to ensure that all pictures are seen before showing a
picture twice.

### Update 8/23/22

Add logic so that two users on the same machine may have different wallpaper changers running at the same
time.  Added logic to disable the wallpaper changer should that be desired.  Initial state is disabled.

## Authors

Robert R. Van Tuyl

Contact:  romeo romeo victor tango alpha tango sam whisky delta echo dot charlie oscar mike

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

