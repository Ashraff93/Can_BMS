#include "CanProc.h"

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;  // can1 port 
Convert convert;
extern uint8_t buff_D[];
  uint16_t VR, CR, EC; 
  uint16_t VF, CF, EF;
void canSniff20(const CAN_message_t &msg) { // global callback
  // Serial.print("T4: ");
  // Serial.print("MB "); Serial.print(msg.mb);
  // Serial.print(" OVERRUN: "); Serial.print(msg.flags.overrun);
  // Serial.print(" BUS "); Serial.print(msg.bus);
  // Serial.print(" LEN: "); Serial.print(msg.len);
  // Serial.print(" EXT: "); Serial.print(msg.flags.extended);
  // Serial.print(" REMOTE: "); Serial.print(msg.flags.remote);
  // Serial.print(" TS: "); Serial.print(msg.timestamp);
  // Serial.print(" ID: "); Serial.print(msg.id, HEX);
  // Serial.print(" IDHIT: "); Serial.print(msg.idhit);
  // Serial.print(" buff_Der: ");
  //   for ( uint8_t i = 0; i < msg.len; i++ ) {
  //   Serial.print(msg.buf[i], HEX); Serial.print(" ");
  // } Serial.println();

  if (msg.id == 0x701){
      switch (msg.buf[1]) {
        case 0:
                heartbeat() = Heartbeat::Initialization;   
        break;
        case 1:
                heartbeat() = Heartbeat::Pre_operational;  
        break;
        case 2:
                heartbeat() = Heartbeat::Operational;  
        break;
        default:

      break;
}
  }
  if (msg.id == 0x201){
       uint16_t VR  = (msg.buf[0]<<8) + msg.buf[1];//The nearest target of sector2
       uint16_t VRF  = VR *10;
       uint16_t CR = (msg.buf[2]<<8) + msg.buf[3];//The nearest target of sector3
       uint16_t CRF  = CR *10;
       uint16_t EC = (msg.buf[0]<<4) + msg.buf[5];;//The nearest target of sector1
        switch (EC) {
        case 0:
                charging_State() = Charging_State::Stop_Charging;   
        break;
        case 1:
                charging_State() = Charging_State::Start_Charging;  
        break;
        default:

      break;
}
  }
  if (msg.id == 0x181 ){
        uint16_t VF  = (msg.buf[0]<<8) + msg.buf[1];//The nearest target of sector2
        uint16_t VFF  = VF *10;
        uint16_t CF = (msg.buf[2]<<8) + msg.buf[3];//The nearest target of sector3
        uint16_t CFF  = CF *10;
        uint16_t EF = (msg.buf[0]<<4) + msg.buf[5];;//The nearest target of sector1
          switch (EF) {
        case 0:
                charging_State() = Charging_State::Stop_Charging;   
        break;
        case 1:
                charging_State() = Charging_State::Start_Charging;  
        break;
        default:

      break;
}
  }
    
}

void sendframe()
{
  CAN_message_t msg;
  msg.id = 0x0A;
  msg.len = 8;
  msg.flags.extended = 0;
  msg.flags.remote   = 0;
  msg.flags.overrun  = 0;
  msg.flags.reserved = 0;
  for ( uint8_t i = 0; i < 8; i++ ){
    msg.buf[i] = buff_D[i];
  }
  
  if (rover_Mode() == Rover_Mode::Active || ros_State()== Ros_State::Ros_Connected){
    // Debugging_Serial_Print
    // for ( uint8_t i = 0; i < msg.len; i++ ) {
    //   Serial.print(msg.buf[i], HEX); Serial.print(" ");
    // } 
    // Serial.println();
    // hex_values = "";

    // for ( uint8_t i = 0; i < msg.len; i=i+2 ) {
    //   String combine = String(msg.buf[i], HEX) + String(msg.buf[i+1], HEX);
    //   hex_values += String(convert.hexaToDecimal(combine), DEC) + " ";
    // } 
    can1.write(msg);       // write to can1
  }
}

void CanBus::begin(uint32_t dataRate){
  can1.begin();
  can1.setBaudRate(dataRate);     // 500kbps data rate
  can1.enableFIFO();
  can1.enableFIFOInterrupt();
  can1.onReceive(FIFO, canSniff20);
  can1.mailboxStatus();
  timer.begin(sendframe, 200000); // Send frame every 200ms 
}

void CanBus::CanB_Event(){
  can1.events();
  if (Comm_Establish_Button() || Comm_Establish()){
    led->Update(1); //Call 
  }
  else{
    led->Update(0);
  }
}



