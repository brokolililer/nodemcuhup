/*
Hup Projesi Nodemcu Kodları
 */

 
const int buton_saydir = 15;
int sayac = 0;
int butonDurumu = 0;

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <MFRC522.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define RST_PIN 20 // RST-PIN for RC522 - RFID - SPI
#define SS_PIN  2  // SDA-PIN for RC522 - RFID - SPI 
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance
const char* ssid = "burak_iphone";
const char* password = "huptestnet";
WiFiClient client;
//const IPAddress server(192,168,1,22);
Adafruit_SSD1306 display(-1);
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup () {
  pinMode(buton_saydir, INPUT);
  SPI.begin(); 
  mfrc522.PCD_Init(); 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  display.display();
  delay(8000);
  display.clearDisplay();
  display.display();
  while (WiFi.status() != WL_CONNECTED) { 
  delay(5000);
  Serial.println("Connecting..."); 
  
  }
    if (WiFi.status() == WL_CONNECTED) { 
        Serial.println("Baglandim");
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0,0);
        display.println("Kart yaklastir...");
        display.setCursor(0,10);
        display.println("Hup Yemekhane");
        display.setCursor(0,20);
        display.println("MTK - 479");
        display.setCursor(0,30);
        display.println("Projesidir.");               
        display.display();
        display.setCursor(0,55);
        display.println((String)"IP:192.168.1." +sayac);               
        display.display();

     
  } 
}
 
void loop() {
    butonDurumu = digitalRead(buton_saydir);
    if (butonDurumu == HIGH) {
    display.clearDisplay();
    //display.display();  
    sayac ++;
    //Serial.println(sayac);
    delay(500);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Kart yaklastir...");
    display.setCursor(0,10);
    display.println("Hup Yemekhane");
    display.setCursor(0,20);
    display.println("MTK - 479");
    display.setCursor(0,30);
    display.println("Projesidir.");               
    display.display();
    display.setCursor(0,55);
    display.println((String)"IP:192.168.1." +sayac);               
    display.display();
    setup();
    
 
    }

  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    
    return;
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {

    return;
  }
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     //Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  content.toUpperCase();
  if (content.substring(1) == "9E 1B AE 29") // Mavi Kart
  {
    HTTPClient http;  
    String postData;
    postData = "amount=3&sender=9E1BAE29&receiver=00";
    http.begin((String)"http://192.168.1."+String(sayac)+(String)":3001/transaction/broadcast");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpCode = http.POST(postData);
    
    if (httpCode > 0) { 
 
      String payload = http.getString();     
      Serial.println(payload); 
      Serial.println("Hup Basarili !");
      display.clearDisplay();     
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.print("Hup Basarili!");
      display.setCursor(0,25);
      display.print("Afiyet Olsun!");
      display.setCursor(0,50);
      display.print("Yemek : 3 HUP");              
      delay(3000);
      display.display();        
      http.end();
      setup();
        
    }
    
  }
  else if (content.substring(1) == "44 C8 EF E4") // Müslüm Kart
  {
    HTTPClient http;
    String postData;
    postData = "amount=3&sender=44C8EFE4&receiver=00";
    http.begin((String)"http://192.168.1."+String(sayac)+(String)":3002/transaction/broadcast");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpCode = http.POST(postData);
            
    if (httpCode > 0) { //Check the returning code
 
      String payload = http.getString();     
      Serial.println(payload); 
      Serial.println("Hup Basarili !");
      display.clearDisplay();     
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.print("Hup Basarili!");
      display.setCursor(0,25);
      display.print("Afiyet Olsun!");
      display.setCursor(0,50);
      display.print("Yemek : 3 HUP");              
      delay(3000);
      display.display();        
      http.end();
      setup();        
    }    
  }
   else if (content.substring(1) == "CE 32 DE E6") // Fatih Kart
  {

    HTTPClient http; 
    String postData;
    postData = "amount=3&sender=CE32DEE6&receiver=00";
    http.begin((String)"http://192.168.1."+String(sayac)+(String)":3003/transaction/broadcast");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpCode = http.POST(postData);
   
    if (httpCode > 0) { //Check the returning code
      
      String payload = http.getString();     
      Serial.println(payload); 
      Serial.println("Hup Basarili !");
      display.clearDisplay();     
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.print("Hup Basarili!");
      display.setCursor(0,25);
      display.print("Afiyet Olsun!");
      display.setCursor(0,50);
      display.print("Yemek : 3 HUP");              
      delay(3000);
      display.display();        
      http.end();
      setup();        
    }    
  }
  else if (content.substring(1) == "E7 5C B6 8B") // Beyaz Kart
  {
    HTTPClient http;  
    String postData;
    postData = "amount=3&sender=E75CB68B&receiver=00";
    http.begin((String)"http://192.168.1."+String(sayac)+(String)":3004/transaction/broadcast");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpCode = http.POST(postData);
    
    if (httpCode > 0) { 
 
      String payload = http.getString();     
      Serial.println(payload); 
      Serial.println("Hup Basarili !");
      display.clearDisplay();     
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.print("Hup Basarili!");
      display.setCursor(0,25);
      display.print("Afiyet Olsun!");
      display.setCursor(0,50);
      display.print("Yemek : 3 HUP");              
      delay(3000);
      display.display();        
      http.end();
      setup();        
    }
  }
  else if (content.substring(1) == "2E BB 71 60") // Burak Kart --> Müslüm Kart " 3 Hup "
  {
    HTTPClient http;  
    String postData;
    postData = "amount=3&sender=2EBB7160&receiver=44C8EFE4";
    http.begin((String)"http://192.168.1."+String(sayac)+(String)":3005/transaction/broadcast");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpCode = http.POST(postData);
    
    if (httpCode > 0) { 
 
      String payload = http.getString();     
      Serial.println(payload); 
      Serial.println("Hup Basarili !");
      display.clearDisplay();     
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.print("Hup Basarili!");
      display.setCursor(0,25);
      display.print("Muslum'e 3 Hup");
      display.setCursor(0,50);
      display.print("gonderildi !");              
      delay(3000);
      display.display();        
      http.end();
      setup();        
    }    
  }    
    else {

      Serial.println("Hup Basarisiz !");
      display.clearDisplay();     
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.print("Hup Basarisiz!");            
      delay(3000);
      display.display();      
      setup();
    }
}
