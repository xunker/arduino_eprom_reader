/*
  WIRING:

  AM27C256 pin
  ------------------------------------
  14            Ground
  28            +5v

  Both 74HC595s
  ------------------------------------
  8             Ground
  16            +5v
  13            Ground
  10            +5v

  Arduino pin   AM27C256 pin
  ------------------------------------
  A0            22 Output enable (OE)
  A1            10 Chip enable (CE)
  2             11 DQ0
  3             12 DQ1
  4             13 DQ2
  5             15 DQ3
  6             16 DQ4
  7             17 DQ5
  8             18 DQ6
  9             19 DQ7

  Arduino pin   1st 74HC595
  ------------------------------------
  A2            14 SER/Data
  A3            11 Clock/SRCLK/SH_CP
  A4            12 Latch/RCLK/ST_CP

  1st 74HC595   2nd 74HC595
  ------------------------------------
  12 Latch      12 Latch
  11 Clock      11 Clock
  9  QH'        14 SER/Data

  1st 74HC595   AM27C256 pin
  ------------------------------------
  15 QA         10 Address 0
  1  QB         9  Address 1
  2  QC         8  Address 2
  3  QD         7  Address 3
  4  QE         6  Address 4
  5  QF         5  Address 5
  6  QG         4  Address 6
  7  QH         3  Address 7

  2nd 74HC595   AM27C256 pin
  ------------------------------------
  15 QA         25 Address 8
  1  QB         24 Address 9
  2  QC         21 Address 10
  3  QD         23 Address 11
  4  QE         2  Address 12
  5  QF         26 Address 13
  6  QG         27 Address 14
  7  QH         Not Connected

*/

#define OE A0
#define CE A1

#define SR_DS A2    // Data Pin
#define SR_SH_CP A3 // Clock Pin
#define SR_ST_CP A4 // Latch Pin

#define DQ0 2
#define DQ1 3
#define DQ2 4
#define DQ3 5
#define DQ4 6
#define DQ5 7
#define DQ6 8
#define DQ7 9

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo/Micro only
  }

  Serial.println("Begin");

  pinMode(OE, OUTPUT);
  pinMode(CE, OUTPUT);

  pinMode(SR_DS, OUTPUT);
  pinMode(SR_SH_CP, OUTPUT);
  pinMode(SR_ST_CP, OUTPUT);

  pinMode(DQ0, INPUT);
  pinMode(DQ1, INPUT);
  pinMode(DQ2, INPUT);
  pinMode(DQ3, INPUT);
  pinMode(DQ4, INPUT);
  pinMode(DQ5, INPUT);
  pinMode(DQ6, INPUT);
  pinMode(DQ7, INPUT);

  Serial.println("Initial Pin Setting");

  delay(500);

  Serial.println("Setting OE Low");
  digitalWrite(OE, LOW);

  delay(500);

  Serial.println("Done initial setting");


}

void loop() {

  Serial.println("Beginning address iteration");

  delay(500);

  for (unsigned int address_a = 0; address_a <= 127; address_a++) {
    for (unsigned int address_b = 0; address_b <= 255; address_b++) {
  
      // Serial.print(
      //   "Setting address: ",
      //   String(address_a, BIN) +
      //   String(address_b, BIN) +
      //   ": "
      // );

      digitalWrite(SR_ST_CP, LOW); // Latch Pin
      shiftOut(SR_DS, SR_SH_CP, MSBFIRST, address_a);
      shiftOut(SR_DS, SR_SH_CP, MSBFIRST, address_b);
      digitalWrite(SR_ST_CP, HIGH); // Latch Pin

      // delay(500);

      // Serial.println("Setting CE High");
      digitalWrite(CE, HIGH);

      // delay(500);

      // Serial.println("Reading Data");
      String addressData = readData();
      Serial.println(addressData);

      // delay(500);
      delay(10);

      // Serial.println("Setting CE Low");
      digitalWrite(CE, LOW);

      // delay(500);

    }
  }
  Serial.println("DONE!");
  delay(60000);
}

String readData() {
  // delay(500);

  // Serial.println("Reading DQ0-DQ7");

  String inputString = "";
  // Big-Endian
  // inputString += digitalRead(DQ0);
  // inputString += digitalRead(DQ1);
  // inputString += digitalRead(DQ2);
  // inputString += digitalRead(DQ3);
  // inputString += digitalRead(DQ4);
  // inputString += digitalRead(DQ5);
  // inputString += digitalRead(DQ6);
  // inputString += digitalRead(DQ7);

  // Little-Endian
  inputString += digitalRead(DQ7);
  inputString += digitalRead(DQ6);
  inputString += digitalRead(DQ5);
  inputString += digitalRead(DQ4);
  inputString += digitalRead(DQ3);
  inputString += digitalRead(DQ2);
  inputString += digitalRead(DQ1);
  inputString += digitalRead(DQ0);

  // Serial.println("Value: " + inputString);

  return inputString;
}
