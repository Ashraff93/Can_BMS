/*
  Debug.h - Include all pre-debug testing using button, switch, led and WS21 based on RGB led- Version 2
  Copyright (c) 2022 RFA.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
*/
#ifndef MY_DEBUG_H
#define MY_DEBUG_H
#include <Arduino.h> //#include "Arduino.h" For Arduino Framework Logic
#include <elapsedMillis.h> //Elapsed time types - for easy-to-use measurements of elapsed time
#include "EnumBoolen.h" //#Control Enum Logic cross all RACE_UGV main function
#define FASTLED_INTERNAL
#include <FastLED.h> //#central include file for FastLED, defines the CFastLED class/object
#define DATA_PIN 5 
#define DATA_PIN_SPR 4 
#define DATA_PIN_SPL 6
#define NUM_LEDS 8
#define BRIGHTNESS  128

#define RedLed 0
#define GreenLed 1
#define BlueLed 2

/**************************************************************************/
  /*!
    \class Flasher Debug.h <Debug.h>
    /// \brief Operate digital led based on I/O in a co-ordinated fashion
  */
/**************************************************************************/
class Flasher {
  
  private:
  int _pin;      // The number of the LED pin
	unsigned long _on;     // milliseconds of on-time
	unsigned long _off;    // milliseconds of off-time
	// These maintain the current state
	int ledState;             		// ledState used to set the LED
	unsigned long previousMillis;  	// will store last time LED was updated
    
  public:
  /**************************************************************************/
  /*!
    /// Constructor. You can have multiple Led setup, all running on the same time with
    /// defferent configuration
    /// functions at frequent enough intervals.
    /// \param[in] pin Any pwm pin number for motor pin 1 that support digital value
    /// \param[in] on time to turn on the led within the function
    /// \param[in] off time to turn off the led within the function
    /// Can be use to turn on any led 
  */
  /**************************************************************************/

    Flasher(int pin, long on, long off);
  /**************************************************************************/
  /*!
    /// Call the update function without sacrifice the loop time 
    /// \param[in] pin1 call by contructor name
  */
  /**************************************************************************/
    virtual void Update(); 
  /**************************************************************************/
  /*!
    /// Turn On(); function without sacrifice the loop time 
    /// \param[in] pin call by contructor name
  */
  /**************************************************************************/
    virtual void On(); 
  /**************************************************************************/
  /*!
    /// Turn Stop(); function without sacrifice the loop time  
    /// \param[in] pin call by contructor name
  */
  /**************************************************************************/
    virtual void Off(); 

};
/**************************************************************************/
  /*!
    \class Flasher Debug.h <Debug.h>
    /// \brief Operate digital led based on I/O in a co-ordinated fashion
  */
/**************************************************************************/
class Relay {
  
  private:
  int _pin;      // The number of the LED pin
	unsigned long _on;     // milliseconds of on-time
	unsigned long _off;    // milliseconds of off-time
	// These maintain the current state
	int ledState;             		// ledState used to set the LED
	unsigned long previousMillis;  	// will store last time LED was updated
    
  public:
  /**************************************************************************/
  /*!
    /// Constructor. You can have multiple Led setup, all running on the same time with
    /// defferent configuration
    /// functions at frequent enough intervals.
    /// \param[in] pin Any pwm pin number for motor pin 1 that support digital value
    /// \param[in] on time to turn on the led within the function
    /// \param[in] off time to turn off the led within the function
    /// Can be use to turn on any led 
  */
  /**************************************************************************/

    Relay(int pin, long on, long off);
  /**************************************************************************/
  /*!
    /// Call the update function without sacrifice the loop time 
    /// \param[in] pin1 call by contructor name
  */
  /**************************************************************************/
    virtual void Update(); 
  /**************************************************************************/
  /*!
    /// Turn On(); function without sacrifice the loop time 
    /// \param[in] pin call by contructor name
  */
  /**************************************************************************/
     virtual void OnB(); 
  /**************************************************************************/
  /*!
    /// Turn Stop(); function without sacrifice the loop time  
    /// \param[in] pin call by contructor name
  */
  /**************************************************************************/
    virtual void OffB(); 
 
};
/**************************************************************************/
  /*!
    \class Ws2812 Debug.h <Debug.h>
    /// \brief Operate RGB Ws2812 Led based on I/O in a co-ordinated fashion
  */
