# Projeto ESP32 + Blynk IoT: Controle de Relés Local e Remoto
Projeto desenvolvido em C++ para Arduino IDE, utilizando o ESP32 com integração ao Blynk IoT.

• **Função Principal**
Controle de 2 relés de forma local (botões físicos) e remota (App Blynk), com indicação de conexão Wi-Fi via LED.

 **Online:** Controle via App Blynk e botões físicos

**Offline:** Controle apenas pelos botões físicos

• **Hardware Utilizado**
1x ESP32
1x 2 Relés (pinos D26 e D27)
1x 2 Botões físicos (pinos D32 e D33)
1x LED de status Wi-Fi (pino D25)

• **Bibliotecas Necessárias**
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

• **Principais Funções do Código**
Função	Descrição
relayOnOff()	Liga/Desliga os relés
with_internet()	Lê botões e atualiza o App
without_internet()	Lê botões (modo offline)
checkBlynkStatus()	Verifica status da conexão
BLYNK_WRITE() / BLYNK_CONNECTED()	Comunicação com o Blynk

• **Aplicações**
-> Automação residencial
-> Controle IoT de dispositivos elétricos
-> Projetos que precisam funcionar online e offline
