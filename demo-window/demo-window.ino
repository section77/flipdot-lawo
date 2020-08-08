// pin assignments
// 
// pin on lolin32 header      // pin on column driver input header
// -------------------------- // ---------------------------------
//         GND                // (1-4, 31-34)
const byte DATA = 15;         // (8)
const byte COLUMN_1 = 2;      // (7)
const byte COLUMN_2 = 0;      // (9)
const byte COLUMN_3 = 4;      // (11)
const byte COLUMN_4 = 16;     // (13)
const byte COLUMN_5 = 17;     // (15)
const byte ROW_1 = 5;         // (17)
const byte ROW_2 = 18;        // (19)
const byte ROW_3 = 23;        // (21)
const byte ROW_4 = 19;        // (23)
const byte ENABLE_SET = 21;   // (10)
const byte ENABLE_RESET = 22; // (12)
const byte MODULE_1 = 13;     // (20)
const byte MODULE_2 = 12;     // (22)
const byte MODULE_3 = 14;     // (24)
const byte MODULE_4 = 27;     // (26)
const byte MODULE_5 = 26;     // (28)

// helper constants
const byte MODULE_PINS[] = {MODULE_1, MODULE_2, MODULE_3, MODULE_4, MODULE_5};
const byte COLUMN_BIT_PINS[] = {COLUMN_1, COLUMN_2, COLUMN_3, COLUMN_4, COLUMN_5};
const byte ROW_BIT_PINS[] = {ROW_1, ROW_2, ROW_3, ROW_4};
const byte MODULE_HEIGHT = 16;
const byte MODULE_WIDTH = 28;
const byte COLUMN_OFFSET_SHORT_MODULE = 14;
const byte DISPLAY_WIDTH = 126;

// program config
const int PAUSE_BETWEEN_DOT_FLIPS_IN_MS = 2; // lowest value to reliably flip all dots with 5A power supply (lights off)
const int MAX_PAUSE_BETWEEN_ACTIONS = 15000;

void loop() {
  sendOrFlicker(random(13));
  delay(random(MAX_PAUSE_BETWEEN_ACTIONS));
}

void sendOrFlicker(byte code) {
  if (code == 0) {
    sendOnIDotLine();
  } else if (code == 1) {
    sendOnLineRight1();
  } else if (code == 2) {
    sendOnLineRight2();
  } else if (code == 3) {
    sendOnLineRight3();
  } else if (code == 4) {
    sendOnLineRight4();
  } else if (code == 5) {
    sendOnLineLeft1();
  } else if (code == 6) {
    sendOnLineLeft2();
  } else if (code == 7) {
    sendOnLineLeft3();
  } else if (code == 8) {
    sendOnLineLeft4();
  } else if (code == 9) {
    flipLetterE(false);
    flipLetterE(true);
  } else if (code == 10) {
    flipLetterC(false);
    flipLetterC(true);
  } else if (code == 11) {
    flipLetterO(false);
    flipLetterO(true);
  } else if (code == 12) {
    flipLetterN(false);
    flipLetterN(true);
  }
}

// custom drawing

void showName() {
  flipLetterS(true);
  flipLetterE(true);
  flipLetterC(true);
  flipLetterT(true);
  flipLetterI(true);
  flipLetterO(true);
  flipLetterN(true);
  flipFirstSeven(true);
  flipSecondSeven(true);
}

void flipLetterS(boolean shouldShowYellow) {
  flipDotSimple(31, 7, shouldShowYellow);
  flipDotSimple(30, 6, shouldShowYellow);
  flipDotSimple(29, 6, shouldShowYellow);
  flipDotSimple(28, 6, shouldShowYellow);
  flipDotSimple(27, 6, shouldShowYellow);
  flipDotSimple(26, 7, shouldShowYellow);
  flipDotSimple(26, 8, shouldShowYellow);
  flipDotSimple(26, 9, shouldShowYellow);
  flipDotSimple(27, 9, shouldShowYellow);
  flipDotSimple(28, 9, shouldShowYellow);
  flipDotSimple(29, 10, shouldShowYellow);
  flipDotSimple(30, 10, shouldShowYellow);
  flipDotSimple(31, 10, shouldShowYellow);
  flipDotSimple(31, 11, shouldShowYellow);
  flipDotSimple(31, 12, shouldShowYellow);
  flipDotSimple(30, 13, shouldShowYellow);
  flipDotSimple(29, 13, shouldShowYellow);
  flipDotSimple(28, 13, shouldShowYellow);
  flipDotSimple(27, 13, shouldShowYellow);
  flipDotSimple(26, 13, shouldShowYellow);
  flipDotSimple(26, 12, shouldShowYellow);
}

