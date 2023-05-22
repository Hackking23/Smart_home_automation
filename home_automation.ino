// This code should be used only when you are using toogle switches. In case of momentry button Output may not be as desired.
#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
const char DEVICE_LOGIN_NAME[]  = "DEVICE_ID"; //Get created automatically when you create things in Arduino Iot cloud
const char SSID[]               ="Wifi_Name";    // Network SSID (name)
const char PASS[]               ="Wife_Password";    // Network password (use for WPA, or use as key for WEP)
const char DEVICE_KEY[]  ="Device_secret _key";    // Secret device password

void onBulbChange();
void onFanChange();
void onLedTubeChange();
void onTubelightChange();

CloudSwitch bulb;
CloudSwitch fan;
CloudSwitch led_tube;
CloudSwitch tubelight;

void initProperties(){
  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(bulb, READWRITE, ON_CHANGE, onBulbChange);
  ArduinoCloud.addProperty(fan, READWRITE, ON_CHANGE, onFanChange);
  ArduinoCloud.addProperty(led_tube, READWRITE, ON_CHANGE, onLedTubeChange);
  ArduinoCloud.addProperty(tubelight, READWRITE, ON_CHANGE, onTubelightChange);
}
WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);

// define the GPIO connected with Relays and switches
#define RelayPin1 23  //D23
#define RelayPin2 22  //D22
#define RelayPin3 21  //D21
#define RelayPin4 19  //D19

#define SwitchPin1 13  //D13
#define SwitchPin2 12  //D13
#define SwitchPin3 14  //D13
#define SwitchPin4 27  //D13

#define wifiLed    2   //D2

int toggleState_1 = 0; //Define integer to remember the toggle state for relay 1
int toggleState_2 = 0; //Define integer to remember the toggle state for relay 2
int toggleState_3 = 0; //Define integer to remember the toggle state for relay 3
int toggleState_4 = 0; //Define integer to remember the toggle state for relay 4

int buttonState1 = HIGH;  // State of button 1
int buttonState2 = HIGH;  // State of button 2
int buttonState3 = HIGH;  // State of button 3
int buttonState4 = HIGH;  // State of button 4

void ispress() {
  //Check if switched is turned On
  if (digitalRead(SwitchPin1) == LOW && buttonState1 == HIGH) {
    buttonState1 = LOW;
    digitalWrite(RelayPin1, LOW);  
    toggleState_1 =1;
    tubelight = toggleState_1;
    Serial.println("tubelight ON");
    }
    
  if (digitalRead(SwitchPin2) == LOW && buttonState2 == HIGH) {
    buttonState2 = LOW;
    digitalWrite(RelayPin2, LOW);  
    toggleState_2 =1;
    led_tube = toggleState_2;
    Serial.println("led_tube ON");
    }
    
  if (digitalRead(SwitchPin3) == LOW && buttonState3 == HIGH) {
    buttonState3 = LOW;
    digitalWrite(RelayPin3, LOW);  
    toggleState_3 =1;
    fan = toggleState_3;
    Serial.println("fan ON");
    }
    
  if (digitalRead(SwitchPin4) == LOW && buttonState4 == HIGH) {
    buttonState4 = LOW;
    digitalWrite(RelayPin4, LOW);
    toggleState_4 =1;
    bulb = toggleState_4;
    Serial.println("bulb ON");
    }  
    
}
void isrelease() {
  if (digitalRead(SwitchPin1) == HIGH && buttonState1 == LOW) {
    buttonState1 = HIGH;
    digitalWrite(RelayPin1, HIGH);  // Toggle relay state
    toggleState_1 =1;
    tubelight = toggleState_1;
    Serial.println("tubelight OFF");
    }
    
  if (digitalRead(SwitchPin2) == HIGH && buttonState2 == LOW) {
    buttonState2 = HIGH;
    digitalWrite(RelayPin2, HIGH);  // Toggle relay state
    toggleState_2 =1;
    led_tube = toggleState_2;
    Serial.println("led_tube OFF");
    }
    
  if (digitalRead(SwitchPin3) == HIGH && buttonState3 == LOW) {
    buttonState3 = HIGH;
    digitalWrite(RelayPin3, HIGH);  // Toggle relay state
    toggleState_3 =1;
    fan = toggleState_3;
    Serial.println("fan OFF");
    }
    
  if (digitalRead(SwitchPin4) == HIGH && buttonState4 == LOW) {
    buttonState4 = HIGH;
    digitalWrite(RelayPin4, HIGH);  // Toggle relay state
    toggleState_4 =1;
    bulb = toggleState_4;
    Serial.println("bulb OFF");
    }
    
}

void doThisOnConnect(){
  Serial.println("Board successfully connected to Arduino IoT Cloud");
  digitalWrite(wifiLed, HIGH); //Turn on WiFi LED
  }
  
void doThisOnSync(){
  Serial.println("Thing Properties synchronised");
  }
  
void doThisOnDisconnect(){
  Serial.println("Board disconnected from Arduino IoT Cloud");
  digitalWrite(wifiLed, LOW); //Turn off WiFi LED
  }
  
void setup() {
  
  Serial.begin(9600);
  delay(1500);
  
  initProperties();
  
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

  //Intially all relay pin should turn off.
  digitalWrite(RelayPin1, HIGH);
  digitalWrite(RelayPin2, HIGH);
  digitalWrite(RelayPin3, HIGH);
  digitalWrite(RelayPin4, HIGH);
  
}
void loop() {
  
  ArduinoCloud.update(); //For synchronizing with updates through Alexaor Arduino IoT Cloud
  
  isrelease();           //For turning on lights if switched press.
  
  ispress();             //For turning off lights if switched press
}

void onTubelightChange(){
  if (tubelight == 1)
  {
    digitalWrite(RelayPin1, LOW);
    Serial.println("tubelight ON");
    toggleState_1 = 1;
  }
  else
  {
    digitalWrite(RelayPin1, HIGH);
    Serial.println("tubelight OFF");
    toggleState_1 = 0;
  }
}

void onLedTubeChange(){
  if (led_tube == 1)
  {
    digitalWrite(RelayPin2, LOW);
    Serial.println("led_tube ON");
    toggleState_2 = 1;
  }
  else
  {
    digitalWrite(RelayPin2, HIGH);
    Serial.println("led_tube OFF");
    toggleState_2 = 0;
  }
}

void onFanChange(){
  if (fan == 1)
  {
    digitalWrite(RelayPin3, LOW);
    Serial.println("fan ON");
    toggleState_3 = 1;
  }
  else
  {
    digitalWrite(RelayPin3, HIGH);
    Serial.println("fan OFF");
    toggleState_3 = 0;
  }
}

void onBulbChange(){
  if (bulb == 1)
  {
    digitalWrite(RelayPin4, LOW);
    Serial.println("bulb ON");
    toggleState_4 = 1;
  }
  else
  {
    digitalWrite(RelayPin4, HIGH);
    Serial.println("bulb OFF");
    toggleState_4 = 0;
  }
}
