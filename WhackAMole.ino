/* Name: Rowa Ahmed  
 * Date: December 7, 2023
 * Name:      Lab 8 - Whack a Mole      */      

// Define game parameters (Modify the numbers only)
#define NUM_PROMPTS      5    // modifies the amount of prompts per round
#define ROUNDS           5    // rounds per game
#define T_ON             1000 // the amount of time the LEDs are ON for the first round
#define K                0.98 // the constant to multiply by every successive round
#define T_OUT            10000 // the milliseconds for time out.

// Define Pins (DO NOT CHANGE)
#define LEDR 12
#define LEDY 11
#define LEDB 10
#define LEDG 9

#define PB_RED    7
#define PB_YELLOW 6
#define PB_BLUE   5
#define PB_GREEN  4
#define PB_START  13

// Function prototypes
void startGame();
void endGame();
void playRound();
void roundflashLEDs(int pattern);
void endflashLEDs(int pattern);

// Variables
int score = 0;
int round_number = 0; 
unsigned long roundstart = 0;
int T_NEW = T_ON;
int T_OFF;
int leds[] = {LEDR, LEDY, LEDB, LEDG};

// Initialization
void setup() {
  Serial.begin(9600);

  pinMode(LEDR, OUTPUT);
  pinMode(LEDY, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(LEDG, OUTPUT);

  pinMode(PB_RED, INPUT);
  pinMode(PB_YELLOW, INPUT);
  pinMode(PB_BLUE, INPUT);
  pinMode(PB_GREEN, INPUT);
  pinMode(PB_START, INPUT);
}

// Main program loop
void loop() {
  if (round_number == 0) {
    if (digitalRead(PB_START) == HIGH) {
      startGame(); 
    }
  } else {
    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - roundstart;

    if (elapsedTime > T_OUT) {
      Serial.println("Button not pressed. Game over!");
      endGame();
    } else {
      playRound();
    }
  }
}

void startGame() {
  score = 0;
  round_number = 1;
  playRound();
}

void endGame() {
  Serial.print("Game over! Final Score: ");
  Serial.println(score);
  round_number = 0; 
  
  endflashLEDs(2);
}

void playRound() {
  roundflashLEDs(2);

  Serial.print("Round  ");
  Serial.println(round_number);

  int array[] = {LEDR, LEDY, LEDB, LEDG};
  randomSeed(analogRead(0));

  int lastButtonPressed = -1; // Initialize to an invalid button

  for (int buttonpress = 0; buttonpress < NUM_PROMPTS; ++buttonpress) {
    int random_index = random(4);
    int currentLED = array[random_index];

    digitalWrite(currentLED, HIGH);

    unsigned long startTime = millis();
    roundstart = startTime;

    Serial.print("LED: ");
    Serial.println(currentLED);

    // Continue checking for button presses during the entire round
    while (millis() - roundstart < (2.0 * T_NEW)) {
      int buttonPressed = -1;

      if (digitalRead(PB_RED) == HIGH) {
        buttonPressed = PB_RED;
      } else if (digitalRead(PB_YELLOW) == HIGH) {
        buttonPressed = PB_YELLOW;
      } else if (digitalRead(PB_BLUE) == HIGH) {
        buttonPressed = PB_BLUE;
      } else if (digitalRead(PB_GREEN) == HIGH) {
        buttonPressed = PB_GREEN;
      }

      // Check for a new button press
      if (buttonPressed != -1 && buttonPressed != lastButtonPressed) {
        score += round_number;
        Serial.print("Round ");
        Serial.print(round_number);
        Serial.print(" --- Score: ");
        Serial.println(score);
        lastButtonPressed = buttonPressed;
      }
    }

    digitalWrite(currentLED, LOW);
    delay(100); // Add a small delay for visual separation
  }

  Serial.print("End of Round Score: ");
  Serial.println(score);
  round_number++;

  T_NEW = T_NEW * K;

  if (round_number > ROUNDS) {
    endGame();
  }
}


/*void playRound() {
  roundflashLEDs(2);

  Serial.print("Round  ");
  Serial.println(round_number);

  int array[] = {LEDR, LEDY, LEDB, LEDG};
  randomSeed(analogRead(0));

  int lastButtonPressed = -1; // Initialize to an invalid button

  for (int buttonpress = 0; buttonpress < NUM_PROMPTS; ++buttonpress) {
    int random_index = random(4);
    int currentLED = array[random_index]; // Check this later

    digitalWrite(currentLED, HIGH);

    unsigned long startTime = millis();
    roundstart = startTime;

 

    // Initialize to an invalid button
    int buttonPressed = -1;

    while (millis() - startTime < T_NEW) {
      if (digitalRead(PB_RED) == HIGH) {
        buttonPressed = PB_RED;
      } else if (digitalRead(PB_YELLOW) == HIGH) {
        buttonPressed = PB_YELLOW;
      } else if (digitalRead(PB_BLUE) == HIGH) {
        buttonPressed = PB_BLUE;
      } else if (digitalRead(PB_GREEN) == HIGH) {
        buttonPressed = PB_GREEN;
      }

      // Check for a new button press
      if (buttonPressed != -1 && buttonPressed != lastButtonPressed) {
        score += round_number;
        Serial.print("Round ");
        Serial.print(round_number);
        Serial.print(" --- Score: ");
        Serial.println(score);
        lastButtonPressed = buttonPressed;
      }

      // Check for timeout
      if ((millis() - roundstart) > T_OUT) {
        Serial.println("Button not pressed, game over!");
        endGame();
        return;
      }
    }

    digitalWrite(currentLED, LOW);
    delay(T_NEW); 
  }

  Serial.print("End of Round Score: ");
  Serial.println(score);
  round_number++;

  T_NEW = T_NEW * K;

  if (round_number > ROUNDS) {
    endGame();
  }
}

/*

/*
void playRound() {
  roundflashLEDs(2);

  Serial.print("Round  ");
  Serial.println(round_number);

  int array[] = {LEDR, LEDY, LEDB, LEDG};
  randomSeed(analogRead(0));

  for (int buttonpress = 0; buttonpress < NUM_PROMPTS; ++buttonpress) {
    int random_index = random(4);
    int currentLED = array[random_index]; // Check this later

    digitalWrite(currentLED, HIGH);

    unsigned long startTime = millis();
    roundstart = startTime;


    while (millis() - startTime < T_NEW) {
      // Check for button press during LED ON and OFF periods
      if (digitalRead(PB_RED) == HIGH && currentLED == LEDR ||
          digitalRead(PB_YELLOW) == HIGH && currentLED == LEDY ||
          digitalRead(PB_BLUE) == HIGH && currentLED == LEDB ||
          digitalRead(PB_GREEN) == HIGH && currentLED == LEDG) {

        // Wait for button release to avoid accidental very short presses
        while (digitalRead(PB_RED) == HIGH || digitalRead(PB_YELLOW) == HIGH ||
               digitalRead(PB_BLUE) == HIGH || digitalRead(PB_GREEN) == HIGH) {
          delay(10);
        }

        score += round_number;
        Serial.print("Round ");
        Serial.print(round_number);
        Serial.print(" --- Score: ");
        Serial.println(score);
        digitalWrite(currentLED, LOW);
        break;
      }

      // Check for timeout
      if ((millis() - roundstart) > T_OUT) {
        Serial.println("Button not pressed, game over!");
        endGame();
        return;
      }
    }

    digitalWrite(currentLED, LOW);
    delay(100); // Add a small delay for visual separation
  }

  Serial.print("End of Round Score: ");
  Serial.println(score);
  round_number++;

  T_NEW = T_NEW * K;

  if (round_number > ROUNDS) {
    endGame();
  }
}
*/
/*
void playRound() {
  roundflashLEDs(2);

  Serial.print("Round  ");
  Serial.println(round_number);

  int array[] = {LEDR, LEDY, LEDB, LEDG};
  randomSeed(analogRead(0));

  for (int buttonpress = 0; buttonpress < NUM_PROMPTS; ++buttonpress) {
    int random_index = random(4);
    int currentLED = array[random_index]; // Check this later

    digitalWrite(currentLED, HIGH);

    unsigned long startTime = millis();
    roundstart = startTime;

    while (millis() - startTime < T_NEW) {
      if (digitalRead(PB_RED) == HIGH && currentLED == LEDR ||
          digitalRead(PB_YELLOW) == HIGH && currentLED == LEDY ||
          digitalRead(PB_BLUE) == HIGH && currentLED == LEDB ||
          digitalRead(PB_GREEN) == HIGH && currentLED == LEDG) {

        // Wait for button release to avoid accidental very short presses
        while (digitalRead(PB_RED) == HIGH || digitalRead(PB_YELLOW) == HIGH ||
               digitalRead(PB_BLUE) == HIGH || digitalRead(PB_GREEN) == HIGH) {
          delay(10);
        }

        score += round_number;
        Serial.print("Round ");
        Serial.print(round_number);
        Serial.print(" --- Score: ");
        Serial.println(score);
        digitalWrite(currentLED, LOW);
        break;
      }

      // Check for timeout
      if ((millis() - roundstart) > T_OUT) {
        Serial.println("Button not pressed, game over!");
        endGame();
        return;
      }

      // Check for button press during LED ON and OFF periods
      if (digitalRead(PB_RED) == HIGH || digitalRead(PB_YELLOW) == HIGH ||
          digitalRead(PB_BLUE) == HIGH || digitalRead(PB_GREEN) == HIGH) {
        // Reset the timer for responsiveness
        startTime = millis();
      }
    }

    digitalWrite(currentLED, LOW);
    delay(100); // Add a small delay for visual separation
  }

  Serial.print("End of Round Score: ");
  Serial.println(score);
  round_number++;

  T_NEW = T_NEW * K;

  if (round_number > ROUNDS) {
    endGame();
  }
}

*/

void roundflashLEDs(int pattern) {
  for (int index = 0; index < 3; index++) {
    for (int value = 0; value < 4; value++) {
      digitalWrite(leds[value], HIGH);
    }
    delay(500);
    for (int value = 0; value < 4; value++) {
      digitalWrite(leds[value], LOW);
    }
    delay(500);
  }
}

void endflashLEDs(int pattern) {
  for (int light_bulb = 0; light_bulb < pattern; ++light_bulb) {
    // Pattern: LEDR -> LEDY -> LEDB -> LEDG
    digitalWrite(LEDR, HIGH);
    delay(200);
    digitalWrite(LEDR, LOW);

    digitalWrite(LEDY, HIGH);
    delay(200);
    digitalWrite(LEDY, LOW);

    digitalWrite(LEDB, HIGH);
    delay(200);
    digitalWrite(LEDB, LOW);

    digitalWrite(LEDG, HIGH);
    delay(200);
    digitalWrite(LEDG, LOW);

    delay(500); 
  }
}


