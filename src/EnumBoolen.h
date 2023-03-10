/*
  EnumBoolen.h - Control Enum Logic cross all RACE_UGV main function- Version 2
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
#ifndef ENUMBOOLEN_H
#define ENUMBOOLEN_H
#include <Arduino.h>

enum Debug_Mode {
  Off_Running,
  On_Running, // GPS detected
};
//  extern enum Obs_State obsState;
inline Debug_Mode& debug_Mode() {
  static Debug_Mode currentdebug_Mode;
  return currentdebug_Mode;
}

enum Switch_Button {
  Off_State,
  On_State, // GPS detected
};
//  extern enum Obs_State obsState;
inline Switch_Button& switch_Button() {
  static Switch_Button currentswitch_Button;
  return currentswitch_Button;
}
enum Switch_Button_Servo {
  Off_State_Servo,
  On_State_Servo, // GPS detected
};
//  extern enum Obs_State obsState;
inline Switch_Button_Servo& switch_Button_Servo() {
  static Switch_Button_Servo currentswitch_Button_Servo;
  return currentswitch_Button_Servo;
}

enum Heartbeat {
  Initialization, // When OBS Outside Parameter
  Pre_operational, // When Auto in active
  Operational
  
};
//  extern enum Obs_State obsState;
inline Heartbeat& heartbeat() {
  static Heartbeat currentHeartbeat;
  return currentHeartbeat;
}
enum BMS_State {
  Request_Charging, // When OBS Outside Parameter
  Not_Charging
  
};
//  extern enum Obs_State obsState;
inline BMS_State& bMS_State() {
  static BMS_State currentbMS_State;
  return currentbMS_State;
}
enum Charging_State {
  Stop_Charging, // When OBS Outside Parameter
  Start_Charging
  
};
//  extern enum Obs_State obsState;
inline Charging_State& charging_State() {
  static Charging_State currentCharging_State;
  return currentCharging_State;
}
enum Heartbeat_State {
  Stop_Charging_State, // When OBS Outside Parameter
  Start_Charging_State
  
};
//  extern enum Obs_State obsState;
inline Heartbeat_State& heartbeat_State() {
  static Heartbeat_State currentheartbeat_State;
  return currentheartbeat_State;
}
inline bool BMS_Establish() {
  if ((bMS_State() == BMS_State::Request_Charging && heartbeat() == Heartbeat::Pre_operational )) {
    return true;
  }
  return false;
}
#endif