/**************************************************************************/



class Ws2812  {
  
  private:
  int _LedN;
	unsigned long _on;     // milliseconds of on-time
	unsigned long _off;    // milliseconds of off-time
	// These maintain the current state
	int ledState;             		// ledState used to set the LED
	unsigned long previousMillis;  	// will store last time LED was updated
  // FastLED _fastLED;  
 
  public:
  /**************************************************************************/
  /*!
    /// Constructor. You can have multiple Led based on Ws2812 setup, all running on the same time with
    /// defferent configuration
    /// functions at frequent enough intervals.
    /// \param[in] LedN Any pwm pin number for motor pin 1 that support digital value
    /// \param[in] on time to turn on the led within the function
    /// \param[in] off time to turn off the led within the function
    /// Can be use to turn on any led 
  */
    Ws2812(int LedN, long on, long off);
  /**************************************************************************/
  /*!
    /// Call the update function without sacrifice the loop time 
    /// \param[in] Co Color selection from define.
    /// #define RedLed 0
    /// #define GreenLed 1
    /// #define BlueLed 2
  */
  /**************************************************************************/
    virtual void Update(int Co); 
  /**************************************************************************/
  /*!
    /// Call the Theme function to use selected color 
    /// \param[in] Color Color selection from define.
    /// #define RedLed 0
    /// #define GreenLed 1
    /// #define BlueLed 2
  */
  /**************************************************************************/
    virtual int Theme(int Color); 
  /**************************************************************************/
  /*!
    /// Call the Reset to reset all pin into 0 or turn black 
    /// \param[in] Color Color selection from define.
    /// #define RedLed 0
    /// #define GreenLed 1
    /// #define BlueLed 2
  */
  /**************************************************************************/
    virtual void Reset(); 
  /**************************************************************************/
  /*!
    /// Call the On funtion to turn the specific led 
    /// \param[in] Color Color selection from define.
    /// #define RedLed 0
  */
  /**************************************************************************/
    virtual void On(); 
  /**************************************************************************/
  /*!
    /// Call the Off funtion to turn off the specific led 
  */
  /**************************************************************************/
    virtual void Off(); 
  /**************************************************************************/
  /*!
    /// Call the Rainbow funtion to run led in rainbow mode 
    /// \param[in] Color Color selection from define.
  */
  /**************************************************************************/
    virtual void Rainbow(); 
  /**************************************************************************/
  /*!
    /// Call the SingleRainbow funtion to run specific led in rainbow mode 
    /// \param[in] Color Color selection from define.
  */
  /**************************************************************************/
    virtual void SingleRainbow(); 
  /**************************************************************************/
  /*!
    /// Call the EncoderIndicator funtion to estabilse encoder condition
    /// \param[in] Value Encoder selection.
  */
  /**************************************************************************/
    virtual void EncoderIndicator(int Value); 
    int EncoderCounter = 0; // counter for the number of EncoderCounter
    int Encoderlast = 0;  // previous state of the Encoderlast
    unsigned long PreviousMillis = 0; // will store last time Button state value 
    unsigned long Next_Interval = 50; // next interval to count
    uint8_t hue = 0;

    
};


class Ws2812_LSP {
  
