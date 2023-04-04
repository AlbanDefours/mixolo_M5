// COCKTAIL.h
#ifndef COCKTAIL_h
#define COCKTAIL_h

#include <Arduino.h>
#include <Firebase_ESP_Client.h>
#include "Container.h"
#include <vector>

using namespace std;

class Ingredient {
  public:
    int id;
    String name;
    int amount;

    Ingredient(int ingredientID,String ingredientName, int ingredientAmount);
    Ingredient(FirebaseJson json);
    Container* findContainerIfQuantity(vector<Container>& containers,float quantity);
};

class Cocktail {
  public:
    int id;
    String name;
    vector<Ingredient> ingredients;
    int totalAmount;

    Cocktail(int cocktailID,String cocktailName,vector<Ingredient>& cocktailIngredients);
    Cocktail(FirebaseJson json);
    bool serve(vector<Container>& containers,int quantity);
};

#endif