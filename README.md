# 🌦️ Real-Time Weather Detection Using NodeMCU ESP8266 and Machine Learning Algorithms
![Logo](https://github.com/ahmadsyahdirizmi/IoT-ML-Weather-Station/blob/9358b034b103e0947dec1945ebb49a90daa10c5b/assets/1718038134155.jpg)

## Table of Contents
- [📌 Introduction](#introduction)
- [🔧 Hardware Components](#hardware-components)
- [💻 Software Components](#software-components)
- [🛠️ System Design](#system-design)
- [🤖 Machine Learning Models](#machine-learning-models)
- [⚙️ Installation and Setup](#installation-and-setup)
- [🚀 Usage](#usage)

## Introduction

This project aims to develop a real-time weather detection system using the NodeMCU ESP8266 microcontroller, integrated with various sensors to collect weather data. The data is then analyzed using machine learning algorithms, specifically K-Means Clustering and Random Forest, to identify patterns and make weather predictions. The system leverages the Internet of Things (IoT) to facilitate real-time monitoring and data collection.

## Hardware Components

- **🔌 NodeMCU ESP8266**: Microcontroller with Wi-Fi capabilities for IoT applications.
- **🌡️ DHT11 Sensor**: Measures temperature and humidity.
- **🌍 BMP280 Sensor**: Measures atmospheric pressure and altitude.
- **📟 OLED SSD1306**: Displays real-time weather data.
- **🔋 5V Adapter**: Powers the NodeMCU and sensors.

## Software Components

- **🖥️ Arduino IDE**: Used to program the NodeMCU ESP8266.
- **☁️ Firebase**: Cloud platform used for storing and retrieving weather data.
- **🐍 Python**: Used for developing and running machine learning models.
- **📚 Libraries**:
  - `Adafruit_GFX.h`, `Adafruit_SSD1306.h`: For OLED display.
  - `DHT.h`: For DHT11 sensor.
  - `Wire.h`, `Adafruit_Sensor.h`, `Adafruit_BMP280.h`: For BMP280 sensor.
  - `ESP8266WiFi.h`, `FirebaseESP8266.h`: For Wi-Fi and Firebase connectivity.

## System Design

1. **📊 Data Collection**: Sensors collect temperature, humidity, atmospheric pressure, and altitude data.
2. **🌐 Data Transmission**: NodeMCU sends the collected data to Firebase in real-time.
3. **🧠 Data Analysis**: Machine learning models analyze the data to detect weather patterns.
4. **📈 Data Visualization**: OLED display shows real-time weather data.

## Machine Learning Models

- **K-Means Clustering**: Used for clustering weather data into different categories.
- **Random Forest**: Used for predicting weather conditions based on the collected data.

## Installation and Setup

1. **🔧 Hardware Setup**:
   - Connect the DHT11, BMP280, and OLED SSD1306 to the NodeMCU ESP8266.
   - Power the NodeMCU using the 5V adapter.

2. **💻 Software Setup**:
   - Install Arduino IDE and necessary libraries.
   - Install Python and required packages for machine learning.
   - Set up a Firebase project and configure it to store weather data.

3. **📲 Programming the NodeMCU**:
   - Write and upload the Arduino code to the NodeMCU to read sensor data and send it to Firebase.

4. **🧠 Running Machine Learning Models**:
   - Develop Python scripts to fetch data from Firebase and run K-Means Clustering and Random Forest algorithms.

## Usage

- **🔄 Real-Time Monitoring**: View real-time weather data on the OLED display.
- **📈 Data Analysis**: Analyze collected data using machine learning models to detect weather patterns and make predictions.
- **🌐 Remote Access**: Access the weather data remotely via the Firebase console.

## References

- **Adafruit DHT11 Sensor Library**: [GitHub](https://github.com/adafruit/DHT-sensor-library)
- **Adafruit BMP280 Library**: [GitHub](https://github.com/adafruit/Adafruit_BMP280_Library)
- **Firebase for ESP8266 Library**: [GitHub](https://github.com/mobizt/Firebase-ESP8266)
