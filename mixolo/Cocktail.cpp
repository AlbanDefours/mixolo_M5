#include "Cocktail.h"
#include "Container.h"

Ingredient::Ingredient(int ingredientID,String ingredientName, int ingredientAmount){
 id = ingredientID;
 name = ingredientName;
amount = ingredientAmount;
}

Container* Ingredient::findContainerIfQuantity(vector<Container>& containers,float quantity){
 for(int j=0; j< containers.size();j++){
      if(containers[j].name == name && containers[j].sufficientQuantity(quantity)) {
        return &containers[j];
      }       
  }
  return  nullptr;  
}

Cocktail::Cocktail(int cocktailID,String cocktailName,vector<Ingredient>& cocktailIngredients){
  id = cocktailID;
  name = cocktailName;
  ingredients = cocktailIngredients;
  totalAmount = 0;
  for(int i=0; i< ingredients.size();i++){
    totalAmount += ingredients[i].amount;
  }
}

bool Cocktail::serve(vector<Container>& containers, int quantity){
  vector<float> ingredientsPercentage;

  for(int i=0; i< ingredients.size();i++){
    bool available = false;
    ingredientsPercentage.push_back(ingredients[i].amount/totalAmount);
    
    if(ingredients[i].findContainerIfQuantity(containers, ingredientsPercentage[i]*quantity) == NULL){
      return false;
    }
  }


  for(int i=0; i< ingredients.size();i++){
    float ingredientQuantity =  ingredientsPercentage[i]*quantity;
    Container container = *ingredients[i].findContainerIfQuantity(containers, ingredientQuantity);
    container.serve(ingredientQuantity);
  }
}