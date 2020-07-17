#include <Arduino.h>

#define BUILD_NUMBER_CTR "v1.0"
#define BUILD_DATE "JULY_2020"

//***IO DEFINED************************************************************************

//BUTTONS
#define BTN_UP			A0	// MIRROR UP BUTTON
#define BTN_DOWN		A1	// MIRROR DOWN BUTTON
#define BTN_LEFT		A2	// MIRROR LEFT BUTTON
#define BTN_RIGHT		A3	// MIRROR RIGHT BUTTON

//SWITCHES
#define SIDE_SW    		A4  // MIRROR SIDE SELECTOR SWITCH

//RELAYS
#define RELAY_LEFT_UP		5	// LEFT MIRROR UP RELAY
#define RELAY_LEFT_DOWN		6	// LEFT MIRROR DOWN RELAY
#define RELAY_LEFT_LEFT		7	// LEFT MIRROR LEFT RELAY
#define RELAY_LEFT_RIGHT	8	// LEFT MIRROR RIGHT RELAY
#define RELAY_RIGHT_UP		9	// RIGHT MIRROR UP RELAY
#define RELAY_RIGHT_DOWN	10	// RIGHT MIRROR DOWN RELAY
#define RELAY_RIGHT_LEFT	11	// RIGHT MIRROR LEFT RELAY
#define RELAY_RIGHT_RIGHT	12	// RIGHT MIRROR RIGHT RELAY


//***INPUTS*********************************************************************

#define BTN_UP_INIT() 		 	pinMode(BTN_UP, INPUT_PULLUP)
#define BTN_DOWN_INIT() 		pinMode(BTN_DOWN, INPUT_PULLUP)
#define BTN_LEFT_INIT() 		pinMode(BTN_LEFT, INPUT_PULLUP)
#define BTN_RIGHT_INIT() 		pinMode(BTN_RIGHT, INPUT_PULLUP)

#define SIDE_SW_INIT() 		 	pinMode(SIDE_SW, INPUT_PULLUP)

//***OUTPUTS********************************************************************

//RELAYS ARE LOGIC LEVEL HIGH
//LEFT SIDE UP RELAY
#define RELAY_LU_INIT()      	pinMode(RELAY_LEFT_UP,OUTPUT)
#define RELAY_LU_START()	 	digitalWrite(RELAY_LEFT_UP,HIGH)
#define RELAY_LU_ON()       	digitalWrite(RELAY_LEFT_UP,LOW) //ACTIVE when LOW
#define RELAY_LU_OFF()      	digitalWrite(RELAY_LEFT_UP,HIGH) //ACTIVE when LOW

//LEFT SIDE DOWN RELAY
#define RELAY_LD_INIT()      	pinMode(RELAY_LEFT_DOWN,OUTPUT)
#define RELAY_LD_START()	 	digitalWrite(RELAY_LEFT_DOWN,HIGH)
#define RELAY_LD_ON()       	digitalWrite(RELAY_LEFT_DOWN,LOW) //ACTIVE when LOW
#define RELAY_LD_OFF()      	digitalWrite(RELAY_LEFT_DOWN,HIGH) //ACTIVE when LOW

//LEFT SIDE LEFT RELAY
#define RELAY_LL_INIT()      	pinMode(RELAY_LEFT_LEFT,OUTPUT)
#define RELAY_LL_START()	 	digitalWrite(RELAY_LEFT_LEFT,HIGH)
#define RELAY_LL_ON()       	digitalWrite(RELAY_LEFT_LEFT,LOW) //ACTIVE when LOW
#define RELAY_LL_OFF()      	digitalWrite(RELAY_LEFT_LEFT,HIGH) //ACTIVE when LOW

//LEFT SIDE RIGHT RELAY
#define RELAY_LR_INIT()      	pinMode(RELAY_LEFT_RIGHT,OUTPUT)
#define RELAY_LR_START()	 	digitalWrite(RELAY_LEFT_RIGHT,HIGH)
#define RELAY_LR_ON()       	digitalWrite(RELAY_LEFT_RIGHT,LOW) //ACTIVE when LOW
#define RELAY_LR_OFF()      	digitalWrite(RELAY_LEFT_RIGHT,HIGH) //ACTIVE when LOW

//RIGHT SIDE UP RELAY
#define RELAY_RU_INIT()      	pinMode(RELAY_RIGHT_UP,OUTPUT)
#define RELAY_RU_START()	 	digitalWrite(RELAY_RIGHT_UP,HIGH)
#define RELAY_RU_ON()       	digitalWrite(RELAY_RIGHT_UP,LOW) //ACTIVE when LOW
#define RELAY_RU_OFF()      	digitalWrite(RELAY_RIGHT_UP,HIGH) //ACTIVE when LOW

