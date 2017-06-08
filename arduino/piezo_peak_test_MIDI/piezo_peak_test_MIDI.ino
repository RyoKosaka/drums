boolean piezo = false;
#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  MIDI.begin(10);
}

void loop() {

  int sensorValue = analogRead(A0);
  int MAX;

  if (sensorValue > 20 &&  piezo == false) {
    int peak1 = analogRead(A0);
    MAX = peak1;
    delay(1);
    int peak2 = analogRead(A0);

    if (peak2 > MAX) {
      MAX = peak2;
    }

    delay(1);
    int peak3 = analogRead(A0);

    if (peak3 > MAX) {
      MAX = peak3;
    }

    delay(1);
    int peak4 = analogRead(A0);

    if (peak4 > MAX) {
      MAX = peak4;
    }

    delay(1);
    int peak5 = analogRead(A0);

    if (peak5 > MAX) {
      MAX = peak5;
    }

    delay(1);
    int peak6 = analogRead(A0);

    if (peak6 > MAX) {
      MAX = peak6;
    }

    MAX = map(MAX, 20, 800, 1, 127);

    if(MAX <= 1){
      MAX = 1;
    }

    if(MAX >= 127){
      MAX = 127;
    }
    
    MIDI.sendNoteOn(38, MAX, 1); //snare note is 38
    MIDI.sendNoteOff(38, 0, 1);

    piezo = true;

    delay(30); //mask time

  }

  if (sensorValue <= 0 && piezo == true) {
    piezo = false;
  }
}
