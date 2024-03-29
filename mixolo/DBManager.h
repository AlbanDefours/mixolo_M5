#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <Arduino.h>
#include <WiFi.h>
#include "WifiManager.h"
#include "Container.h"
#include "Cocktail.h"
#include <vector>


#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

/* 2. Define the API Key */
#define API_KEY "AIzaSyAG61QaFuKsOaGkttKnQVFad9eliV_Aibs"

/* 3. Define the RTDB URL */
#define DATABASE_URL "https://mixolo-95131-default-rtdb.europe-west1.firebasedatabase.app/" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

/* 4. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "mixolo.esp32@gmail.com"
#define USER_PASSWORD "ESP32_Mixolo_2023"

// Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

unsigned long count = 0;
bool signupOK = false;

using namespace std;

vector<vector<int>> pinList = {{
        {0x50, 0, 0x51},
        {0x52, 0, 0x53},
        {0x54, 0, 0x55}
    }};

void setupDB()
{
  initWifiConnection();
  unsigned long ms = millis();
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }

  currentPage = LIST_COCKTAIL;
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  /*if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }*/
  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

  // Limit the size of response payload to be collected in FirebaseData
  fbdo.setResponseSize(2048);

  Firebase.begin(&config, &auth);

  // The WiFi credentials are required for Pico W
  // due to it does not have reconnect feature.
#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
  config.wifi.clearAP();
  config.wifi.addAP(WIFI_SSID, WIFI_PASSWORD);
#endif

  // Comment or pass false value when WiFi reconnection will control by your code or third party library
  Firebase.reconnectWiFi(true);

  Firebase.setDoubleDigits(5);

  config.timeout.serverResponse = 10 * 1000;
}

vector<Container> loadContainers(){
  vector<Container> containers;
  if (Firebase.ready()  ) {
    if (Firebase.RTDB.getArray(&fbdo, "/machines/"+String(MACHINE_ID)+"/containers")) {
      if (fbdo.dataType() == "array") {
        FirebaseJsonArray &value = fbdo.jsonArray();
        for(int i=0;i<value.size();i++){
          FirebaseJsonData result;
          FirebaseJson json;
          value.get(result,i);
          result.get<FirebaseJson>(json);
          containers.push_back(Container(json,pinList[i][2],pinList[i][1],pinList[i][0]));
        }
        for (auto i: containers)
        Serial.println(String(i.name));
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }
   }    
    return containers;
   /*
   vector<Container> con;
   con.push_back(Container(0,"ingredient",75,0,0,0));
   return con;*/
}

vector<Cocktail> loadCocktails(){
  vector<Cocktail> cocktailsResult;
   if (Firebase.ready()  ) {
    if (Firebase.RTDB.getArray(&fbdo, "/machines/"+String(MACHINE_ID)+"/suggestions")) {
      if (fbdo.dataType() == "array") {
        FirebaseJsonArray &value = fbdo.jsonArray();
        for(int i=0;i<value.size();i++){
          FirebaseJsonData result;
          FirebaseJson json;
          value.get(result,i);
          result.get<FirebaseJson>(json);
          cocktailsResult.push_back(Cocktail(json));
        }
        for (auto i: cocktailsResult)
        Serial.println(String(i.name));
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }
   }  
    return cocktailsResult;
   /*vector<Cocktail> cock;
   vector<Ingredient> ing;
   ing.push_back(Ingredient(0,"ingredient",75));
   return cock;*/
}


#endif
