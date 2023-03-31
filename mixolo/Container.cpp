#include "Container.h"
#include "Ultrasonic.h"

Container::Container(int containerID,String containerName, int containerTotalAmount,int containerPumpPin,int containerTriggerPin,int containerEchoPin){
  id   = containerID;
  name = containerName;
  totalAmount = containerTotalAmount;
  triggerPin = containerTriggerPin;
  echoPin = containerEchoPin;
  pumpPin = containerPumpPin;
  remainingAmount = calculRemaining();
  digitalWrite(pumpPin, LOW);
}

float Container::calculRemaining() {
  Ultrasonic ultrasonic(triggerPin, echoPin);
  float distance = ultrasonic.read();
  float liquidLevel = EMPTY_DISTANCE - distance;

  float volumeCM3 = CONTAINER_WIDTH * CONTAINER_LENGTH * liquidLevel; // Calcul colume in cm3
  float volumeCL = volumeCM3/10; // Convert to cl

  remainingAmount = volumeCL;
  return volumeCL;
}  

void Container::pumpON(){
  digitalWrite(pumpPin, HIGH);
  
}

void Container::pumpOFF(){
  digitalWrite(pumpPin, LOW);
}

void Container::serve(int quantity){
  int necessaryTime = quantity / PUMP_FLOW;
  pumpON();
  delay(necessaryTime*1000);
  pumpOFF();
}


bool Container::sufficientQuantity(int quantity){
  return quantity < remainingAmount;
}