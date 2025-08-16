# Simpler design
Original plan: 1 master enum, all connections for a mode defined by 1 enum
Cons:
* Can't define what "type" of mode this is


## Simpler state machine
* No concept of mode "types"
* Only ability:
    * Set newMode, nextModeSuccess, nextModeFailure
