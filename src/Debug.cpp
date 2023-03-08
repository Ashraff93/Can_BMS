
#include "Debug.h"

Flasher::Flasher(int pin, long on, long off) {
  // Use 'this->' to make the difference between the
  // 'pin' attribute of the class and the 
  // local variable 'pin' created from the parameter.
    _pin = pin;//Pointer the ledPin
    pinMode(_pin, OUTPUT); // Attaches the pinMode on ledPin    
	  _on = on; //Pointer the OnTime
	  _off = off; //Pointer the OffTime
	  ledState = LOW; // ledState used to set the LED 
	  previousMillis = 0; 
}

void Flasher::Update(){
  // check to see if it's time to change the state of the LED
  unsigned long currentMillis = millis();//Get the current "time" (actually the number of milliseconds since the program started)
  if((ledState == HIGH) && (currentMillis - previousMillis >= _on)){ //Check whether the period has elapsed
    ledState = LOW;  // Turn it off
    previousMillis = currentMillis;  // Remember the time
    digitalWrite(_pin, ledState);  // Update the actual LED
  }
  else if ((ledState == LOW) && (currentMillis - previousMillis >= _off)){ //Check whether the period has elapsed
    ledState = HIGH;  // turn it on
    previousMillis = currentMillis;   // Remember the time
    digitalWrite(_pin, ledState);	  // Update the actual LED
  }
}
void Flasher::On(){
  digitalWrite(_pin, HIGH); // ledState used to set the LED
}
void Flasher::Off(){
  digitalWrite(_pin, LOW); // ledState used to set the LED
}


Relay::Relay(int pin, long on, long off) {
  // Use 'this->' to make the difference between the
  // 'pin' attribute of the class and the 
  // local variable 'pin' created from the parameter.
    _pin = pin;//Pointer the ledPin
    pinMode(_pin, OUTPUT); // Attaches the pinMode on ledPin
    digitalWrite(_pin, HIGH); // ledState used to set the LED   
	  _on = on; //Pointer the OnTime
	  _off = off; //Pointer the OffTime
	  ledState = LOW; // ledState used to set the LED 
	  previousMillis = 0; 
}

void Relay::Update(){
  // check to see if it's time to change the state of the LED
  unsigned long currentMillis = millis();//Get the current "time" (actually the number of milliseconds since the program started)
  if((ledState == HIGH) && (currentMillis - previousMillis >= _on)){ //Check whether the period has elapsed
    ledState = LOW;  // Turn it off
    previousMillis = currentMillis;  // Remember the time
    digitalWrite(_pin, ledState);  // Update the actual LED
  }
  else if ((ledState == LOW) && (currentMillis - previousMillis >= _off)){ //Check whether the period has elapsed
    ledState = HIGH;  // turn it on
    previousMillis = currentMillis;   // Remember the time
    digitalWrite(_pin, ledState);	  // Update the actual LED
  }
}

void Relay::OnB(){
  digitalWrite(_pin, LOW); // ledState used to set the LED
}
void Relay::OffB(){
  digitalWrite(_pin, HIGH); // ledState used to set the LED
}



