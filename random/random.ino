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

// program config
const int PAUSE_BETWEEN_DOT_FLIPS_IN_MS = 2; // lowest value to reliably flip all dots with 5A power supply (lights off)
const int PAUSE_BETWEEN_RANDOM_FLIP_IN_MS = 50;

void loop() {
  flipRandomDot();
  delay(PAUSE_BETWEEN_RANDOM_FLIP_IN_MS);
}

// helper functions

void flipRandomDot() {
  int moduleIndex = random(sizeof(MODULE_PINS));
  int rowIndex = random(MODULE_HEIGHT);
  int columnIndex = random(getStartColumnOfModule(moduleIndex), MODULE_WIDTH);
  boolean shouldShowYellow = random(2) == 1;
  flipDot(moduleIndex, rowIndex, columnIndex, shouldShowYellow);
}

byte getStartColumnOfModule(byte moduleIndex) {
  if (moduleIndex == 0) {
    return COLUMN_OFFSET_SHORT_MODULE;
  } else {
    return 0;
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

  delay(5000);
}

