# README: Traffic Light Control System Using Arduino Uno

Project Overview
This project implements a traffic light control system for a four-way intersection with a pedestrian crossing feature. It uses an ESP32, LEDs for traffic and pedestrian signals, and a push button for pedestrian crossing requests. The project demonstrates state-based control using a Finite State Machine (FSM).

Hardware Components
1 x ESP32
12 x LEDs (Red, Yellow, Green for North-South and East-West traffic lights)
2 x LEDs (Pedestrian Walk and Don't Walk signals)
1 x Push button (for pedestrian crossing request)

Connect a Green LED to digital pin D2 
Connect a Yellow LED to digital pin D3 
Connect a Red LED to digital pin D4.
Connect East-West Traffic Lights:

Connect a Green LED to digital pin D5
Connect a Yellow LED to digital pin D6 
Connect a Red LED to digital pin D7 
Connect Pedestrian Signals:

Connect the Walk LED to digital pin D8 
Connect the Don’t Walk LED to digital pin D9 
Connect the Push Button:

Connect one terminal of the push button to digital pin D0.
Connect the other terminal to GND.
Use the internal pull-up resistor of the ESP32 by configuring the button pin as INPUT_PULLUP in the code.
Power Connections:

Ensure all ground connections share a common ground.
Software Setup
Install the Arduino IDE:

Download and install the Arduino IDE.
Load the Code:

Open the provided Arduino sketch (traffic_light_control.ino) in the Arduino IDE.
Ensure the correct board and port are selected under Tools > Board > ESP32 and Tools > Port.
Compile and Upload the Code:

Click the Verify button to compile the code.

Operation

Traffic Light Cycle:

The system begins with the North-South Green light and cycles through the states:
North-South Yellow → East-West Green → East-West Yellow.
Pedestrian Crossing:

Press the push button till the walk sign lighten up (Blue) to request a pedestrian crossing.
The system transitions to the Pedestrian Walk state after completing the current light cycle.
Pedestrian signals (Walk and Don't Walk) operate accordingly.

Testing
Ensure all LEDs light up correctly based on the state transitions.
Verify that pressing the button interrupts the normal traffic cycle for pedestrian crossing.

