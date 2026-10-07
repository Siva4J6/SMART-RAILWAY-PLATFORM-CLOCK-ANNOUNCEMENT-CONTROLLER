<img width="2086" height="754" alt="image" src="https://github.com/user-attachments/assets/fdf5f71e-4d07-41cd-8ea4-423f4c3680ec" />

Real-Time Train Schedule Monitoring • Passenger Information • Smart Alerts • Admin Control

An embedded railway platform information and monitoring system developed using the LPC2148 ARM7TDMI-S microcontroller and Embedded C. The system uses a Real-Time Clock (RTC) to monitor current time and compare it with stored train schedules. It automatically displays upcoming train information, identifies delays, provides visual status indications through LEDs, and generates audible alerts using a buzzer.



📌 Project Overview

The Smart Railway Platform Clock & Announcement Controller is designed to automate railway platform information management.

The system continuously monitors the current date and time using the RTC and compares it with predefined train schedules. Based on the comparison, the system can display:

- Train number
- Train name
- Destination
- Arrival time
- Departure time
- Platform number
- Train status
- Delay information

The system also provides an Admin Mode through an external interrupt, allowing authorized users to modify RTC settings and train schedule information using a keypad.



🎯 Objectives

- 🕐 Maintain and display real-time date and time using an RTC.
- 🚆 Store and manage information for multiple trains.
- 📺 Display train number, name, destination, timing, and platform.
- ⏱️ Automatically compare the current time with train schedules.
- 🔔 Detect approaching trains within the configured time window.
- 🟢 Provide visual train-status indication using LEDs.
- 🔊 Provide audio alerts using a buzzer.
- 🔄 Automatically update the displayed train information.
- ↔️ Display long train names using LCD scrolling.
- 🔐 Provide authorized Admin Mode for system configuration.
- ⌨️ Allow modification of RTC and train information through a keypad.
- 🛤️ Validate platform assignments and timing information.
- ✅ Validate user inputs before saving changes.
- ⚙️ Reduce manual intervention in railway platform information management.


⭐ Key Features

🕐 Real-Time Clock Monitoring

The RTC maintains the current date and time and provides the reference time for schedule comparison.

🚆 Train Schedule Management

The system stores information for multiple trains, including their train number, name, destination, arrival time, departure time, platform, and delay information.

📺 LCD Information Display

A 16×2 LCD is used to display current time and train-related information.

⏱️ Automatic Schedule Comparison

The LPC2148 continuously compares the RTC time with the stored train schedule.

🚦 Train Status Indication

LED| Status
🟢 Green| Train On-Time
🟡 Yellow| Train Approaching
🔴 Red| Train Delayed

🔊 Buzzer Alert

The buzzer provides an audible notification when a train is approaching or when an important schedule condition occurs.

🔄 Automatic Train Selection

After a train's scheduled time has passed, the system can move to the next relevant train.

🔐 Admin Mode

An administrator can enter configuration mode through an external interrupt and modify system information after authorization.

⌨️ Keypad-Based Configuration

The 4×4 matrix keypad is used for entering and modifying train and RTC information.

📜 LCD Scrolling

Long train names and information can be displayed using scrolling.


🧩 System Block Diagram


<img width="2056" height="765" alt="image" src="https://github.com/user-attachments/assets/3737d61d-a5f2-40e3-a23f-9e930a119ec9" />



🧠 System Architecture

The system is divided into the following major modules:

<img width="1536" height="1024" alt="ChatGPT Image Oct 1, 2026, 06_47_35 PM" src="https://github.com/user-attachments/assets/16742585-fb3c-4b6f-b3fe-314991879496" />

                   
⚙️ System Working

The system operates mainly in two modes:

🟢 Normal Mode

1. The system initializes the required peripherals.
2. The RTC provides the current date and time.
3. Stored train schedule information is loaded.
4. The current RTC time is compared with train timings.
5. The system identifies the relevant upcoming train.
6. Train information is displayed on the LCD.
7. The train status is indicated using LEDs.
8. The buzzer provides an alert when required.
9. Long train names can be displayed using LCD scrolling.
10. After the relevant train schedule has passed, the system updates the display for the next train.



