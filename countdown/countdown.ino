#include "font8x8_basic.h"
#include "6x8_horizontal_LSB_1.h"
#include "config.h"
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// pin assignments
// 
// pin on lolin32 header      // pin on column driver input header
// -------------------------- // ---------------------------------
//         GND                // (1-4, 31-34)
const byte DATA = 0;
const byte COLUMN_1 = 21;
const byte COLUMN_2 = 19;
const byte COLUMN_3 = 23;
const byte COLUMN_4 = 18;
const byte COLUMN_5 = 5;
const byte ROW_1 = 17;
const byte ROW_2 = 16;
const byte ROW_3 = 4;
const byte ROW_4 = 22;
const byte ENABLE_SET = 2;
const byte ENABLE_RESET = 15;
const byte MODULE_1 = 27;
const byte MODULE_2 = 14;
const byte MODULE_3 = 12;
const byte MODULE_4 = 13;
const byte MODULE_5 = 26; // not connected


// helper constants
const byte MODULE_PINS[] = {MODULE_1, MODULE_2, MODULE_3, MODULE_4};
const byte COLUMN_BIT_PINS[] = {COLUMN_1, COLUMN_2, COLUMN_3, COLUMN_4, COLUMN_5};
const byte ROW_BIT_PINS[] = {ROW_1, ROW_2, ROW_3, ROW_4};
const byte MODULE_HEIGHT = 16;
const byte MODULE_WIDTH = 28;
const byte COLUMN_OFFSET_SHORT_MODULE = 14;
const byte DISPLAY_WIDTH = 126;

const byte MODE_LEFT_TO_RIGHT = 1;
const byte MODE_RIGHT_TO_LEFT = 2;
const byte MODE_CURTAIN_OUT = 3;

// program config
const int PAUSE_BETWEEN_DOT_FLIPS_IN_MS = 2; // lowest value to reliably flip all dots with 5A power supply (lights off)
const int MAX_PAUSE_BETWEEN_ACTIONS = 5000;

// Event time
long timeJubilee = 1700000000;
// Heilig Abend 20:00 CET
long timeJubilee2 = 1703444400;

// internal storage for the current state of the display
boolean dotmatrix[DISPLAY_WIDTH][MODULE_HEIGHT];

// last time the clock was updated
long lastUpdate = 0;

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
  

void setup() {

  Serial.begin(115200);
  
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

  //delay(2000);

  // connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);    
  }

  // Initialize NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT 0 = 0
  timeClient.setTimeOffset(0);
  timeClient.update();  
  lastUpdate = timeClient.getEpochTime();

  // TEST
  // timeJubilee = lastUpdate + 25;

  // Reset Display to blank
  for (int x = 0; x < DISPLAY_WIDTH; x++) {
    for (int y = 0; y < MODULE_HEIGHT; y++) {
      flipDotSimple(x, y, false, true);
    }
  }
}


void loop() {

  char txtCurTime[19];
  char txtTime2Wait[19];
  // char txtCurTimeOld[18];
  // char txtTime2WaitOld[18];

  if (timeClient.getEpochTime() - lastUpdate > 3600) {
    timeClient.update();
    lastUpdate = timeClient.getEpochTime();
    // Display löschen
    for (int x = 0; x < DISPLAY_WIDTH; x++) {
      for (int y = 0; y < MODULE_HEIGHT; y++) {
        flipDotSimple(x, y, false, true);
      }
    }
  } else {
    flipDisplay(false, MODE_CURTAIN_OUT);
  }
 
  // section77 Schriftzug anzeigen
  showName(true);
  delay(2000);

  // section77 Schriftzug wieder löschen
  showName(false);

  // Countdown bis zu DEM EREIGNIS anzeigen
  long curTime = timeClient.getEpochTime();
  long timeToWait = timeJubilee - curTime;
  sprintf(txtTime2Wait, "Noch %12ss", printfcomma(timeToWait));
  if (timeJubilee == timeJubilee2) {
    sprintf(txtCurTime, "%s", " bis Weihnachten  ");
    showText6x8(2, 0, txtTime2Wait, true);
    showText6x8(2, 8, txtCurTime, true);
  } else {
    sprintf(txtCurTime, " %15ss", printfcomma(curTime));
    showText6x8(0, 0, txtCurTime, true);
    showText6x8(0, 8, txtTime2Wait, true);
  }

  // we don't want to miss THE EVENT
  int loops = timeToWait < 60 ? 80: 15;

  for (int i=0; i<loops; i++) {
    long curTime = timeClient.getEpochTime();
    long timeToWait = timeJubilee - curTime;
    if (timeToWait < 0) {
      happyDings();
      break;
    }
    sprintf(txtTime2Wait, "Noch %12ss", printfcomma(timeToWait));
    if (timeJubilee == timeJubilee2) {
      sprintf(txtCurTime, "%s", " bis Weihnachten  ");
      showText6x8(2, 0, txtTime2Wait, true);
      showText6x8(2, 8, txtCurTime, true);
    } else {
      sprintf(txtCurTime, " %15ss", printfcomma(curTime));
      showText6x8(0, 0, txtCurTime, true);
      showText6x8(0, 8, txtTime2Wait, true);
    }

    while (timeClient.getEpochTime() == curTime) {}

  }

}


