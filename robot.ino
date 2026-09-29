#include <Wire.h>
#include <U8g2lib.h>

// OLED: SH1106 128x64
U8G2_SH1106_128X64_NONAME_F_HW_I2C oled(U8G2_R0, U8X8_PIN_NONE);

// ESP32 Dev Module I2C pins
#define SDA_PIN 21
#define SCL_PIN 22

// Touch sensor
#define TOUCH_PIN 4

bool happyFace = false;

void setup() {
  Wire.begin(SDA_PIN, SCL_PIN);

  oled.begin();
  oled.clearBuffer();

  pinMode(TOUCH_PIN, INPUT);

  drawFace();
}

void loop() {

  if (digitalRead(TOUCH_PIN) == HIGH) {
    happyFace = !happyFace;
    drawFace();

    delay(500);
  }
}

void drawFace() {

  oled.clearBuffer();

  // Left eye
  if (happyFace) {
    oled.drawLine(25, 30, 35, 25);
    oled.drawLine(35, 25, 45, 30);

    // Right eye
    oled.drawLine(80, 30, 90, 25);
    oled.drawLine(90, 25, 100, 30);
  } 
  else {
    oled.drawDisc(35, 30, 8);
    oled.drawDisc(90, 30, 8);
  }

  // Small smile
  oled.drawLine(55, 45, 64, 50);
  oled.drawLine(64, 50, 73, 45);

  // Clock
  oled.setFont(u8g2_font_6x10_tf);
  oled.drawStr(42, 62, "10:30");

  oled.sendBuffer();
}