void flipLetterE(boolean shouldShowYellow) {
  flipDotSimple(35, 9, shouldShowYellow);
  flipDotSimple(36, 9, shouldShowYellow);
  flipDotSimple(37, 9, shouldShowYellow);
  flipDotSimple(38, 9, shouldShowYellow);
  flipDotSimple(39, 9, shouldShowYellow);
  flipDotSimple(39, 8, shouldShowYellow);
  flipDotSimple(39, 7, shouldShowYellow);
  flipDotSimple(38, 7, shouldShowYellow);
  flipDotSimple(38, 6, shouldShowYellow);
  flipDotSimple(37, 6, shouldShowYellow);
  flipDotSimple(36, 6, shouldShowYellow);
  flipDotSimple(35, 6, shouldShowYellow);
  flipDotSimple(35, 7, shouldShowYellow);
  flipDotSimple(34, 8, shouldShowYellow);
  flipDotSimple(34, 9, shouldShowYellow);
  flipDotSimple(34, 10, shouldShowYellow);
  flipDotSimple(34, 11, shouldShowYellow);
  flipDotSimple(35, 12, shouldShowYellow);
  flipDotSimple(36, 13, shouldShowYellow);
  flipDotSimple(37, 13, shouldShowYellow);
  flipDotSimple(38, 13, shouldShowYellow);
  flipDotSimple(39, 12, shouldShowYellow);
}

void flipLetterC(boolean shouldShowYellow) {
  flipDotSimple(47, 7, shouldShowYellow);
  flipDotSimple(46, 6, shouldShowYellow);
  flipDotSimple(45, 6, shouldShowYellow);
  flipDotSimple(44, 6, shouldShowYellow);
  flipDotSimple(43, 7, shouldShowYellow);
  flipDotSimple(42, 8, shouldShowYellow);
  flipDotSimple(42, 9, shouldShowYellow);
  flipDotSimple(42, 10, shouldShowYellow);
  flipDotSimple(42, 11, shouldShowYellow);
  flipDotSimple(43, 12, shouldShowYellow);
  flipDotSimple(44, 13, shouldShowYellow);
  flipDotSimple(45, 13, shouldShowYellow);
  flipDotSimple(46, 13, shouldShowYellow);
  flipDotSimple(47, 12, shouldShowYellow);
}

void flipLetterT(boolean shouldShowYellow) {
  flipDotSimple(52, 4, shouldShowYellow);
  flipDotSimple(52, 5, shouldShowYellow);
  flipDotSimple(52, 6, shouldShowYellow);
  flipDotSimple(52, 7, shouldShowYellow);
  flipDotSimple(52, 8, shouldShowYellow);
  flipDotSimple(52, 9, shouldShowYellow);
  flipDotSimple(52, 10, shouldShowYellow);
  flipDotSimple(52, 11, shouldShowYellow);
  flipDotSimple(52, 12, shouldShowYellow);
  flipDotSimple(53, 13, shouldShowYellow);
  flipDotSimple(54, 13, shouldShowYellow);
  flipDotSimple(55, 13, shouldShowYellow);
  flipDotSimple(50, 6, shouldShowYellow);
  flipDotSimple(51, 6, shouldShowYellow);
  flipDotSimple(52, 6, shouldShowYellow);
  flipDotSimple(53, 6, shouldShowYellow);
  flipDotSimple(54, 6, shouldShowYellow);
  flipDotSimple(55, 6, shouldShowYellow);
}

