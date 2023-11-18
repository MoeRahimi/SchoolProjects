#include <string>

#include <gpio_library> //would be specific to microcontoller used. Pin and port numbers are arbitrary since there is no defined board. *Loosely* based on Arduino GPIO functions.
#define MICROCONTROLLER_RX 7 //port which the tub recieves data from the microcontroller
#define MICROCONTROLLER_TX 8 //port which the tub sends data to the microcontroller
#define FULL_SENSOR_PIN 9 // Pin connected to the full sensor
#define EMPTY_SENSOR_PIN 10 // Pin connected to the empty sensor
#define HOT_WATER_ACTUATOR_PIN 11 // Pin controlling the hot water actuator
#define COLD_WATER_ACTUATOR_PIN 12 // Pin controlling the cold water actuator
#define DRAIN_VALVE_PIN 13 // Pin controlling the drain valve
#define LOCK_ACTUATOR_PIN 14 // Pin controlling the lock actuator
#define HEATER_COIL_PIN_1 15 // Pin controlling the heater coil 1 warm temp
#define HEATER_COIL_PIN_2 16 // Pin controlling the heater coil 2 hot temp
#define MOTOR_CONTROL_PIN 17 // Pin controlling the motor

//Functions to hand the GPIO
std::string MicroInput() { // Function to read input from the microcontroller
    char microcontrollerInput;
    SerialPin(MICROCONTROLLER_RX, INPUT, &microcontrollerInput);
    return microcontrollerInput;
}
void MicroOutput(char data) { // Function to send data to the microcontroller
    SerialPin(MICROCONTROLLER_TX, OUTPUT, data);
}

bool isFull() { // Function to read the full sensor state
    bool fullState;
    SerialPin(FULL_SENSOR_PIN, INPUT, &fullState);
    return fullState;
}

bool isEmpty() { // Function to read the empty sensor state
    bool emptyState;
    SerialPin(EMPTY_SENSOR_PIN, INPUT, &emptyState);
    return emptyState;
}

void setHotWater(bool state) { // Function to control the hot water actuator. Let's say 5v
    SerialPin(HOT_WATER_ACTUATOR_PIN, OUTPUT, state);
}

void setColdWater(bool state) { // Function to control the cold water actuator. Let's say 5v
    SerialPin(COLD_WATER_ACTUATOR_PIN, OUTPUT, state);
}

void setDrainValve(bool state) { // Function to control the drain valve. Let's say 5v
    SerialPin(DRAIN_VALVE_PIN, OUTPUT, state);
}

void setLockActuator(bool state) { // Function to control the lock actuator. Let's say 5v
    SerialPin(LOCK_ACTUATOR_PIN, OUTPUT, state);
}

void setHeaterCoils(bool state1, bool state2) { // Function to control the heater coils
    SerialPin(HEATER_COIL_PIN_1, OUTPUT, state1);
    SerialPin(HEATER_COIL_PIN_2, OUTPUT, state2);
}

void SetMotorSpeed(int speed) { // Convert 'speed' to a PWM value
    int pwmValue = map(speed, 0, 100, 0, 255); // Assuming 'speed' is between 0-100%
    AnalogWrite(MOTOR_CONTROL_PIN, pwmValue); // Assuming 'AnalogWrite' is the function to write PWM value to a pin
}

//Additonal functions
void HandleWaterFilling() { //Function for filling the tub
    std::string command = MicroInput();
    switch (command) {
    case "hot": // Hot water
        setHotWater(true);
        setColdWater(false);
        setHeaterCoils(true, true);
        break;
    case "cold": // Cold water
        setHotWater(false);
        setColdWater(true);
        setHeaterCoils(false, false);
        break;
    case "warm": // Warm water (both hot and cold)
        setHotWater(true);
        setColdWater(true);
        setHeaterCoils(true, false);
        break;
    default:
        break;
    }
    while (!isFull()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100))
    }
    MicroOutput('F');     // Once the tub is full, send the signal back to the microcontroller
    setHotWater(false);
    setColdWater(false);//Shutoff to prevent overfilling
}

void DrainTub() {
    setDrainValve(true); // Open the drain valve
    setHeaterCoils(false, false);
    while (!isEmpty()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    setDrainValve(false); // Close the drain valve
    MicroOutput('E'); // Signal that the tub is empty
}

void HandleWashingCycle(int speed, std::chrono::steady_clock::time_point finishTime) {
    SetMotorSpeed(speed); // Set the motor speed
    while (std::chrono::steady_clock::now() < finishTime) {
        std::this_thread::sleep_for(std::chrono::minutes(1));
    }
}

int main() {
    int main() {
        while (true) {
            std::string command = MicroInput(); // Listen for commands from the microcontroller

            if (command == "drain") {
                DrainTub();
            }
            else if (isdigit(command)) {
                int speed = std::stoi(MicroInput()); // Get the speed for the wash or rinse cycle
                auto duration = std::chrono::minutes(MicroInput()); // Get the duration
                auto finishTime = std::chrono::steady_clock::now() + duration;
                HandleWashingCycle(speed, finishTime);
            }
            else if (command == "hot" || command == "cold" || command == "warm") {
                HandleWaterFilling(&command); // Handle the water filling based on the temperature command
            }
        }
        return 0;
    }
};
