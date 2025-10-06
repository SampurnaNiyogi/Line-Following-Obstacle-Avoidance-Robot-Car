# Line-Following-Obstacle-Avoidance-Robot-Car
Our Arduino-powered robot uses IR and ultrasonic sensors for autonomous line-following and obstacle avoidance. After overcoming significant development challenges, the robot is now fully functional and being upgraded with maze-solving algorithms for advanced navigation.
# 🤖 Line Following & Obstacle Avoidance Robot Car

A smart autonomous robot car built using *Arduino UNO, capable of **line following* and *obstacle avoidance*.  
This project integrates *IR sensors, **ultrasonic sensing, and **servo-controlled scanning* to navigate intelligently in dynamic environments.  

---

## ⚙ Components Used (in working order)

- *Arduino UNO* – microcontroller for overall control  
- *L298N Motor Driver* – controls motor direction and speed  
- *4 Hobby Gear Motors* – provide motion for the car chassis  
- *Robot Car Chassis* – base structure of the robot  
- *IR Sensors* – detect black/white path for line following  
- *Ultrasonic Sensor (HC-SR04)* – measure distance to obstacles  
- *Servo Motor* – rotates the ultrasonic sensor for scanning  
- *LM2596 DC-DC Buck & Boost Converter* – stabilizes voltage supply  
- *Li-ion Batteries* – power source  
- *Breadboard & Jumper Wires* – for circuit prototyping  
- *LEDs* – used for status indication and debugging  

---

## 🧠 Features

- 🛣 *Line Following Mode:* Tracks the line path using IR sensors.  
- 🚧 *Obstacle Avoidance Mode:* Detects and avoids obstacles using ultrasonic sensor and servo.  
- 🔋 *Power Efficient:* Uses LM2596 converter for consistent voltage regulation.  
- 🧩 *Modular Design:* Easily extendable for future upgrades like maze-solving or path optimization.

---

## 🧰 Circuit Overview

The *IR sensors* continuously monitor the path and send signals to the *Arduino UNO*.  
When an obstacle is detected by the *ultrasonic sensor, the **servo motor* rotates to scan the environment and determine the best direction.  
The *L298N motor driver* receives control signals to move the robot accordingly.

---

## 🚧 Challenges Faced

Building this robot wasn’t easy — we faced:
- Multiple *code errors* and *wiring mismatches*
- Limited time due to *assignments and exams*
- Periods of *low motivation and sleepless debugging nights*

Despite all setbacks, persistence and teamwork led to success 🎉.

---

## 🚀 Future Enhancements

We’re now working on:
- 🧭 *Maze Solving Algorithm*
- 🧠 *Advanced Path Optimization*
- 🗺 *Integration with Mapping & Localization (Future Phase)*

Stay tuned for updates as we continue improving this project!

---

## 🧑‍💻 Contributors

- *Sampurna Niyogi*  
- *Hrichik Khandait*  

---

## 🔗 Repository Link

Find all the code and circuit details here:  
👉 [GitHub Repository](https://github.com/SampurnaNiyogi/Line-Following-Obstacle-Avoidance-Robot-Car)

---

## 🏷 Tags

#Arduino #Robotics #EmbeddedSystems #ObstacleAvoidance #LineFollower #Automation #IOT #CSEProjects

---

⭐ *If you like this project, don’t forget to star the repo!*
