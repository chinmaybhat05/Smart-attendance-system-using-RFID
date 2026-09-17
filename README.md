# Smart-attendance-system-using-RFID

An IoT-based attendance system built using an ESP32, MFRC522 RFID reader, and Blynk IoT. The system identifies users through their RFID card UID and displays the attendance record remotely through the Blynk Terminal widget.

Features

- RFID-based user identification
- ESP32-based embedded system
- Wireless connectivity using Wi-Fi
- Blynk IoT integration for remote attendance monitoring
- UID-to-user name mapping
- Attendance information displayed through a Blynk Terminal
- Serial Monitor output for debugging
- Timestamp generation based on ESP32 "millis()"

Hardware Requirements

Component| Purpose
ESP32 Development Board| Main microcontroller
MFRC522 RFID Reader| Reads RFID card/tag UID
RFID Cards/Tags| User identification
Wi-Fi Network| Internet connectivity
USB Cable| Programming and power

Software & Libraries

- Arduino IDE
- ESP32 Arduino Core
- "Blynk IoT" (https://blynk.io/)
- MFRC522 Library
- SPI Library

System Architecture

       RFID Card / Tag
              │
              ▼
       ┌──────────────┐
       │   MFRC522    │
       │ RFID Reader  │
       └──────┬───────┘
              │ SPI
              ▼
       ┌──────────────┐
       │     ESP32    │
       │ Microcontroller│
       └──────┬───────┘
              │
           Wi-Fi
              │
              ▼
       ┌──────────────┐
       │  Blynk Cloud │
       └──────┬───────┘
              │
              ▼
       ┌──────────────┐
       │    Blynk     │
       │   Terminal   │
       └──────────────┘

How It Works

1. The ESP32 initializes the SPI interface and MFRC522 RFID reader.
2. The ESP32 connects to the configured Wi-Fi network through Blynk.
3. The system continuously checks for a new RFID card.
4. When a card is detected, the MFRC522 reads its UID.
5. The UID is compared with the predefined list of registered users.
6. If a matching UID is found, the corresponding user's name is identified.
7. The attendance information is sent to the Blynk Terminal.
8. The RFID card is halted after processing to prepare for the next scan.

Example output:

Attendance Recorded:
Name: Alice Johnson
UID: a1b2c3d4
Timestamp: 125 seconds
--------------------

RFID User Database

The current implementation stores the registered users directly in the ESP32 firmware:

String uids[] = {
    "A1B2C3D4",
    "B4C3D2A1",
    "C1D2A3B4"
};

String names[] = {
    "Alice Johnson",
    "Bob Smith",
    "Charlie Brown"
};

To add a new user, add the RFID UID and corresponding name to these arrays.

«Note: The UIDs and names shown above are example values. Replace them with the actual RFID card UIDs and user information before deployment.»

Pin Configuration

The MFRC522 is connected to the ESP32 through SPI.

MFRC522 Pin| ESP32 Pin
SDA / SS| GPIO 5
RST| GPIO 22
SPI| ESP32 hardware SPI pins
VCC| 3.3V
GND| GND

The SPI interface is initialized using:

SPI.begin();

Blynk Configuration

The project uses the Blynk Terminal widget to display attendance information remotely.

Before uploading the firmware, configure:

#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"

Also configure your Wi-Fi credentials:

char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

Do not upload real Wi-Fi credentials or Blynk authentication tokens to a public GitHub repository.

Project Structure

Smart-attendance-system-using-RFID/
│
├── finalProject.ino
└── README.md

Setup

1. Install Arduino IDE

Install the Arduino IDE and configure ESP32 board support.

2. Install Required Libraries

Install the following libraries through the Arduino IDE Library Manager:

- Blynk
- MFRC522

The SPI library is included with the Arduino environment.

3. Configure Credentials

Enter your own:

- Blynk Template ID
- Blynk Template Name
- Blynk Auth Token
- Wi-Fi SSID
- Wi-Fi password

4. Register RFID Cards

Read the UID of each RFID card and add the UID and corresponding user name to the arrays in "finalProject.ino".

5. Upload

Select the appropriate ESP32 board and COM port in Arduino IDE, then upload the firmware.

6. Monitor Attendance

Open the Blynk application and access the configured Terminal widget. Scan a registered RFID card to record an attendance event.

Limitations

The current version is a basic embedded IoT prototype.

- User information is stored directly in firmware.
- Attendance records are displayed through the Blynk Terminal rather than stored in a dedicated database.
- The timestamp uses "millis()", so it represents elapsed time since the ESP32 started rather than actual date and time.
- There is no authentication mechanism for individual RFID cards beyond UID matching.
- Duplicate scans are not filtered by a database or attendance schedule.

Possible Improvements

The system can be extended with:

- RTC or NTP-based real date and time
- Cloud/database-based attendance storage
- Daily attendance reports
- Duplicate-scan prevention
- OLED/LCD display
- Buzzer or LED feedback
- Admin interface for registering/removing users
- SD-card attendance logging
- Web dashboard
- Secure credential management
- Multiple attendance sessions and timetable support

Technologies Used

Microcontroller: ESP32
Programming Language: C/C++ (Arduino)
RFID: MFRC522
Communication: SPI, Wi-Fi
IoT Platform: Blynk
Development Environment: Arduino IDE

License

This project is intended for educational and demonstration purposes.