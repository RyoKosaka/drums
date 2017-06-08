boolean piezo = false;

void setup() {

  Serial.begin(38400);
}

void loop() {

  int sensorValue = analogRead(A0);
  int MAX;

  if (sensorValue > 35 &&  piezo == false) {
    int peak1 = analogRead(A0);
    Serial.println("  ");
    Serial.println(peak1);
    MAX = peak1;

    delay(1);
    int peak2 = analogRead(A0);
    Serial.println(peak2);

    if (peak2 > MAX) {
      MAX = peak2;
    }

    delay(1);
    int peak3 = analogRead(A0);
    Serial.println(peak3);

    if (peak3 > MAX) {
      MAX = peak3;
    }

    delay(1);
    int peak4 = analogRead(A0);
    Serial.println(peak4);

    if (peak4 > MAX) {
      MAX = peak4;
    }

    delay(1);
    int peak5 = analogRead(A0);
    Serial.println(peak5);

    if (peak5 > MAX) {
      MAX = peak5;
    }

    delay(1);
    int peak6 = analogRead(A0);
    Serial.println(peak6);

    if (peak6 > MAX) {
      MAX = peak6;
    }
    Serial.println("  ");
    Serial.print("MAX = ");
    Serial.print(MAX);
    Serial.println("  ");

    piezo = true;

    delay(30); //mask time

  }

  if (sensorValue <= 0 && piezo == true) {
    piezo = false;
  }
}
