/**************************************************************************
Unterprogramme für die Ausgabe auf dem OLED-Display

startbild: Anzeige des Startbildes
ausgabeMaske: Anzeige der Maske
ausgabeZaehler: Anzeige der aktuellen Besucherzahl
ausgabeLS: Anzeige des Zustandes der Lichtschranke
ausgabeSpannung: Anzeige der Spannung

**************************************************************************/

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

void ausgabeMaske(boolean alles) {
  // Anzeige der Maske
  display.drawLine(0,54,127,54,WEISS);
  // Anzeige der Inhalte
  if (alles) {
    ausgabeZaehler();  
    ausgabeLS();
    ausgabeSpannung();
  }
  display.display();
}

void ausgabeZaehler() {
  zaehlerAenderung=false;
  display.fillRect(0,0,127,15,SSD1306_BLACK);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  if (durchgang)
    display.fillCircle(5,7,3,SSD1306_WHITE);
  display.setCursor(12,0);
  display.print(zaehler);
  display.display();
}

void ausgabeLS() {
  // Anzeige des Zustandes der Lichtschranke
  boolean zustand=digitalRead(PIN_LS);
  lsAenderung=false;
  display.fillRect(0,56,7,63,SSD1306_BLACK);
  if (zustand)
    display.drawCircle(4,60,3,SSD1306_WHITE);
  else
    display.fillCircle(4,60,3,SSD1306_WHITE);
  display.display();
}

void ausgabeSpannung() {
  // Anzeige der Spannung
  display.fillRect(92,56,127,63,SSD1306_BLACK);
  float u=(analogRead(PIN_U)/1023.)*3.3*1.91;
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(92,56);
  display.print(u);
  display.print(F(" V"));
  display.display();
}