void flipLetterI(boolean shouldShowYellow) {
  flipDotSimple(59, 6, shouldShowYellow);
  flipDotSimple(60, 6, shouldShowYellow);
  flipDotSimple(61, 6, shouldShowYellow);
  flipDotSimple(61, 7, shouldShowYellow);
  flipDotSimple(61, 8, shouldShowYellow);
  flipDotSimple(61, 9, shouldShowYellow);
  flipDotSimple(61, 10, shouldShowYellow);
  flipDotSimple(61, 11, shouldShowYellow);
  flipDotSimple(61, 12, shouldShowYellow);
  flipDotSimple(58, 13, shouldShowYellow);
  flipDotSimple(59, 13, shouldShowYellow);
  flipDotSimple(60, 13, shouldShowYellow);
  flipDotSimple(61, 13, shouldShowYellow);
  flipDotSimple(62, 13, shouldShowYellow);
  flipDotSimple(63, 13, shouldShowYellow);
  flipDotSimple(64, 13, shouldShowYellow);
  flipDotSimple(61, 3, shouldShowYellow);
  flipDotSimple(61, 4, shouldShowYellow);
}

void flipLetterO(boolean shouldShowYellow) {
  flipDotSimple(67, 6, shouldShowYellow);
  flipDotSimple(68, 6, shouldShowYellow);
  flipDotSimple(69, 6, shouldShowYellow);
  flipDotSimple(70, 6, shouldShowYellow);
  flipDotSimple(70, 7, shouldShowYellow);
  flipDotSimple(71, 7, shouldShowYellow);
  flipDotSimple(71, 8, shouldShowYellow);
  flipDotSimple(71, 9, shouldShowYellow);
  flipDotSimple(71, 10, shouldShowYellow);
  flipDotSimple(71, 11, shouldShowYellow);
  flipDotSimple(71, 12, shouldShowYellow);
  flipDotSimple(70, 12, shouldShowYellow);
  flipDotSimple(70, 13, shouldShowYellow);
  flipDotSimple(69, 13, shouldShowYellow);
  flipDotSimple(68, 13, shouldShowYellow);
  flipDotSimple(67, 13, shouldShowYellow);
  flipDotSimple(67, 12, shouldShowYellow);
  flipDotSimple(66, 12, shouldShowYellow);
  flipDotSimple(66, 11, shouldShowYellow);
  flipDotSimple(66, 10, shouldShowYellow);
  flipDotSimple(66, 9, shouldShowYellow);
  flipDotSimple(66, 8, shouldShowYellow);
  flipDotSimple(66, 7, shouldShowYellow);
  flipDotSimple(67, 7, shouldShowYellow);
}

void flipLetterN(boolean shouldShowYellow) {
  flipDotSimple(74, 6, shouldShowYellow);
  flipDotSimple(74, 7, shouldShowYellow);
  flipDotSimple(74, 8, shouldShowYellow);
  flipDotSimple(74, 9, shouldShowYellow);
  flipDotSimple(74, 10, shouldShowYellow);
  flipDotSimple(74, 11, shouldShowYellow);
  flipDotSimple(74, 12, shouldShowYellow);
  flipDotSimple(74, 13, shouldShowYellow);
  flipDotSimple(75, 7, shouldShowYellow);
  flipDotSimple(76, 6, shouldShowYellow);
  flipDotSimple(77, 6, shouldShowYellow);
  flipDotSimple(78, 6, shouldShowYellow);
  flipDotSimple(79, 7, shouldShowYellow);
  flipDotSimple(79, 8, shouldShowYellow);
  flipDotSimple(79, 9, shouldShowYellow);
  flipDotSimple(79, 10, shouldShowYellow);
  flipDotSimple(79, 11, shouldShowYellow);
  flipDotSimple(79, 12, shouldShowYellow);
  flipDotSimple(79, 13, shouldShowYellow);
}

void flipFirstSeven(bool shouldShowYellow) {
  flipDotSimple(82, 4, shouldShowYellow);
  flipDotSimple(83, 4, shouldShowYellow);
  flipDotSimple(84, 4, shouldShowYellow);
  flipDotSimple(85, 4, shouldShowYellow);
  flipDotSimple(86, 4, shouldShowYellow);
  flipDotSimple(87, 4, shouldShowYellow);
  flipDotSimple(88, 4, shouldShowYellow);
  flipDotSimple(88, 5, shouldShowYellow);
  flipDotSimple(87, 5, shouldShowYellow);
  flipDotSimple(87, 6, shouldShowYellow);
  flipDotSimple(86, 7, shouldShowYellow);
  flipDotSimple(86, 8, shouldShowYellow);
  flipDotSimple(85, 9, shouldShowYellow);
  flipDotSimple(85, 10, shouldShowYellow);
  flipDotSimple(84, 11, shouldShowYellow);
  flipDotSimple(84, 12, shouldShowYellow);
  flipDotSimple(83, 13, shouldShowYellow);
}

