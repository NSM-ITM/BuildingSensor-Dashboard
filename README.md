# BuildingSensor-Dashboard
A part of small pilot IoT projects for building management of Information Technology Museum, National Science Museum, Thailand

---

## Current running dashboard can be found [here](https://nsmitm-d3b46.firebaseapp.com/)

---

## Project Element:
- NodeMCU + DHT11 & HTML Dashboard for temperature monitoring system in NSM's buildings

### Technical Note
- Replace one or more of following variables in each file before using:
  - Arduino
    - FIREBASE_HOST
    - FIREBASE_AUTH
    - WIFI_SSID
    - WIFI_PASSWORD
  - Dashboard
    - apiKey
    - authDomain
    - databaseURL

- Install the latest version of following libraries in Arduino IDE:
  - [Adafruit Sensor](https://github.com/adafruit/Adafruit_Sensor)
  - [ArduinoJson](https://github.com/bblanchon/ArduinoJson)
  - [DHT Sensor](https://github.com/adafruit/DHT-sensor-library)
  - [Firebase Arduino](https://github.com/FirebaseExtended/firebase-arduino) * SSL is updated every now and then, updating library and re-upload to NodeMCU is required
  - [PMS](https://github.com/fu-hsi/pms) - Plantower PMS7003

---

## Dashboard
- Static dashboard on [Firebase Hosting](https://firebase.google.com/docs/hosting)

---

## Deployment
- Final working Arduino source code, to be uploaded on each NodeMCU device

---

## FirebaseArduino
- Testing source code for communication between NodeMCU and Firebase

---

## FirebaseSensor
- Testing source code for communication between NodeMCU, Firebase, and respective sensor(s) in pre-assigned structure

---

## GetMacAddress
- Getting MAC Address of each NodeMCU for network authorization registration

---

## ServerPing
- Testing source code for communication between NodeMCU and other HTTP endpoint

