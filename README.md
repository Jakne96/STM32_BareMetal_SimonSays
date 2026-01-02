# STM32_BareMetal_SimonSays
Game of Simon Says made on STM32F401RE Nucleo Board.
It generates the sequence to repeat, uses 4 LEDs for signaling and 4 buttons to control.

**Game loop:**
Game welcomes you with all LEDs turning up a few times, then it shows you sequence of 4 moves to repeat, if you're correct, next sequence will be generated with additional step added.
If you make mistake, all LEDs will shine and new sequence will be generated, returning to the first level(4 diodes)
If you pass the sequence 3 times, congratulations! You won the game, it will reset to 4 steps again.
I implemented distinct lighting sequences to inform the player if he passed the level, made mistake or won the whole game.

**Purpose**
This project was made to make me more comfortable around baremetal programming and to practice code organisation.
I used STM32CubeIDE, but without HAL or CubeMX
Used delay is primitive and it blocks the CPU, but is appropriate for this project. 
My next step would be to design delay based on timer.

**How to make:**
If you have STM32F401RE Nucleo, you should just import the project files, connect the LEDs with resistors, and buttons and it should work.

**If you want to use another STM32 MCU:**
Create STM32 Project in STM32CubeIDE, choose your MCU, Targeted project type to empty. Then you need to download and include the chip_headers folders for the MCU, for example here is a library for F401 which I used: https://github.com/nmanhas2/LIBRARIES_STM32F401

**Pinout:**
I used PC0-3 as input for the buttons
PC4-7 were used for LEDs

**Below is the video of the game:**(work in progress)
