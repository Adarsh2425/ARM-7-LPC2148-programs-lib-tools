			  #include <LPC214x.h>

#define NUM_CONTROLLERS 5

void adjustLoads(int* loads, int voltageDifference) {
    for (int i = 0; i < NUM_CONTROLLERS; ++i) {
        if (abs(voltageDifference) > 5) {
            // Adjust load based on voltage difference
            int loadAdjustment = voltageDifference * 0.1; // Simple adjustment rule
            loads[i] -= loadAdjustment;
        }
    }
}

int main() {
    int loads[NUM_CONTROLLERS] = {100, 150, 120, 180, 200};
    int measuredVoltage = 220; // Initial voltage

    while (1) {
        // Simulate voltage fluctuations
        measuredVoltage += rand() % 11 - 5; // Random voltage fluctuations between -5 and 5 volts

        // Check voltage and adjust loads
        int voltageDifference = measuredVoltage - 220; // Target voltage is 220V
        adjustLoads(loads, voltageDifference);

        // Ensure loads are within a certain range
        for (int i = 0; i < NUM_CONTROLLERS; ++i) {
            loads[i] = (loads[i] < 50) ? 50 : loads[i];
            loads[i] = (loads[i] > 200) ? 200 : loads[i];
        }

        // Simulate system behavior (you can insert more complex logic here)

        // Add delay to simulate real-time operation
        for (int i = 0; i < 100000; ++i) {
            __NOP();
        }
    }
}