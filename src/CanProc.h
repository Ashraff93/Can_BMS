/*
  Debug.h - Control all traffic link betweeN mcu and device throught CAN 2.0- Version 2
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

#ifndef CANPROC_H
#define CANPROC_H
#include <Arduino.h> //#include "Arduino.h" For Arduino Framework Logic
#include <elapsedMillis.h> //#Elapsed time types - for easy-to-use measurements of elapsed time
#include "EnumBoolen.h" //#Control Enum Logic cross all RACE_UGV main function
#include <FlexCAN_T4.h> //#base format currently, features and enhancements with CAN2.0 and CANFD
#include <Convert.h> //All converted data type that been compile into sub and constructor

#include "Debug.h" //#include "Mm.h" For Enum Logic

/**************************************************************************/
  /*!
    \class CanBus CanBus.h <CanBus.h>
    /// \brief Control all CAN2.0 communication in a co-ordinated fashion
  */
/**************************************************************************/
class CanBus {
    // Class Member Variables
    // Constructor - creates a CanBus
  private:
  
    Flasher* led; //Pointer class Ws2812 Led
    String DecHex_Linear; // String DecHex_Linear declaration
    String DecHex_Angular; // String DecHex_Linear declaration
    String hex_values = "";
    int Map_Linear; // Interger Map_Linear declaration
    int Map_Angular; // Interger Map_Angular declaration
    double forward_mapped; // double forward_mapped declaration
    double backward_mapped; // double backward_mapped declaration
    double right_mapped; // double right_mapped declaration
    double left_mapped; // double left_mapped declaration
    const byte MaxByteArraySize = 2; // byte MaxByteArraySize declaration
    IntervalTimer timer;

  public:
  /**************************************************************************/
  /*!
    /// Constructor. You can have CAN2.0 prtotcal device, all communicated
    /// at different speeds and function, provided you call their CanBUS()
    /// functions at frequent enough intervals.
    /// \param[in] ws2812  Call class led to pointer with constructor or object
    /// for specific task
  */

  /**************************************************************************/
  CanBus(Flasher& flasher) {
      led = &flasher;
    }
  /**************************************************************************/
  /*!
    /// Begin CAN communication.
    /// \param[in] dataRate datarate setup for CAN communication establised.
  */
  /**************************************************************************/
    void begin(uint32_t dataRate); 
  /**************************************************************************/
  /*!
    /// Update Can bus event and starting comunication.
    /// \param[in] dataRate datarate setup for CAN communication establised.
    /// running canSniff20(const CAN_message_t &msg) every datarate to make sure
    /// continuously communication inbetween mcu and device
  */
  /**************************************************************************/
    void CanB_Event(); //Void Function Parameter IncomingNewMessage declaration
    void Send_EventRaw(uint16_t V,uint16_t C,uint16_t CS, boolean K ); //Void Function Parameter IncomingNewMessage declaration
    String Conversion(uint16_t VR);
  struct Charging_message
  {
    uint16_t _voltage_reference; //Limit switch status
    uint16_t _current_reference; //Alarm value status
    uint16_t _charging_reference; //Error value status
  };Charging_message  charging_message;
    struct Heartbeat_message
  {
    uint16_t _voltage_reference; //Limit switch status
    uint16_t _current_reference; //Alarm value status
    uint16_t _charging_reference; //Error value status
  };Heartbeat_message  heartbeat_message;
    
};

#endif