  private:
  int _LedN;
	unsigned long _on;     // milliseconds of on-time
	unsigned long _off;    // milliseconds of off-time
	// These maintain the current state
	int ledState;             		// ledState used to set the LED
	unsigned long previousMillis;  	// will store last time LED was updated
    
    
  public:
  /**************************************************************************/
  /*!
    /// Constructor. You can have multiple Led based on Ws2812 setup, all running on the same time with
    /// defferent configuration
    /// functions at frequent enough intervals.
    /// \param[in] LedN Any pwm pin number for motor pin 1 that support digital value
    /// \param[in] on time to turn on the led within the function
    /// \param[in] off time to turn off the led within the function
    /// Can be use to turn on any led 
  */
    Ws2812_LSP(int LedN, long on, long off);
  /**************************************************************************/
  /*!
    /// Call the update function without sacrifice the loop time 
    /// \param[in] Co Color selection from define.
    /// #define RedLed 0
    /// #define GreenLed 1
    /// #define BlueLed 2
  */
  /**************************************************************************/
    void Update(int Co); 
  /**************************************************************************/
  /*!
    /// Call the Theme function to use selected color 
    /// \param[in] Color Color selection from define.
    /// #define RedLed 0
    /// #define GreenLed 1
    /// #define BlueLed 2
  */
  /**************************************************************************/
     int Theme(int Color); 
  /**************************************************************************/
  /*!
    /// Call the Reset to reset all pin into 0 or turn black 
    /// \param[in] Color Color selection from define.
    /// #define RedLed 0
    /// #define GreenLed 1
    /// #define BlueLed 2
  */
  /**************************************************************************/
     void Reset(); 
  /**************************************************************************/
  /*!
    /// Call the On funtion to turn the specific led 
    /// \param[in] Color Color selection from define.
    /// #define RedLed 0
  */
  /**************************************************************************/
    void On(); 
  /**************************************************************************/
  /*!
    /// Call the Off funtion to turn off the specific led 
  */
  /**************************************************************************/
     void Off(); 
  /**************************************************************************/
  /*!
    /// Call the Rainbow funtion to run led in rainbow mode 
    /// \param[in] Color Color selection from define.
  */
  /**************************************************************************/
    void Rainbow(); 
  /**************************************************************************/
  /*!
    /// Call the SingleRainbow funtion to run specific led in rainbow mode 
    /// \param[in] Color Color selection from define.
  */
  /**************************************************************************/
     void SingleRainbow(); 
  /**************************************************************************/
  /*!
    /// Call the EncoderIndicator funtion to estabilse encoder condition
    /// \param[in] Value Encoder selection.
  */
  /**************************************************************************/
    uint8_t hue = 0;

    
};
class Ws2812_RSP {
  
  private:
  int _LedN;
	unsigned long _on;     // milliseconds of on-time
	unsigned long _off;    // milliseconds of off-time
	// These maintain the current state
	int ledState;             		// ledState used to set the LED
	unsigned long previousMillis;  	// will store last time LED was updated
    
    
  public:
  /**************************************************************************/
  /*!
    /// Constructor. You can have multiple Led based on Ws2812 setup, all running on the same time with
    /// defferent configuration
    /// functions at frequent enough intervals.
    /// \param[in] LedN Any pwm pin number for motor pin 1 that support digital value
    /// \param[in] on time to turn on the led within the function
    /// \param[in] off time to turn off the led within the function
    /// Can be use to turn on any led 
  */
    Ws2812_RSP(int LedN, long on, long off);
  /**************************************************************************/
  /*!
    /// Call the update function without sacrifice the loop time 
    /// \param[in] Co Color selection from define.
    /// #define RedLed 0
    /// #define GreenLed 1
    /// #define BlueLed 2
  */
  /**************************************************************************/
  void Update(int Co); 
  /**************************************************************************/
  /*!
    /// Call the Theme function to use selected color 
    /// \param[in] Color Color selection from define.
    /// #define RedLed 0
    /// #define GreenLed 1
    /// #define BlueLed 2
  */
  /**************************************************************************/
   void Cylon(); 
  /**************************************************************************/
  /*!
    /// Call the Theme function to use selected color 
    /// \param[in] Color Color selection from define.
    /// #define RedLed 0
    /// #define GreenLed 1
    /// #define BlueLed 2
  */
  /**************************************************************************/
     int Theme(int Color); 
  /**************************************************************************/
  /*!
    /// Call the Reset to reset all pin into 0 or turn black 
    /// \param[in] Color Color selection from define.
    /// #define RedLed 0
    /// #define GreenLed 1
    /// #define BlueLed 2
  */
  /**************************************************************************/
    void Reset(); 
  /**************************************************************************/
  /*!
    /// Call the On funtion to turn the specific led 
    /// \param[in] Color Color selection from define.
    /// #define RedLed 0
  */
  /**************************************************************************/
     void On(); 
  /**************************************************************************/
  /*!
    /// Call the Off funtion to turn off the specific led 
  */
  /**************************************************************************/
     void Off(); 
  /**************************************************************************/
  /*!
    /// Call the Rainbow funtion to run led in rainbow mode 
    /// \param[in] Color Color selection from define.
  */
  /**************************************************************************/
    void Rainbow(); 
  /**************************************************************************/
  /*!
    /// Call the SingleRainbow funtion to run specific led in rainbow mode 
    /// \param[in] Color Color selection from define.
  */
  /**************************************************************************/
     void SingleRainbow(); 
      void DRL(); 
       void AllOff(); 
        void RightBlinker(); 
  /**************************************************************************/
  /*!
    /// Call the EncoderIndicator funtion to estabilse encoder condition
    /// \param[in] Value Encoder selection.
  */
  /**************************************************************************/
    uint8_t hue = 0;
       unsigned long PreviousMillis = 0; // will store last time Button state value 
    unsigned long Next_Interval = 15; // next interval to count
unsigned long BlinkerSpeed = 50; //Turn Signal Running LED Speed. Adjust this to match with your vehicle turn signal speed.
unsigned long BlinkerOffDelay = 500; //Turn Signal Off time. Adjust this to match with your vehicle turn signal speed.

int DRLColour = 3; //Change LED colour here, 1-Ice Blue, 2-Orange, 3-Blue, 4-White, 5-Red, 6-Green, 7- Magenta, 8- Yellow


int r,g,b;
    
};
/**************************************************************************/
  /*!
    \class ButtState Debug.h <Debug.h>
    /// \brief Operate any button switch based on I/O in a co-ordinated fashion
  */
