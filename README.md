# Kalman-Enhanced Ultrasonic Radar: Arduino Obstacle Detection System  

## Objectives:
The primary objective of this project is to design and implement a **low-cost ultrasonic radar system** capable of detecting obstacles in its environment while mitigating measurement noise through **Kalman filtering**. The system aims to:  

- Demonstrate the integration of an ultrasonic sensor with a servo motor for angular scanning.  
- Apply a state estimation algorithm (1D Kalman filter) to enhance the accuracy and reliability of distance measurements.  
- Provide a hands-on platform for students to understand predictive filtering, sensor fusion, and real-time data visualization.  
- Illustrate potential applications of radar-like sensing in robotics, automotive safety, and environmental monitoring.  

---

## Project Overview:
This project models a **miniature radar system** using the Arduino Uno, an HC-SR04 ultrasonic distance sensor, and a micro servo motor. The ultrasonic sensor is mounted on the servo, which sweeps across a defined angular range (20°–160°), emulating a radar scanning motion. At each angular step, distance measurements are acquired, filtered, and plotted in real time.  

A **Kalman filter** is embedded in the microcontroller code to smooth sensor readings by combining predictions with noisy measurements. This filtering process produces more consistent range data compared to raw sensor outputs, thereby enabling more robust obstacle detection.  

The system is implemented within **Tinkercad Circuits**, enabling students to engage in experimentation, prototyping, and replication in a virtual setting, while retaining the flexibility to extend the design to physical hardware.  

👉 [Click here to access the Tinkercad simulation](https://www.tinkercad.com/things/7kQgTeDa8EL-ultrasonickalmanradar)  

---

## Components:
The following components are required for implementation:  

- **Arduino Uno R3** – Microcontroller for system control and processing.  
- **HC-SR04 Ultrasonic Sensor** – For measuring obstacle distances.  
- **SG90 Micro Servo Motor** – To enable angular scanning of the sensor.  
- **LEDs (optional)** – Status indication and proximity alerts.  
- **220 Ω resistors** – Current limiting for LEDs.  
- **Breadboard and jumper wires** – For circuit prototyping.  

---

## Working Principle:  
The system functions by integrating servo-based scanning, ultrasonic measurement, predictive filtering, and visual feedback into a unified obstacle detection platform:  

1. **Servo-based Scanning:** The servo motor rotates the ultrasonic sensor in discrete angular increments between 20° and 160°, emulating the sweep of a radar antenna.  
2. **Distance Measurement:** At each position, the Arduino activates the HC-SR04 sensor to emit an ultrasonic pulse and measure the time delay of the returning echo, which is then converted into a distance value.  
3. **Kalman Filtering:** Raw measurements are processed through a one-dimensional Kalman filter, which fuses the predicted state with the new measurement. This reduces noise, smooths fluctuations, and produces a more reliable distance profile.  
4. **Data Visualization:** The processed and raw data are transmitted in CSV format to the Arduino Serial Plotter, enabling a visual comparison between noisy and filtered outputs.  
5. **Alert Mechanism:** An LED indicator illuminates whenever an object is detected within a predefined threshold (e.g., < 25 cm), providing a demonstration of a simple obstacle-warning system.  

---

## Applications:
This project has direct relevance to several real-world domains:  

- **Automotive systems:** Low-cost parking assistance and blind-spot detection.  
- **Mobile robotics:** Obstacle detection and mapping in autonomous navigation.  
- **Industrial automation:** Monitoring object presence or proximity on conveyor belts.  
- **Smart environments:** Occupancy monitoring or movement detection in rooms and corridors.  
- **Level estimation:** Measuring fill levels in containers, bins, or tanks.  

---

## Learning Outcomes: 
Through the design and implementation of this project, the following outcomes are expected:  

- Gain **practical experience** with ultrasonic sensing and servo-based actuation.  
- Understand the implementation of a **Kalman filter** for sensor noise reduction in embedded systems.  
- Explore the interaction between **signal processing and control mechanisms** in real time.  
- Develop skills in **Arduino programming, sensor interfacing, and data visualization**.  
- Foster an appreciation of the broader applications of **predictive filtering and radar-like sensing** in robotics, automotive engineering, and industrial systems.  

---

## Repository Structure: 
```bash
01_ultrasonic_kalman_radar/
├── ultrasonic_kalman_radar.ino   # Arduino source code
├── README.md                     # Project documentation (this file)
