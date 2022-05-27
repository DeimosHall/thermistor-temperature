#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define sensor 33
double voltage = 0, temperature = 0;

void setup() {
  pinMode(sensor,INPUT);
  Serial.begin(115200);
  Serial.println("Connection started");

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
  }
}

void loop() {
  voltage = (analogRead(sensor) * 3.3 / 4095) + 0.1; // This + 0.1 is an adc correction
  temperature = voltage * 80 / 2;
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(25, 0);
  display.println("Temperature");
  display.display();

  display.setTextSize(2);
  display.setCursor(15, 30);
  display.println(temperature);
  display.display();
  
  display.setCursor(80, 30);
  display.println("C");
  display.display();
  delay(100);
}
