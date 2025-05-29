
// # Course: IoT and Edge Computing
// # This code is based on the Lab8a_CarsClassify template and is tailored for the Thyroid classification model

#include <EloquentTinyML.h>
#include "occupancy_detection_esp32.h"  // Header file containing the Thyroid classification model

#define NUMBER_OF_INPUTS 5   // Define the number of model input features (example value)
#define NUMBER_OF_OUTPUTS 1    // Define the number of model output classes (example value)
#define TENSOR_ARENA_SIZE 5*1024  // Tensor arena size for the model

Eloquent::TinyML::TfLite<NUMBER_OF_INPUTS, NUMBER_OF_OUTPUTS, TENSOR_ARENA_SIZE> ml;

void setup() {
    Serial.begin(115200);
    ml.begin(occupancy_detection_esp32);  // Initialize model from the header file
}

float fResult[NUMBER_OF_OUTPUTS] = {0}; 

void loop() {
    // Sample input expected to predict "0" (no occupancy)
    float input1[] = {0.103390f, 0.808161f, 0.011636f, 0.056048f, 0.695337f}; // Low CO2, low light, etc.
    
    // Sample input expected to predict "1" (occupied)
    float input2[] = {0.902989f, 0.424878f, 0.461570f, 0.457190f, 0.565011f}; // Higher CO2, higher light, etc.

    // Predict occupancy for input1
    float fRes1 = ml.predict(input1, fResult);
    Serial.println("\nThe output value for input1 (no occupancy) is:");
    Serial.println(fRes1);
    displayOutput(fResult);

    // Predict occupancy for input2
    float fRes2 = ml.predict(input2, fResult);
    Serial.println("\nThe output value for input2 (occupied) is:");
    Serial.println(fRes2);
    displayOutput(fResult);

    delay(5000); // Delay for 5 seconds
}


void initfResult(float *fResult) {
    for (int i = 0; i < NUMBER_OF_OUTPUTS; i++) {
        fResult[i] = 0.0f;
    }
}

void displayOutput(float *fResult) {
    for (int i = 0; i < NUMBER_OF_OUTPUTS; i++) {
        Serial.print(fResult[i]);
        Serial.print(" ");
    }
    Serial.println();
}
