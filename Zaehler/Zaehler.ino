/**************************************************************************
Besucherzähler für die Bibi Wulfen

Version 0.3
(c) 2022 Jörg Skapski, Markus Soick
**************************************************************************/

// Bibliotheken
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Version
#define VERSION "(c) 2022, v0.3"

// Konstanten
#define PIN_U A0  // Eingangs-Pin zur Spannungsmessung
#define PIN_LS D5  // Eingangs-Pin für die Lichtschranke (D3=GPIO0)

// OLED-Display
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
#define WEISS SSD1306_WHITE
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  // Pins initialisieren
  pinMode(PIN_LS,INPUT);
  // OLED initialisieren
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  display.clearDisplay();
  display.display();

  // Startbildschirm
  startbild();
}

void loop() {
  // Spannung auslesen
  float u=(analogRead(PIN_U)/1023.)*3.3*1.91;
  // Lichtschranke auslesen
  boolean ls=digitalRead(PIN_LS);
  // Maske ausgeben
  display.clearDisplay();
  display.drawLine(0,54,127,54,WEISS);
  // LS-Zustand ausgeben
  display.setCursor(0,56);
  display.print(ls?F("Blockiert"):F("Frei"));
  // Spannung ausgeben
  display.setCursor(92,56);
  display.print(u);
  display.print(F(" V"));
  // Display aktualisieren
  display.display();
  delay(500);
}

void startbild() {
  // Anzeige des Startbildschirmes
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(12,0);
  display.print(F("Besucher-"));
  display.setCursor(24,16);
  display.print(F("z\x84hler"));
  display.setTextSize(1);
  display.setCursor(0,40);
  display.println(F(VERSION));
  display.println(F("J\x94rg Skapski"));
  display.println(F("Markus Soick"));
  display.display();

  delay(5000);
  display.clearDisplay();
  display.display();
}
