// pin assignments
// 
// pin on arduino header      // pin on column driver input header
// -------------------------- // ---------------------------------
//         GND                // (1-4, 31-34)
const byte DATA = 0;          // (8)
const byte COLUMN_1 = 1;      // (7)
const byte COLUMN_2 = 2;      // (9)
const byte COLUMN_3 = 3;      // (11)
const byte COLUMN_4 = 4;      // (13)
const byte COLUMN_5 = 5;      // (15)
const byte ROW_1 = 6;         // (17)
const byte ROW_2 = 7;         // (19)
const byte ROW_3 = 8;         // (21)
const byte ROW_4 = 9;         // (23)
const byte ENABLE_SET = 10;   // (10)
const byte ENABLE_RESET = 11; // (12)
const byte MODULE_1 = 12;     // (20)
const byte MODULE_2 = 13;     // (22)
//         MODULE_3           // (24)
//         MODULE_4           // (26)
//         MODULE_5           // (28)

// helper constants
const byte MODULE_PINS[] = {MODULE_1, MODULE_2}; // TODO extend when a board with enough i/o ports is available
const byte COLUMN_BIT_PINS[] = {COLUMN_1, COLUMN_2, COLUMN_3, COLUMN_4, COLUMN_5};
const byte ROW_BIT_PINS[] = {ROW_1, ROW_2, ROW_3, ROW_4};
const byte MODULE_HEIGHT = 16;
const byte MODULE_WIDTH_SMALL = 14;
const byte MODULE_WIDTH_LARGE = 28;

// program config
const int PAUSE_BETWEEN_DOT_FLIPS_IN_MS = 250; // TODO decrease slowly to measure maximum current draw
const int PAUSE_BETWEEN_PATTERNS_IN_MS = 5000;

void loop() {
  flipDisplay(true);
  delay(PAUSE_BETWEEN_PATTERNS_IN_MS);
  flipDisplay(false);
  delay(PAUSE_BETWEEN_PATTERNS_IN_MS);
  flipDisplayAlternating(true);
  delay(PAUSE_BETWEEN_PATTERNS_IN_MS);
  flipDisplayAlternating(false);
  delay(PAUSE_BETWEEN_PATTERNS_IN_MS);
}

// helper functions

void flipDisplayAlternating(boolean startWithYellow) {
  boolean nextDotIsYellow = startWithYellow;
  for (byte moduleIndex = 0; moduleIndex < sizeof(MODULE_PINS); moduleIndex++) {
    nextDotIsYellow = flipModuleAlternating(moduleIndex, nextDotIsYellow);
  }
}

boolean flipModuleAlternating(byte moduleIndex, boolean startWithYellow) {
  boolean nextDotIsYellow = startWithYellow;
  for (byte columnIndex = 0; columnIndex < getColumnsOnModule(moduleIndex); columnIndex++) {
    nextDotIsYellow = flipColumnAlternating(moduleIndex, columnIndex, nextDotIsYellow);
  }
  return nextDotIsYellow;
}

boolean flipColumnAlternating(byte moduleIndex, byte columnIndex, boolean startWithYellow) {
  boolean shouldShowYellow = startWithYellow;
  for (byte rowIndex = 0; rowIndex < MODULE_HEIGHT; rowIndex++) {
    flipDot(moduleIndex, rowIndex, columnIndex, shouldShowYellow);
    shouldShowYellow = !shouldShowYellow;
  }
  return shouldShowYellow;
}

void flipDisplay(boolean shouldShowYellow) {
  for (byte moduleIndex = 0; moduleIndex < sizeof(MODULE_PINS); moduleIndex++) {
    flipModule(moduleIndex, shouldShowYellow);
  }
}

void flipModule(byte moduleIndex, boolean shouldShowYellow) {
  for (byte columnIndex = 0; columnIndex < getColumnsOnModule(moduleIndex); columnIndex++) {
    flipColumn(moduleIndex, columnIndex, shouldShowYellow);
  }
}

byte getColumnsOnModule(byte moduleIndex) {
  if (moduleIndex == 0) {
    return MODULE_WIDTH_SMALL;
  } else {
    return MODULE_WIDTH_LARGE;
  }
}

void flipColumn(byte moduleIndex, byte columnIndex, boolean shouldShowYellow) {
  for (byte rowIndex = 0; rowIndex < MODULE_HEIGHT; rowIndex++) {
    flipDot(moduleIndex, rowIndex, columnIndex, shouldShowYellow);
  }
}

// basic dot flipping stuff

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
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  digitalWrite(0, LOW);
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);

  delay(2000);
}

