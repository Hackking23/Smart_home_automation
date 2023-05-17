/* 
  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  CloudSwitch bulb;
  CloudSwitch fan;
  CloudSwitch led_tube;
  CloudSwitch tubelight;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"
//#include <IRremote.h>      //uncomment when contolling with IR remote too
//#define IR_RECV_PIN 35     //D35 pin connected with IR Receiver IC

// define the GPIO connected with Relays and switches
#define RelayPin1 23  //D23
#define RelayPin2 22  //D22
#define RelayPin3 21  //D21
#define RelayPin4 19  //D19

#define SwitchPin1 13  //D13
#define SwitchPin2 12  //D12
#define SwitchPin3 14  //D14
#define SwitchPin4 27  //D27

#define wifiLed    2   //D2

int toggleState_1 = 0; //Define integer to remember the toggle state for relay 1
int toggleState_2 = 0; //Define integer to remember the toggle state for relay 2
int toggleState_3 = 0; //Define integer to remember the toggle state for relay 3
int toggleState_4 = 0; //Define integer to remember the toggle state for relay 4

//comment out below code if you want to add dht sensor to read the temperature of your room
/*void readSensor(){
     
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  else {
    humidity1 = h;
    temperature = t;
   // Serial.println(tempareture);
  }  
}*/

/*void sendSensor()
{
  readSensor();
}*/

//Don't forgot to update the hex code according to your IR remote.

//IRrecv irrecv(IR_RECV_PIN);
//decode_results results;
/*void ir_remote_control(){
  if (irrecv.decode(&results)) {
    
      switch(results.value){
          case 0x80BF49B6:  relayOnOff(1); switch1 = toggleState_1; break; //update the HEX-code
          case 0x80BFC936:  relayOnOff(2); switch2 = toggleState_2; break; //update the HEX-code
          case 0x80BF33CC:  relayOnOff(3); switch3 = toggleState_3; break; //update the HEX-code
          case 0x80BF718E:  relayOnOff(4); switch4 = toggleState_4; break; //update the HEX-code
          default : break;         
        }   
        //Serial.println(results.value, HEX);    
        irrecv.resume();   
  } 
}*/


void relayOnOff(int relay) {

  switch (relay) {
    case 1:
      if (toggleState_1 == 0) {
        digitalWrite(RelayPin1, LOW); // turn on relay 1
        toggleState_1 = 1;
        Serial.println("tubelight ON");
      }
      else {
        digitalWrite(RelayPin1, HIGH); // turn off relay 1
        toggleState_1 = 0;
        Serial.println("tubelight OFF");
      }
      delay(100);
      break;
    case 2:
      if (toggleState_2 == 0) {
        digitalWrite(RelayPin2, LOW); // turn on relay 2
        toggleState_2 = 1;
        Serial.println("led_tube ON");
      }
      else {
        digitalWrite(RelayPin2, HIGH); // turn off relay 2
        toggleState_2 = 0;
        Serial.println("led_tube OFF");
      }
      delay(100);
      break;
    case 3:
      if (toggleState_3 == 0) {
        digitalWrite(RelayPin3, LOW); // turn on relay 3
        toggleState_3 = 1;
        Serial.println("fan ON");
      } else {
        digitalWrite(RelayPin3, HIGH); // turn off relay 3
        toggleState_3 = 0;
        Serial.println("fan OFF");
      }
      delay(100);
      break;
    case 4:
      if (toggleState_4 == 0) {
        digitalWrite(RelayPin4, LOW); // turn on relay 4
        toggleState_4 = 1;
        Serial.println("bulb ON");
      }
      else {
        digitalWrite(RelayPin4, HIGH); // turn off relay 4
        toggleState_4 = 0;
        Serial.println("bulb OFF");
      }
      delay(100);
      break;
    default : break;
  }
}

