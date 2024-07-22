## Whack-A-Mole Arduino Game

This project is a single-player "Whack-A-Mole" game implemented using an Arduino. The game features four colored LEDs and four pushbuttons, with a serial monitor to display the current score and other game information. The game consists of consecutive rounds, where the player must press the button corresponding to the LED that lights up.

### Features
- **Start Button:** Initiates the game.
- **LEDs:** Four LEDs light up in a random order, one at a time.
- **Pushbuttons:** Player must press the corresponding button for the lit LED within a certain time window.
- **Rounds:** Game consists of multiple rounds, with the LED ON time decreasing progressively.
- **Score Display:** Current score displayed in the serial monitor after each successful button press.
- **Timeout:** Game stops if no button is pressed within a certain time limit.

### Hardware Requirements
- Arduino board (e.g., Arduino Uno)
- 4 LEDs (Red, Yellow, Blue, Green)
- 4 Pushbuttons
- 5 Resistors (220 ohm or suitable for your LEDs)
- Breadboard and jumper wires

### Software Requirements
- Arduino IDE
- Tinkercad (optional, for circuit simulation)

### Circuit Diagram
Connect the components as follows:
- **LEDs:**
  - Red LED: Pin 12
  - Yellow LED: Pin 11
  - Blue LED: Pin 10
  - Green LED: Pin 9
- **Pushbuttons:**
  - Red Button: Pin 7
  - Yellow Button: Pin 6
  - Blue Button: Pin 5
  - Green Button: Pin 4
  - Start Button: Pin 13

### Setup and Installation
1. **Clone the Repository:**
   ```sh
   git clone https://github.com/rowaahmed/WhackAMole.git
   cd whack-a-mole-arduino
   ```
2. **Open Arduino IDE:**
   - Open the `whack_a_mole.ino` file in the Arduino IDE.

3. **Upload the Sketch:**
   - Connect your Arduino board to your computer.
   - Select the appropriate board and port in the Arduino IDE.
   - Upload the sketch to the Arduino board.

### Game Rules
1. Press the Start button to begin the game.
2. In each round, an LED lights up randomly.
3. Press the corresponding button for the lit LED before the next LED lights up.
4. If the correct button is pressed, the LED turns off immediately, and the score is updated.
5. The game advances to the next round after all prompts are completed.

### Scoring
- Score is calculated by adding the round index to the previous score for each successful button press.
- Displayed in the Serial Monitor in the format: `Round x --- Score: y`
- Final score is displayed when the game ends.

### Timeout
- If no button is pressed within 60 seconds, the game stops, and a message "Button not pressed, game over!" is displayed.

### Bonus Features
- **Transition Between Rounds:** At the end of each successful round, all four LEDs flash in a chosen pattern.
- **Game End:** At the end of the game, LEDs flash in a different pattern.

### Contributing
Contributions are welcome! Please fork this repository and submit pull requests for any improvements or bug fixes.

### License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

Enjoy playing the Whack-A-Mole game! If you have any questions or feedback, feel free to open an issue or contact the project maintainers.