void flipSecondSeven(bool shouldShowYellow) {
  flipDotSimple(90, 4, shouldShowYellow);
  flipDotSimple(91, 4, shouldShowYellow);
  flipDotSimple(92, 4, shouldShowYellow);
  flipDotSimple(93, 4, shouldShowYellow);
  flipDotSimple(94, 4, shouldShowYellow);
  flipDotSimple(95, 4, shouldShowYellow);
  flipDotSimple(96, 4, shouldShowYellow);
  flipDotSimple(96, 5, shouldShowYellow);
  flipDotSimple(95, 5, shouldShowYellow);
  flipDotSimple(95, 6, shouldShowYellow);
  flipDotSimple(94, 7, shouldShowYellow);
  flipDotSimple(94, 8, shouldShowYellow);
  flipDotSimple(93, 9, shouldShowYellow);
  flipDotSimple(93, 10, shouldShowYellow);
  flipDotSimple(92, 11, shouldShowYellow);
  flipDotSimple(92, 12, shouldShowYellow);
  flipDotSimple(91, 13, shouldShowYellow);
}

void showLinesRight() {
  // 3rd from top
  flipDotSimple(97, 4, true);
  flipDotSimple(98, 4, true);
  flipDotSimple(99, 4, true);
  flipDotSimple(100, 4, true);
  flipDotSimple(101, 4, true);
  flipDotSimple(102, 4, true);
  flipDotSimple(103, 4, true);
  flipDotSimple(104, 4, true);
  flipDotSimple(105, 4, true);
  flipDotSimple(105, 5, true);
  flipDotSimple(105, 6, true);
  flipDotSimple(105, 7, true);
  for (byte i = 105; i < 126; i++) {
    flipDotSimple(i, 8, true);
  }

  // 1st from top
  flipDotSimple(82, 3, true);
  flipDotSimple(82, 2, true);
  for (byte i = 82; i < 117; i++) {
    flipDotSimple(i, 1, true);
  }
  flipDotSimple(116, 2, true);
  flipDotSimple(116, 3, true);
  for (byte i = 116; i < 126; i++) {
    flipDotSimple(i, 4, true);
  }

  // 4th from top
  flipDotSimple(101, 8, true);
  flipDotSimple(101, 7, true);
  flipDotSimple(101, 6, true);
  flipDotSimple(102, 6, true);
  flipDotSimple(103, 6, true);
  flipDotSimple(103, 7, true);
  flipDotSimple(103, 8, true);
  flipDotSimple(102, 8, true);
  flipDotSimple(102, 9, true);
  flipDotSimple(102, 10, true);
  flipDotSimple(102, 11, true);
  flipDotSimple(102, 12, true);
  flipDotSimple(102, 13, true);
  flipDotSimple(103, 13, true);
  flipDotSimple(104, 13, true);
  flipDotSimple(105, 13, true);
  flipDotSimple(105, 12, true);
  flipDotSimple(105, 11, true);
  for (byte i = 105; i < 126; i++) {
    flipDotSimple(i, 10, true);
  }
  
  // 2nd from top
  flipDotSimple(110, 4, true);
  flipDotSimple(109, 4, true);
  flipDotSimple(108, 4, true);
  flipDotSimple(108, 5, true);
  flipDotSimple(108, 6, true);
  flipDotSimple(109, 6, true);
  flipDotSimple(110, 6, true);
  flipDotSimple(110, 5, true);
  flipDotSimple(111, 5, true);
  flipDotSimple(112, 5, true);
  flipDotSimple(113, 5, true);
  flipDotSimple(114, 5, true);
  for (byte i = 114; i < 126; i++) {
    flipDotSimple(i, 6, true);
  }
}

