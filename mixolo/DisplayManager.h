#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H
#include <M5Stack.h>
#include "Cocktail.h"
#include "DBManager.h"

enum Pages {
  LIST_COCKTAIL,
  POPUP_QUANTITY,
  MAKE_COCKTAIL,
  ERROR_PAGE,
  COCKTAIL_FINISH
};

int currentCocktail = 0;     // Cocktail actuellement sélectionné
int quantity = 15;
Pages currentPage = LIST_COCKTAIL;




void displayError(String message) {
  currentPage = ERROR_PAGE;
  M5.Lcd.fillScreen(RED);  // Efface l'écran
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextFont(0);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setTextDatum(MC_DATUM);
  M5.Lcd.drawString("ERREUR : ", M5.Lcd.width() / 2, M5.Lcd.height() / 2 - 20);  // Affiche le nom du cocktail au centre de l'écran
  M5.Lcd.setTextDatum(MC_DATUM);
  M5.Lcd.drawString(message, M5.Lcd.width() / 2,  M5.Lcd.height() / 2 + 20);
}

void bottomArrows() {
  M5.Lcd.fillRect(0,  M5.Lcd.height() - 45,  M5.Lcd.width(), 50, BLACK);
  
  int upPosition = 55;
  M5.Lcd.drawTriangle(upPosition - 10, 230, upPosition + 10, 230, upPosition, 210, WHITE);
  int downPosition = M5.Lcd.width() - upPosition;
  M5.Lcd.drawTriangle(downPosition - 10, 210, downPosition + 10, 210, downPosition, 230, WHITE);
  M5.Lcd.drawCircle(M5.Lcd.width() / 2, 220, 10, WHITE);
}


void bottomPlusMinus() {
  M5.Lcd.fillRect(0,  M5.Lcd.height() - 45,  M5.Lcd.width(), 50, BLACK);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextFont(0);
  M5.Lcd.setTextSize(4);
  M5.Lcd.setTextDatum(MC_DATUM);

  int upPosition = 55;
  M5.Lcd.setCursor(upPosition - 7, 205);
  M5.Lcd.println("+");

  int downPosition = M5.Lcd.width() - upPosition;
  M5.Lcd.setCursor(downPosition - 7, 205);
  M5.Lcd.println("-");
  M5.Lcd.drawCircle(M5.Lcd.width() / 2, 220, 10, WHITE);
}


// Fonction pour afficher une carte de cocktail
void displayCocktailCard(vector<Cocktail>& cocktails) {
  if(!cocktails.empty()){
    currentPage = LIST_COCKTAIL;
    Cocktail cocktail = cocktails[currentCocktail];
    M5.Lcd.fillRect(0, 0, M5.Lcd.width(), M5.Lcd.height() - 45, WHITE);
    M5.Lcd.setTextColor(BLACK);
    M5.Lcd.setTextFont(0);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setTextDatum(MC_DATUM);
    M5.Lcd.drawString(String(cocktail.id+1)+" - " + cocktail.name, M5.Lcd.width() / 2, 40);  // Affiche le nom du cocktail au centre de l'écran
    M5.Lcd.setTextFont(0);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextDatum(TL_DATUM);
    M5.Lcd.drawString("Ingredients :", 10, 80);  // Affiche la liste des ingrédients
    String ingredients = "";
    for(int i=0;i<cocktail.ingredients.size();i++){
      ingredients += " "+cocktail.ingredients[i].name+",";
    }
    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextWrap(true, false);
    M5.Lcd.setTextWrap(50, 0);
    M5.Lcd.setCursor(10, 105);
    M5.Lcd.setTextPadding(20);
    M5.Lcd.println(ingredients);
    
    bottomArrows();
  }else{
    displayError("Cocktails Empty");
  }
}

void displayMenuQuantity() {
  currentPage = POPUP_QUANTITY;
  M5.Lcd.fillRect(15, M5.Lcd.height() / 4, M5.Lcd.width() - 30, M5.Lcd.height() / 2, WHITE);
  M5.Lcd.drawRect(15, M5.Lcd.height() / 4, M5.Lcd.width() - 30, M5.Lcd.height() / 2, BLACK);
  M5.Lcd.setTextColor(BLACK);
  M5.Lcd.setTextFont(0);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextDatum(MC_DATUM);
  M5.Lcd.drawString("Quantite de Cocktail :", M5.Lcd.width() / 2, M5.Lcd.height() / 4 + 20);  // Affiche le nom du cocktail au centre de l'écran
  M5.Lcd.setTextFont(0);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setTextDatum(MC_DATUM);
  M5.Lcd.drawString(String(quantity) + " cl", M5.Lcd.width() / 2, M5.Lcd.height() / 2 + 5);  // Affiche la liste des ingrédients
  M5.Lcd.setTextDatum(TL_DATUM);
  
  bottomPlusMinus();
}

