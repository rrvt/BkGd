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

Install the applications using the msi file.  However there are three additional steps.

This application is not "digitally signed" which makes it subject to being rejected by any and perhaps
all virus checkers.  In particular Norton Security scans it an rejects it.  It must be given an
exception.  Here are some steps that work in Norton Security:

  - Open Norton Security
  - Select Settings in Device Security
  - Select "Antivirus" Setting
  - Select "Scans and Risks" Tab
  - Under Title "Exclusions/Low Risks" select "Items to Exclude from Scans" configure
  - Choose "Add Files" Button
  - Using the Open Folder button find "Program Files (x89)BkGd/BkGdEx.exe"
  - Select the OK button.

This should allow the startup executable to start when a person logs into the system.  Other virus
protecting software will need to be suitably changed to exclude BkGdEx.exe.  Good Luck.

Step 2 is to use the Windows Settings to allow a background picture to be used as wallpaper.
The procedure is something like this:

  - Select "Settings"
  - Select "Personalization"
  - Select "Background"
  - Select "Picture" in the "Personalize your background" drop down menu
  - Select "Fit" in the "Choose a fit for your desktop image" drop down menu

Step 3 is to enable the Wallpaper Changer, BkGdEx.  Here are those steps:

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

### Update 6/22/24

Added an icon to the MIT License rtf file.

### Update 6/13/24

Update WinPos.

### Update 4/17/24 & 4/18/24

Improved the way Toolbars and Window Position and size are handled.

### Update 3/12/24

Added more output to BkGd window for most commands.  Added count of pictures used for background.  Added
index of current picture.  Added maximum number of hits before finding an un-displayed picture in current
incarnation of BkGd background app.

### Update 2/16/24

Reorganized the Library so that it compiles once into Debug and Release directories under the Library
directory.

### Update 12/11/23

Improve (modify) ExpandableP and associated changes.

### Update 6/25/23

Library Update.

### Update 3/31/23

Added Report Orientation Dialog to App.

### Update 3/15/23

Complete move of orientation to reports.

### Update 3/13/23

When there are multiple reports the printed output orientation is by report, not the printer.  Thus the
orientation is associated with the report and the standard Options dialog contains the orientation for the
NotePad Report.  Other reports will need a way to designate the printer output orietation.

The NotePad output managers have been moved into CScrView so that it is available in all applications
without further development.  Of course other reports may be written following the pattern of the NotePad
report.

Some additional bug fixes.

### Update 3/8/23

Added numbers to notepad archive output.

### Update 3/7/23

Fixed (hopefully) Print and Print Preview.  See MakeApp for details.

### Update 10/30/22

Start app at the same position and size as when the app last exited.  Update the background of the
toolbar.  Update the help file icons.

### Update 9/14/22

Added a little logic to copy information on the window into the clip board.  Here are the steps:

  - The line is divided by tabs.
  - The mouse cursor is placed on a line after a tab.
  - When the left mouse button is pressed the part of the line from the tab to the end of the line is
selected and highlighted.
  - There are several ways to copy the selected text into the clip board:
    * Press Ctrl-C
    * Instead of a single press, double click the left mouse button
    * Use the Menu/Edit/Copy Command
    * Press the right mouse button and select the Copy Command in the popup menu

### Update 9/10/22

Changed the Icon name in WixApp so that the startup executable is represented in the Win11
Settings/App/Startup nicely.

### Update 9/6/22

Add command to display the next wallpaper image.

### Update 9/5/22

Corrected the initialization logic.  Added logic to ensure that all pictures are seen before showing a
picture twice.  Keeps track of the current and last picture.  The Get Current Path returns both paths
and puts it in the clip board.

### Update 8/23/22

Add logic so that two users on the same machine may have different wallpaper changers running at the same
time.  Added logic to disable the wallpaper changer should that be desired.  Initial state is disabled.

## Authors

Robert R. Van Tuyl

Contact:  romeo romeo victor tango alpha tango sam whisky delta echo dot charlie oscar mike

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

