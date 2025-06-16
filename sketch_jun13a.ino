#define BLYNK_TEMPLATE_ID "SEUTEMPLATEIDAQUI"
#define BLYNK_TEMPLATE_NAME "SEUTEMPLATENOMEAQUI"
#define BLYNK_AUTH_TOKEN "SEUTOKENAQUI"  // Pegue no console Blynk ou no app

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

BlynkTimer timer;

#define WIFI_SSID "REDEWIFIAQUI"         // Nome da sua rede Wi-Fi
#define WIFI_PASS "SENHAWIFIAQUI"        // Senha do Wi-Fi

#define RELAY_PIN_1   26                 // Relé 1 - GPIO 26
#define RELAY_PIN_2   27                 // Relé 2 - GPIO 27
#define WIFI_LED      25                 // LED de status WiFi - GPIO 25
#define PUSH_BUTTON_1 32                 // Botão físico 1 - GPIO 32
#define PUSH_BUTTON_2 33                 // Botão físico 2 - GPIO 33

#define VPIN_BUTTON_1 V1
#define VPIN_BUTTON_2 V2

int toggleState_1 = 1;
int toggleState_2 = 1;

int pushButton1State = HIGH;
int pushButton2State = HIGH;

int wifiFlag = 0;

void alternarReles(int rele) {
  if (rele == 1) {
    if (toggleState_1 == 0) {
      digitalWrite(RELAY_PIN_1, HIGH);
      toggleState_1 = 1;
    } else {
      digitalWrite(RELAY_PIN_1, LOW);
      toggleState_1 = 0;
    }
    delay(200);
  }

  if (rele == 2) {
    if (toggleState_2 == 0) {
      digitalWrite(RELAY_PIN_2, HIGH);
      toggleState_2 = 1;
    } else {
      digitalWrite(RELAY_PIN_2, LOW);
      toggleState_2 = 0;
    }
    delay(200);
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

void modoOnline() {
  if (digitalRead(PUSH_BUTTON_1) == LOW) {
    alternarReles(1);
    Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
  }

  if (digitalRead(PUSH_BUTTON_2) == LOW) {
    alternarReles(2);
    Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);
  }
}

void modoOffline() {
  if (digitalRead(PUSH_BUTTON_1) == LOW) {
    alternarReles(1);
  }

  if (digitalRead(PUSH_BUTTON_2) == LOW) {
    alternarReles(2);
  }
}

void verificarStatusWiFi() {
  if (Blynk.connected()) {
    wifiFlag = 0;
    digitalWrite(WIFI_LED, HIGH);
  } else {
    wifiFlag = 1;
    digitalWrite(WIFI_LED, LOW);
  }
}

void inicializarPinos() {
  pinMode(RELAY_PIN_1, OUTPUT);
  digitalWrite(RELAY_PIN_1, toggleState_1);

  pinMode(RELAY_PIN_2, OUTPUT);
  digitalWrite(RELAY_PIN_2, toggleState_2);

  pinMode(PUSH_BUTTON_1, INPUT_PULLUP);
  pinMode(PUSH_BUTTON_2, INPUT_PULLUP);

  pinMode(WIFI_LED, OUTPUT);
}

void setup() {
  Serial.begin(9600);

  inicializarPinos();

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Blynk.config(BLYNK_AUTH_TOKEN);

  timer.setInterval(3000L, verificarStatusWiFi);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi Conectado");
    Blynk.run();
  } else {
    Serial.println("WiFi Desconectado");
  }

  timer.run();

  if (wifiFlag == 0) {
    modoOnline();
  } else {
    modoOffline();
  }
}
