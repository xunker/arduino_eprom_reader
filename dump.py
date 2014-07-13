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
