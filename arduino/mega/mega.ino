//////////////////////////////////////////   INITIAL VALUE   ////////////////////////////////////////////

//*** NOTICE * peakValue and velocity must be zero.
//*** NOTICE * Except for the notes, the hi-hat should have the same value for open and close.

int SNARE[6] = {150, 950, 38, 3, 0, 0}; //{threshold, sensitivity, note, flag, velocity, peakValue}
int SNARE_RIM[6] = {5, 500, 37, 3 , 0, 0};
int HIHAT[6] = {100, 800, 46, 1, 0, 0};
int HIHAT_CLOSE[6] = {100, 800, 42, 1, 0, 0};
int KICK[6] = {200, 700, 36, 1, 0, 0};
int HIGHTOM[6] = {200, 700, 50, 1, 0, 0};
int MIDTOM[6] = {200, 700, 45, 1, 0, 0};
int LOWERTOM[6] = {200, 700, 41, 1, 0, 0};
int CRASH[6] = {200, 700, 49, 1, 0, 0};
int RIDE[6] = {200, 700, 51, 1, 0, 0};
int BELL[6] = {200, 700, 53, 1, 0, 0};
int HIHAT_PEDAL[4] = {600, 0, 44, 0};
int SETTING[4] = {4, 500 ,100 ,1};  //{scantime, snare/rim, pedalVelocity , masktime}

/////////////////////////////////////////////////////////////////////////////////////////////

#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

boolean snareFlag = false;
boolean hihatFlag = false;
boolean kickFlag = false;
boolean hightomFlag = false;
boolean midtomFlag = false;
boolean lowertomFlag = false;
boolean crashFlag = false;
boolean rideFlag = false;
boolean bellFlag = false;
boolean pedalFlag = false;

void setup() {
  MIDI.begin(10);
}

