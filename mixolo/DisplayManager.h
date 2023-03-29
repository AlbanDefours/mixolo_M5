#include <M5Stack.h>

enum Pages {
  LIST_COCKTAIL,
  POPUP_QUANTITY,
  MAKE_COCKTAIL,
  WIFI_CONNECTION,
  COCKTAIL_FINISH
};

const int numCocktails = 3;  // Nombre de cocktails dans la liste
int currentCocktail = 0;     // Cocktail actuellement sélectionné
int quantity = 15;
Pages currentPage = LIST_COCKTAIL;

// Liste des cocktails avec leur nom et leurs ingrédients
String cocktailNames[] = { "Margarita", "Cosmopolitan", "Mojito" };
String cocktailIngredients[] = { "Tequila, Cointreau, Jus de citron vert", "Vodka, Jus de cranberry, Jus de citron vert", "Rhum, Jus de citron vert, Menthe, Eau gazeuse" };





// Fonction pour afficher une carte de cocktail
void displayCocktailCard(String name, String ingredients) {
  M5.Lcd.fillRect(0, 0, M5.Lcd.width(), M5.Lcd.height() - 45, WHITE);
  M5.Lcd.setTextColor(BLACK);
  M5.Lcd.setTextFont(0);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setTextDatum(MC_DATUM);
  M5.Lcd.drawString("1 - " + name, M5.Lcd.width() / 2, 40);  // Affiche le nom du cocktail au centre de l'écran
  M5.Lcd.setTextFont(0);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextDatum(TL_DATUM);
  M5.Lcd.drawString("Ingredients :", 10, 80);  // Affiche la liste des ingrédients
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextWrap(true, false);
  M5.Lcd.setTextWrap(50, 0);
  M5.Lcd.setCursor(10, 105);
  M5.Lcd.setTextPadding(20);
  M5.Lcd.println(ingredients);
}

void displayMenuQuantity() {
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
}

void displayMakeCocktail() {
  M5.Lcd.fillScreen(BLACK);  // Efface l'écran
  M5.Lcd.fillRect(0, 0, M5.Lcd.width(), M5.Lcd.height(), WHITE);
  M5.Lcd.setTextColor(BLACK);
  M5.Lcd.setTextFont(0);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setTextDatum(MC_DATUM);
  M5.Lcd.drawString("En cours : ", M5.Lcd.width() / 2, 40);  // Affiche le nom du cocktail au centre de l'écran
  M5.Lcd.setTextDatum(MC_DATUM);
  M5.Lcd.drawString(String(cocktailNames[currentCocktail]), M5.Lcd.width() / 2, 95);
}

void bottomArrows() {
  int upPosition = 55;
  M5.Lcd.drawTriangle(upPosition - 10, 230, upPosition + 10, 230, upPosition, 210, WHITE);
  int downPosition = M5.Lcd.width() - upPosition;
  M5.Lcd.drawTriangle(downPosition - 10, 210, downPosition + 10, 210, downPosition, 230, WHITE);
  M5.Lcd.drawCircle(M5.Lcd.width() / 2, 220, 10, WHITE);
}

void bottomPlusMinus() {
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextFont(0);
  M5.Lcd.setTextSize(4);
  M5.Lcd.setTextDatum(MC_DATUM);

  int upPosition = 55;
  M5.Lcd.setCursor(upPosition - 5, 205);
  M5.Lcd.println("+");

  int downPosition = M5.Lcd.width() - upPosition;
  M5.Lcd.setCursor(downPosition + 5, 205);
  M5.Lcd.println("-");
  M5.Lcd.drawCircle(M5.Lcd.width() / 2, 220, 10, WHITE);
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

void wifiConnection() {
  M5.Lcd.fillScreen(BLACK);  // Efface l'écran
  M5.Lcd.fillRect(0, 0, M5.Lcd.width(), M5.Lcd.height(), WHITE);
  M5.Lcd.setTextColor(BLACK);
  M5.Lcd.setTextFont(0);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setTextDatum(MC_DATUM);
  M5.Lcd.drawString("Connection Wifi", M5.Lcd.width() / 2, 40);  // Affiche le nom du cocktail au centre de l'écran
  M5.Lcd.setTextDatum(MC_DATUM);
  M5.Lcd.drawString(WIFI_SSID, M5.Lcd.width() / 2, 95);
      drawLoaderAsync(15, M5.Lcd.height() / 3 * 2, 25, 50, TFT_RED);
}


void displayLoop() {
  M5.update();
  switch (currentPage) {
    case LIST_COCKTAIL:
      bottomArrows();
      if (M5.BtnA.wasPressed()) {  // Bouton A pour monter dans la liste
        currentCocktail = (currentCocktail + numCocktails - 1) % numCocktails;
        displayCocktailCard(cocktailNames[currentCocktail], cocktailIngredients[currentCocktail]);
      }
      if (M5.BtnC.wasPressed()) {  // Bouton C pour descendre dans la liste
        currentCocktail = (currentCocktail + 1) % numCocktails;
        displayCocktailCard(cocktailNames[currentCocktail], cocktailIngredients[currentCocktail]);
      }
      if (M5.BtnB.wasPressed()) {
        quantity = 15;
        currentPage = POPUP_QUANTITY;
        M5.Lcd.fillRect(0, M5.Lcd.height() - 45, M5.Lcd.width(), 45, BLACK);
        displayMenuQuantity();
      }
      break;
    case POPUP_QUANTITY:
      bottomPlusMinus();
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
        displayMakeCocktail();
      }
      break;
    case MAKE_COCKTAIL:
      drawLoaderAsync(15, M5.Lcd.height() / 3 * 2, 25, 50, TFT_BLUE);
      if (M5.BtnB.wasPressed()) {
        currentPage = LIST_COCKTAIL;
        displayCocktailCard(cocktailNames[currentCocktail], cocktailIngredients[currentCocktail]);
      }
      break;
      case WIFI_CONNECTION:
      drawLoaderAsync(15, M5.Lcd.height() / 3 * 2, 25, 50, TFT_RED);
      break;
  }
}