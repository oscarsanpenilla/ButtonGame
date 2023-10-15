# Guess the Secret Password Game
## Overview
This repository contains an implementation of a **console game** in which the user has to guess a sequence of three button presses.
The sequence can contain any combination, e.g. BAC, CCB, AAA.
The LEDs should always represent the result of the last 3 button presses.
* LED 3 will always represent the most recent button event
* LED 2 the one before that
* LED 1 the one before that

**Red** indicates that the button pressed was wrong for this position, and does not appear in a different position.
**Orange** indicates that the button pressed was wrong for this position, but it does appear in a different position.
**Green** indicates that the button pressed was correct for this position.

The button sequence is randomly generated on system start-up.

### How to win?
After 3 successful button inputs the player wins and another random sequence is generated.


## Dependencies
* GTest (optional)
```bash
sudo apt install libgtest-dev
```
* Cmake 3.10 or greater
```bash
sudo apt install cmake
```
* Ensure that you have all the required compilers and tools installed. You can install the build essential package on Debian-based systems to ensure this:
```
sudo apt install build-essential
```

## Build
Open a bash terminal and run the following commands
```bash
git clone https://github.com/oscarsanpenilla/ButtonGame
mkdir -p /path/to/ButtonGame/build
cd /path/to/ButtonGame/build
cmake ..
make
```
## Run
Make sure you are still in the build directory `cd /path/to/ButtonGame/build`

To play the game
```bash
./buttonGame
```

To run the tests
```bash
./game_tests
```

---
# Test Plan and Results
### 1. ButtonsGame Initialization (ButtonsGame, init)
- **Objective:** Validate that all LEDs are OFF upon game initialization.
- **Test Steps:**
   1. Instantiate `ButtonsGameImpl`.
   2. Retrieve the LED states.
   3. Check that all LEDs are OFF.
- **Expected Result:** All LEDs should be OFF.
- **Status:** PASS

### 2. Valid Button Press (ButtonsGame, onButtonPressValid)
- **Objective:** Ensure the game handles valid and invalid button presses appropriately.
- **Test Steps:**
   1. Press buttons 'A', 'B', and 'C'.
   2. Attempt to press an invalid button 'Z'.
   3. Catch and assert the expected error.
- **Expected Result:** Game should accept valid buttons and throw an error on invalid button press.
- **Status:** PASS

### 3. Single Press (ButtonsGame, singlePress)
- **Objective:** Test the game’s response to a single button press.
- **Test Steps and Expected Results:**
   - Press 'A', LED3 should be GREEN.
   - Press 'B', LED3 should be ORANGE.
   - Press 'B' in a password of "AAA", LED3 should be RED.
- **Expected Result:** Only one LED should be one with the corresponding color
- **Status:** PASS

### 4. Double Press (ButtonsGame, doublePress)
- **Objective:** Test the game’s response to two sequential button presses.
- **Test Steps and Expected Results:**
   - Press 'A' then 'B', LED2 and LED3 should both be GREEN.
   - Press 'A' twice, LED2 should be GREEN and LED3 should be ORANGE.
   - Press 'C' then 'B', LED2 should be ORANGE and LED3 should be GREEN.
   - Press 'C' then 'A' in a game with a password of "AAA", LED2 should be RED and LED3 should be GREEN.
- **Status:** PASS

### 5. Triple Press (ButtonsGame, triplePress)
- **Objective:** Test the game’s response to three sequential button presses.
- **Test Steps and Expected Results:**
   - Press 'A', 'B', then another 'B', LED1 should be GREEN, LED2 should be GREEN, and LED3 should be ORANGE.
   - Press 'A' three times, all LEDs should be ORANGE.
   - Press 'A', 'B', then 'C', all LEDs should be GREEN.
   - Press 'C', 'A', then 'B' in a game with a password of "AAA", LED1 should be RED, LED2 should be GREEN, and LED3 should be RED.
- **Status:** PASS

### 6. Win Condition (ButtonsGame, treeGreenWin)
- **Objective:** Validate that the user wins upon illuminating three green lights.
- **Test Steps:**
   1. Press 'A' three times to light up three green LEDs.
   2. Assert that the user has won.
   3. Reset the game.
   4. Press 'B' then 'A' twice.
   5. Assert that the user has not won.
   6. Press 'A' to light up the third green LED and assert the win.
- **Expected Result:** The user should win upon getting three green lights.
- **Status:** PASS

## Test Execution and Results
- **Execution Date:** 2023-10-15
- **Executed by:** Oscar Sandoval

### Summary of Results
- **Total Test Cases:** 6
- **Passed:** 6
- **Failed:** 0