void manual_control() {
  //Manual Switch Control
  if (digitalRead(SwitchPin1) == LOW) {
    delay(200);
    relayOnOff(1);
    tubelight = toggleState_1;
  }
  else if (digitalRead(SwitchPin2) == LOW) {
    delay(200);
    relayOnOff(2);
    led_tube = toggleState_2;
  }
  else if (digitalRead(SwitchPin3) == LOW) {
    delay(200);
    relayOnOff(3);
    fan = toggleState_3;
  }
  else if (digitalRead(SwitchPin4) == LOW) {
    delay(200);
    relayOnOff(4);
    bulb = toggleState_4;
  }
}

void doThisOnConnect(){
  /* add your custom code here */
  Serial.println("Board successfully connected to Arduino IoT Cloud");
  digitalWrite(wifiLed, HIGH); //Turn on WiFi LED
}
void doThisOnSync(){
  /* add your custom code here */
  Serial.println("Thing Properties synchronised");
}

void doThisOnDisconnect(){
  /* add your custom code here */
  Serial.println("Board disconnected from Arduino IoT Cloud");
  digitalWrite(wifiLed, LOW); //Turn off WiFi LED
}

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);

  // Defined in thingProperties.h
  initProperties();
  
  //irrecv.enableIRIn(); // Start the receiver
  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  ArduinoCloud.addCallback(ArduinoIoTCloudEvent::CONNECT, doThisOnConnect);
  ArduinoCloud.addCallback(ArduinoIoTCloudEvent::SYNC, doThisOnSync);
  ArduinoCloud.addCallback(ArduinoIoTCloudEvent::DISCONNECT, doThisOnDisconnect);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(RelayPin4, OUTPUT);

  pinMode(wifiLed, OUTPUT);

  pinMode(SwitchPin1, INPUT_PULLUP);
  pinMode(SwitchPin2, INPUT_PULLUP);
  pinMode(SwitchPin3, INPUT_PULLUP);
  pinMode(SwitchPin4, INPUT_PULLUP);

  //During Starting all Relays should TURN OFF
  digitalWrite(RelayPin1, HIGH);
  digitalWrite(RelayPin2, HIGH);
  digitalWrite(RelayPin3, HIGH);
  digitalWrite(RelayPin4, HIGH);
}

void loop() {

  ArduinoCloud.update();
  
  manual_control();     //Manual Control
  //ir_remote_control();  //IR Remote Control
}


/*
  Since led_tube is READ_WRITE variable, onled_tubeChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onLedTubeChange()  {
  // Add your code here to act upon led_tube change
  if (led_tube == 1)
  {
    digitalWrite(RelayPin2, HIGH);
    Serial.println("led_tube ON");
    toggleState_2 = 0;
  }
  else
  {
    digitalWrite(RelayPin2, LOW);
    Serial.println("led_tube OFF");
    toggleState_2 = 1;
  }
}

/*
  Since fan is READ_WRITE variable, onfanChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onFanChange()  {
  // Add your code here to act upon fan change
  if (fan == 1)
  {
    digitalWrite(RelayPin3, HIGH);
    Serial.println("fan ON");
    toggleState_3 = 0;
  }
  else
  {
    digitalWrite(RelayPin3, LOW);
    Serial.println("fan OFF");
    toggleState_3 = 1;
  }
}

/*
  Since bulb is READ_WRITE variable, onbulbChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onBulbChange()  {
  // Add your code here to act upon bulb change
  if (bulb == 1)
  {
    digitalWrite(RelayPin4, HIGH);
    Serial.println("bulb ON");
    toggleState_4 = 0;
  }
  else
  {
    digitalWrite(RelayPin4, LOW);
    Serial.println("bulb OFF");
    toggleState_4 = 1;
  }
}



/*
  Since Tubelight is READ_WRITE variable, onTubelightChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onTubelightChange()  {
  // Add your code here to act upon Tubelight change
  if (tubelight == 1)
  {
    digitalWrite(RelayPin1, HIGH);
    Serial.println("tubelight ON");
    toggleState_1 = 0;
  }
  else
  {
    digitalWrite(RelayPin1, LOW);
    Serial.println("tubelight OFF");
    toggleState_1 = 1;
  }
}
