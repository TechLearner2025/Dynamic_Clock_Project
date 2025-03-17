# Dynamic Clock on Seven Segment Display (SSD)

## Project Description
This project implements a dynamic (configurable) digital clock using a seven-segment display (SSD) controlled by an internal timer. The clock operates in both **Run Mode** and **Configuration Mode** as per user inputs.

## Features
- **24-Hour Format Clock:** Displays time in `HH.MM` format.
- **Blinking Decimal Point:** The decimal point of the hour's one's place blinks at a rate of `0.5 Hz` (every `500 ms`) in run mode.
- **Configuration Mode:**
  - Activated via a **Set/Edit Key (DKS4)**.
  - Allows switching between hour and minute adjustment via a **Choose Field Key (DKS3)**.
  - The selected field blinks at a rate of `0.5 Hz` to indicate selection.
  - Increment/Decrement values using **Increment Key (DKS1)** and **Decrement Key (DKS2)** respectively.
- **Run Mode:** Once the configuration is complete, pressing the **Set/Edit Key (DKS4)** starts the clock, resuming normal operation.
- **Time Initialization:** Clock starts from `00.00` upon power-on or reset.

## Inputs
1. **DKS1 (Increment Key):** Increments the selected field (hours or minutes).
2. **DKS2 (Decrement Key):** Decrements the selected field.
3. **DKS3 (Choose Field Key):** Toggles between hour and minute selection.
4. **DKS4 (Set/Edit Key):** Switches between configuration and run mode.

## Output
- Displays time on a four-digit SSD in `HH.MM` format.
- Blinking decimal point and digits as per the current mode.

## File Structure
- **Main Code File:** Implements the clock logic, interrupt handling, SSD display functions, and input processing.

## Requirements
- Microcontroller configured to use an internal timer (Timer0).
- Seven-segment display connected to the microcontroller.
- Push-buttons or digital switches as inputs for time setting and editing.

## Compilation and Usage
1. Compile the code using a compatible compiler (e.g., MPLAB XC8 for PIC microcontrollers).
2. Load the compiled code onto the microcontroller.
3. Power on the board and observe the clock starting from `00.00`.

## Future Improvements
- Adding support for external timers or real-time clocks (RTCs).
- Enhancing input handling with debouncing mechanisms.