🔐 Admin Mode

Admin Mode is used to modify system configuration.

Admin Mode Flow

Admin Switch Pressed
        ↓
External Interrupt
        ↓
Admin Mode Activated
        ↓
Authentication
        ↓
    ┌───────────────┐
    │ Select Option │
    └───────┬───────┘
            │
       ┌────┴────┐
       ↓         ↓
     RTC      Train Data
    Update       Update
       │         │
       └────┬────┘
            ↓
      Input Validation
            ↓
    Schedule Validation
            ↓
      Save Valid Data
            ↓
       Normal Mode



🔑 Admin Functions

The administrator can:

- Update RTC date.
- Update RTC time.
- Select train information.
- Modify train arrival time.
- Modify train departure time.
- Modify destination.
- Modify platform information.
- Modify updated train timings.
- Validate entered information.
- Check platform timing conflicts.
- Save valid changes.



🚆 Train Information

The system maintains information such as:

Train Number
Train Name
Destination
Scheduled Arrival
Scheduled Departure
Updated Arrival
Updated Departure
Platform Number
Delay Information

Example Train Database

Train No.| Train Name| Destination| Arrival| Departure| Platform| Delay
12627| Karnataka Express| New Delhi| 06:30| 06:35| 1| 0 min
12028| Shatabdi Express| Chennai| 07:15| 07:20| 2| 0 min
12785| Kacheguda Express| Hyderabad| 08:00| 08:05| 3| 20 min
 


⏱️ Train Status Logic

The system compares the current RTC time with the relevant train schedule.
<img width="1312" height="1199" alt="image" src="https://github.com/user-attachments/assets/77a97e5e-9bc1-40d1-8857-6b44c11849f3" />

            
📺 LCD Display

The 16×2 LCD provides passenger information such as:

TRAIN: 12627
KARNATAKA EXPRESS

and relevant information such as:

ARR: 06:30
PLAT: 1

Long train names can be displayed using LCD scrolling.

---

💡 LED Status Indication

The system uses three LEDs for simple visual identification of train status.

🟢 Green LED

Indicates the train is operating according to the stored schedule.

🟡 Yellow LED

Indicates that the train is approaching within the configured time window.

🔴 Red LED

Indicates that the train has a delay.



🔊 Buzzer

The buzzer provides an audio notification for important train events.

It can be activated when:

- A train is approaching.
- A relevant schedule condition occurs.
- An important train-status update is detected.

---

⌨️ Keypad

A 4×4 matrix keypad is used for user input.

It can be used for:

- Admin authentication.
- Menu selection.
- RTC modification.
- Train selection.
- Train timing modification.
- Platform modification.
- Data entry.

---

⚡ External Interrupt

The Admin switch is connected to an external interrupt.

Admin Switch
     ↓
External Interrupt
     ↓
Interrupt Service Routine
     ↓
Admin Mode Flag
     ↓
Admin Configuration

This allows the normal display operation to be interrupted when administrator configuration is required.



🧱 Hardware Requirements

Component| Purpose
LPC2148| Main microcontroller
16×2 LCD| Display train information
RTC| Maintain real-time date and time
4×4 Matrix Keypad| User/Admin input
Green LED| On-time indication
Yellow LED| Approaching indication
Red LED| Delay indication
Buzzer| Audio notification
Push Button/Switch| Admin interrupt
Power Supply| System power



💻 Software Requirements

Software / Technology| Purpose
Embedded C| Application programming
Keil µVision| Code development and compilation
Flash Magic| Microcontroller programming
Proteus| Simulation and testing
LPC2148| ARM7 embedded platform



🛠️ Technology Stack

