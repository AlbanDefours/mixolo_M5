#include <M5Stack.h>
#define MACHINE_ID 1678288101932 

const char* WIFI_NAME = "MIXOLO WIFI MANAGER";

#include "Ultrasonic.h"
#include "DBManager.h"
#include "DisplayManager.h"
bool waitConnection = true;

vector<Cocktail> cocktails;
vector<Container> containers;

void setup() {
  Serial.begin(115200);
  M5.begin();
  M5.Lcd.fillScreen(RED);
  WiFi.mode(WIFI_STA);
  setupDB();
  loadData();
  displayCocktailCard(cocktails);
  //displayCocktailCard();
}

void loadData(){
    cocktails = loadCocktails();
    Serial.println("COCKTAIL : "+String( cocktails.size()));

    containers = loadContainers();
    Serial.println("CONTAINER : "+String( containers.size()));

}

void loop() { 
 if(WiFi.status() == WL_CONNECTED){
  waitConnection = false;*/
  displayM5(cocktails);
 }else{
  if(!waitConnection){
    setupDB();
    waitConnection = true;
  }
 }
  //Serial.printf("Distance: %.1f cm\n", distance); // Affichage de la distance sur le port série pour le débogage
 // delay(500);
}