/**************************************************************************/
class ButtState { 
  private:
    int _pin;// The number of the LED pin
    // These maintain the current state
    int buttonPushCounter = 0;   // counter for the number of button presses
    int buttonState = 0;         // current state of the button
    int lastButtonState = 0;     // previous state of the button
    unsigned long PreviousMillis = 0; // will store last time Button state value 
    unsigned long Next_Interval = 100; // next interval to count
    Flasher* led; //Pointer class Flasher Led
    
  public:
  /**************************************************************************/
  /*!
    /// Constructor. You can have multiple Button based , all running on the same time with
    /// defferent configuration
    /// functions at frequent enough intervals.
    /// \param[in] pin Any pwm pin number for analog and digital.
    /// \param[in] Flasher& Flasher time to turn on the led within the class.
  */
  /**************************************************************************/
    ButtState(int pin, Flasher& Flasher); //Pass reference to Serial object into a class
  /**************************************************************************/
  /*!
    /// Call the Update function to update any state changing on the button
  */
  /**************************************************************************/
    void Update(); // Methods Update Button State
    
};
/**************************************************************************/
  /*!
    \class Switch Debug.h <Debug.h>
    /// \brief Operate any button switch based on I/O in a co-ordinated fashion
  */
/**************************************************************************/
class Switch { 

  private:
    int _pin;// The number of the LED pin
    int _Number;// The number of the LED pin
    // These maintain the current state
    int buttonPushCounter = 0;   // counter for the number of button presses
    int buttonState = 0;         // current state of the button
    int lastButtonState = 0;     // previous state of the button
    unsigned long PreviousMillis = 0; // will store last time Button state value 
    unsigned long Next_Interval = 10; // next interval to count
    Flasher* led; //Pointer class Flasher Led
    
  public:
    /**************************************************************************/
  /*!
    /// Constructor. You can have multiple Switch based , all running on the same time with
    /// defferent configuration
    /// functions at frequent enough intervals.
    /// \param[in] pin Any pwm pin number for analog and digital.
    /// \param[in] Number& Number on switch register.
    /// \param[in] Flasher& Flasher time to turn on the led within the class.
  */
  /**************************************************************************/
    Switch(int pin,int Number, Flasher& Flasher); //Pass reference to Serial object into a class
    void Update(); // Methods Update Button State
    
    
};
#endif