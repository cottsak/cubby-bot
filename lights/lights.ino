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

bool celingLightsEnabled = false;
bool emergencyLightsEnabled = false;

void elF1() { digitalWrite(outputPinFet2, HIGH); delay(50); digitalWrite(outputPinFet2, LOW); delay(50); }
void elF2() { digitalWrite(outputPinFet2, HIGH); delay(50); digitalWrite(outputPinFet2, LOW); delay(50); }
void elF3() { digitalWrite(outputPinFet2, HIGH); delay(50); digitalWrite(outputPinFet2, LOW); delay(50); }
void elF4() { digitalWrite(outputPinFet2, HIGH); delay(50); digitalWrite(outputPinFet2, LOW); delay(50); }
void elF5() { digitalWrite(outputPinFet2, HIGH); delay(50); digitalWrite(outputPinFet2, LOW); delay(50); }
void elF6() { delay(300); }
void elF7() { digitalWrite(outputPinFet3, HIGH); delay(50); digitalWrite(outputPinFet3, LOW); delay(50); }
void elF8() { digitalWrite(outputPinFet3, HIGH); delay(50); digitalWrite(outputPinFet3, LOW); delay(50); }
void elF9() { digitalWrite(outputPinFet3, HIGH); delay(50); digitalWrite(outputPinFet3, LOW); delay(50); }
void elF10() { digitalWrite(outputPinFet3, HIGH); delay(50); digitalWrite(outputPinFet3, LOW); delay(50); }
void elF11() { digitalWrite(outputPinFet3, HIGH); delay(50); digitalWrite(outputPinFet3, LOW); delay(50); }
void elF12() { delay(300); }
void  (*emergencyLightsSequenceFP[])() = { elF1, elF2, elF3, elF4, elF5, elF6, elF7, elF8, elF9, elF10, elF11, elF12 };
int emergencyLightsSequenceIndex = 0;

void setup() {
  Serial.begin(9600);

  middleButton.attachClick(middleButtonClick);
  topButton.attachClick(topButtonClick);

  pinMode(outputPinFet1, OUTPUT);
  pinMode(outputPinFet2, OUTPUT);
  pinMode(outputPinFet3, OUTPUT);

  Serial.println("ready!");
}

void loop() {
  middleButton.tick();   // pump loop
  topButton.tick();

  updateLights();
}

void middleButtonClick() {
  // one flash to ack input
  digitalWrite(LED_BUILTIN, HIGH); delay(100); digitalWrite(LED_BUILTIN, LOW);

  // toggle
  celingLightsEnabled = !celingLightsEnabled;
}

void topButtonClick() {
  // two flashes ack input
  digitalWrite(LED_BUILTIN, HIGH); delay(100); digitalWrite(LED_BUILTIN, LOW); delay(100);
  digitalWrite(LED_BUILTIN, HIGH); delay(100); digitalWrite(LED_BUILTIN, LOW);
  
  // toggle
  emergencyLightsEnabled = !emergencyLightsEnabled;
}

void updateLights() {
  digitalWrite(outputPinFet1, celingLightsEnabled ? HIGH : LOW);

  // flashing pattern from function array (really should be using interrupts)
  if(emergencyLightsEnabled) {
    emergencyLightsSequenceFP [emergencyLightsSequenceIndex++] ();
    if (emergencyLightsSequenceIndex >= 12)
      emergencyLightsSequenceIndex = 0;
  }else{
    digitalWrite(outputPinFet2, LOW);
    digitalWrite(outputPinFet3, LOW);
  }
}

