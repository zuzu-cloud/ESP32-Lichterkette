const int tasterPin = 5;          // Taster an GPIO5
const int dacPin    = 25;         // DAC1 (GPIO25)

const int spannungen[] = {190, 196, 202, 208, 214, 220};  // DAC-Werte für 2.456–2.844 V
const int maxStufe = sizeof(spannungen) / sizeof(spannungen[0]);  // 6 Stufen

int stufe = -1;  // -1 = AUS
bool letzterTasterStatus = HIGH;
unsigned long letzteTaste = 0;
const unsigned long cooldown = 300;  // 0.3 s

void setup() {
  pinMode(tasterPin, INPUT_PULLUP);
  dacWrite(dacPin, 0);  // Start AUS
}

void loop() {
  bool tasterStatus = digitalRead(tasterPin);

  if (tasterStatus == LOW &&
      letzterTasterStatus == HIGH &&
      millis() - letzteTaste > cooldown) {

    letzteTaste = millis();
    stufe++;

    if (stufe == maxStufe) {
      dacWrite(dacPin, 0);  // AUS nach max
    } else if (stufe > maxStufe) {
      stufe = 0;            // Neustart ab erster Spannung
      dacWrite(dacPin, spannungen[stufe]);
    } else {
      dacWrite(dacPin, spannungen[stufe]);
    }
  }

  letzterTasterStatus = tasterStatus;
}
