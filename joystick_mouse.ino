#include <Mouse.h>

// Mouse buttons
#define MOUSE_SWITCH 2      // switch to turn on and off mouse control
#define MOUSE_LEFT_BTN 5
#define MOUSE_RIGHT_BTN 3

#define MOUSE_X_AXIS_INPT A0
#define MOUSE_Y_AXIS_INPT A1

#define LOOP_DELAY 5

// Operation modes for readMouseButton function
#define INPUT_LOW_MODE 1
#define INPUT_HIGH_MODE 2
#define INPUT_CHANGED_MODE 3

bool mouseActive = false;    // whether or not to control the mouse
bool lastSwitchState = HIGH; // previous switch state
bool lastMouseRightState = HIGH;
bool lastMouseLeftState = HIGH;

void setup() {
  pinMode(MOUSE_SWITCH, INPUT);       // the switch pin
  pinMode(MOUSE_LEFT_BTN, INPUT);
  pinMode(MOUSE_RIGHT_BTN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void handleMouse() {
  int xReading = analogRead(MOUSE_X_AXIS_INPT);
  int yReading = analogRead(MOUSE_Y_AXIS_INPT);

  // map the reading from the analog input range to the output range:
  int mouseX = map(xReading, 0, 1024, -10, 10);
  int mouseY = map(yReading, 0, 1024, 10, -10);

  if (mouseX > 1 || mouseX < -1 || mouseY < -1 || mouseY > 1)
  {
    Mouse.move(mouseX, mouseY, 0);
  }
}

bool readMouseButton(int button, bool &lastState, unsigned char mode = INPUT_LOW_MODE) {
  bool ret = false;
  bool state = digitalRead(button);
  if (state != lastState) {
    if ((mode == INPUT_LOW_MODE && state == LOW) || (mode == INPUT_HIGH_MODE && state == HIGH) || mode == INPUT_CHANGED_MODE) {
      ret = true;
    }
  }
  lastState = state;
  return ret;
}

void loop() {
  if (readMouseButton(MOUSE_SWITCH, lastSwitchState)) {
    if (mouseActive) {
      Mouse.end();
      mouseActive = false;
    } else {
      Mouse.begin();
      mouseActive = true;
    }
  }
  digitalWrite(LED_BUILTIN, mouseActive);

  if (mouseActive) {
    handleMouse();

    if (readMouseButton(MOUSE_LEFT_BTN, lastMouseLeftState, INPUT_CHANGED_MODE)) {
      if (lastMouseLeftState == LOW && !Mouse.isPressed()) {
        Mouse.press();
      } else if (lastMouseLeftState == HIGH && Mouse.isPressed())
        Mouse.release();
    }

    if (readMouseButton(MOUSE_RIGHT_BTN, lastMouseRightState, INPUT_HIGH_MODE)) {
      Mouse.press(MOUSE_RIGHT);
      Mouse.release(MOUSE_RIGHT);
    }
  }
  delay(LOOP_DELAY);
}
