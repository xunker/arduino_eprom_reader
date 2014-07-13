/*
  Python:

  #!/usr/bin/env python
  import serial
  import re
  ser = serial.Serial('/dev/tty.usbmodemfa132121', 9600, 8, parity=serial.PARITY_NONE, timeout=1, rtscts=1, dsrdtr=1)

  buffer_size=512
  f = open('dump.bin', 'w', buffer_size)

  pattern = re.compile("^\d\d\d\d\d\d\d\d$")

  line = 'start'
  while (line):
    line = ser.readline().strip()

    print line
    if pattern.match(line):
      f.write(chr(int(line, 2)))

    if line == "DONE!":
      line = ""

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
