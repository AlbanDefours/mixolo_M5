// CONTAINER.h
#ifndef CONTAINER_h
#define CONTAINER_h

#include <Arduino.h>
#include "Ultrasonic.h"

const float EMPTY_DISTANCE = 19;
const float CONTAINER_WIDTH = 10.5;
const float CONTAINER_LENGTH = 10.5;
const float PUMP_FLOW = 6.67; // in cl/s

class Container {
  public:
    int id;
    String name;
    int remainingAmount;
    int totalAmount;

    int triggerPin;
    int echoPin;
    int pumpPin;

    Container(int containerID,String containerName, int containerTotalAmount,int containerPumpPin,int containerTriggerPin,int containerEchoPin);
    float calculRemaining();
    void pumpON();
    void pumpOFF();
    void serve(int quantity);
    bool sufficientQuantity(int quantity);
};

#endif