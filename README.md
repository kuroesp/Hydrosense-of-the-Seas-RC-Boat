<div align ="center">
  
  # 🤖 Hydrosense of the Seas RC Boat
  ### Real-time automatic sensor depth 
</div>

## ✨ Table of Contents
- [Why this project exists?](#%E2%80%8D-why-this-project-exists)
- [Project Introduction](#-project-introduction)
- [Features](#ⓘ-features)
- [Hardware & Software](#%EF%B8%8F-hardware--software)
- [API AI Services](#-ai-api-services)
- [Voice Asisstant Architecture](#_-voice-asisstant-architecture)
- [Pin Connections](#-pin-connections)


## 👨🏻‍💻 Why this project exists? 
In archipelagic provinces like the Riau Islands, numerous natural beaches are formed, which often leads to a relatively high risk of tsunamis. Furthermore, waste drainage remains a persistent urban issue, and in recent years, the Riau Islands have experienced an increase in flood disaster hotspots. This has posed a challenge for SAR (Search and Rescue) volunteers due to the rising demand for personnel.

To address this, this prototype is introduced as a supportive tool for SAR teams in executing their duties. Hydrosense of the Seas is equipped with an ultrasonic sensor to estimate the water depth of a recently occurred tsunami, allowing SAR teams to precisely monitor and estimate the daily decrease in flood volume. Additionally, the mobile-based remote control makes it easy for anyone to navigate the boat, enabling it to access tight spaces or areas that are difficult for humans to reach.

## ֎🇦🇮 Project Introduction

The Hydrosense of the Seas RC Boat is a first-generation prototype designed to assist SAR (Search and Rescue) teams in executing their duties. This boat is integrated with a remote control system via Bluetooth, connecting a mobile phone to the boat's onboard Bluetooth module. The remote control interface features navigation controls for moving forward, backward, and turning right or left. Additionally, it displays real-time water depth readings. When the depth reaches or exceeds 1 meter, an onboard buzzer or alarm will sound, indicating that the water is quite deep.

In general, the Hydrosense of the Seas RC boat serves as a tool to enhance the capabilities of resource-constrained SAR teams. Although it is still in its foundational stage, the hope is that this project can be further enhanced and improved for the benefit of society and the public in the future.

## ⓘ Features
- Alarm indicator
- Real-time depth sensor (for remote control)
- Wide area controller
- Real-time depth (for lcd)

## 🛠️ Hardware & Software 
### Hardware : 
- Arduino UNO
- Buck converter
- Lipo Battery Output 12V (2200 mAh)
- L298N Motor Driver
- Buzzer
- Propeller shaft
- Led
- HC-05 Bluetooth
- Sensor Ultrasonic JSN Sr04t
- Lcd 16x2 + I2C Module
- Potensiometer
- Wire : (Male to Male), (Male to Female)
- USB Cable
- Breadboard (Terminal)
- Impraboard (Base)
- Plastic Base (Inner base)

### Software : 
- Arduino IDE
- MIT APP INVENTOR


## >_ Voice Asisstant Architecture
- SETUP : When system get power supply from USB or battery, Script will be setup program.
- CONNECT THE BLUETOOTH : Connect your smartphone into HC-05 Bluetooth
- RELEASE TRIG : After setup ready, ultrasonic sensor will release Trig signal in front of sensor
- CATCH FROM ECHO : Then, Echo signal will be catched the Trig signal again.
- FORWARD VALUE : After the sensor have a value, Arduino uno will forward to bluetooth from RX/TX Com to HC05.
- FORWARD VALUE : 
Another forward goes to lcd 16x2 to show realtime depth value.
- STATEMENT : If a depth reach above one meters then, buzzer will be turn on.
- CONTROLLER : If the bluetooth has been connected, the propeller will be move according the user movement. 


## 🔌 Pin Connections

### Arduino Uno - Breadboard : 
| EPS32 | Breadboard | 
|-------|------------|
| VIN | First Red Rail |
| GND | First Blue Rail | 

### Motor Driver - Arduino Uno :
|Motor Driver Pin | Arduino Uno Pin | Descriptions |
|------------|-----------|--------------|
| VDD | 3.3V | Do not 5V! | 
| GND | GND | Put in Breadboard | 
| L/R | GND | Left Channel Select, put in Breadboard | 
| SD | D32 | Serial Data | 
| WS | D15 | L/R Clock | 
| SCK | D14 | Serial Clock | 

### Buck Converter - LiPo Battery : 
|Buck converter Pin | Lipo Battery | Description | 
|---------------------|-----------|-------------|
| VCC | VIN | Put in Breadboard |
| GND | GND | Put in Breadboard | 
| CS | D5 | Card Data |
| MISO | D19 | Output data |
| MOSI | D23 | Input data |
| SCK | D18 | Serial Clock |