void loop() {

  /////////////////////////////////// CIRCUIT ///////////////////////////////////////

  int piezoValue_0 = analogRead(A0); //snare head
  int piezoValue_1 = analogRead(A1); //snare rim
  int piezoValue_2 = analogRead(A2); //hi-hat
  int piezoValue_3 = analogRead(A3); //kick drum
  int piezoValue_4 = analogRead(A4); //high tom
  int piezoValue_5 = analogRead(A5); //mid tom
  int piezoValue_6 = analogRead(A6); //low tom
  int piezoValue_7 = analogRead(A7); //crash
  int piezoValue_8 = analogRead(A8); //ride
  int piezoValue_9 = analogRead(A9); //bell
  int fsrValue_0 = analogRead(A10); //pedal

  ////////////////////////////////// SNARE ///////////////////////////////////

  if (piezoValue_0 > SNARE[0] && snareFlag == false) {

    for (int i = 0; i < SETTING[0]; i++) {
      int peak0 = analogRead(A0);
      int peak1 = analogRead(A1);
      delay(1);

      if (peak0 > SNARE[4]) {
        SNARE[4] = peak0;
      }

      if (peak1 > SNARE_RIM[4]) {
        SNARE_RIM[4] = peak1;
      }
    }

    SNARE[5] = SNARE[4];
    SNARE_RIM[5] = SNARE_RIM[4];
    SNARE[4] = map(SNARE[4], SNARE[0], SNARE[1], 0, 127);
    SNARE_RIM[4] = map(SNARE_RIM[4], SNARE_RIM[0], SNARE_RIM[1], 0, 127);
    SNARE[4] = ( SNARE[4] *  SNARE[4]) / 127; // Curve setting
    //SNARE_RIM[4] = (SNARE_RIM[4] * SNARE_RIM[4]) / 127;

    if (SNARE[4] <= 1) {
      SNARE[4] = 1;
    }

    if (SNARE[4] > 127) {
      SNARE[4] = 127;
    }

    if (SNARE_RIM[4] <= 0) {
      SNARE_RIM[4] = 0;
    }

    if (SNARE_RIM[4] > 127) {
      SNARE_RIM[4] = 127;
    }

    if (SNARE_RIM[5] > SETTING[1]) {
      MIDI.sendNoteOn(SNARE_RIM[2], SNARE_RIM[4], 1);   //(note, velocity, channel)
      MIDI.sendNoteOn(SNARE_RIM[2], 0, 1);
      snareFlag = true;
    }

    //else if (SNARE[5] > SNARE_RIM[5])
    else {
      MIDI.sendNoteOn(SNARE[2], SNARE[4], 1);   //(note, velocity, channel)
      MIDI.sendNoteOn(SNARE[2], 0, 1);
      snareFlag = true;
    }
  }

  //////////////////////////////// HI-HAT /////////////////////////////////////

  if (piezoValue_2 > HIHAT[0] && hihatFlag == false) {

    for (int i = 0; i < SETTING[0]; i++) {
      int peak2 = analogRead(A2);
      delay(1);

      if (peak2 > HIHAT[4]) {
        HIHAT[4] = peak2;
      }
    }

    HIHAT[5] = HIHAT[4];
    HIHAT[4] = map(HIHAT[4], HIHAT[0], HIHAT[1], 0, 127);
    HIHAT[4] = (HIHAT[4] * HIHAT[4]) / 127;

    if (HIHAT[4] <= 1) {
      HIHAT[4] = 1;
    }

    if (HIHAT[4] > 127) {
      HIHAT[4] = 127;
    }

    if (fsrValue_0 < HIHAT_PEDAL[0]) {
      MIDI.sendNoteOn(HIHAT[2], HIHAT[4], 1);
      MIDI.sendNoteOn(HIHAT[2], 0, 1);
      hihatFlag = true;
    }

    else if (fsrValue_0 >= HIHAT_PEDAL[0]) {
      MIDI.sendNoteOn(HIHAT_CLOSE[2], HIHAT[4], 1);
      MIDI.sendNoteOn(HIHAT_CLOSE[2], 0, 1);
      hihatFlag = true;
    }
  }

  //////////////////////////////////// KICK //////////////////////////////////

  if (piezoValue_3 > KICK[0] && kickFlag == false) {

    for (int i = 0; i < SETTING[0]; i++) {
      int peak3 = analogRead(A3);
      delay(1);

      if (peak3 > KICK[4]) {
        KICK[4] = peak3;
      }
    }

    KICK[5] = KICK[4];
    KICK[4] = map(KICK[4], KICK[0], KICK[1], 0, 127);
    KICK[4] = (KICK[4] * KICK[4]) / 127;

    if (KICK[4] <= 1) {
      KICK[4] = 1;
    }

    if (KICK[4] > 127) {
      KICK[4] = 127;
    }

    MIDI.sendNoteOn(KICK[2], KICK[4], 1);
    MIDI.sendNoteOn(KICK[2], 0, 1);
    kickFlag = true;
  }

  //////////////////////////////////// HIGH TOM //////////////////////////////////

  if (piezoValue_4 > HIGHTOM[0] && hightomFlag == false) {

    for (int i = 0; i < SETTING[0]; i++) {
      int peak4 = analogRead(A4);
      delay(1);

      if (peak4 > HIGHTOM[4]) {
        HIGHTOM[4] = peak4;
      }
    }

    HIGHTOM[5] = HIGHTOM[4];
    HIGHTOM[4] = map(HIGHTOM[4], HIGHTOM[0], HIGHTOM[1], 0, 127);
    HIGHTOM[4] = (HIGHTOM[4] * HIGHTOM[4]) / 127;

    if (HIGHTOM[4] <= 1) {
      HIGHTOM[4] = 1;
    }

    if (HIGHTOM[4] > 127) {
      HIGHTOM[4] = 127;
    }

    MIDI.sendNoteOn(HIGHTOM[2], HIGHTOM[4], 1);
    MIDI.sendNoteOn(HIGHTOM[2], 0, 1);
    hightomFlag = true;
  }
  //////////////////////////////////// MID TOM //////////////////////////////////

  if (piezoValue_5 > MIDTOM[0] && midtomFlag == false) {

    for (int i = 0; i < SETTING[0]; i++) {
      int peak5 = analogRead(A5);
      delay(1);

      if (peak5 > MIDTOM[4]) {
        MIDTOM[4] = peak5;
      }
    }

    MIDTOM[5] = MIDTOM[4];
    MIDTOM[4] = map(MIDTOM[4], MIDTOM[0], MIDTOM[1], 0, 127);
    MIDTOM[4] = (MIDTOM[4] * MIDTOM[4]) / 127;

    if (MIDTOM[4] <= 1) {
      MIDTOM[4] = 1;
    }

    if (MIDTOM[4] > 127) {
      MIDTOM[4] = 127;
    }

    MIDI.sendNoteOn(MIDTOM[2], MIDTOM[4], 1);
    MIDI.sendNoteOn(MIDTOM[2], 0, 1);
    midtomFlag = true;
  }

  //////////////////////////////////// LOWER TOM //////////////////////////////////

  if (piezoValue_6 > LOWERTOM[0] && lowertomFlag == false) {

    for (int i = 0; i < SETTING[0]; i++) {
      int peak6 = analogRead(A6);
      delay(1);

      if (peak6 > LOWERTOM[4]) {
        LOWERTOM[4] = peak6;
      }
    }

    LOWERTOM[5] = LOWERTOM[4];
    LOWERTOM[4] = map(LOWERTOM[4], LOWERTOM[0], LOWERTOM[1], 0, 127);
    LOWERTOM[4] = (LOWERTOM[4] * LOWERTOM[4]) / 127;

    if (LOWERTOM[4] <= 1) {
      LOWERTOM[4] = 1;
    }

    if (LOWERTOM[4] > 127) {
      LOWERTOM[4] = 127;
    }

    MIDI.sendNoteOn(LOWERTOM[2], LOWERTOM[4], 1);
    MIDI.sendNoteOn(LOWERTOM[2], 0, 1);
    lowertomFlag = true;
  }

  //////////////////////////////////// CRASH //////////////////////////////////

  if (piezoValue_7 > CRASH[0] && crashFlag == false) {

    for (int i = 0; i < SETTING[0]; i++) {
      int peak7 = analogRead(A7);
      delay(1);

      if (peak7 > CRASH[4]) {
        CRASH[4] = peak7;
      }
    }

    CRASH[5] = CRASH[4];
    CRASH[4] = map(CRASH[4], CRASH[0], CRASH[1], 0, 127);
    CRASH[4] = (CRASH[4] * CRASH[4]) / 127;

    if (CRASH[4] <= 1) {
      CRASH[4] = 1;
    }

    if (CRASH[4] > 127) {
      CRASH[4] = 127;
    }

    MIDI.sendNoteOn(CRASH[2], CRASH[4], 1);
    MIDI.sendNoteOn(CRASH[2], 0, 1);
    crashFlag = true;
  }

  //////////////////////////////////// RIDE //////////////////////////////////

  if (piezoValue_8 > RIDE[0] && rideFlag == false) {

    for (int i = 0; i < SETTING[0]; i++) {
      int peak8 = analogRead(A8);
      delay(1);

      if (peak8 > RIDE[4]) {
        RIDE[4] = peak8;
      }
    }

    RIDE[5] = RIDE[4];
    RIDE[4] = map(RIDE[4], RIDE[0], RIDE[1], 0, 127);
    RIDE[4] = (RIDE[4] * RIDE[4]) / 127;

    if (RIDE[4] <= 1) {
      RIDE[4] = 1;
    }

    if (RIDE[4] > 127) {
      RIDE[4] = 127;
    }

    MIDI.sendNoteOn(RIDE[2], RIDE[4], 1);
    MIDI.sendNoteOn(RIDE[2], 0, 1);
    rideFlag = true;
  }

  //////////////////////////////////// BELL //////////////////////////////////

  if (piezoValue_9 > BELL[0] && bellFlag == false) {

    for (int i = 0; i < SETTING[0]; i++) {
      int peak9 = analogRead(A9);
      delay(1);

      if (peak9 > BELL[4]) {
        BELL[4] = peak9;
      }
    }

    BELL[5] = BELL[4];
    BELL[4] = map(BELL[4], BELL[0], BELL[1], 0, 127);
    BELL[4] = (BELL[4] * BELL[4]) / 127;

    if (BELL[4] <= 1) {
      BELL[4] = 1;
    }

    if (BELL[4] > 127) {
      BELL[4] = 127;
    }

    MIDI.sendNoteOn(BELL[2], BELL[4], 1);
    MIDI.sendNoteOn(BELL[2], 0, 1);
    bellFlag = true;
  }
  ///////////////////////////// HIHAT PEDAL ////////////////////////////

  if (fsrValue_0 > HIHAT_PEDAL[0] && pedalFlag == false) {
    MIDI.sendNoteOn(HIHAT_PEDAL[2], SETTING[2], 1);  //(note, velocity, channel)
    MIDI.sendNoteOn(HIHAT_PEDAL[2], 0, 1);
    pedalFlag = true;
  }

  ////////////////////////////// FLAG /////////////////////////////

  if (piezoValue_0 < (SNARE[5] * (0.01 * SNARE[3])) && snareFlag == true) {
    delay(SETTING[3]); //mask time
    int sensorValue0 = analogRead(A0);
    if (sensorValue0 < (SNARE[5] * (0.01 * SNARE[3]))) {
      snareFlag = false;
    }
  }

  if (fsrValue_0 <= HIHAT_PEDAL[0] && piezoValue_2 < (HIHAT[5] * (0.01 * HIHAT[3])) && hihatFlag == true) {
    delay(SETTING[3]);
    int sensorValue1 = analogRead(A2);
    if (sensorValue1 < (HIHAT[5] * (0.01 * HIHAT[3]))) {
      hihatFlag = false;
    }
  }

  if (fsrValue_0 >= HIHAT_PEDAL[0] && piezoValue_2 < (HIHAT[5] * (0.01 * HIHAT[3])) && hihatFlag == true) {
    delay(SETTING[3]);
    int sensorValue2 = analogRead(A2);
    if (sensorValue2 < (HIHAT[5] * (0.01 * HIHAT[3]))) {
      hihatFlag = false;
    }
  }

  if (piezoValue_3 < (KICK[5] * (0.01 * KICK[3])) && kickFlag == true) {
    delay(SETTING[3]);
    int sensorValue3 = analogRead(A3);
    if (piezoValue_3 < (KICK[5] * (0.01 * KICK[3]))) {
      kickFlag = false;
    }
  }
  if (piezoValue_4 < (HIGHTOM[5] * (0.01 * HIGHTOM[3])) && hightomFlag == true) {
    delay(SETTING[3]);
    int sensorValue4 = analogRead(A4);
    if (piezoValue_4 < (HIGHTOM[5] * (0.01 * HIGHTOM[3]))) {
      hightomFlag = false;
    }
  }
  if (piezoValue_5 < (MIDTOM[5] * (0.01 * MIDTOM[3])) && midtomFlag == true) {
    delay(SETTING[3]);
    int sensorValue5 = analogRead(A5);
    if (piezoValue_5 < (HIGHTOM[5] * (0.01 * HIGHTOM[3]))) {
      midtomFlag = false;
    }
  }

  if (piezoValue_6 < (LOWERTOM[5] * (0.01 * LOWERTOM[3])) && lowertomFlag == true) {
    delay(SETTING[3]);
    int sensorValue6 = analogRead(A6);
    if (piezoValue_6 < (LOWERTOM[5] * (0.01 * LOWERTOM[3]))) {
      lowertomFlag = false;
    }
  }

  if (piezoValue_7 < (CRASH[5] * (0.01 * CRASH[3])) && crashFlag == true) {
    delay(SETTING[3]);
    int sensorValue7 = analogRead(A7);
    if (piezoValue_7 < (CRASH[5] * (0.01 * CRASH[3]))) {
      crashFlag = false;
    }
  }

  if (piezoValue_8 < (RIDE[5] * (0.01 * RIDE[3])) && rideFlag == true) {
    delay(SETTING[3]);
    int sensorValue8 = analogRead(A8);
    if (piezoValue_8 < (RIDE[5] * (0.01 * RIDE[3]))) {
      rideFlag = false;
    }
  }

  if (piezoValue_9 < (BELL[5] * (0.01 * BELL[3])) && bellFlag == true) {
    delay(SETTING[3]);
    int sensorValue9 = analogRead(A9);
    if (piezoValue_9 < (BELL[5] * (0.01 * BELL[3]))) {
      bellFlag = false;
    }
  }

  if ( fsrValue_0 <= HIHAT_PEDAL[0] && pedalFlag == true) {
    pedalFlag = false;
  }
}
