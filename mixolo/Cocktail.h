// COCKTAIL.h
#ifndef COCKTAIL_h
#define COCKTAIL_h

#include <Arduino.h>
#include "Container.h"
#include <vector>

using namespace std;

class Ingredient {
  public:
    int id;
    String name;
    int amount;

    Ingredient(int ingredientID,String ingredientName, int ingredientAmount);
    Container* findContainerIfQuantity(vector<Container>& containers,float quantity);
};

class Cocktail {
  public:
    int id;
    String name;
    vector<Ingredient> ingredients;
    int totalAmount;

    Cocktail(int cocktailID,String cocktailName,vector<Ingredient>& cocktailIngredients);
    bool serve(vector<Container>& containers,int quantity);
};

#endif