#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

// Constants
const double TRACK_LENGTH = 100.0;         // meters
const double INITIAL_TEMP = 300.0;         // K (room temp)
const double CRITICAL_TEMP = 90.0;         // K (superconductor's Tc)
const double MAX_CURRENT = 500.0;          // Amps (arbitrary limit)
const double COOL_RATE = 5.0;              // K cooled per tick
const double HEAT_LEAK = 1.0;              // K gained per tick (ambient)
const double LIFT_PER_AMP = 0.1;           // Newtons per Amp (arbitrary)
const double TRAIN_MASS = 1000.0;          // kg (light train)
const double GRAVITY = 9.8;                // m/s^2

// Helper to clear the screen (works on most systems)
void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

int main() {
    // Simulation variables
    double trainPos = 0.0;
    double trainSpeed = 0.0;
    double scTemp = INITIAL_TEMP;
    double current = 0.0;
    double coolant = 100.0; // Percent
    bool cooling = true;
    bool running = true;
    std::string status = "IDLE";

    srand(time(0));

    while (running) {
        // -- 1. Simulate cooling/heating --
        if (cooling && coolant > 0) {
            scTemp -= COOL_RATE;
            coolant -= 1.0; // Consumes coolant
            if (coolant < 0) coolant = 0;
        } else {
            scTemp += HEAT_LEAK;
        }
        // Clamp temp
        if (scTemp < 20.0) scTemp = 20.0;

        // -- 2. Calculate lift force from current (if below Tc) --
        double maglevLift = 0.0;
        if (scTemp < CRITICAL_TEMP && current > 0) {
            maglevLift = current * LIFT_PER_AMP;
            status = "LEVITATING";
        } else if (scTemp >= CRITICAL_TEMP && current > 0) {
            maglevLift = 0.0;
            status = "QUENCH! (No Levitation)";
        } else {
            status = "IDLE";
        }

        // -- 3. Move the train if levitating and enough lift --
        if (maglevLift > TRAIN_MASS * GRAVITY * 0.9) { // need 90% of weight for stable lift
            trainPos += trainSpeed;
            if (trainPos > TRACK_LENGTH) {
                trainPos = TRACK_LENGTH;
                trainSpeed = 0;
                status = "ARRIVED";
                running = false;
            }
        } else {
            trainSpeed = 0; // can't move if not levitating
        }

        // -- 4. ASCII Dashboard --
        clearScreen();
        std::cout << "====== Maglev Superconductor Simulator ======\n";
        std::cout << "Train Position: " << std::fixed << std::setprecision(2) << trainPos << " / " << TRACK_LENGTH << " m\n";
        std::cout << "Train Speed:    " << trainSpeed << " m/s\n";
        std::cout << "SC Temp:        " << scTemp << " K (Tc = " << CRITICAL_TEMP << " K)\n";
        std::cout << "Current:        " << current << " A (max " << MAX_CURRENT << " A)\n";
        std::cout << "Coolant:        " << coolant << " %\n";
        std::cout << "Maglev Lift:    " << maglevLift << " N\n";
        std::cout << "Status:         " << status << "\n";
        std::cout << "============================================\n";

        // -- 5. User Controls --
        std::cout << "\nControls: [1] Set Current  [2] Set Speed  [3] Toggle Cooling  [4] Refill Coolant  [5] Quit\n";
        std::cout << "Enter choice: ";
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                double newCurrent;
                std::cout << "Set current (A, max " << MAX_CURRENT << "): ";
                std::cin >> newCurrent;
                if (newCurrent < 0) newCurrent = 0;
                if (newCurrent > MAX_CURRENT) newCurrent = MAX_CURRENT;
                current = newCurrent;
                break;
            }
            case 2: {
                double newSpeed;
                std::cout << "Set train speed (m/s, recommended 1–10): ";
                std::cin >> newSpeed;
                if (newSpeed < 0) newSpeed = 0;
                if (newSpeed > 50) newSpeed = 50;
                trainSpeed = newSpeed;
                break;
            }
            case 3:
                cooling = !cooling;
                std::cout << (cooling ? "Cooling ON.\n" : "Cooling OFF.\n");
                break;
            case 4:
                coolant = 100.0;
                std::cout << "Coolant refilled!\n";
                break;
            case 5:
                running = false;
                break;
            default:
                std::cout << "Invalid choice.\n";
        }

        // Simulate time passing between ticks
        std::cout << "\n[Press Enter to continue...]";
        std::cin.ignore();
        std::cin.get();
    }

    std::cout << "\nSimulation ended. Thanks for playing with superconductors!\n";
    return 0;
}