void happyDings() {
  flipDisplay(false, MODE_CURTAIN_OUT);
  showText6x8(0, 4, "Happy New", true);
  delay(1000);
  int pos = 10;
  while (pos < 13) {
    showText6x8(pos * 6 , 4, ".", true);
    delay(1000);
    pos++;
  }
  showText6x8((pos+1) * 6 , 4, "Dings!", true);
  delay(5000);
  timeJubilee = timeJubilee2;
}

// custom drawing

void showText6x8(int posX, int posY, String text, bool set) {
  for (int i = 0; i < text.length(); i++) {
    char character = text.charAt(i);
    for (int n=0; n < 8; n++) {
      for (int bit=2; bit < 8; bit++) {
        if (font6x8_basic[character][n] & (1 << bit)) {
          flipDotSimple(posX + i * 6 + bit, posY + n, set);
        } else {
          flipDotSimple(posX + i * 6 + bit, posY + n, !set);
        }

      }
    }
  }
}

void showText8x8(int posX, int posY, String text) {
  for (int i = 0; i < text.length(); i++) {
    char character = text.charAt(i);
    for (int n=0; n < 8; n++) {
      for (int bit=0; bit < 8; bit++) {
        flipDotSimple(posX + i * 8 + bit, posY + n, font8x8_basic[character][n] & (1 << bit));
      }
    }
  }
}