void sendOnLineRight1() {
  toggleDot(87, 4);
  toggleDot(86, 4);
  toggleDot(85, 4);
  toggleDot(84, 4);
  toggleDot(83, 4);
  toggleDot(82, 4);
  toggleDot(82, 3);
  toggleDot(82, 2);
  for (byte i = 82; i < 117; i++) {
    toggleDot(i, 1);
  }
  toggleDot(116, 2);
  toggleDot(116, 3);
  for (byte i = 116; i < 126; i++) {
    toggleDot(i, 4);
  }
}

void sendOnLineRight2() {
  for (byte i = 125; i > 113; i--) {
    toggleDot(i, 6);
  }
  toggleDot(114, 5);
  toggleDot(113, 5);
  toggleDot(112, 5);
  toggleDot(111, 5);
  toggleDot(110, 5);
}

void sendOnLineRight3() {
  for (byte i = 90; i < 106; i++) {
    toggleDot(i, 4);
  }
  toggleDot(105, 5);
  toggleDot(105, 6);
  toggleDot(105, 7);
  for (byte i = 105; i < 126; i++) {
    toggleDot(i, 8);
  }
}

void sendOnLineRight4() {
  for (byte i = 125; i > 104; i--) {
    toggleDot(i, 10);
  }
  toggleDot(105, 11);
  toggleDot(105, 12);
  toggleDot(105, 13);
  toggleDot(104, 13);
  toggleDot(103, 13);
  toggleDot(102, 13);
  toggleDot(102, 12);
  toggleDot(102, 11);
  toggleDot(102, 10);
  toggleDot(102, 9);
  toggleDot(102, 8);
}

void showLinesLeft() {
  // 4th from top
  flipDotSimple(25, 12, true);
  flipDotSimple(24, 12, true);
  flipDotSimple(23, 12, true);
  for (byte i = 23; i >= 0; i--) {
    flipDotSimple(i, 11, true);
  }

  // 2nd from top
  flipDotSimple(52, 3, true);
  for (byte i = 52; i > 13; i--) {
    flipDotSimple(i, 2, true);
  }
  flipDotSimple(14, 3, true);
  flipDotSimple(14, 4, true);
  flipDotSimple(14, 5, true);
  flipDotSimple(14, 6, true);
  for (byte i = 14; i >= 0; i--) {
    flipDotSimple(i, 7, true);
  }

  // 3rd from top
  flipDotSimple(19, 6, true);
  flipDotSimple(20, 6, true);
  flipDotSimple(21, 6, true);
  flipDotSimple(21, 7, true);
  flipDotSimple(21, 8, true);
  flipDotSimple(20, 8, true);
  flipDotSimple(19, 8, true);
  flipDotSimple(19, 7, true);
  flipDotSimple(18, 7, true);
  flipDotSimple(17, 7, true);
  flipDotSimple(16, 7, true);
  flipDotSimple(16, 8, true);
  for (byte i = 16; i >= 0; i--) {
    flipDotSimple(i, 9, true);
  }

  // 1st from top
  flipDotSimple(8, 1, true);
  flipDotSimple(7, 1, true);
  flipDotSimple(6, 1, true);
  flipDotSimple(6, 2, true);
  flipDotSimple(6, 3, true);
  flipDotSimple(7, 3, true);
  flipDotSimple(8, 3, true);
  flipDotSimple(8, 2, true);
  flipDotSimple(9, 2, true);
  flipDotSimple(10, 2, true);
  flipDotSimple(11, 2, true);
  flipDotSimple(12, 2, true);
  flipDotSimple(12, 3, true);
  flipDotSimple(12, 4, true);
  for (byte i = 12; i >= 0; i--) {
    flipDotSimple(i, 5, true);
  }
}

void sendOnLineLeft1() {
  for (byte i = 0; i < 13; i++) {
    toggleDot(i, 5);
  }
  toggleDot(12, 4);
  toggleDot(12, 3);
  toggleDot(12, 2);
  toggleDot(11, 2);
  toggleDot(10, 2);
  toggleDot(9, 2);
  toggleDot(8, 2);
}

void sendOnLineLeft2() {
  toggleDot(52, 6);
  toggleDot(52, 5);
  toggleDot(52, 4);
  toggleDot(52, 3);
  for (byte i = 52; i > 13; i--) {
    toggleDot(i, 2);
  }
  toggleDot(14, 3);
  toggleDot(14, 4);
  toggleDot(14, 5);
  toggleDot(14, 6);
  for (byte i = 14; i >= 0; i--) {
    toggleDot(i, 7);
  }
}

