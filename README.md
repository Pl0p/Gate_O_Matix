
#   Gate sequencer by Plop
  *Update 17 FEB 2021*

##   64 step sequencer, 8 parts, multiple play mode, eurorack format.


###   TODO :
- #### SOFTWARE
	 - [ ] Clock multiplier/divider per part
	 - [ ] Detect clock internal/external (switching jack)
	 - [ ] Reset -> interupt
	 - [ ] Patern choice
	 - [ ] Save/Load (SD card)
	 - [x] Tempo
	 - [x] Part choice
	 - [x] Number of step
	 - [x] Pages navigation
	 - [x] Step ON-OFF
	 - [x] Play mode
	 - [x] Fill/Clear
	 - [x] Copy/Past
	 - [x] Pause/Play/Stop
	 - [x] Gate size
	 - [x] Step jump
	 - [x] Reset
	 - [x] Internal clock
  
 - #### HARDWARE
	 - [ ] Use blue pills for Master
	 - [x] Add switching jack for clock
	 - [ ] Add SD card
	 - [ ] 12v alimentation
	 - [ ] Buffered output
	 - [x] Screen driver
	 - [x] LED driver
	 - [x] Key matrix
      
- ####     SCHEMATIC & PCB
	 - [ ] Resistor value for LED & screen
	 - [x] Routing Main_Board
	 - [ ] Drawing CPU_Board
	 - [ ] Drawing Output_Board



##   FUNCTIONS :
#### Buttons  :
	-  Step on/off
	-  Shift + step button = step jump
	-  Fill
	-  Fill + shift = Clear
	-  Copy/Paste
	-  Copy/Paste + shift = Save
	-  Pause/Play
	-  Pause/Play + shift = Stop
	    

#### Encoders :
	- Tempo
	- Tempo + push = clock divider
	-  Gate length
	- Gate length + push = Number of step
	- Page navigation
	- Page navigation + push = Play mode
	  
#### Selecter :
	- Part choice

#### Play mode :
	- Forward
	- Backward
	- Ping Pong
	- Random
	- Brownien
