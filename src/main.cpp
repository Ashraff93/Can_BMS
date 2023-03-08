//AR_Configuration
using namespace std;
#include <Arduino.h> //#include "Arduino.h" For Arduino Framework Logic
#include <string> //# Contains macro definitions, constants and declarations of functions and types used not only for string handling
#include <cstring> //#This header file defines several functions to manipulate C strings and arrays
#include <Wire.h> //#include "Wire.h" For TWI/I2C Hardware Configuration
#include <MsTimer2.h> //#include "MsTimer2.h" For Timers AVR architecture
#include "EnumBoolen.h" //#include "Mm.h" For Enum Logic
#include "CanProc.h" //#include "CanProc.h" For CANBUS Communication
#include "Debug.h" //#include "Mm.h" For Enum Logic
#include <Encoder.h> //#include "Encoder.h" For GPS Communication

  /*!
    LED_Declaration
  */
/**************************************************************************/
Flasher LedBD(13, 100, 150);//Led on Board Pin 13
// Relay BL(7, 1000, 1000);//Led on Board Pin 1
// Relay BR(8, 1000, 1000);//Led on Board Pin 3
Ws2812 LED_System(0,100,150); //Led System Indicator declaration
Ws2812 LED_CanBus(1,100,150); //Led Rover Indicator based on CANBUS Activity declaration
Ws2812 LED_Rosserial(2,100,150); //Led ROS Indicator based communication declaration
Ws2812 LedEncoderR(3,100,150); //Led Right Rover Encoder Indicator movement declaration
Ws2812 LedEncoderL(4,100,150); //Led Left Rover Encoder Indicator movement declaration
Ws2812 LED5(5,100,150);
Ws2812 LED6(6,100,150);
Ws2812 LED7(7,100,150);
Ws2812 Ws2812_Led(0,0,0);
Ws2812_RSP Ws(0,0,0);



/**************************************************************************/
  /*!
    Canbus_Declaration
  */
/**************************************************************************/

CanBus CanB1(LED_CanBus); //Declaration on canbus with object led

//Debugging_Configuration
#define HWSERIAL Serial1 //#define UART1SERIAL Serial2 RX:TX(0,1)



//Millis Testing Loop
unsigned long PreviousMillis_Relay_On = 0;
unsigned long PreviousMillis_Relay_Off = 0;
unsigned long PreviousMillis_Keyboard = 0;     // will store last time MAVLink was transmitted and listened
unsigned long PreviousMillis_Debugging = 0; 
unsigned long Next_Interval_Relay_On = 1000;
unsigned long Next_Interval_Relay_Off = 1000;
unsigned long Next_Interval_Keyboard = 20;
unsigned long Next_Interval_Debugging = 20;
unsigned long Interval_Count_On = 0;// will store last time MAVLink was transmitted and listened
unsigned long Interval_Count_Off = 0;// will store last time MAVLink was transmitted and listened

// timers for the sub-main loop
unsigned long currentMillis;
long previousMillis = 0;    // set up timers
float loopTime = 10;
//Rover_Global_Value
uint8_t buff_D[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

void setup() {

  CanB1.begin(250000); 

}

void loop() {
  LedBD.Update();
  LED_System.SingleRainbow(); //Call Front SingleRainbow
  // Ws.Rainbow(); //Call Front SingleRainbow

  CanB1.CanB_Event(); //Call Canbus Communication

 
}