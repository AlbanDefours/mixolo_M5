#include <M5Stack.h>
#include <M5_EXTIO2.h>

#define NUM_EXTIO_PORTS 8 // Nombre de ports EXTIO sur le M5Stack
M5_EXTIO2 extio;

void displayError(String message) {
  M5.Lcd.fillScreen(RED);  // Efface l'écran
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextFont(0);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setTextDatum(MC_DATUM);
  M5.Lcd.drawString("ERREUR : ", M5.Lcd.width() / 2, M5.Lcd.height() / 2 - 20);  // Affiche le nom du cocktail au centre de l'écran
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextDatum(MC_DATUM);
  M5.Lcd.drawString(message, M5.Lcd.width() / 2,  M5.Lcd.height() / 2 + 20);
}

void setup() {
  M5.begin();
  M5.Power.begin();
  M5.Lcd.print("Test des ports EXTIO...");
  Serial.begin(115200);
  while (!extio.begin(&Wire, 21, 22, 0x45)) {
  Serial.println("extio Connect Error");
  displayError("extio Connect Error");
  delay(1000);
  }
  extio.setAllPinMode( DIGITAL_OUTPUT_MODE);
  //extio.setPinMode(0, DIGITAL_OUTPUT_MODE);
}

void loop() { 
  
  extio.setAllPinMode( DIGITAL_OUTPUT_MODE);
  for (int i = 0; i < NUM_EXTIO_PORTS; i++) {
    M5.Lcd.clear();
    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextDatum(MC_DATUM);
    M5.Lcd.drawString("Test du port EXTIO " + String(i) + "...", M5.Lcd.width() / 2, M5.Lcd.height() / 2 - 25);
    delay(1000);
    extio.setDigitalOutput(i, HIGH);
    M5.Lcd.drawString("Etat du relais : ON", M5.Lcd.width() / 2, M5.Lcd.height() / 2);
    delay(1000);
    extio.setDigitalOutput(i, LOW);
    M5.Lcd.drawString("Etat du relais : OFF", M5.Lcd.width() / 2, M5.Lcd.height() / 2+25);
    delay(2000);
  }
  extio.setAllPinMode( ADC_INPUT_MODE);
  for (int i = 0; i < NUM_EXTIO_PORTS; i++) {
    M5.Lcd.clear();
    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextDatum(MC_DATUM);
    M5.Lcd.drawString("Test du port EXTIO " + String(i) + "...", M5.Lcd.width() / 2, M5.Lcd.height() / 2 - 25);
    M5.Lcd.drawString("Données : ", M5.Lcd.width() / 2, M5.Lcd.height() / 2);
    M5.Lcd.drawString(String(extio.getAnalogInput(i, _12bit)), M5.Lcd.width() / 2, M5.Lcd.height() / 2+25);
    delay(4000);
  }
}
