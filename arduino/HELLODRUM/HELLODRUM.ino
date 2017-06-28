/*

  " HELLO DRUM " Ver.1.0

  Created June 28, 2017
  by Ryo Kosaka

*/

//////////////////////////////////////////   INITIAL VALUE   ////////////////////////////////////////////

//{threshold, sensitivity, note, flag, velocity, peakValue} 
//*** NOTICE *** peakValue and velocity must be zero.
//*** NOTICE *** Except for the notes, the hi-hat should have the same value for open and close.

int SNARE[6] = {150, 950, 38, 3, 0, 0};
int SNARE_RIM[6] = {5, 500, 37, 3 , 0, 0}; 
int HIHAT[6] = {100, 800, 46, 1, 0, 0};     
int HIHAT_CLOSE[6] = {100, 800, 42, 1, 0, 0};
int KICK[6] = {200, 700, 36, 1, 0, 0};
int HIHAT_PEDAL[4] = {600, 0, 44, 0};
int SETTING[4] = {4, 500 ,100 ,1};  //{scantime, snare/rim, pedalVelocity , masktime}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <MIDI.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  // LCD PIN
MIDI_CREATE_DEFAULT_INSTANCE();

boolean snareFlag = false;
boolean hihatFlag = false;
boolean kickFlag = false;
boolean pedalFlag = false;
boolean buttonState = true;
boolean buttonState_set = true;
int UPDOWN = 0;
int NEXTBACK = 0;

void setup() {
  MIDI.begin(10);
  lcd.begin(16, 2);
  lcd.print("hello, world!");
  lcd.setCursor(0, 1);
  lcd.print("hello, drum!");
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
}

