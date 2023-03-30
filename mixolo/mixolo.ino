#include <M5Stack.h>

const char* WIFI_NAME = "MIXOLO WIFI MANAGER";

#include "Ultrasonic.h"
#include "DBManager.h"
#include "DisplayManager.h"
#define TRIGGER_PIN G26 // Pin de déclenchement du capteur ultrasonique
#define ECHO_PIN G36    // Pin d'écoute du capteur ultrasonique

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN); // Initialisation de la bibliothèque Ultrasonic
bool waitConnection = true;

void setup() {
  Serial.begin(115200);
  M5.begin();
  M5.Lcd.fillScreen(BLACK);
  WiFi.mode(WIFI_STA);
  setupDB();

  //displayCocktailCard();
}

void loop() { 
 if(WiFi.status() == WL_CONNECTED){
  waitConnection = false;
  displayM5();
  float distance = ultrasonic.read(); // Lecture de la distance mesurée par le capteur ultrasonique
 }else{
  if(!waitConnection){
    setupDB();
    waitConnection = true;
  }
 }
  //Serial.printf("Distance: %.1f cm\n", distance); // Affichage de la distance sur le port série pour le débogage
 // delay(500);
}