Microcontroller : LPC2148
Architecture    : ARM7TDMI-S
Programming     : Embedded C
IDE             : Keil µVision
Simulation      : Proteus
Programming     : Flash Magic
Display         : 16×2 LCD
Input           : 4×4 Matrix Keypad
Timekeeping     : RTC
Alert           : Buzzer
Status          : LEDs
Interrupt       : External Interrupt



📁 Project Structure

A modular project structure can be maintained as follows:

Smart-Railway-Platform-Clock/
│
├── main.c
│
├── lcd.c
├── lcd.h
│
├── rtc.c
├── rtc.h
│
├── keypad.c
├── keypad.h
│
├── train.c
├── train.h
│
├── compare.c
├── compare.h
│
├── led.c
├── led.h
│
├── buzzer.c
├── buzzer.h
│
├── interrupt.c
├── interrupt.h
│
├── delay.c
├── delay.h
│
├── README.md
│
└── Documentation/



🧩 Software Modules

"main.c"

Controls the overall application flow and integrates all modules.

"lcd.c / lcd.h"

Contains LCD initialization and display functions.

"rtc.c / rtc.h"

Handles RTC initialization, reading and time/date operations.

"keypad.c / keypad.h"

Handles keypad scanning and user input.

"train.c / train.h"

Contains train information and train database management.

"compare.c / compare.h"

Compares RTC time with train schedule and determines train status.

"led.c / led.h"

Controls the train-status LEDs.

"buzzer.c / buzzer.h"

Controls buzzer alerts.

"interrupt.c / interrupt.h"

Handles external interrupt and Admin Mode activation.

"delay.c / delay.h"

Provides required software delay functions.



🔄 Overall Program Flow
<img width="1024" height="1536" alt="image" src="https://github.com/user-attachments/assets/ebe45b40-9a83-446c-b5b6-9d720877bbc8" />

              


📊 Functional Requirements

The system should be able to:

- Display the current date and time.
- Store multiple train schedules.
- Display train information.
- Compare current time with train timings.
- Identify upcoming trains.
- Identify delayed trains.
- Provide LED status indication.
- Provide buzzer alerts.
- Accept keypad input.
- Enter Admin Mode using an interrupt.
- Modify train information.
- Modify RTC information.
- Validate user inputs.
- Update train information after valid changes.



🔒 Data Validation

Before storing modified information, the system can validate:

- Valid time values.
- Valid train information.
- Valid platform number.
- Valid schedule values.
- Platform timing conflicts.
- User-entered configuration data.

Only valid information should be stored and used for schedule comparison.



🧪 Testing

The system can be tested using different train scheduling conditions.

Test Case| Input Condition| Expected Result
TC01| Normal RTC time| Current time displayed
TC02| Train approaching| Yellow LED + alert
TC03| Train on schedule| Green LED
TC04| Train delayed| Red LED
TC05| Long train name| LCD scrolling
TC06| Admin switch pressed| Admin Mode
TC07| Valid authentication| Admin functions available
TC08| Invalid input| Data rejected
TC09| RTC modification| Updated time displayed
TC10| Train schedule modification| Updated schedule used
TC11| Train time passed| Next train selected
TC12| Platform conflict| Conflict detected



📈 Expected Result

The completed system provides an automated railway platform information mechanism capable of monitoring train schedules using real-time clock information.

The system displays relevant train information on the LCD, indicates train status using LEDs, provides buzzer alerts, and allows authorized modification of RTC and train schedule information through Admin Mode.



✅ Advantages

- Reduces manual intervention.
- Provides real-time schedule monitoring.
- Automatically updates train information.
- Provides both visual and audio alerts.
- Supports multiple train schedules.
- Provides administrator configuration.
- Uses modular embedded software design.
- Improves accessibility of platform information.
- Can be simulated before hardware implementation.
- Suitable for embedded-system learning and demonstration.



⚠️ Limitations

- Train information depends on the data stored in the system.
- The basic system does not obtain live railway data from an external railway server.
- The number of trains is limited by the available memory and software design.
- LCD size limits the amount of information displayed at one time.
- RTC accuracy depends on proper RTC configuration and hardware conditions.
- The system requires administrator updates when schedule information changes.



