# Speedrun Tools

Speedrun Tools is a [Bakkes Mod Plugin](https://bakkesplugins.com/) aimed at making speedrunning easier and more efficient. The following tools will
only work in freeplay and workshop runs.

## Download

Required Downloads
* [BakkesMod](https://bakkesmod.com/download.php) (if you don't have it already)
* [Speedrun Tools Plugin](https://bakkesplugins.com/plugins/view/165)
  
Needed to use LiveSplit Tools
* [LiveSplit](https://livesplit.org/) (timing software)
* [LiveSplit Server](https://github.com/LiveSplit/LiveSplit.Server) (how this plugin talks to LiveSplit)

## Features

* LiveSplit Client
    * Connect to and control LiveSplit
    * Auto splitters for:
        * Tutorial Basic
        * Tutorial Advanced
        * Panic's Air Race Beach
        * Leth's Giant Rings
        * Air Dribble Hoops
        * Speed Jump Rings 1
* Custom mutators including
    * Auto airroll left, auto airroll right, disabled airroll
    * Unlimited boost, zero boost
    * Custom gravity
    * Custom game speed
* Save state mimics, including
    * Game save states
    * Game state rewind
* Kismet Sequence Variable Editor
    * View and edit kismet variables

## How to Open the In-game Menu

* Open the BakkesMod console and type `toggle menu speedruntools`
    * You can also bind this command to a key by typing `bind F9 "toggle menu speedruntools"`
* Open it through the settings window at `Bakkesmod settings (F2)` -> `Plugins` -> `Speedrun Tools`

## Console Variables (CVars) and Commands

The following CVars and Commands are best used through the in-game menu. They can also be accessed through the BakkesMod console.

**LiveSplit Client**

* `speedrun_livesplit_connect` (command): Try to connect to the LiveSplit Server
* `speedrun_livesplit_disconnect` (command): Disconnect from the LiveSplit Server
* `speedrun_livesplit_startorsplit` (command): Start or splitTimer the timer
* `speedrun_livesplit_start` (command): Start the timer
* `speedrun_livesplit_pause` (command): Pause the timer
* `speedrun_livesplit_resume` (command): Resume the timer
* `speedrun_livesplit_reset` (command):  Reset the timer
* `speedrun_livesplit_split` (command): Split the timer
* `speedrun_livepslit_skipsplit` (command): Skip the next splitTimer
* `speedrun_livesplit_unodsplit` (command): Undo the previous splitTimer

**Mutators**

* `speedrun_mutators_car_boost` (cvar): The local car's boost mutator
    * `0` - Off
    * `1` - Zero Boost
    * `2` - Unlimited Boost

* `speedrun_mutators_car_airroll` (cvar): The local car's air roll mutator
    * `0` - Off
    * `1` - Disable Air Roll
    * `2` - Auto Air Roll Left
    * `3` - Auto Air Roll Right

* `speedrun_mutators_game_gravity` (cvar): The current game gravity
    * `float`

* `speedrun_mutators_game_speed` (cvar): The current game speed
    * `float`

**Save States**

* `speedrun_savestates_save` (command): Saves the current game state

* `speedrun_savestates_load` (command): Loads the previously saved game state

* `speedrun_savestates_rewind` (command): Rewinds the game back in time

* `speedrun_savestates_rewindlength` (cvar): The amount of time that the game will be rewound
    * `float`

* `speedrun_savestates_rewindsaveinterval` (cvar): The frequency that the game state is recorded for rewinding
    * `float`
    