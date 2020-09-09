# Speedrun Tools (version 1.0)

Speedrun Tools is a [Bakkes Mod Plugin](https://bakkesplugins.com/) aimed at making speedrunning easier.

## How to open the in-game menu

Press `F9` while in game. If that doesn't work try one of the following:

* Open the console and type `toggle menu speedruntools`
  * You can also bind this command to a key in the console `bind F9 "toggle menu speedruntools"`
* Open it through the settings window at `Bakkesmod settings (F2)` -> `Plugins` -> `Speedrun Tools`

## Toolkits

**Mutators Toolkit** allows the setting of custom mutators for custom run categories.

Boost mutator

* `speedrun_mutator_car_boost`
  * `0` - Off
  * `1` - Zero Boost
  * `2` - Unlimited Boost
  
* `speedrun_mutator_car_autoairroll`
  * `0` - Off
  * `1` - Disable Air Roll
  * `2` - Auto Air Roll Left
  * `3` - Auto Air Roll Right
  
* `speedrun_mutator_game_gravity`
    * `float` - Set the current game gravity
  
* `speedrun_mutator_game_speed`
    * `float` - Set the current game speed
    
**Save States Toolkit** allows the saving of the current game state to be loaded back or rewound for practice.

* `speedrun_savestate_rewind` - Rewind the game state back in time

* `speedrun_savestate_rewindlength`
  * `float` - Length of the rewind
  
* `speedrun_savestate_rewindsaveinterval`
  * `float` - How frequently the game state is recorded for rewinding
  
* `speedrun_savestate_save` - Save the current game state

* `speedrun_savestate_load` - Load the previously saved game state

**Analysis Toolkit** allows for viewing important stats about the current game state.

**LiveSplit Toolkit** allows for interaction with LiveSplit and the ability to enable auto splitter.

* `speedrun_livesplit_connect` - Try to connect to the LiveSplit Server
* `speedrun_livesplit_disconnect` - Disconnect from the LiveSplit Server
* `speedrun_livesplit_startorsplit` - Start or split the timer
* `speedrun_livesplit_start` - Start the timer
* `speedrun_livesplit_pause` - Pause the timer
* `speedrun_livesplit_resume` - Resume the timer
* `speedrun_livesplit_reset` -  Reset the timer
* `speedrun_livesplit_split` - Split the timer
* `speedrun_livepslit_skipsplit` - Skip the next split
* `speedrun_livesplit_unodsplit` - Undo the previous split

**LiveSplit Toolkit** allows for viewing the kismet sequence variables (useful in workshop maps).

* `speedrun_kismet_list` - Log the sequence vars to the console
