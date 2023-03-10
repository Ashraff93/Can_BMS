//AR_Configuration
using namespace std;
#include <Arduino.h> //#include "Arduino.h" For Arduino Framework Logic
#include <string> //# Contains macro definitions, constants and declarations of functions and types used not only for string handling
#include <cstring> //#This header file defines several functions to manipulate C strings and arrays
#include <Wire.h> //#include "Wire.h" For TWI/I2C Hardware Configuration
#include "EnumBoolen.h" //#include "EnumBoolen.h" For Enum Logic
#include "CanProc.h" //#include "CanProc.h" For CANBUS Communication
#include "Debug.h" //#include "Mm.h" For Enum Logic
  /*!
    LED_Declaration
  */
/**************************************************************************/
Flasher LedBD(13, 100, 150);//Led on Board Pin 13
Flasher LED_CanBus(7, 1000, 1000);//Led on Board Pin 1

/**************************************************************************/
  /*!
    Canbus_Declaration
  */
/**************************************************************************/
CanBus CanB1(LED_CanBus); //Declaration on canbus with object led


uint8_t buff_D[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

void setup() {
  CanB1.begin(250000); 
}

void loop() {
  LedBD.Update();
  CanB1.CanB_Event(); //Call Canbus Communication

  if(BMS_Establish()== true){
    Serial.println(CanB1.charging_message._voltage_reference);
    Serial.println(CanB1.charging_message._current_reference);
    Serial.println(CanB1.charging_message._charging_reference);
    if(charging_State() == Charging_State::Start_Charging){
      CanB1.Send_EventRaw(32.1,100,1, true);
    }
    else{

    }
  } 
 
}