CRGB leds[NUM_LEDS];/// Representation of an RGB pixel (Red, Green, Blue)
Ws2812::Ws2812(int LedN, long on, long off) {
  _LedN = LedN;
  _on = on; //Pointer the on
	_off = off; //Pointer the off
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
  FastLED.setBrightness( BRIGHTNESS );
  ledState = LOW; // ledState used to set the LED 
	previousMillis = 0;
}
int Ws2812::Theme(int Color){
  int col = Color;//Pointer the Color
    switch (col) { //Select case base on color selection
        case 0:
          col=CRGB::Red; //#define RedLed 0
        break;
        case 1:
          col=CRGB::Green; //#define GreenLed 1
        break;
        case 2:
          col=CRGB::Blue; //#define BlueLed 2
        break;
        default:
    break;
  }
  return col;

}
void Ws2812::Update(int Co){
  // check to see if it's time to change the state of the LED
  int temC = Theme(Co); //Call function
  unsigned long currentMillis = millis();//Get the current "time" (actually the number of milliseconds since the program started)
  if((ledState == HIGH) && (currentMillis - previousMillis >= _on)){ //Check whether the period has elapsed
    ledState = LOW;  // Turn it off
    previousMillis = currentMillis;  // Remember the time
    leds[_LedN] = temC;
    FastLED.show(); /// Update all our controllers with the current led colors
  }
  else if ((ledState == LOW) && (currentMillis - previousMillis >= _off)){ //Check whether the period has elapsed
    ledState = HIGH;  // turn it on
    previousMillis = currentMillis;   // Remember the time
    leds[_LedN] = CRGB::Black; /// Representation of an RGB pixel (Red, Green, Blue)
    FastLED.show(); /// Update all our controllers with the current led colors
  }
}
void Ws2812::Reset(){
   FastLED.clear (); /// reset or clear all our controllers with the current led colors
   //fill_solid( leds, NUM_LEDS, CRGB::Black);
   FastLED.show(); /// Update all our controllers with the current led colors
}
void Ws2812::Off(){
    
    leds[_LedN] = CRGB::Black; /// Representation of an RGB pixel (Red, Green, Blue)
    FastLED.show(); /// Update all our controllers with the current led colors
  
}
void Ws2812::On(){
  unsigned long currentMillis = millis(); ///Get the current "time" (actually the number of milliseconds since the program started)
  if (currentMillis - previousMillis >= _on) { ///Check whether the period has elapsed
    previousMillis = currentMillis; // Remember the time
    leds[_LedN] = CRGB::Red; /// Representation of an RGB pixel (Red, Green, Blue)
    FastLED.show(); /// Update all our controllers with the current led colors
  }
  else{
    leds[_LedN] = CRGB::Black;/// Representation of an RGB pixel (Red, Green, Blue)
    FastLED.show(); /// Update all our controllers with the current led colors
  }
}
void Ws2812::Rainbow(){
   for (int i = 0; i < NUM_LEDS; ++i) {
    leds[i] = CHSV(hue + (i * 10), 255, 255);
  }
  //You can change the pattern speed here
  EVERY_N_MILLISECONDS(15){
    hue++;
  }
  FastLED.show(); /// Update all our controllers with the current led colors
}
void Ws2812::SingleRainbow(){
  //  for (int i = 0; i < NUM_LEDS; ++i) {
    leds[_LedN] = CHSV(hue + (_LedN * 10), 255, 255);
  // }
    unsigned long currentMillis = millis();//Get the current "time" (actually the number of milliseconds since the program started)
  if (currentMillis - PreviousMillis >= Next_Interval) { //Check whether the period has elapsed
    PreviousMillis = currentMillis; //IMPORTANT to save the start time of the current function.
   hue++;
  } 
  // EVERY_N_MILLISECONDS(15){
    
  // }
  FastLED.show(); /// Update all our controllers with the current led colors
}

void Ws2812::EncoderIndicator(int Value){
  unsigned long currentMillis = millis();//Get the current "time" (actually the number of milliseconds since the program started)
  if (currentMillis - PreviousMillis >= Next_Interval) { //Check whether the period has elapsed
    PreviousMillis = currentMillis; // Remember the time
    int Encodernow = Value; //Pointer the off  
    if (Encodernow != Encoderlast){ // if the state has changed, increment the counter
      Update(GreenLed);
    }
    else{
      Update(RedLed);
    }
    // save the current state as the last state, for next time through the loop
    Encoderlast = Encodernow; 
  }
}
///////Ws2812_LSP//////
CRGB leds_lsp[NUM_LEDS];/// Representation of an RGB pixel (Red, Green, Blue)
Ws2812_LSP::Ws2812_LSP(int LedN, long on, long off) {
  _LedN = LedN;
  _on = on; //Pointer the on
	_off = off; //Pointer the off
  FastLED.addLeds<WS2812, DATA_PIN_SPL, GRB>(leds_lsp, NUM_LEDS);  // GRB ordering is typical
  FastLED.setBrightness( BRIGHTNESS );
  ledState = LOW; // ledState used to set the LED 
	previousMillis = 0;
}
//////