//RIGHT SIDE DOWN RELAY
#define RELAY_RD_INIT()      	pinMode(RELAY_RIGHT_DOWN,OUTPUT)
#define RELAY_RD_START()	 	digitalWrite(RELAY_RIGHT_DOWN,HIGH)
#define RELAY_RD_ON()       	digitalWrite(RELAY_RIGHT_DOWN,LOW) //ACTIVE when LOW
#define RELAY_RD_OFF()      	digitalWrite(RELAY_RIGHT_DOWN,HIGH) //ACTIVE when LOW

//RIGHT SIDE LEFT RELAY
#define RELAY_RL_INIT()      	pinMode(RELAY_RIGHT_LEFT,OUTPUT)
#define RELAY_RL_START()	 	digitalWrite(RELAY_RIGHT_LEFT,HIGH)
#define RELAY_RL_ON()       	digitalWrite(RELAY_RIGHT_LEFT,LOW) //ACTIVE when LOW
#define RELAY_RL_OFF()      	digitalWrite(RELAY_RIGHT_LEFT,HIGH) //ACTIVE when LOW

//RIGHT SIDE UP RELAY
#define RELAY_RR_INIT()      	pinMode(RELAY_RIGHT_RIGHT,OUTPUT)
#define RELAY_RR_START()	 	digitalWrite(RELAY_RIGHT_RIGHT,HIGH)
#define RELAY_RR_ON()       	digitalWrite(RELAY_RIGHT_RIGHT,LOW) //ACTIVE when LOW
#define RELAY_RR_OFF()      	digitalWrite(RELAY_RIGHT_RIGHT,HIGH) //ACTIVE when LOW


uint8_t Switch_State = 0;         // current state of the SIDE SWITCH
uint8_t lastSwitchState = 0;      // previous state of the SIDE SWITCH
uint8_t BTNU_State = 0;           // current state of the UP BUTTON
uint8_t lastBTNUState = 0;        // previous state of the UP BUTTON
uint8_t BTND_State = 0;           // current state of the DOWN BUTTON
uint8_t lastBTNDState = 0;        // previous state of the DOWN BUTTON
uint8_t BTNL_State = 0;           // current state of the LEFT BUTTON
uint8_t lastBTNLState = 0;        // previous state of the LEFT BUTTON
uint8_t BTNR_State = 0;           // current state of the RIGHT BUTTON
uint8_t lastBTNRState = 0;        // previous state of the RIGHT BUTTON

#define DEBOUNCE_INTERVAL	200	// Button Debounce

typedef struct TIMER_HANDLER{
  uint32_t millis = 0;
  uint32_t tSaved = 0;
  uint8_t run = false; // run immediately
}timereached_t;

//Individual Timers
	timereached_t tDebounce;


//Function Prototypes
uint8_t TimeReached(TIMER_HANDLER* tSaved, uint32_t ElapsedTime);
void SWITCH_Check();
void UP_Check();
void DOWN_Check();
void LEFT_Check();
void RIGHT_Check();


void setup() {
	Serial.begin(9600);
	BTN_UP_INIT();
  	BTN_DOWN_INIT();
  	BTN_LEFT_INIT();
  	BTN_RIGHT_INIT();
  	SIDE_SW_INIT();
	
	RELAY_RU_INIT(); RELAY_RU_START();
	RELAY_RD_INIT(); RELAY_RD_START();
	RELAY_RL_INIT(); RELAY_RL_START();
	RELAY_RR_INIT(); RELAY_RR_START();
	RELAY_LU_INIT(); RELAY_LU_START();
	RELAY_LD_INIT(); RELAY_LD_START();
	RELAY_LL_INIT(); RELAY_LL_START();
	RELAY_LR_INIT(); RELAY_LR_START();


}

void loop() {
	SWITCH_Check();
  	UP_Check();
  	DOWN_Check();
  	LEFT_Check();
  	RIGHT_Check();


}

void SWITCH_Check(){
	// read the SIDE SELECTOR SWITCH input pin:
  	Switch_State = digitalRead(SIDE_SW);
  	// compare the switch State to its previous state
  	if (Switch_State != lastSwitchState && TimeReached(&tDebounce,DEBOUNCE_INTERVAL)) {
      // save the current state as the last state, for next time through the loop
      lastSwitchState = Switch_State;
	  Serial.println ("Switch state changed");
		}
	
}

