# Projeto ESP32 + Blynk IoT: Controle de Relés Local e Remoto
Projeto desenvolvido em C++ para Arduino IDE, utilizando o ESP32 com integração ao Blynk IoT.

• **Função Principal**

Controle de 2 relés de forma local (botões físicos) e remota (App Blynk), com indicação de conexão Wi-Fi via LED.

 **Online:** Controle via App Blynk e botões físicos

**Offline:** Controle apenas pelos botões físicos

• **Hardware Utilizado**
1x ESP32

1x 2 Relés 3.3v (pinos D26 e D27)

1x 2 Botões físicos (pinos D32 e D33)

1x LED de status Wi-Fi (pino D25)

• **Bibliotecas Necessárias**
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

• **Principais Funções do Código**

relayOnOff()	Liga/Desliga os relés  

with_internet()	Lê botões e atualiza o App  

without_internet()	Lê botões (modo offline)  

checkBlynkStatus()	Verifica status da conexão  

BLYNK_WRITE() / BLYNK_CONNECTED()	Comunicação com o Blynk

• **Aplicações**

-> Automação residencial

-> Controle IoT de dispositivos elétricos

-> Projetos que precisam funcionar online e offline


**Conexoes do hardware:**


| Fio                           | Origem           | Destino                |
| ----------------------------- | ---------------- | ---------------------- |
| **Fio de Controle do Relé**   | GPIO 26 do ESP32 | Pino IN do Módulo Relé |
| **Alimentação do Relé (VCC)** | 5V do ESP32      | VCC do Relé            |
| **GND do Relé**               | GND do ESP32     | GND do Relé            |

| Fio                            | Origem               | Destino                                   |
| ------------------------------ | -------------------- | ----------------------------------------- |
| **Polo Positivo da Fonte 12V** | Saída + da Fonte 12V | Pino COM do Relé                          |
| **Polo Negativo da Fonte 12V** | Saída - da Fonte 12V | Fio Preto do Solenoide (GND da fechadura) |

| Fio                                      | Origem          | Destino                   |
| ---------------------------------------- | --------------- | ------------------------- |
| **Fio Positivo do Solenoide (vermelho)** | Pino NO do Relé | Fio Vermelho do Solenoide |

| Fio               | Origem                        | Destino                                       |
| ----------------- | ----------------------------- | --------------------------------------------- |
| **Push Button 1** | Um lado no GPIO 32 do ESP32   | Outro lado no GND                             |
| **Push Button 2** | Um lado no GPIO 33 do ESP32   | Outro lado no GND                             |
| **LED WiFi**      | Anodo (+) no GPIO 25 do ESP32 | Cátodo (-) no GND via resistor (220Ω ou 330Ω) |

