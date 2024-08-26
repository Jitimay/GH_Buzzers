const int relayPins[] = {0, 1, 2, 3, 4, 5, 6, 7}; // Define the pins for your 8 relays
const int buttonPins[] = {14, 15, 16, 17, 18, 19, 20, 21}; // Define the pins for your 8 pushbuttons
const int debounceDelay = 2000; // 4 seconds (4000 milliseconds)
const int buttonDebounceDelay = 50; // 50 milliseconds for button debounce

unsigned long lastButtonPressTime = 0; // To track the time of the last button press
bool isRelayActive = false; // To track whether any relay is currently active
int activeRelayIndex = -1; // To store the index of the active relay

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], LOW); // Turn off all relays initially
    pinMode(buttonPins[i], INPUT_PULLUP); // Use the internal pull-up resistors for the buttons
  }
}

void loop() {
  unsigned long currentTime = millis(); // Get the current time

  if (!isRelayActive) {
    // Check each pushbutton for activation
    for (int i = 0; i < 8; i++) {
      if (digitalRead(buttonPins[i]) == LOW) { // Button pressed
        delay(buttonDebounceDelay); // Wait for button debounce
        if (digitalRead(buttonPins[i]) == LOW) { // Check if button is still pressed
          activateRelay(i);
          lastButtonPressTime = currentTime; // Record the time of the button press
          isRelayActive = true; // Indicate that a relay is active
          activeRelayIndex = i; // Store the active relay index
          break; // Exit the loop after activating one relay
        }
      }
    }
  }

  // Reset the system after 4 seconds of relay activation
  if (isRelayActive && currentTime - lastButtonPressTime >= debounceDelay) {
    turnOffAllRelays();
    isRelayActive = false;
    activeRelayIndex = -1; // Reset the activeRelayIndex
  }
}

void turnOffAllRelays() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(relayPins[i], LOW);
  }
}

void activateRelay(int relayIndex) {
  if (relayIndex >= 0 && relayIndex < 8) {
    // Turn off all relays first
    turnOffAllRelays();
    // Activate only the specified relay
    digitalWrite(relayPins[relayIndex], HIGH);
  }
}