void sendOnLineLeft3() {
  for (byte i = 0; i < 17; i++) {
    toggleDot(i, 9);
  }
  toggleDot(16, 8);
  toggleDot(16, 7);
  toggleDot(17, 7);
  toggleDot(18, 7);
  toggleDot(19, 7);
}

void sendOnLineLeft4() {
  toggleDot(30, 13);
  toggleDot(29, 13);
  toggleDot(28, 13);
  toggleDot(27, 13);
  toggleDot(26, 13);
  toggleDot(26, 12);
  toggleDot(25, 12);
  toggleDot(24, 12);
  toggleDot(23, 12);
  for (byte i = 23; i >= 0; i--) {
    toggleDot(i, 11);
  }
}

void showIDotLine() {
  flipDotSimple(70, 0, true);
  flipDotSimple(70, 1, true);
  flipDotSimple(70, 2, true);
  flipDotSimple(70, 3, true);
  flipDotSimple(69, 3, true);
  flipDotSimple(68, 3, true);
  flipDotSimple(67, 3, true);
  flipDotSimple(66, 3, true);
  flipDotSimple(65, 3, true);
  flipDotSimple(64, 3, true);
  flipDotSimple(63, 3, true);
  flipDotSimple(62, 3, true);
  flipDotSimple(61, 2, true);
  flipDotSimple(60, 2, true);
  flipDotSimple(59, 2, true);
  flipDotSimple(59, 3, true);
  flipDotSimple(59, 4, true);
  flipDotSimple(60, 4, true);
}

void sendOnIDotLine() {
  toggleDot(61, 3);
  toggleDot(62, 3);
  toggleDot(63, 3);
  toggleDot(64, 3);
  toggleDot(65, 3);
  toggleDot(66, 3);
  toggleDot(67, 3);
  toggleDot(68, 3);
  toggleDot(69, 3);
  toggleDot(70, 3);
  toggleDot(70, 2);
  toggleDot(70, 1);
  toggleDot(70, 0);
}


// helper functions

void flipDisplay(boolean shouldShowYellow) {
  for (byte moduleIndex = 0; moduleIndex < sizeof(MODULE_PINS); moduleIndex++) {
    flipModule(moduleIndex, shouldShowYellow);
  }
}

void flipModule(byte moduleIndex, boolean shouldShowYellow) {
  for (byte columnIndex = getStartColumnOfModule(moduleIndex); columnIndex < MODULE_WIDTH; columnIndex++) {
    flipColumn(moduleIndex, columnIndex, shouldShowYellow);
  }
}

byte getStartColumnOfModule(byte moduleIndex) {
  if (moduleIndex == 0) {
    return COLUMN_OFFSET_SHORT_MODULE;
  } else {
    return 0;
  }
}

void flipColumn(byte moduleIndex, byte columnIndex, boolean shouldShowYellow) {
  for (byte rowIndex = 0; rowIndex < MODULE_HEIGHT; rowIndex++) {
    flipDot(moduleIndex, rowIndex, columnIndex, shouldShowYellow);
  }
}

void toggleDot(byte x, byte y) {
  flipDotSimple(x, y, false);
  delay(100);
  flipDotSimple(x, y, true);
}

// basic dot flipping stuff

void flipDotSimple(byte x, byte y, boolean shouldShowYellow) {
  if (x >= DISPLAY_WIDTH || y >= MODULE_HEIGHT) {
    return;
  }
  
  byte xWithOffset = x + COLUMN_OFFSET_SHORT_MODULE;
  byte moduleIndex = xWithOffset / MODULE_WIDTH;
  byte columnOnModule = xWithOffset % MODULE_WIDTH;

  flipDot(moduleIndex, y, columnOnModule, shouldShowYellow);
}

void flipDot(byte moduleIndex, byte rowIndex, byte columnIndex, boolean shouldShowYellow) {
  setRowAddress(rowIndex);
  setColumnAddress(columnIndex);
  flipDotAtModule(moduleIndex, shouldShowYellow);
  
  if (PAUSE_BETWEEN_DOT_FLIPS_IN_MS > 0) {
    delay(PAUSE_BETWEEN_DOT_FLIPS_IN_MS);
  }
}

