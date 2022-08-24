/**************************************************************************
Besucherzähler für die Bibi Wulfen

Version 0.4
(c) 2022 Jörg Skapski, Markus Soick
**************************************************************************/

// Bibliotheken
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Version
#define VERSION "(c) 2022, v0.4"

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

// Globale Variablen
unsigned long alteZeit=0;

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

  // Maske
  ausgabeMaske();
  ausgabeLS(digitalRead(PIN_LS));
  ausgabeSpannung();
}

void loop() {
  // jede Sekunde die Anzeige der Spannung aktualisieren
  unsigned long zeit=millis();
  if (zeit<alteZeit || zeit-alteZeit>1000) {
    alteZeit=zeit;
    ausgabeSpannung();
  }
}
