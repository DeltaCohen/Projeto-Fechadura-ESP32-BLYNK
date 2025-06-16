#define BLYNK_TEMPLATE_ID "SEUTEMPLATEIDAQUI"
#define BLYNK_TEMPLATE_NAME "SEUTEMPLATENOMEAQUI"
#define BLYNK_AUTH_TOKEN "SEUTOKENAQUI"  // Pegue no app ou console.blynk.io

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

BlynkTimer timer;

int toggleState_1 = 1;
int pushButton1State = HIGH;

int toggleState_2 = 1;
int pushButton2State = HIGH;

int wifiFlag = 0;

#define WIFI_SSID "REDEWIFIAQUI"         // Coloque o nome da sua rede Wi-Fi
#define WIFI_PASS "SENHAWIFIAQUI"            // Coloque a senha da sua rede

#define RELAY_PIN_1      26             // D26
#define RELAY_PIN_2      27             // D27
#define WIFI_LED         25             // D25

#define PUSH_BUTTON_1    32             // D32
#define PUSH_BUTTON_2    33             // D33

#define VPIN_BUTTON_1    V1 
#define VPIN_BUTTON_2    V2

void relayOnOff(int relay) {
  switch(relay){
    case 1: 
      if(toggleState_1 == 0){
        digitalWrite(RELAY_PIN_1, HIGH); // turn on relay 1
        toggleState_1 = 1;
      } else {
        digitalWrite(RELAY_PIN_1, LOW); // turn off relay 1
        toggleState_1 = 0;
      }
      delay(200);
      break;

    case 2: 
      if(toggleState_2 == 0){
        digitalWrite(RELAY_PIN_2, HIGH); // turn on relay 2
        toggleState_2 = 1;
      } else {
        digitalWrite(RELAY_PIN_2, LOW); // turn off relay 2
        toggleState_2 = 0;
      }
      delay(200);
      break;

    default: break;      
  } 
}

BLYNK_CONNECTED() {
  Blynk.syncVirtual(VPIN_BUTTON_1);
  Blynk.syncVirtual(VPIN_BUTTON_2);
}

BLYNK_WRITE(VPIN_BUTTON_1) {
  toggleState_1 = param.asInt();
  digitalWrite(RELAY_PIN_1, toggleState_1);
}

BLYNK_WRITE(VPIN_BUTTON_2) {
  toggleState_2 = param.asInt();
  digitalWrite(RELAY_PIN_2, toggleState_2);
}

void with_internet(){
  if (digitalRead(PUSH_BUTTON_1) == LOW) {
    relayOnOff(1);
    Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
  }
  if (digitalRead(PUSH_BUTTON_2) == LOW) {
    relayOnOff(2);
    Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);
  }
}

void without_internet(){
  if (digitalRead(PUSH_BUTTON_1) == LOW) {
    relayOnOff(1);
  }
  if (digitalRead(PUSH_BUTTON_2) == LOW) {
    relayOnOff(2);
  }
}

void checkBlynkStatus() {
  bool isconnected = Blynk.connected();
  if (!isconnected) {
    wifiFlag = 1;
    digitalWrite(WIFI_LED, LOW);
  } else {
    wifiFlag = 0;
    digitalWrite(WIFI_LED, HIGH);
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(RELAY_PIN_1, OUTPUT);
  pinMode(PUSH_BUTTON_1, INPUT_PULLUP);
  digitalWrite(RELAY_PIN_1, toggleState_1);

  pinMode(RELAY_PIN_2, OUTPUT);
  pinMode(PUSH_BUTTON_2, INPUT_PULLUP);
  digitalWrite(RELAY_PIN_2, toggleState_2);

  pinMode(WIFI_LED, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  Blynk.config(BLYNK_AUTH_TOKEN);  // agora com Blynk IoT
  timer.setInterval(3000L, checkBlynkStatus);
}

void loop() {  
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Not Connected");
  } else {
    Serial.println("Connected");
    Blynk.run();
  }

  timer.run();

  if (wifiFlag == 0)
    with_internet();
  else
    without_internet();
}