CRGB leds_rsp[NUM_LEDS];/// Representation of an RGB pixel (Red, Green, Blue)
Ws2812_RSP::Ws2812_RSP(int LedN, long on, long off) {
  _LedN = LedN;
  _on = on; //Pointer the on
	_off = off; //Pointer the off
  FastLED.addLeds<WS2812, DATA_PIN_SPR, GRB>(leds_rsp, NUM_LEDS);  // GRB ordering is typical
  FastLED.setBrightness( BRIGHTNESS );
  ledState = LOW; // ledState used to set the LED 
	previousMillis = 0;
}
///////Ws2812_RSP//////
void Ws2812_RSP::DRL()
{
switch (DRLColour) 
 {
  case 1:
  g = 255;
  b = 255;
  break;
  
  case 2:
  r = 255;
  g = 165;
  break;
  
  case 3:
  b = 255;
  break; 

  case 4:
  r = 255;
  g = 255;
  b = 255;
  break; 

  case 5:
  r = 255;
  break; 

  case 6:
  g = 255;
  break; 

  case 7:
  r = 255;
  b = 255;
  break;

  case 8:
  r = 255;
  g = 255;
  break;
}

  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds_rsp[i] = CRGB(r, g, b);
  }
    FastLED.show();  
}


void Ws2812_RSP::AllOff()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds_rsp[i] = CRGB(0, 0, 0);
  }
    FastLED.show();  
}

void Ws2812_RSP::RightBlinker()
{
        unsigned long currentMillis = millis();//Get the current "time" (actually the number of milliseconds since the program started)
  if (currentMillis - PreviousMillis >= BlinkerSpeed) { //Check whether the period has elapsed
    PreviousMillis = currentMillis; //IMPORTANT to save the start time of the current function.
     for (int i = 0; i < NUM_LEDS; i++)
  {
    leds_rsp[i] = CRGB::Green;
    FastLED.show();
  
  }
  } 


}

void Ws2812_RSP::Rainbow(){
   for (int i = 0; i < NUM_LEDS; ++i) {
    leds_rsp[i] = CHSV(hue + (i * 10), 255, 255);
  }
  //You can change the pattern speed here
  //     unsigned long currentMillis = millis();//Get the current "time" (actually the number of milliseconds since the program started)
  // if (currentMillis - PreviousMillis >= Next_Interval) { //Check whether the period has elapsed
  //   PreviousMillis = currentMillis; //IMPORTANT to save the start time of the current function.
  //  hue++;
  // } 
  EVERY_N_MILLISECONDS(15){
    hue++;
  }
  FastLED.show(); /// Update all our controllers with the current led colors
}
void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds_rsp[i].nscale8(250); } }
void Ws2812_RSP::Cylon(){
          unsigned long currentMillis = millis();//Get the current "time" (actually the number of milliseconds since the program started)
  if (currentMillis - PreviousMillis >= BlinkerOffDelay) { //Check whether the period has elapsed
    PreviousMillis = currentMillis; //IMPORTANT to save the start time of the current function.
   
RightBlinker();

  } 
  AllOff();
  // //   for (int i = 0; i < (NUM_LEDS); i++)
  // // {
  // //   leds_rsp[i] = CRGB(30, 0, 0);
  // //   leds_rsp[i-1] = CRGB(0, 0, 0);
  // //   leds_rsp[(NUM_LEDS-1)-i] = CRGB(30, 0, 0);
  // //   leds_rsp[(NUM_LEDS)-i] = CRGB(0, 0, 0);
  // //   FastLED.show();
  // //   delay (StartupSpeed);    
  // // }
  
  // for (int j = ((NUM_LEDS)-1); j >= 0; j--)
  // {
  //   leds_rsp[j] = CRGB(30, 0, 0);
  //   leds_rsp[(NUM_LEDS-1)+((NUM_LEDS)-j)] = CRGB(30, 0, 0);
  //   FastLED.show();
  //   delay (StartupSpeed);    
  // }

  // for (int j = ((NUM_LEDS)-1); j >= 0; j--)
  // {
  //   leds_rsp[j] = CRGB(255, 0, 0);
  //   leds_rsp[(NUM_LEDS/-1)+((NUM_LEDS)-j)] = CRGB(255, 0, 0);
  //   FastLED.show();
  //   delay (StartupSpeed);    
  // }

  // for (int j = 255; j >= 60; j--)
  // {  
  //   for (int i = 0; i < NUM_LEDS; i++)
  //   {
  //   leds_rsp[i] = CRGB(j, 0, 0);
  //   }
  //   FastLED.show();  
  //   delay (5);
  // }
  // Reverse();
  //   uint8_t val = random(10);
  // leds_rsp[val] = CHSV(0, 255, random(255));
  // FastLED.show();
  // leds_rsp[val] = CHSV(0, 255, 0);
  // delay(10);
  // static uint8_t hue = 0;
	// // Serial.print("x");
	// // First slide the led in one direction
	// for(int i = 0; i < NUM_LEDS; i++) {
	// 	// Set the i'th led to red 
	// 	leds_rsp[i] = CHSV(hue++, 255, 255);
	// 	// Show the leds
	// 	FastLED.show(); 
	// 	// now that we've shown the leds, reset the i'th led to black
	// 	leds_rsp[i] = CRGB::Black;
	// 	fadeall();
	// 	// Wait a little bit before we loop around and do it again
	// 	delay(50);
	// }
}
void Ws2812_RSP::Reset(){
   FastLED.clear (); /// reset or clear all our controllers with the current led colors
   //fill_solid( leds, NUM_LEDS, CRGB::Black);
   FastLED.show(); /// Update all our controllers with the current led colors
}
//////
ButtState::ButtState(int pin, Flasher& flasher) {
  // Use 'this->' to make the difference between the
  // 'pin' attribute of the class and the 
  // local variable 'pin' created from the parameter.
  _pin = pin; //Assign the pin local Bpin
  pinMode(_pin, INPUT); // Attaches the pinMode on ledPin    
  led = &flasher; //led contains the address of flasher
}

