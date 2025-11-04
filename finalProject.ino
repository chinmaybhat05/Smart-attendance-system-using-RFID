#define BLYNK_TEMPLATE_ID "TMPL3t6BAmgCk"
#define BLYNK_TEMPLATE_NAME "Attendence"
#define BLYNK_AUTH_TOKEN "OS5fEW4b7P4qAN8xKFWl2Yx0_wqXPpTW"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <MFRC522.h>
#include <SPI.h>

// Blynk Auth Token

// Wi-Fi credentials
char ssid[] = "Bolt";
char pass[] = "Boeing 737";

// RFID and Blynk setup
#define SS_PIN 5
#define RST_PIN 22
MFRC522 mfrc522(5,22);
WidgetTerminal terminal(V0);  // Terminal widget on Virtual Pin V1

// UID and name mappings
String uids[] = {"A1B2C3D4", "B4C3D2A1", "C1D2A3B4"};
String names[] = {"Alice Johnson", "Bob Smith", "Charlie Brown"};
int numUsers = sizeof(uids) / sizeof(uids[0]);

void setup() {
  Serial.begin(115200);
  
  // Initialize SPI and RFID
  SPI.begin();
  mfrc522.PCD_Init();
 mfrc522.PCD_Init();

  // Initialize Blynk and clear the Terminal
   Blynk.begin(BLYNK_AUTH_TOKEN,ssid,pass);
  terminal.clear();

  terminal.println("RFID attendance system started. Please scan your card.");
  terminal.flush();
}

void loop() {
  Blynk.run();

  // Check if an RFID card is present
  {
   if (!mfrc522.PICC_IsNewCardPresent()){
    return;
    }  // put your main code here, to run repeatedly:
if(!mfrc522.PICC_ReadCardSerial()){
  return;
}
    String uid = "";
  
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      uid += String(mfrc522.uid.uidByte[i], HEX);
    }

    Serial.print("UID detected: ");
    Serial.println(uid);
    
    // Look up name for the scanned UID
    String name = "Unknown User";
    for (int i = 0; i < numUsers; i++) {
      if (uid.equalsIgnoreCase(uids[i])) {
        name = names[i];
        break;
      }
    }
    
    // Display the attendance in Terminal widget
    terminal.println("Attendance Recorded:");
    terminal.println("Name: " + name);
    terminal.println("UID: " + uid);
    terminal.println("Timestamp: " + String(millis() / 1000) + " seconds");
    terminal.println("--------------------");
    terminal.flush();  // Send data to Blynk app immediately
    
    // Halt RFID reading until the next scan
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
  }
}
