// Code generated by Arduino IoT Cloud, DO NOT EDIT.

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char DEVICE_LOGIN_NAME[]  = "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx";

const char SSID[]               = SECRET_SSID;    // Network SSID (name)
const char PASS[]               = SECRET_OPTIONAL_PASS;    // Network password (use for WPA, or use as key for WEP)
const char DEVICE_KEY[]  = SECRET_DEVICE_KEY;    // Secret device password

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
