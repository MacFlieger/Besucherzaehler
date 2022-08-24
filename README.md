# Besucherzaehler

Besucherzähler für die Bibi Wulfen

## Kurzbeschreibung

Mittels einer Lichtschranke sollen Besucherzahlen mit einem ESP8266 Mikrocontroller gemessen und angezeigt werden.

## Komponenten

- Wemos D1 Mini ESP8266 Mikrokontroller
- LM2596S DC Spannungswandler
- 0,96" OLED Display SSD1306 blau 128x64 I2C
- 12V Lichtschranke

## Schaltplan

Im Ordner "Schaltung" sind die KiCad-Dateien und der aktuelle Schaltplan als PDF gespeichert.

## Software

Im Ordner "Zaehler" ist die aktuelle Software gespeichert. Hauptprogramm ist "Zaehler.ino"

## Aufteilung des Bildschirmes

Gesamtgröße 128x64 Pixel

- Zeile 53-55 (3px hoch): Trennlinie 
- Zeile 56-63 (8px hoch): Statusanzeige
	- Spalte 0-7 (8px breit): Zustand der Lichtschranke
	- Spalte 92-127 (6char=36Pixel breit): Anzeige der Spannung

## Nützliches

Tabelle der Sonderzeichen bei Wikipedia  
[Codepage 437](https://de.wikipedia.org/wiki/Codepage_437)