void loop() {

  /////////////////////////////////// CIRCUIT ///////////////////////////////////////

  int button_set = digitalRead(6);
  int button_up = digitalRead(7);
  int button_down = digitalRead(8);
  int button_next = digitalRead(9);
  int button_back = digitalRead(10);
  int piezoValue_0 = analogRead(A0); //snare head
  int piezoValue_1 = analogRead(A1); //snare rim
  int piezoValue_2 = analogRead(A2); //hi-hat
  int piezoValue_3 = analogRead(A3); //kick drum
  int fsrValue_0 = analogRead(A4); //hi-hat pedal

  ////////////////////////////////// EDIT MODE ////////////////////////////////////

  int UP[4] = {5, 50, 1,1};  //{threshold, sensitivity, note, flag}
  int UP_ADVANCE[4] = {1, 50, 1,1};  //{scantime, rim / head, pedal velocity ,masktime}

  char* instrument[] = {
    "SNARE HEAD",  "SNARE RIM", "HIHAT OPEN",
    "HIHAT CLOSE", "HIHAT PEDAL", "KICK", "ADVANCED SETTING"
  };

  char* setting[] = {
    "THRESHOLD",  "SENSITIVITY", "NOTE", "FLAG"
  };

  char* setting_ADVANCE[] = {
    "SCAN TIME", "HEAD / RIM ","PEDAL VELO", "MASK TIME"
  };

  if (UPDOWN < 0) {
    UPDOWN = 6;
  }

  if (UPDOWN > 6) {
    UPDOWN = 0;
  }

  if (NEXTBACK < 0) {
    NEXTBACK = 3;
  }

  if (NEXTBACK > 3) {
    NEXTBACK = 0;
  }

  ////////////////////////////// EDIT BUTTON ////////////////////////////////

  if (button_set == LOW && buttonState == true && buttonState_set == true) {
    lcd.clear();
    lcd.print("EDIT");
    buttonState = false;
    buttonState_set = false;
    delay(500);
  }

  if (button_set == LOW && buttonState == true && buttonState_set == false) {
    lcd.clear();
    lcd.print("EDIT DONE");
    buttonState = false;
    buttonState_set = true;
    delay(500);
  }

  if (button_up == LOW && buttonState == true && buttonState_set == false) {

    switch (UPDOWN) {
      case 0:
        SNARE[NEXTBACK] = SNARE[NEXTBACK] + UP[NEXTBACK];
        break;

      case 1:
        SNARE_RIM[NEXTBACK] = SNARE_RIM[NEXTBACK] + UP[NEXTBACK];
        break;

      case 2:
        switch (NEXTBACK) {
          case 2:
            HIHAT[NEXTBACK] = HIHAT[NEXTBACK] + UP[NEXTBACK];
            break;

          default:
            HIHAT_CLOSE[NEXTBACK] = HIHAT_CLOSE[NEXTBACK] + UP[NEXTBACK];
            HIHAT[NEXTBACK] = HIHAT[NEXTBACK] + UP[NEXTBACK];
        }
        break;

      case 3:
        switch (NEXTBACK) {
          case 2:
            HIHAT_CLOSE[NEXTBACK] = HIHAT_CLOSE[NEXTBACK] + UP[NEXTBACK];
            break;

          default:
            HIHAT_CLOSE[NEXTBACK] = HIHAT_CLOSE[NEXTBACK] + UP[NEXTBACK];
            HIHAT[NEXTBACK] = HIHAT[NEXTBACK] + UP[NEXTBACK];
        }
        break;

      case 4:
      switch (NEXTBACK) {
          case 0:
            HIHAT_PEDAL[NEXTBACK] = HIHAT_PEDAL[NEXTBACK] + UP[NEXTBACK];
            break;

          case 2:
            HIHAT_PEDAL[NEXTBACK] = HIHAT_PEDAL[NEXTBACK] + UP[NEXTBACK];
          break;
        }
        break;

      case 5:
        KICK[NEXTBACK] = KICK[NEXTBACK] + UP[NEXTBACK];
        break;

      case 6:
        SETTING[NEXTBACK] = SETTING[NEXTBACK] + UP_ADVANCE[NEXTBACK];
        break;
    }
    buttonState = false;
    delay(30);
  }

  if (button_down == LOW && buttonState == true && buttonState_set == false) {

    switch (UPDOWN) {
      case 0:
        SNARE[NEXTBACK] = SNARE[NEXTBACK] - UP[NEXTBACK];
        break;

      case 1:
        SNARE_RIM[NEXTBACK] = SNARE_RIM[NEXTBACK] - UP[NEXTBACK];
        break;

      case 2:
        switch (NEXTBACK) {
          case 2:
            HIHAT[NEXTBACK] = HIHAT[NEXTBACK] - UP[NEXTBACK];
            break;

          default:
            HIHAT_CLOSE[NEXTBACK] = HIHAT_CLOSE[NEXTBACK] - UP[NEXTBACK];
            HIHAT[NEXTBACK] = HIHAT[NEXTBACK] - UP[NEXTBACK];
        }
        break;

      case 3:
        switch (NEXTBACK) {
          case 2:
            HIHAT_CLOSE[NEXTBACK] = HIHAT_CLOSE[NEXTBACK] - UP[NEXTBACK];
            break;

          default:
            HIHAT_CLOSE[NEXTBACK] = HIHAT_CLOSE[NEXTBACK] - UP[NEXTBACK];
            HIHAT[NEXTBACK] = HIHAT[NEXTBACK] - UP[NEXTBACK];
        }
        break;

      case 4:
              switch (NEXTBACK) {
          case 0:
            HIHAT_PEDAL[NEXTBACK] = HIHAT_PEDAL[NEXTBACK] - UP[NEXTBACK];
            break;

          case 2:
            HIHAT_PEDAL[NEXTBACK] = HIHAT_PEDAL[NEXTBACK] - UP[NEXTBACK];
          break;
        }
        break;

      case 5:
        KICK[NEXTBACK] = KICK[NEXTBACK] - UP[NEXTBACK];
        break;

      case 6:
        SETTING[NEXTBACK] = SETTING[NEXTBACK] - UP_ADVANCE[NEXTBACK];
        break;
    }
    buttonState = false;
    delay(30);
  }

  ///////////////////////////// UP DOWN NEXT BACK ////////////////////////////////

  if (button_up == LOW && buttonState == true && buttonState_set == true) {
    UPDOWN = ++UPDOWN;
    buttonState = false;
    delay(30);
  }

  if (button_down == LOW && buttonState == true && buttonState_set == true) {
    UPDOWN = --UPDOWN;
    buttonState = false;
    delay(30);
  }

  if (button_next == LOW && buttonState == true && buttonState_set == true) {
    NEXTBACK = ++NEXTBACK;
    buttonState = false;
    delay(30);
  }

  if (button_back == LOW && buttonState == true && buttonState_set == true) {
    NEXTBACK = --NEXTBACK;
    buttonState = false;
    delay(30);
  }

  if (buttonState == false && button_up == HIGH && button_down == HIGH && button_next == HIGH && button_back == HIGH && button_set == HIGH) {
    switch (UPDOWN) {
      case 0:
        lcd.clear();
        lcd.print(instrument[UPDOWN]);
        lcd.setCursor(0, 1);
        lcd.print(setting[NEXTBACK]);
        lcd.setCursor(12, 1);
        lcd.print(SNARE[NEXTBACK]);
        break;

      case 1:
        lcd.clear();
        lcd.print(instrument[UPDOWN]);
        lcd.setCursor(0, 1);
        lcd.print(setting[NEXTBACK]);
        lcd.setCursor(12, 1);
        lcd.print(SNARE_RIM[NEXTBACK]);
        break;

      case 2:
        lcd.clear();
        lcd.print(instrument[UPDOWN]);
        lcd.setCursor(0, 1);
        lcd.print(setting[NEXTBACK]);
        lcd.setCursor(12, 1);
        lcd.print(HIHAT[NEXTBACK]);
        break;

      case 3:
        lcd.clear();
        lcd.print(instrument[UPDOWN]);
        lcd.setCursor(0, 1);
        lcd.print(setting[NEXTBACK]);
        lcd.setCursor(12, 1);
        lcd.print(HIHAT_CLOSE[NEXTBACK]);
        break;

      case 4:
        lcd.clear();
        lcd.print(instrument[UPDOWN]);
        lcd.setCursor(0, 1);
        lcd.print(setting[NEXTBACK]);
        lcd.setCursor(12, 1);
        lcd.print(HIHAT_PEDAL[NEXTBACK]);
        break;

      case 5:
        lcd.clear();
        lcd.print(instrument[UPDOWN]);
        lcd.setCursor(0, 1);
        lcd.print(setting[NEXTBACK]);
        lcd.setCursor(12, 1);
        lcd.print(KICK[NEXTBACK]);
        break;

      case 6:
        lcd.clear();
        lcd.print(instrument[UPDOWN]);
        lcd.setCursor(0, 1);
        lcd.print(setting_ADVANCE[NEXTBACK]);
        lcd.setCursor(12, 1);
        lcd.print(SETTING[NEXTBACK]);
        break;
    }
    buttonState = true;
  }

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
      lcd.clear();
      lcd.print("SNARE RIM");
      lcd.setCursor(0, 1);
      lcd.print(SNARE_RIM[4]);
      snareFlag = true;
    }

    //else if (SNARE[5] > SNARE_RIM[5])
    else {
      MIDI.sendNoteOn(SNARE[2], SNARE[4], 1);   //(note, velocity, channel)
      MIDI.sendNoteOn(SNARE[2], 0, 1);
      lcd.clear();
      lcd.print("SNARE HEAD");
      lcd.setCursor(0, 1);
      lcd.print(SNARE[4]);
//      lcd.setCursor(10, 1);
//      lcd.print(SNARE_RIM[5]);
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
      lcd.clear();
      lcd.print("HIHAT OPEN");
      lcd.setCursor(0, 1);
      lcd.print(HIHAT[4]);
      hihatFlag = true;
    }

    else if (fsrValue_0 >= HIHAT_PEDAL[0]) {
      MIDI.sendNoteOn(HIHAT_CLOSE[2], HIHAT[4], 1);
      MIDI.sendNoteOn(HIHAT_CLOSE[2], 0, 1);
      lcd.clear();
      lcd.print("HIHAT CLOSE");
      lcd.setCursor(0, 1);
      lcd.print(HIHAT[4]);
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
    lcd.clear();
    lcd.print("KICK");
    lcd.setCursor(0, 1);
    lcd.print(KICK[4]);
    kickFlag = true;
  }

  ///////////////////////////// HIHAT PEDAL ////////////////////////////

  if (fsrValue_0 > HIHAT_PEDAL[0] && pedalFlag == false) {
    MIDI.sendNoteOn(HIHAT_PEDAL[2], SETTING[2], 1);  //(note, velocity, channel)
    MIDI.sendNoteOn(HIHAT_PEDAL[2], 0, 1);
    lcd.clear();
    lcd.print("HIHAT PEDAL");
    lcd.setCursor(0, 1);
    lcd.print(SETTING[2]);
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

  if (fsrValue_0 >= HIHAT_PEDAL[0] && piezoValue_2 < (HIHAT[5] *(0.01 * HIHAT[3])) && hihatFlag == true) {
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

  if ( fsrValue_0 <= HIHAT_PEDAL[0] && pedalFlag == true) {
    pedalFlag = false;
  }
}