void ButtState::Update(){
  unsigned long currentMillis = millis();//Get the current "time" (actually the number of milliseconds since the program started)
  if (currentMillis - PreviousMillis >= Next_Interval) { //Check whether the period has elapsed
    PreviousMillis = currentMillis; //IMPORTANT to save the start time of the current function.
    buttonState = digitalRead(_pin); //Assign buttonState input from Bpin
    if (buttonState != lastButtonState){ // if the state has changed, increment the counter
      if (buttonState == HIGH) { // if the current state is HIGH then the button went from off to on:
      buttonPushCounter++; //Inreasing buttonPushCounter by 1
      } else {
                   // if the current state is LOW then the button went from on to off:
      }
    }
    // save the current state as the last state, for next time through the loop
    lastButtonState = buttonState;  
  } 
    /** Update Button State VALUE
    * @brief  Compare buttonPushCounter WITH MODULATION 2
    * @brief State of button press or not
    * @param if Update enum rover_Mode() = Rover_Mode::Active;
    * @param else Nothing Change
    * @brief State of button press or not
    * @brief rover_Mode() = Rover_Mode::Inactive; 
    */
  if (buttonPushCounter % 2 == 0) {
    led->Update(); // Update Led Button State
    rover_Mode() = Rover_Mode::Active;
  } 
  else {
    led->Off(); // Stop Led Button State
    rover_Mode() = Rover_Mode::Inactive;
  }  
}

Switch::Switch(int pin,int Number, Flasher& flasher) {
  // Use 'this->' to make the difference between the
  // 'pin' attribute of the class and the 
  // local variable 'pin' created from the parameter.
  _Number = Number;
  _pin = pin; //Assign the pin local Bpin
  pinMode(_pin, INPUT_PULLUP); // Attaches the pinMode on ledPin    
  led = &flasher; //led contains the address of flasher
}

void Switch::Update(){
  if(_Number == 1){
    unsigned long currentMillis = millis();//Get the current "time" (actually the number of milliseconds since the program started)
    if (currentMillis - PreviousMillis >= Next_Interval) { //Check whether the period has elapsed
    PreviousMillis = currentMillis; //IMPORTANT to save the start time of the current function.
    //Serial.println(digitalRead(Bpin));
      if (digitalRead(_pin) == LOW) {
        switch_Button() = Switch_Button::On_State;
        led->Update(); // Update Led Button State
        } else {
    // D7 pin is low due to pushbutton pressed
        switch_Button() = Switch_Button::Off_State;
        led->Off(); // Update Led Button State
      } 
    } 
  }
  else if(_Number == 2){
    unsigned long currentMillis = millis();//Get the current "time" (actually the number of milliseconds since the program started)
    if (currentMillis - PreviousMillis >= Next_Interval) { //Check whether the period has elapsed
      PreviousMillis = currentMillis; //IMPORTANT to save the start time of the current function.
    //Serial.println(digitalRead(Bpin));
    if (digitalRead(_pin) == LOW) {
      switch_Button_Servo() = Switch_Button_Servo::On_State_Servo;
      led->Update(); // Update Led Button State
    } 
    else {
    // D7 pin is low due to pushbutton pressed
      switch_Button_Servo() = Switch_Button_Servo::Off_State_Servo;
      led->Off(); // Update Led Button State
    } 
    } 
  }
}

