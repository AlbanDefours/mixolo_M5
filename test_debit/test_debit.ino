#include <M5Stack.h>
#include <M5_EXTIO2.h>

#define NUM_EXTIO_PORTS 8 // Nombre de ports EXTIO sur le M5Stack
M5_EXTIO2 extio;

bool isClick = false;
bool lastState = false;

void setup() {
  M5.begin();
  M5.Power.begin();
  M5.Lcd.print("Test des ports EXTIO...");
  Serial.begin(115200);
  while (!extio.begin(&Wire, 21, 22, 0x45)) {
  Serial.println("extio Connect Error");
  delay(1000);
  }
  extio.setAllPinMode( DIGITAL_OUTPUT_MODE);
  M5.Lcd.clear();
        M5.Lcd.setTextSize(2);
        M5.Lcd.setTextDatum(MC_DATUM);
        extio.setDigitalOutput(0, LOW);
        M5.Lcd.drawString("Etat du relais : OFF", M5.Lcd.width() / 2, M5.Lcd.height() / 2);
}
void loop() { 
  M5.update();
    
    if(M5.BtnB.wasPressed()){
        M5.Lcd.clear();
        M5.Lcd.setTextSize(2);
        M5.Lcd.setTextDatum(MC_DATUM);
        extio.setDigitalOutput(0, HIGH);
        M5.Lcd.drawString("Etat du relais : ON", M5.Lcd.width() / 2, M5.Lcd.height() / 2);
        for(int i=0;i<10;i++){
          M5.Lcd.fillRect(0, 0, M5.Lcd.width(),45, BLACK);
          M5.Lcd.setTextColor(WHITE);
          M5.Lcd.setTextSize(3);
          M5.Lcd.setTextDatum(MC_DATUM);
          M5.Lcd.drawString(String(10-i), M5.Lcd.width() / 2,45 / 2);
          delay(1000);
        }
        M5.Lcd.clear();
        M5.Lcd.setTextSize(2);
        M5.Lcd.setTextDatum(MC_DATUM);
        extio.setDigitalOutput(0, LOW);
        M5.Lcd.drawString("Etat du relais : OFF", M5.Lcd.width() / 2, M5.Lcd.height() / 2);
    }
}
