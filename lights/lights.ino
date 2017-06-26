#include <OneButton.h>

// pin 2 is middle button
OneButton middleButton(2, true);
// pin 3 is top button
OneButton topButton(3, true);

// mosfet 1
bool fet1High = false;
const int outputPinFet1 = 10;
// mosfet 2
bool fet2High = false;
const int outputPinFet2 = 11;
// mosfet 3
bool fet3High = false;
const int outputPinFet3 = 12;

void setup() {
  Serial.begin(9600);

  middleButton.attachClick(middleButtonClick);
  topButton.attachClick(topButtonClick);

  pinMode(outputPinFet1, OUTPUT);
  pinMode(outputPinFet2, OUTPUT);
  pinMode(outputPinFet3, OUTPUT);

  Serial.println("ready!");
  toggleFet1(); delay(200); toggleFet1(); // test and setting default states
  toggleFet2(); delay(200); toggleFet2();
  toggleFet3(); delay(200); toggleFet3();
}

void loop() {
  middleButton.tick();   // pump loop
  topButton.tick();
}

void middleButtonClick() {
  // one flash for fet1
  digitalWrite(LED_BUILTIN, HIGH); delay(100); digitalWrite(LED_BUILTIN, LOW);

  toggleFet1();
}

void topButtonClick() {
  // two flashes for fet2
  digitalWrite(LED_BUILTIN, HIGH); delay(100); digitalWrite(LED_BUILTIN, LOW); delay(100);
  digitalWrite(LED_BUILTIN, HIGH); delay(100); digitalWrite(LED_BUILTIN, LOW);
  
  toggleFet2();
}

void toggleFet1() {
  fet1High = !fet1High;
  digitalWrite(outputPinFet1, fet1High ? HIGH : LOW);
}

void toggleFet2() {
  fet2High = !fet2High;
  digitalWrite(outputPinFet2, fet2High ? HIGH : LOW);  
}

void toggleFet3() {
  fet3High = !fet3High;
  digitalWrite(outputPinFet3, fet3High ? HIGH : LOW);  
}


