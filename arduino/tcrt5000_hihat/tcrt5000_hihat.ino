/*

  "TCRT5000 TEST "

  Created Feb 21, 2018
  by Ryo Kosaka

*/

/* NOTICE

  You have to install some library.
  1.MIDI : https://playground.arduino.cc/Main/MIDILibrary

*/

//////////////////////////////////////////   INITIAL VALUE   ////////////////////////////////////////////

int HIHAT[6] = {1000, 100, 150, 10, 46, 0};        // *** NOTICE ***  Except for NOTE, make open and close same value.
int HIHAT_CLOSE[6] = {1000, 100, 150, 10, 42, 0};  //{sensitivity, threshold1, threshold2, retrigger,note, velocity}  *** NOTICE *** velocity must be zero.
int HIHAT_PEDAL[4] = {200, 0, 44, 0};
int SETTING[4] = {4, 80, 100 , 35}; //{scantime, snare/rim, pedalVelocity , masktime}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

boolean hihatFlag = false;
boolean pedalFlag = false;
int hihatExValue = 0;
int hihatState = 0;
int exTCRT = 0;
unsigned long time_hit_hihat;
unsigned long time_end_hihat;

void setup() {
  MIDI.begin(10);
  delay(100);
}

void loop() {
  /////////////////////////////// CIRCUIT /////////////////////////////////////

  int piezoValue = analogRead(A1); //hi-hat
  int TCRT = analogRead(A0); //hi-hat pedal

  //////////////////////////////// HI-HAT /////////////////////////////////////

  if (piezoValue > HIHAT[1]) {
    time_hit_hihat = millis();

    if (time_hit_hihat - time_end_hihat < HIHAT[3]) {
      hihatFlag = true;
    }

    if (piezoValue - hihatExValue > HIHAT[2]) {
      hihatFlag = false;
    }

    if (hihatFlag == false) {

      for (int i = 0; i < SETTING[0]; i++) {
        int peak = analogRead(A1);
        if (peak > HIHAT[5]) {
          HIHAT[5] = peak;
        }

        while (millis() - time_hit_hihat < 1);
      }

      HIHAT[5] = map(HIHAT[5], HIHAT[1], HIHAT[0], 0, 127);

      if (HIHAT[5] <= 1) {
        HIHAT[5] = 1;
      }

      if (HIHAT[5] > 127) {
        HIHAT[5] = 127;
      }

      //HIHAT[5] = (HIHAT[5] * HIHAT[5]) / 127 + 1;

      if (TCRT > HIHAT_PEDAL[0]) {
       hihatState = 0; //open
      }
      else{
       hihatState = 1; //close
      }

      switch (hihatState) {
        case 0:
          MIDI.sendNoteOn(HIHAT[4], HIHAT[5], 1);   //(note, velocity, channel)
          MIDI.sendNoteOff(HIHAT[4], 0, 1);
          hihatFlag = true;
          break;

        case 1:
          MIDI.sendNoteOn(HIHAT_CLOSE[4], HIHAT[5], 1);   //(note, velocity, channel)
          MIDI.sendNoteOff(HIHAT_CLOSE[4], 0, 1);
          hihatFlag = true;
          break;
      }
    }
  }

  if (hihatFlag == true) {
    time_end_hihat = millis();
    hihatExValue = analogRead(A1);
    hihatFlag = false;
  }

  /////////////////////// HIHAT PEDAL /////////////////////////

  if (TCRT < HIHAT_PEDAL[0] && pedalFlag == false) {
    MIDI.sendNoteOn(HIHAT_PEDAL[2], SETTING[2], 1);  //(note, velocity, channel)
    MIDI.sendNoteOff(HIHAT_PEDAL[2], 0, 1);
    pedalFlag = true;
  }

  if (TCRT > HIHAT_PEDAL[0] + 100 && pedalFlag == true) {
    pedalFlag = false;
  }

  /////////////////////// HIHAT PEDAL CC /////////////////////////

  TCRT = map(TCRT, 900, 100, 0, 127);
  if (TCRT > 127) {
    TCRT = 127;
  }
  if (TCRT < 0) {
    TCRT = 0;
  }

  if (exTCRT != TCRT) {
    MIDI.sendControlChange(4, TCRT, 1);
    exTCRT = TCRT;
  }
}