String printfcomma (long n) {
    String result = "";
    char tmp[20];
    if (n < 0) {
        result = "-";
        result += printfcomma (-n);
        return result;
    }
    if (n < 1000) {
        sprintf(tmp, "%d", n);
        result = result + tmp;
        return result;
    }
    result = result + printfcomma (n/1000);
    sprintf (tmp, ".%03d", n%1000);
    result = result + tmp;
    return result;
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

void showName(boolean show) {
  flipLetterS(show);
  flipLetterE(show);
  flipLetterC(show);
  flipLetterT(show);
  flipLetterI(show);
  flipLetterO(show);
  flipLetterN(show);
  flipFirstSeven(show);
  flipSecondSeven(show);
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
  for (int i = 105; i < 126; i++) {
    flipDotSimple(i, 8, true);
  }

  // 1st from top
  flipDotSimple(82, 3, true);
  flipDotSimple(82, 2, true);
  for (int i = 82; i < 117; i++) {
    flipDotSimple(i, 1, true);
  }
  flipDotSimple(116, 2, true);
  flipDotSimple(116, 3, true);
  for (int i = 116; i < 126; i++) {
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
  for (int i = 105; i < 126; i++) {
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
  for (int i = 114; i < 126; i++) {
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
  for (int i = 82; i < 117; i++) {
    toggleDot(i, 1);
  }
  toggleDot(116, 2);
  toggleDot(116, 3);
  for (int i = 116; i < 126; i++) {
    toggleDot(i, 4);
  }
}

void sendOnLineRight2() {
  for (int i = 125; i > 113; i--) {
    toggleDot(i, 6);
  }
  toggleDot(114, 5);
  toggleDot(113, 5);
  toggleDot(112, 5);
  toggleDot(111, 5);
  toggleDot(110, 5);
}

void sendOnLineRight3() {
  for (int i = 90; i < 106; i++) {
    toggleDot(i, 4);
  }
  toggleDot(105, 5);
  toggleDot(105, 6);
  toggleDot(105, 7);
  for (int i = 105; i < 126; i++) {
    toggleDot(i, 8);
  }
}

void sendOnLineRight4() {
  for (int i = 125; i > 104; i--) {
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
  for (int i = 23; i >= 0; i--) {
    flipDotSimple(i, 11, true);
  }

  // 2nd from top
  flipDotSimple(52, 3, true);
  for (int i = 52; i > 13; i--) {
    flipDotSimple(i, 2, true);
  }
  flipDotSimple(14, 3, true);
  flipDotSimple(14, 4, true);
  flipDotSimple(14, 5, true);
  flipDotSimple(14, 6, true);
  for (int i = 14; i >= 0; i--) {
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
  for (int i = 16; i >= 0; i--) {
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
  for (int i = 12; i >= 0; i--) {
    flipDotSimple(i, 5, true);
  }
}

void sendOnLineLeft1() {
  for (int i = 0; i < 13; i++) {
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
  for (int i = 52; i > 13; i--) {
    toggleDot(i, 2);
  }
  toggleDot(14, 3);
  toggleDot(14, 4);
  toggleDot(14, 5);
  toggleDot(14, 6);
  for (int i = 14; i >= 0; i--) {
    toggleDot(i, 7);
  }
}

void sendOnLineLeft3() {
  for (int i = 0; i < 17; i++) {
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
  for (int i = 23; i >= 0; i--) {
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

void flipColumn(int x, boolean shouldShowYellow) {
  for (int y = 0; y < MODULE_HEIGHT; y++) {
    flipDotSimple(x, y, shouldShowYellow);
  }
}

void flipDisplay(boolean shouldShowYellow) {
  flipDisplay(shouldShowYellow, MODE_LEFT_TO_RIGHT);
}

void flipDisplay(boolean shouldShowYellow, byte mode) {
  switch (mode) {
    case MODE_LEFT_TO_RIGHT:
      for (int x = 0; x < DISPLAY_WIDTH; x++) {
        flipColumn(x, shouldShowYellow);
     }
      break;
    case MODE_RIGHT_TO_LEFT:
      for (int x = DISPLAY_WIDTH - 1; x >= 0; x--) {
        flipColumn(x, shouldShowYellow);
      }
      break;
    case MODE_CURTAIN_OUT:
      for (int a = 0; a < DISPLAY_WIDTH / 2; a++) {
        int x = DISPLAY_WIDTH / 2 - 1 - a;
        flipColumn(x, shouldShowYellow);
        x = DISPLAY_WIDTH / 2 + a;
        flipColumn(x, shouldShowYellow);
      }

  }
}

void flipModule(byte moduleIndex, boolean shouldShowYellow) {
  for (int columnIndex = 0; columnIndex < MODULE_WIDTH; columnIndex++) {
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
  for (int rowIndex = 0; rowIndex < MODULE_HEIGHT; rowIndex++) {
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
  flipDotSimple(x, y, shouldShowYellow, false);
}

void flipDotSimple(byte x, byte y, boolean shouldShowYellow, boolean force) {
  if (x >= DISPLAY_WIDTH || y >= MODULE_HEIGHT) {
    return;
  }

  byte moduleIndex = x / MODULE_WIDTH;
  byte columnOnModule = x % MODULE_WIDTH;

  if (dotmatrix[x][y] != shouldShowYellow || force) {
    dotmatrix[x][y] = shouldShowYellow;
    flipDot(moduleIndex, y, columnOnModule, shouldShowYellow);
    Serial.printf("{\"row\": %d, \"column\": %d, \"status\": %d}\n", y, x, shouldShowYellow);
  }
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
  for (int rowIndexBit = 0; rowIndexBit < sizeof(ROW_BIT_PINS); rowIndexBit++) {
    boolean isBitSet = bitRead(rowIndex, rowIndexBit);
    if (isBitSet) {
      digitalWrite(ROW_BIT_PINS[rowIndexBit], HIGH);
    } else {
      digitalWrite(ROW_BIT_PINS[rowIndexBit], LOW);
    }
  }
}

void setColumnAddress(byte columnIndex) {
  for (int columnIndexBit = 0; columnIndexBit < sizeof(COLUMN_BIT_PINS); columnIndexBit++) {
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
