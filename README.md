# 🚀 RFID Based Smart Electronic Voting System
ARM7 LPC2148 | Embedded C | UART (Interrupt) | I2C | RTC | EEPROM

📌 Project Overview
This project is a prototype RFID-based electronic voting system built using the ARM7 LPC2148 microcontroller.

The system ensures:
Secure voter authentication using RFID
Time-restricted voting using RTC
Officer-controlled configuration
Persistent vote storage using external EEPROM
This project demonstrates practical implementation of:
UART interrupt handling
I2C communication
EEPROM memory mapping
Embedded menu-driven system design
Real-time control using RTC

🎯 Key Features
✔ RFID-based authentication
✔ Officer access with password protection
✔ Voting allowed only within configured time
✔ Duplicate voting prevention
✔ EEPROM-based permanent vote storage
✔ LCD-based menu interface
✔ Keypad-based user interaction
✔ Interrupt-driven UART for RFID reading

🧠 System Architecture
RFID Reader → UART Interrupt → LPC2148
EEPROM (24C256) ↔ I2C
RTC Module ↔ I2C
LCD ↔ GPIO
Keypad ↔ GPIO

The microcontroller acts as the central controller that manages all peripherals.

🔌 GPIO Pin Connections
Below are the hardware connections used in this project.

📟 LCD (20x4) – 4-bit Mode
LCD Pin	LPC2148 Pin
RS	P0.0
EN	P0.1
D4	P0.4
D5	P0.5
D6	P0.6
D7	P0.7
⌨ Keypad (4x4 Matrix)
Row Pins	LPC2148
R1	P0.8
R2	P0.9
R3	P0.10
R4	P0.11
Column Pins	LPC2148
C1	P0.12
C2	P0.13
C3	P0.14
C4	P0.15
📡 RFID Reader
RFID Pin	LPC2148
TX	RXD0 (P0.1)
RX	TXD0 (P0.0)

Communication Method: UART0 with Interrupt
💾 EEPROM – 24C256 (I2C)
EEPROM Pin	LPC2148 Pin
SDA	P0.27
SCL	P0.28

Communication Method: I2C0
🕒 RTC Module (I2C)
RTC Pin	LPC2148
SDA	P0.27
SCL	P0.28
⚙️ How the System Works
1️⃣ Officer Configuration

Officer logs in using:
RFID card
Password
Officer can:
Set voting start time
Set voting end time
View results
Reset system

2️⃣ Voting Process
System waits for RFID card.
Voter presents card.

System checks:
Is voting time active?
Has voter already voted?
If valid → Party list displayed.
Voter selects option using keypad.
Vote count updated in EEPROM.
System blocks duplicate voting.

💾 EEPROM Memory Structure
Address Range	Stored Data
0x0000	Voting control flags
0x0010	Start time
0x0020	End time
0x0100	Officer credentials
0x0200	Voter credentials
0x0500	Vote counts
🔄 Why UART Interrupt?

UART interrupt is used to:
Avoid continuous polling
Improve efficiency
Handle asynchronous RFID data reception
The ISR sets a flag when complete card data is received.

🧪 Challenges Faced
Managing EEPROM write acknowledgment
Designing memory mapping structure
Handling UART data correctly in interrupt
Preventing duplicate votes
Debugging I2C timing issues

🔮 Future Improvements
Implement wear-leveling for EEPROM
Add encryption for stored credentials
Add checksum validation
Convert system to RTOS-based architecture
Improve tamper resistance

🎥 Project Demo Video
👉 Watch the full working demo here:
[YouTube Demo Link Here]
(Replace with your actual link)

🛠 Tools Used
Keil µVision
Flash Magic
ARM7 LPC2148
Embedded C
UART & I2C Protocol Implementation

👨‍💻 Author
Gali Narendra
Embedded Systems Developer
Hyderabad, India

GitHub: https://github.com/ngali8032
YouTube: (Add your channel link here)