🌍 Applications

The concept can be applied to:

- 🚆 Railway platforms
- 🚉 Small railway stations
- 🏢 Railway information counters
- 🚌 Bus/transport information systems
- 🏫 Educational embedded-system demonstrations
- 🧪 Embedded-system laboratories
- 📡 Real-time schedule display systems



🔮 Future Enhancements

The system can be extended with:

- 🌐 Wi-Fi-based live train information.
- 📱 Mobile application integration.
- ☁️ Cloud-based schedule management.
- 🖥️ Larger passenger information displays.
- 🗣️ Voice-based announcements.
- 🌍 Multi-language passenger information.
- 📡 Centralized railway schedule updates.
- 📊 Data logging and history.
- 🔔 Advanced notification mechanisms.
- 🤖 Intelligent prediction of delays.



🎓 Skills Demonstrated

This project demonstrates practical knowledge of:

- Embedded C
- ARM7 architecture
- LPC2148 microcontroller
- RTC programming
- LCD interfacing
- Matrix keypad interfacing
- GPIO programming
- External interrupts
- LED control
- Buzzer control
- Time comparison logic
- Structures in C
- Modular programming
- Embedded system design
- Hardware-software integration
- Proteus simulation
- Keil µVision
- Debugging and testing



💼 Why This Project Is Useful for an Embedded Engineer

This project demonstrates how an embedded system can combine hardware peripherals, real-time processing, user input, interrupts, display management, and decision-making logic into one application.

It provides practical exposure to:

Hardware
   ↓
Microcontroller
   ↓
Embedded C
   ↓
Peripheral Drivers
   ↓
Real-Time Processing
   ↓
Decision Making
   ↓
User Interface
   ↓
Alerts & Output


🧠 Core Concepts Used

LPC2148
   │
   ├── GPIO
   ├── RTC
   ├── External Interrupt
   ├── LCD Interface
   ├── Keypad Interface
   └── Output Control
          │
          ▼
     Embedded C
          │
          ▼
   Train Schedule Logic
          │
          ▼
   Real-Time Monitoring




📸 Project Documentation

The repository can include:

📁 Documentation
   ├── Block Diagram
   ├── Circuit Diagram
   ├── Flowchart
   ├── Project Mind Map
   ├── Simulation Screenshots
   ├── Hardware Images
   └── Project Report




🎥 Project Demonstration

The project demonstration can show:

1. System startup.
2. RTC time display.
3. Train information display.
4. Train approaching condition.
5. LED status indication.
6. Buzzer alert.
7. LCD scrolling.
8. Admin switch operation.
9. Admin authentication.
10. Train information modification.
11. RTC modification.
12. Updated schedule operation.




📌 Project Information

Category| Details
Project Name| Smart Railway Platform Clock & Announcement Controller
Domain| Embedded Systems
Microcontroller| LPC2148
Architecture| ARM7TDMI-S
Programming Language| Embedded C
Display| 16×2 LCD
Input| 4×4 Matrix Keypad
Timekeeping| RTC
Alert| Buzzer
Status Indication| Green, Yellow & Red LEDs
Interrupt| External Interrupt
IDE| Keil µVision
Simulation| Proteus
Programming Tool| Flash Magic



🏁 Conclusion

The Smart Railway Platform Clock & Announcement Controller demonstrates the implementation of a real-time embedded system for railway platform information management.

By combining LPC2148, RTC, LCD, keypad, LEDs, buzzer, and external interrupt functionality, the system can monitor train schedules, display relevant passenger information, indicate train status, generate alerts, and provide administrator-controlled schedule configuration.

The project provides practical experience in Embedded C, ARM7 microcontroller programming, peripheral interfacing, interrupt handling, real-time processing, modular software development, simulation, and system integration.




👩‍💻 Project Developed Using

LPC2148 ARM7TDMI-S • Embedded C • Keil µVision • Proteus • RTC • LCD • Keypad • LEDs • Buzzer • External Interrupt