void setRowAddress(byte rowIndex) {
  for (byte rowIndexBit = 0; rowIndexBit < sizeof(ROW_BIT_PINS); rowIndexBit++) {
    boolean isBitSet = bitRead(rowIndex, rowIndexBit);
    if (isBitSet) {
      digitalWrite(ROW_BIT_PINS[rowIndexBit], HIGH);
    } else {
      digitalWrite(ROW_BIT_PINS[rowIndexBit], LOW);
    }
  }
}

void setColumnAddress(byte columnIndex) {
  for (byte columnIndexBit = 0; columnIndexBit < sizeof(COLUMN_BIT_PINS); columnIndexBit++) {
    boolean isBitSet = bitRead(columnIndex, columnIndexBit);
    if (isBitSet) {
      digitalWrite(COLUMN_BIT_PINS[columnIndexBit], HIGH);
    } else {
      digitalWrite(COLUMN_BIT_PINS[columnIndexBit], LOW);
    }
  }
}

void flipDotAtModule(byte moduleIndex, boolean shouldShowYellow) {
  if (shouldShowYellow) {
    flipDotYellowAtModule(moduleIndex);
  } else {
    flipDotBlackAtModule(moduleIndex);
  }
}

void flipDotYellowAtModule(byte moduleIndex) {
  digitalWrite(DATA, HIGH);
  delayMicroseconds(100);
  digitalWrite(MODULE_PINS[moduleIndex], HIGH);
  digitalWrite(ENABLE_SET, HIGH);
  delayMicroseconds(750);
  digitalWrite(ENABLE_SET, LOW);
  digitalWrite(MODULE_PINS[moduleIndex], LOW);
  delayMicroseconds(100);
  
}

void flipDotBlackAtModule(byte moduleIndex) {
  digitalWrite(DATA, LOW);
  delayMicroseconds(100);
  digitalWrite(MODULE_PINS[moduleIndex], HIGH);
  digitalWrite(ENABLE_RESET, HIGH);
  delayMicroseconds(750);
  digitalWrite(ENABLE_RESET, LOW);
  digitalWrite(MODULE_PINS[moduleIndex], LOW);
  delayMicroseconds(100);
}

void setup() {
  pinMode(DATA, OUTPUT);
  pinMode(COLUMN_1, OUTPUT);
  pinMode(COLUMN_2, OUTPUT);
  pinMode(COLUMN_3, OUTPUT);
  pinMode(COLUMN_4, OUTPUT);
  pinMode(COLUMN_5, OUTPUT);
  pinMode(ROW_1, OUTPUT);
  pinMode(ROW_2, OUTPUT);
  pinMode(ROW_3, OUTPUT);
  pinMode(ROW_4, OUTPUT);
  pinMode(ENABLE_SET, OUTPUT);
  pinMode(ENABLE_RESET, OUTPUT);
  pinMode(MODULE_1, OUTPUT);
  pinMode(MODULE_2, OUTPUT);
  pinMode(MODULE_3, OUTPUT);
  pinMode(MODULE_4, OUTPUT);
  pinMode(MODULE_5, OUTPUT);

  digitalWrite(DATA, LOW);
  digitalWrite(COLUMN_1, LOW);
  digitalWrite(COLUMN_2, LOW);
  digitalWrite(COLUMN_3, LOW);
  digitalWrite(COLUMN_4, LOW);
  digitalWrite(COLUMN_5, LOW);
  digitalWrite(ROW_1, LOW);
  digitalWrite(ROW_2, LOW);
  digitalWrite(ROW_3, LOW);
  digitalWrite(ROW_4, LOW);
  digitalWrite(ENABLE_SET, LOW);
  digitalWrite(ENABLE_RESET, LOW);
  digitalWrite(MODULE_1, LOW);
  digitalWrite(MODULE_2, LOW);
  digitalWrite(MODULE_3, LOW);
  digitalWrite(MODULE_4, LOW);
  digitalWrite(MODULE_5, LOW);

  delay(2000);

  flipDisplay(false);
  delay(500);

  showName();
  delay(5000);

  showLinesRight();
  showLinesLeft();
  delay(3000);

  showIDotLine();
  delay(5000);
}
