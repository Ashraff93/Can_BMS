#include "CanProc.h"
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;  // can1 port 
Convert convert;
extern uint8_t buff_D[];
uint16_t VRF, CRF, EC; 
uint16_t VFF, CFF, EF;
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
                heartbeat() = Heartbeat::Initialization;//0 : initialization
        break;
        case 1:
                heartbeat() = Heartbeat::Pre_operational;//1 : pre-operational  
        break;
        case 2:
                heartbeat() = Heartbeat::Operational;//2 : operational 
        break;
        default:

      break;
}
  }
  if (msg.id == 0x201){
    bMS_State() = BMS_State::Request_Charging;
    uint16_t VR  = (msg.buf[0]<<8) + msg.buf[1];//voltage reference low<<voltage reference high
    VRF  = VR /10;// *10, ex: 321 = 32.1V
    uint16_t CR = (msg.buf[2]<<8) + msg.buf[3];//current reference low<<current reference high
    CRF  = CR /10;//*10, ex: 1000 = 100A
    EC = (msg.buf[0]<<4) + msg.buf[5];//Enable command 
    switch (EC) {
      case 0:
            charging_State() = Charging_State::Stop_Charging;//0: stop Charging   
      break;
      case 1:
            charging_State() = Charging_State::Start_Charging;//1: start Charging
      break;
      default:

      break;
    }
  }
  else{
    bMS_State() = BMS_State::Not_Charging;
  }
  if (msg.id == 0x181 ){
        uint16_t VF  = (msg.buf[0]<<8) + msg.buf[1];//voltage reference low<<voltage reference high
        VFF  = VF /10;// *10, ex: 321 = 32.1V
        uint16_t CF = (msg.buf[2]<<8) + msg.buf[3];//current reference low<<current reference high
        CFF  = CF /10;//*10, ex: 1000 = 100A
        uint16_t EF = (msg.buf[0]<<4) + msg.buf[5];//Enable command 
          switch (EF) {
        case 0:
                charging_State() = Charging_State::Stop_Charging;//0: stop Charging   
        break;
        case 1:
                charging_State() = Charging_State::Start_Charging;//1: start Charging
        break;
        default:

      break;
}
  }
    
}

void sendframe()
{
  CAN_message_t msg;
  msg.id = 0x181;
  msg.len = 8;
  msg.flags.extended = 0;
  msg.flags.remote   = 0;
  msg.flags.overrun  = 0;
  msg.flags.reserved = 0;
  for ( uint8_t i = 0; i < 8; i++ ){
    msg.buf[i] = buff_D[i];
  }
  
  if (charging_State() == Charging_State::Start_Charging){ 
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
  charging_message._voltage_reference = VRF;
  charging_message._current_reference = CRF;
  charging_message._charging_reference = EC;
  heartbeat_message._voltage_reference = VFF;
  heartbeat_message._current_reference = CFF;
  heartbeat_message._charging_reference = EF;

}
byte nibble(char c){
  if (c >= '0' && c <= '9')
    return c - '0';

  if (c >= 'a' && c <= 'f')
    return c - 'a' + 10;

  if (c >= 'A' && c <= 'F')
    return c - 'A' + 10;

  return 0;  // Not a valid hexadecimal character
}
void hexCharacterStringToBytes(byte *byteArray, const char *hexString){
  bool oddLength = strlen(hexString) & 1;
  byte currentByte = 0;
  byte byteIndex = 0;

  for (byte charIndex = 0; charIndex < strlen(hexString); charIndex++)
  {
    bool oddCharIndex = charIndex & 1;

    if (oddLength){
      if (oddCharIndex){ // If the length is odd
        currentByte = nibble(hexString[charIndex]) << 4; // odd characters go in high nibble
      }
      else{
        currentByte |= nibble(hexString[charIndex]);// Even characters go into low nibble
        byteArray[byteIndex++] = currentByte;
        currentByte = 0;
      }
    }
    else{
      if (!oddCharIndex){ // If the length is even
        currentByte = nibble(hexString[charIndex]) << 4; // Odd characters go into the high nibble
      }
      else{
        currentByte |= nibble(hexString[charIndex]); // Odd characters go into low nibble
        byteArray[byteIndex++] = currentByte;
        currentByte = 0;
      }
    }
  }
}

void Upper_ByteState(){
    buff_D[2] = 0x00;
    buff_D[3] = 0x00;
}
void Lower_ByteState(){
    buff_D[0] = 0x00;
    buff_D[1] = 0x00;
}

void dumpByteArray_Voltage(const byte * byteArray_Voltage, const byte arraySize){
      buff_D[0] = byteArray_Voltage[0];
      buff_D[1] = byteArray_Voltage[1];
}
void dumpByteArray_Current(const byte * byteArray_Current, const byte arraySize){
      buff_D[2] = byteArray_Current[0];
      buff_D[3] = byteArray_Current[1];
}
void dumpByteArray_CS(const byte * byteArray_CS, const byte arraySize){
      buff_D[4] = byteArray_CS[0];
      buff_D[5] = byteArray_CS[1];
}
String CanBus:: Conversion(uint16_t V){
    String SFD="";
    if(V<=255){
        String Tem = "00" + convert.decimalToHexa(V);
        SFD = Tem;
    }
    else{
        SFD = convert.decimalToHexa(V);
    }
   return SFD;
}
void CanBus::Send_EventRaw(uint16_t V,uint16_t C,uint16_t CS, boolean K){

  if(K == true){
    
    byte byteArray_V[MaxByteArraySize] = {0};
    hexCharacterStringToBytes(byteArray_V, CanBus::Conversion(V).c_str());
    dumpByteArray_Voltage(byteArray_V, MaxByteArraySize);

    byte byteArray_C[MaxByteArraySize] = {0};
    hexCharacterStringToBytes(byteArray_C, CanBus::Conversion(C).c_str());
    dumpByteArray_Voltage(byteArray_C, MaxByteArraySize);
    
    byte byteArray_CS[MaxByteArraySize] = {0};
    hexCharacterStringToBytes(byteArray_CS, CanBus::Conversion(CS).c_str());
    dumpByteArray_Voltage(byteArray_CS, MaxByteArraySize);
  }
}


