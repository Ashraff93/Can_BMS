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
enum Rover_Mode {
  Inactive, // When both AB and Auto inactive
  Active, // When Auto in active
};
//  extern enum Obs_State obsState;
inline Rover_Mode& rover_Mode() {
  static Rover_Mode currentRover_Mode;
  return currentRover_Mode;
}
enum Rover_State {
  Diconnected, // When OBS Outside Parameter
  Connected, // When Auto in active

};
//  extern enum Obs_State obsState;
inline Rover_State& rover_State() {
  static Rover_State currentRover_State;
  return currentRover_State;
}
enum Ros_State {
  Ros_Diconnected, // When OBS Outside Parameter
  Ros_Connected, // When Auto in active
  
};
//  extern enum Obs_State obsState;
inline Ros_State& ros_State() {
  static Ros_State currentRos_State;
  return currentRos_State;
}
//&& rover_State() == Rover_State::Connected)
inline bool Comm_Establish_Button() {
  if ((rover_Mode() == Rover_Mode::Active && rover_State() == Rover_State::Connected )) {
    return true;
  }
  return false;
}
inline bool Comm_Establish() {
  if ((ros_State() == Ros_State::Ros_Connected && rover_State() == Rover_State::Connected)) {
    return true;
  }
  return false;
}
inline bool Comm_Debug_Establish() {
  if (debug_Mode() == Debug_Mode::On_Running) {
    return true;
  }
  return false;
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
enum Charging_State {
  Stop_Charging, // When OBS Outside Parameter
  Start_Charging
  
};
//  extern enum Obs_State obsState;
inline Charging_State& charging_State() {
  static Charging_State currentCharging_State;
  return currentCharging_State;
}
#endif