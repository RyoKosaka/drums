// YAMAHA PCY135/155
// 3-ZONE RIDE SENSING TEST
// with EZdrummer2

#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();
int RIDE[4] = {500, 50, 51, 0}; // {sensitivity, threshold, note, velocity}*** NOTICE *** velocity must be zero.
boolean rideFlag = false;
boolean rideChokeFlag = false;
unsigned long time_hit_ride;
unsigned long time_end_ride;
unsigned long time_choke_ride;

void setup() {
  MIDI.begin(10);
}

void loop() {
  int piezoValue = analogRead(A0); //bow piezo
  int sensorValue = analogRead(A1); //edge and cup sensor

  if (abs(piezoValue - sensorValue) > RIDE[1]) {
    time_hit_ride = millis();

    if (time_hit_ride - time_end_ride < 10) { //retrigger cancel
      rideFlag = true;
    }

    if (rideFlag == false) {
      for (int i = 0; i < 4; i++) {  //peak scan
        int peak = analogRead(A0);
        if (peak > RIDE[3]) {
          RIDE[3] = peak;
        }
        while (millis() - time_hit_ride < 1);
      }

      //bow
      if (sensorValue < 50) {
        RIDE[3] = map(RIDE[3], 0, 500, 1, 127);

        if (RIDE[3] <= 1) {
          RIDE[3] = 1;
        }

        if (RIDE[3] > 127) {
          RIDE[3] = 127;
        }
        MIDI.sendNoteOn(RIDE[2], RIDE[3], 1);   //(note, velocity, channel)
        MIDI.sendNoteOn(RIDE[2], 0, 1);
        rideFlag = true;
      }

      //edge
      else if (sensorValue > 500 && sensorValue < 520) {
        RIDE[3] = map(RIDE[3], 0, 600, 1, 127);

        if (RIDE[3] <= 1) {
          RIDE[3] = 1;
        }

        if (RIDE[3] > 127) {
          RIDE[3] = 127;
        }

        MIDI.sendNoteOn(59, RIDE[3], 1);   //(note, velocity, channel) edge note is 59
        MIDI.sendNoteOn(59, 0, 1);
        rideFlag = true;
      }

      //cup
      else if (sensorValue > 520) {
        MIDI.sendNoteOn(53, 100, 1);   //(note, velocity, channel) cup note is 53
        MIDI.sendNoteOn(53, 0, 1);
        rideFlag = true;
      }
    }
  }

  if (rideChokeFlag == false && sensorValue > 500 && sensorValue < 900  && abs(piezoValue - sensorValue) < 10) {
    time_choke_ride = millis();
    if (time_choke_ride - time_end_ride < 10) {
      rideChokeFlag = true;
    }
    else {
      MIDI.sendPolyPressure(RIDE[2], 127, 1);
      MIDI.sendPolyPressure(53, 127, 1);
      MIDI.sendPolyPressure(59, 127, 1);
      MIDI.sendPolyPressure(RIDE[2], 0, 1);
      MIDI.sendPolyPressure(53, 0, 1);
      MIDI.sendPolyPressure(59, 0, 1);
      rideChokeFlag = true;
    }
  }

  if (rideChokeFlag == true &&  sensorValue < 10) {
    time_end_ride = millis();
    rideChokeFlag = false;
  }

  if (rideFlag == true && piezoValue < RIDE[1] && sensorValue < 10) {
    time_end_ride = millis();
    rideFlag = false;
  }
}
