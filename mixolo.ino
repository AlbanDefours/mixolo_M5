#include <M5Stack.h>
#include "Ultrasonic.h"
#include "DBManager.h"
#include "DisplayManager.h"
#define TRIGGER_PIN G26 // Pin de déclenchement du capteur ultrasonique
#define ECHO_PIN G36    // Pin d'écoute du capteur ultrasonique

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN); // Initialisation de la bibliothèque Ultrasonic


void setup() {
  Serial.begin(115200);
  M5.begin();
  M5.Lcd.fillScreen(BLACK);
  wifiConnection();
  setupDB();

  displayCocktailCard(cocktailNames[currentCocktail], cocktailIngredients[currentCocktail]);
}

void loop() {
  displayLoop();
  float distance = ultrasonic.read(); // Lecture de la distance mesurée par le capteur ultrasonique
  //Serial.printf("Distance: %.1f cm\n", distance); // Affichage de la distance sur le port série pour le débogage
 // delay(500); 
}
