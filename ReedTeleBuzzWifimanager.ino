#include <ESP8266WiFi.h>
#include <WiFiManager.h>  // Library WiFiManager untuk pengaturan WiFi

#include "CTBot.h" // Library CTBot untuk mengakses API Telegram
CTBot myBot;

String token = "TELEGRAM_BOT_TOKEN";  // Ganti dengan token bot Anda
const int userid = TELEGRAM_ID; // Ganti dengan ID Telegram Anda

const int reedPin = 5;    // Pin reed switch D1
const int buzzerPin = 4;  // Pin buzzer D2
const int led1 = 16;      // Pin led1 Hijau D0
const int led2 = 0;       // Pin led2 Merah D3

int status = 1; // Status alarm
int lastReedState = HIGH; // Status reed switch sebelumnya

void setup() {
  Serial.begin(115200);

  // Membuat instance WiFiManager
  WiFiManager wifiManager;

  // Jika ingin menghapus konfigurasi WiFi yang tersimpan sebelumnya
  wifiManager.resetSettings();

  // Menyiapkan portal konfigurasi dan menunggu pengguna memilih jaringan WiFi
  if (!wifiManager.autoConnect("ESP8266-WifiSetup")) {
    Serial.println("Gagal menyambung ke WiFi, akan reboot...");
    delay(3000);
    ESP.restart();
  }

  Serial.println("Tersambung ke WiFi!");

  // Inisialisasi bot setelah terhubung ke WiFi
  myBot.setTelegramToken(token);

  if (myBot.testConnection()) {
    Serial.println("\ntestConnection Bot terhubung");
  } else {
    Serial.println("\ntestConnection Bot gagal terhubung");
  }

  pinMode(reedPin, INPUT_PULLUP);  // Aktifkan pull-up internal untuk reed switch
  pinMode(buzzerPin, OUTPUT);      // Atur pin buzzer sebagai output
  pinMode(led1, OUTPUT);           // Pin led1 sebagai output
  pinMode(led2, OUTPUT);           // Pin led2 sebagai output
}

void loop() {
  int reedState = digitalRead(reedPin);  // Membaca status reed switch
  TBMessage msg;

  // Mengecek apakah ada pesan baru dari bot
  if (myBot.getNewMessage(msg)) {
    String pesan = msg.text;

    if (pesan == "ON") {
      status = 1;
      myBot.sendMessage(msg.sender.id, "Alarm Menyala");
    } else if (pesan == "OFF") {
      status = 0;
      myBot.sendMessage(msg.sender.id, "Alarm Mati");
    }
  }

  if (status == 1) {

    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW); 

    if (reedState != lastReedState) {  // Jika ada perubahan status
      lastReedState = reedState;
      if (reedState == LOW) {
        digitalWrite(buzzerPin, LOW);  // Nyalakan buzzer saat pintu tertutup
        Serial.println("Pintu tertutup");
      } else {
        digitalWrite(buzzerPin, HIGH);  // Matikan buzzer saat pintu terbuka
        Serial.println("Pintu terbuka");
        myBot.sendMessage(userid, "Peringatan !! Pintu terbuka");
      }
    }
  } else {
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
  }

  delay(500);
}
