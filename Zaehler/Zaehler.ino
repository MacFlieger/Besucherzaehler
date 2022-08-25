/**************************************************************************
Besucherzähler für die Bibi Wulfen

Version 0.6
(c) 2022 Jörg Skapski, Markus Soick
**************************************************************************/

// Bibliotheken
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Version
#define VERSION "(c) 2022, v0.6"

// Konstanten
#define PIN_U A0  // Eingangs-Pin zur Spannungsmessung
#define PIN_LS D5  // Eingangs-Pin für die Lichtschranke (D5=GPIO14)

// OLED-Display
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
#define WEISS SSD1306_WHITE
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Globale Variablen
unsigned long timerZeit=0;      // Zeit der letzten Timerausführung
unsigned long lsZeit=0;         // Zeit der letzten LS-Unterbrechung
unsigned long zaehler=0;        // Anzahl der Besucher
boolean lsAenderung=false;      // Flag für die Aktualisierung des LS-Zustandes
boolean zaehlerAenderung=false; // Flag für die Aktualisierung des Zählers
boolean durchgang=false;        // Flag zum Halbieren der erfassten Durchgänge (Rein und Raus sind ein Besucher)

void ICACHE_RAM_ATTR lsUnterbrechung() {
  // die Lichtschranke hat den Zustand geändert
  if (digitalRead(PIN_LS)) {
    // die LS ist frei
    lsAenderung=true;
  }
  else {
    // die LS ist unterbrochen
    lsAenderung=true;
    unsigned long zeit=millis();
    // Prellen der LS unterdrücken
    if (zeit<lsZeit || zeit-lsZeit>1) {
      durchgang=!durchgang;
      if (!durchgang)
        zaehler++;
      zaehlerAenderung=true;
      lsZeit=zeit;
    }
  }
}

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

  // Maske mit Inhalten ausgeben
  ausgabeMaske(true);

  // Interrupt für die Lichtschranke aktivieren
  attachInterrupt(digitalPinToInterrupt(PIN_LS), lsUnterbrechung, CHANGE);

}

void loop() {
  // jede Sekunde die Anzeige der Spannung aktualisieren
  unsigned long zeit=millis();
  if (zeit<timerZeit || zeit-timerZeit>1000) {
    timerZeit=zeit;
    ausgabeSpannung();
  }
  // evtl. Aktualisierung des Zustandes der Lichtschranke
  if (lsAenderung) {
    ausgabeLS();
  }
  // evtl. Aktualisierung des Zählers
  if (zaehlerAenderung) {
    ausgabeZaehler();
  }
}