void displayMakeCocktail(vector<Cocktail>& cocktails) {
  if(!cocktails.empty()){
    currentPage = MAKE_COCKTAIL;
    Cocktail cocktail = cocktails[currentCocktail];
    M5.Lcd.fillScreen(BLACK);  // Efface l'écran
    M5.Lcd.fillRect(0, 0, M5.Lcd.width(), M5.Lcd.height(), WHITE);
    M5.Lcd.setTextColor(BLACK);
    M5.Lcd.setTextFont(0);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setTextDatum(MC_DATUM);
    M5.Lcd.drawString("En cours : ", M5.Lcd.width() / 2, 40);  // Affiche le nom du cocktail au centre de l'écran
    M5.Lcd.setTextDatum(MC_DATUM);
    M5.Lcd.drawString(cocktail.name, M5.Lcd.width() / 2, 95);
  }else{
    displayError("Cocktails Empty");
  }
}
void drawProgressBar(int x, int y, int width, int height, int progress, int COLOR) {
  int border = 2;
  int barHeight = height - 2 * border;
  int barWidth = width - 2 * border;

  // Draw border rectangle
  M5.Lcd.drawRect(x, y, width, height, BLACK);

  // Draw progress bar background
  M5.Lcd.fillRect(x + border, y + border, barWidth, barHeight, TFT_LIGHTGREY);

  // Draw progress bar
  int barProgress = (barWidth * progress) / 100;
  M5.Lcd.fillRect(x + border, y + border, barProgress, barHeight, COLOR);
  M5.Lcd.fillRect(x + border, y + border, barProgress - 45, barHeight, TFT_LIGHTGREY);
}

void drawLoaderAsync(int x, int y, int height, int delayMs,int COLOR) {
  static int angle = 0;
  static int lastTime = 0;

  if (millis() - lastTime >= delayMs) {
    lastTime = millis();

    drawProgressBar(x, y, M5.Lcd.width() - x * 2, height, angle,COLOR);
    delay(50);

    angle += 2;
    if (angle >= 100) {
      angle = 0;
    }
  }
}

void wifiConnectionScreen() {
  M5.Lcd.fillScreen(BLACK);  // Efface l'écran
  M5.Lcd.fillRect(0, 0, M5.Lcd.width(), M5.Lcd.height(), WHITE);
  M5.Lcd.setTextColor(BLACK);
  M5.Lcd.setTextFont(0);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setTextDatum(MC_DATUM);
     M5.Lcd.drawString("Recherche d'un", M5.Lcd.width() / 2,  M5.Lcd.height() / 2-35); 
    M5.Lcd.drawString("reseau Wifi", M5.Lcd.width() / 2,  M5.Lcd.height() / 2);
    M5.Lcd.drawString("connu", M5.Lcd.width() / 2,  M5.Lcd.height() / 2 +35);  
 
}
// Fonction pour afficher une carte de cocktail
void displayQrCodeWifi() {
  M5.Lcd.fillScreen(BLACK);  // Efface l'écran
  M5.Lcd.fillRect(0, 0, M5.Lcd.width(), M5.Lcd.height(), WHITE);
  M5.Lcd.setTextColor(BLACK); 
  M5.Lcd.setTextFont(0);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextDatum(MC_DATUM);
  M5.Lcd.drawString("Connectez-vous au Wifi :", M5.Lcd.width() / 2, 30);  
  M5.Lcd.setTextColor(BLUE);// 
  M5.Lcd.drawString(WIFI_NAME, M5.Lcd.width() / 2, 60);
  M5.Lcd.qrcode( "http://192.168.4.1",M5.Lcd.width() / 2-75, 95, 150,
        6); 
  M5.Lcd.setTextColor(BLACK);// 
  M5.Lcd.drawString("Puis allez sur ce site :", M5.Lcd.width() / 2, 90);
}

void displayM5(vector<Cocktail>& cocktails) {
  M5.update();
  switch (currentPage) {
    case LIST_COCKTAIL:
      if (M5.BtnA.wasPressed()) {  // Bouton A pour monter dans la liste
        currentCocktail = (currentCocktail + cocktails.size() - 1) % cocktails.size();
        displayCocktailCard(cocktails);
      }
      if (M5.BtnC.wasPressed()) {  // Bouton C pour descendre dans la liste
        currentCocktail = (currentCocktail + 1) % cocktails.size();
        displayCocktailCard(cocktails);
      }
      if (M5.BtnB.wasPressed()) {
        quantity = 15;
        currentPage = POPUP_QUANTITY;
        displayMenuQuantity();
      }
      break;
    case POPUP_QUANTITY:
      if (M5.BtnA.wasPressed()) {  // Bouton A pour monter dans la liste
        quantity += 5;
        displayMenuQuantity();
      }
      if (M5.BtnC.wasPressed()) {  // Bouton C pour descendre dans la liste
        if (quantity - 5 >= 0) {
          quantity -= 5;
        }
        displayMenuQuantity();
      }
      if (M5.BtnB.wasPressed()) {
        currentPage = MAKE_COCKTAIL;
        displayMakeCocktail(cocktails);
      }
      break;
    case MAKE_COCKTAIL:
      drawLoaderAsync(15, M5.Lcd.height() / 3 * 2, 25, 50, TFT_BLUE);
      if (M5.BtnB.wasPressed()) {
        currentPage = LIST_COCKTAIL;
        displayCocktailCard(cocktails);
      }
      break;
  }
}
#endif