void UP_Check(){
	// read the pushbutton input pin for the UP BUTTON:
  	BTNU_State = digitalRead(BTN_UP);
  	// compare the buttonState to its previous state
  	if (BTNU_State != lastBTNUState && TimeReached(&tDebounce,DEBOUNCE_INTERVAL)) {
      // save the current state as the last state, for next time through the loop
      lastBTNUState = BTNU_State;
		}
	else if (Switch_State == LOW && BTNU_State == LOW){ //if the selector switch is to the LEFT (logic level LOW) activate left UP relay
		RELAY_LU_ON();
		Serial.println ("Left UP Selected");
		}
	else if (Switch_State == HIGH && BTNU_State == LOW){ //if the selector switch is to the RIGHT (logic level HIGH) activate right UP relay
		RELAY_RU_ON();
		Serial.println ("Right UP Selected");
		}
	else {
		RELAY_RU_OFF(); //Make sure the relay is off if not commanded
		RELAY_LU_OFF(); //Make sure the relay is off if not commanded
	}
}

void DOWN_Check(){
	// read the pushbutton input pin for the DOWN button:
  	BTND_State = digitalRead(BTN_DOWN);
  	// compare the buttonState to its previous state
  	if (BTND_State != lastBTNDState && TimeReached(&tDebounce,DEBOUNCE_INTERVAL)) {
      // save the current state as the last state, for next time through the loop
      lastBTNDState = BTND_State;
		}
	else if (Switch_State == LOW && BTND_State == LOW){ //if the selector switch is to the LEFT (logic level LOW) activate left DOWN relay
		RELAY_LD_ON();
		Serial.println ("Left DOWN Selected");
		}
	else if (Switch_State == HIGH && BTND_State == LOW){ //if the selector switch is to the RIGHT (logic level HIGH) activate right DOWN relay
		RELAY_RD_ON();
		Serial.println ("Right DOWN Selected");
		}
	else {
		RELAY_RD_OFF(); //Make sure the relay is off if not commanded
		RELAY_LD_OFF(); //Make sure the relay is off if not commanded
	}
}

void LEFT_Check(){
	// read the pushbutton input pin for the LEFT button:
  	BTNL_State = digitalRead(BTN_LEFT);
  	// compare the buttonState to its previous state
  	if (BTNL_State != lastBTNLState && TimeReached(&tDebounce,DEBOUNCE_INTERVAL)) {
      // save the current state as the last state, for next time through the loop
      lastBTNLState = BTNL_State;
		}
	else if (Switch_State == LOW && BTNL_State == LOW){ //if the selector switch is to the LEFT (logic level LOW) activate left LEFT relay
		RELAY_LL_ON();
		Serial.println ("Left LEFT Selected");
		}
	else if (Switch_State == HIGH && BTNL_State == LOW){ //if the selector switch is to the RIGHT (logic level HIGH) activate right LEFT relay
		RELAY_RL_ON();
		Serial.println ("Right LEFT Selected");
		}
	else {
		RELAY_RL_OFF(); //Make sure the relay is off if not commanded
		RELAY_LL_OFF(); //Make sure the relay is off if not commanded
	}
}

void RIGHT_Check(){
	// read the pushbutton input pin for the RIGHT button:
  	BTNR_State = digitalRead(BTN_RIGHT);
  	// compare the buttonState to its previous state
  	if (BTNR_State != lastBTNRState && TimeReached(&tDebounce,DEBOUNCE_INTERVAL)) {
      // save the current state as the last state, for next time through the loop
      lastBTNRState = BTNR_State;
		}
	else if (Switch_State == LOW && BTNR_State == LOW){ //if the selector switch is to the LEFT (logic level LOW) activate left RIGHT relay
		RELAY_LR_ON();
		Serial.println ("Left RIGHT Selected");
		}
	else if (Switch_State == HIGH && BTNR_State == LOW){ //if the selector switch is to the RIGHT (logic level HIGH) activate right RIGHT relay
		RELAY_RR_ON();
		Serial.println ("Right RIGHT Selected");
		}
	else {
		RELAY_RR_OFF(); //Make sure the relay is off if not commanded
		RELAY_LR_OFF(); //Make sure the relay is off if not commanded
	}
}

// Time elapsed function USED FOR DEBOUNCE
uint8_t TimeReached(TIMER_HANDLER* tSaved, uint32_t ElapsedTime){
  if(
    (abs(millis()-tSaved->millis)>=ElapsedTime)
    ||(tSaved->run == true)    
    ){ 
      tSaved->millis=millis();
      tSaved->run = false;
    return true;
  }
  return false;
}