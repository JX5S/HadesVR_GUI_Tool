# HadesVR Tool

This is a companion project to [HadesVR](https://github.com/HadesVR/HadesVR/), an open source SteamVR driver for DIY VR headsets. HadesVR is normally configured by modifying a json file in a text editor, this tool is a more user-friendly GUI for the same parameters.

# Main features

There are several annoying values to find which this tool aims to simplify. Namely:
- There is a button to open SteamVR's driver folder
- It checks if the driver is in the correct folder
- Device selection is done by simply choosing from a list
- Screen selection is done by simply choosing from a list
All other settings are also present

# Compiling
It has been tested with mingw-64 and QT6.7. Currently compiler choice shouldn't matter. I compiled it using QT Creator. Compiling for Linux doesn't make sense, since HadesVR is windows-only.

# Known bugs
- Darkmode icons load on Windows 10 when darkmode is selected

# Testing
There is a button to choose the settings file manually. You can select any file with the right .vrsettings file extension and it'll overwrite it with the right JSON file on saving.
