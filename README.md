# Door Monitoring dengan ESP8266 dan Reed Switch

Proyek ini adalah sistem monitoring pintu menggunakan **ESP8266**, **reed switch**, **buzzer**, dan **lampu indikator (LED)**. Sistem ini dapat memantau status pintu (terbuka atau tertutup) dan mengirimkan notifikasi ke Telegram melalui bot ketika pintu terbuka. Sistem juga memiliki fitur pengaturan Wi-Fi menggunakan **WiFiManager**, sehingga pengguna dapat dengan mudah mengonfigurasi jaringan Wi-Fi.

---

## Fitur Utama
- **Pemantauan Pintu:** 
  - Membaca status pintu (terbuka/tutup) menggunakan **reed switch**.
- **Alarm dan Indikator:**
  - Mengaktifkan buzzer saat pintu terbuka.
  - LED Hijau: Alarm aktif, LED Merah: Alarm nonaktif.
- **Notifikasi Telegram:**
  - Mengirimkan pesan peringatan saat pintu terbuka.
  - Mengontrol status alarm (ON/OFF) melalui Telegram.
- **Pengaturan Wi-Fi Dinamis:**
  - Memanfaatkan **WiFiManager** untuk konfigurasi Wi-Fi tanpa perlu mengubah kode.

---

## Komponen yang Digunakan
1. **NodeMCU ESP8266:**
   - Mikrokontroler berbasis Wi-Fi yang menghubungkan sistem ke internet dan Telegram.
2. **Reed Switch:**
   - Sensor magnetik untuk mendeteksi apakah pintu terbuka atau tertutup.
3. **Buzzer:**
   - Memberikan alarm saat pintu terbuka.
4. **LED Hijau & Merah:**
   - Indikator status sistem (aktif atau tidak).
5. **Bot Telegram:**
   - Menggunakan bot Telegram untuk mengirim notifikasi dan menerima perintah.

---

## Library yang Digunakan
1. **ESP8266WiFi**  
   - Menghubungkan ESP8266 ke jaringan Wi-Fi.  
   - [Dokumentasi](https://arduino-esp8266.readthedocs.io/en/latest/).

2. **WiFiManager**  
   - Mempermudah konfigurasi Wi-Fi melalui portal web.  
   - [GitHub WiFiManager](https://github.com/tzapu/WiFiManager).

3. **CTBot**  
   - Library untuk komunikasi dengan API Telegram.  
   - [GitHub CTBot](https://github.com/shurillu/CTBot).

4. **ArduinoJson**  
   - Parsing JSON untuk data Telegram (sudah termasuk dalam CTBot).

---

## Cara Kerja
1. **Konfigurasi Awal:**
   - Saat NodeMCU pertama kali dinyalakan, portal Wi-Fi akan muncul. 
   - Pilih jaringan Wi-Fi dan masukkan password melalui antarmuka web.

2. **Pemantauan Pintu:**
   - **Reed switch** mendeteksi status pintu.
   - Jika pintu terbuka, buzzer berbunyi dan pesan dikirimkan ke bot Telegram.

3. **Kontrol Telegram:**
   - Kirim pesan "ON" ke bot untuk mengaktifkan alarm.
   - Kirim pesan "OFF" ke bot untuk menonaktifkan alarm.

4. **Indikator LED:**
   - LED Hijau menyala jika alarm aktif.
   - LED Merah menyala jika alarm mati.

---

## Persiapan dan Penggunaan
1. **Konfigurasi Bot Telegram:**
   - Buat bot Telegram menggunakan **BotFather** dan dapatkan token.
   - Ganti **`TELEGRAM_BOT_TOKEN`** dengan token Anda.
   - Dapatkan Telegram ID Anda (misalnya, menggunakan [bot ini](https://t.me/userinfobot)) dan masukkan ke variabel **`TELEGRAM_ID`**.

2. **Unggah Kode:**
   - Pastikan semua library sudah terinstal.
   - Unggah kode ke NodeMCU menggunakan **Arduino IDE**.

3. **Koneksi Wi-Fi:**
   - Sambungkan NodeMCU ke Wi-Fi melalui portal konfigurasi yang dibuat oleh **WiFiManager**.

4. **Tes Sistem:**
   - Uji reed switch dengan membuka dan menutup pintu.
   - Pastikan notifikasi diterima di Telegram.

---

## Diagram Pin
| Komponen       | Pin NodeMCU |
|----------------|-------------|
| Reed Switch    | D1 (GPIO5)  |
| Buzzer         | D2 (GPIO4)  |
| LED Hijau      | D0 (GPIO16) |
| LED Merah      | D3 (GPIO0)  |

---

## Catatan
- Jika Wi-Fi gagal tersambung, NodeMCU akan otomatis restart.
- **WiFiManager** akan menyimpan konfigurasi Wi-Fi, tetapi dapat direset menggunakan `wifiManager.resetSettings()`.

---

## Lisensi
Proyek ini bersifat open-source. Anda bebas menggunakan, memodifikasi, dan mendistribusikan dengan tetap mencantumkan kredit kepada pengembang.
