# PrisonGame [Work in progress]

Download with: `git clone https://github.com/ThomasWilliamWallace/PrisonGame.git --recursive`

The `--recursive` flag is required to download the git submodules.

Three parts:
* Source/HardTime2 is the main game world and is opened using the `HardTime2.uproject` unreal engine file.
* Source/hardtime_textworld is a text based game world used for testing the AI, and is opened with the `Hardtime_split.workspace` codelite IDE file.
* Source/htn_planner is the AI planner engine, and is a git submodule copied in from https://github.com/ThomasWilliamWallace/htn_planner.

![Planner in use in Unreal game engine- plan is displayed at top of screen.](Plan_unreal_screenshot.PNG)
