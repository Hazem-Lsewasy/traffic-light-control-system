// Define pins for North-South traffic light
#define NS_GREEN_PIN 2      // North-South Green LED
#define NS_YELLOW_PIN 3     // North-South Yellow LED
#define NS_RED_PIN 4        // North-South Red LED

// Define pins for East-West traffic light
#define EW_GREEN_PIN 5      // East-West Green LED
#define EW_YELLOW_PIN 6     // East-West Yellow LED
#define EW_RED_PIN 7        // East-West Red LED

// Define pins for pedestrian signal
#define PED_WALK_PIN 8      // Pedestrian Walk LED
#define PED_DONT_WALK_PIN 9 // Pedestrian Don't Walk LED

// Define pin for pedestrian button
#define PED_BUTTON_PIN 0   // Push button for pedestrian crossing request

// Define traffic light states for the FSM
enum TrafficState { NS_GREEN, NS_YELLOW, EW_GREEN, EW_YELLOW, PED_WALK, ALL_RED };
TrafficState currentState = NS_GREEN; // Initialize the state to NS_GREEN

// Timing constants (in milliseconds)
unsigned long lastTransition = 0;       // Tracks the last state transition time
const unsigned long greenTime = 5000;   // Green light duration: 5 seconds
const unsigned long yellowTime = 2000; // Yellow light duration: 2 seconds
const unsigned long pedestrianTime = 5000; // Pedestrian Walk signal duration: 5 seconds
int flag = 0; // flag to indicate which Green signal will be trun ON


void setup() {
    // Set all traffic light LEDs as output pins
    pinMode(NS_GREEN_PIN, OUTPUT);
    pinMode(NS_YELLOW_PIN, OUTPUT);
    pinMode(NS_RED_PIN, OUTPUT);
    pinMode(EW_GREEN_PIN, OUTPUT);
    pinMode(EW_YELLOW_PIN, OUTPUT);
    pinMode(EW_RED_PIN, OUTPUT);

    // Set pedestrian signal LEDs as output pins
    pinMode(PED_WALK_PIN, OUTPUT);
    pinMode(PED_DONT_WALK_PIN, OUTPUT);

    // Set pedestrian button as input with internal pull-up resistor
    pinMode(PED_BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
    unsigned long currentTime = millis(); // Get the current time in milliseconds
    bool pedestrianRequest = digitalRead(PED_BUTTON_PIN) == LOW; // Check if pedestrian button is pressed

    // FSM logic: handle each traffic light state
    switch (currentState) {
        case NS_GREEN: // North-South traffic light is green
            // Turn on NS Green, turn off NS Yellow and NS Red
            digitalWrite(NS_GREEN_PIN, HIGH);
            digitalWrite(NS_YELLOW_PIN, LOW);
            digitalWrite(NS_RED_PIN, LOW);
            // Turn off EW Green, EW Yellow; Turn on EW Red
            digitalWrite(EW_GREEN_PIN, LOW);
            digitalWrite(EW_YELLOW_PIN, LOW);
            digitalWrite(EW_RED_PIN, HIGH);
            // Pedestrian signals: Walk OFF, Don't Walk ON
            digitalWrite(PED_WALK_PIN, LOW);
            digitalWrite(PED_DONT_WALK_PIN, HIGH);

            // Check if time for green is over or pedestrian button pressed
            if (currentTime - lastTransition > greenTime || pedestrianRequest) {
                currentState = NS_YELLOW; // Transition to NS Yellow
                lastTransition = currentTime; // Update the transition time
            }
            break;

        case NS_YELLOW: // North-South traffic light is yellow
            // Turn on NS Yellow, turn off NS Green and NS Red
            digitalWrite(NS_GREEN_PIN, LOW);
            digitalWrite(NS_YELLOW_PIN, HIGH);

            // Transition to East-West green after yellow duration
            if (currentTime - lastTransition > yellowTime) {
                currentState = EW_GREEN;
                lastTransition = currentTime;
            }
            break;

        case EW_GREEN: // East-West traffic light is green
            // Turn on EW Green, turn off EW Yellow and EW Red
            digitalWrite(EW_GREEN_PIN, HIGH);
            digitalWrite(EW_YELLOW_PIN, LOW);
            digitalWrite(EW_RED_PIN, LOW);
            // Turn off NS Green, NS Yellow; Turn on NS Red
            digitalWrite(NS_GREEN_PIN, LOW);
            digitalWrite(NS_YELLOW_PIN, LOW);
            digitalWrite(NS_RED_PIN, HIGH);

            // Check if time for green is over or pedestrian button pressed
            if (currentTime - lastTransition > greenTime || pedestrianRequest) {
                currentState = EW_YELLOW; // Transition to EW Yellow
                lastTransition = currentTime;
            }
            break;

        case EW_YELLOW: // East-West traffic light is yellow
            // Turn on EW Yellow, turn off EW Green
            digitalWrite(EW_GREEN_PIN, LOW);
            digitalWrite(EW_YELLOW_PIN, HIGH);

            // Transition to Pedestrian Walk or North-South green
            if (currentTime - lastTransition > yellowTime) {
                currentState = pedestrianRequest ? PED_WALK : NS_GREEN;
                lastTransition = currentTime;
            }
            break;

        case PED_WALK:  // Pedestrian Walk signal
            // Turn on Pedestrian Walk signal, turn off Don't Walk
            digitalWrite(PED_WALK_PIN, HIGH);
            digitalWrite(PED_DONT_WALK_PIN, LOW);
            // Turn Off East-West traffic light signal
            digitalWrite(EW_YELLOW_PIN, LOW);
            digitalWrite(NS_YELLOW_PIN, LOW);
            // Turn ON East-West and North-South traffic light signal
            digitalWrite(NS_RED_PIN, HIGH);
            digitalWrite(EW_RED_PIN, HIGH);

            // Transition to the next traffic light signal
            if (currentTime - lastTransition > pedestrianTime) {  
                currentState = flag ? EW_GREEN : NS_GREEN;
                lastTransition = currentTime;
            }
            break;
    }
}

