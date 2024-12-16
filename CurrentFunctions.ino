void readOffsets() {
  for (int i = 0; i < NUM_DRIVERS; i++) {
    long sum = 0;
    for (int j = 0; j < NUM_SAMPLES; j++) {
      sum += analogRead(pinCURRENTSENSOR[i]);
    }
    //float averageReading = sum * ADC_TO_VOLTAGE / (float)NUM_SAMPLES;  // Calculate average
    Offsets[i] = sum / NUM_SAMPLES;
    //measuredCurrents[i] = (sum / NUM_SAMPLES) * (ADC_TO_VOLTAGE);
  }
}

void printOffsets() {
  Serial.print("Offsets = ");
  for (int i = 0; i < NUM_DRIVERS; i++) {
    Serial.print(Offsets[i], 2);
    if (i < NUM_DRIVERS - 1) {
      Serial.print(",");
    }
  }
  Serial.println();
}


// Function to read measured currents
// Command: GET MEASURED CURRENTS
void readMeasuredCurrents() {
  for (int i = 0; i < NUM_DRIVERS; i++) {
    long sum = 0;
    for (int j = 0; j < NUM_SAMPLES; j++) {
      sum += analogRead(pinCURRENTSENSOR[i]);
    }
    float avg = sum / NUM_SAMPLES;
    measuredCurrents[i] = ((avg - Offsets[i]) * 0.0563) - 0.0053;
  }
}

// Function to print measured currents
// Command: GET MEASURED CURRENTS
void printMeasuredCurrents() {
  readMeasuredCurrents();
  Serial.print("Measured Currents = ");
  for (int i = 0; i < NUM_DRIVERS; i++) {
    Serial.print(measuredCurrents[i], 2);
    if (i < NUM_DRIVERS - 1) {
      Serial.print(",");
    }
  }
  Serial.println();
}


// Function to set target currents
// Command: SET TARGET CURRENTS:
void setTargetCurrents(String command) {
  String values = command.substring(20);  // Adjusted to 17 for "SET TARGET CURRENTS:"
  values.trim();
  int index = 0;

  int startIndex = 0;
  int commaIndex = values.indexOf(',');

  // Parse the target currents from the command string and store them in targetCurrents array
  while (commaIndex != -1 && index < NUM_DRIVERS) {
    String value = values.substring(startIndex, commaIndex);
    targetCurrents[index++] = value.toFloat();
    startIndex = commaIndex + 1;
    commaIndex = values.indexOf(',', startIndex);
  }

  // Handle the last value after the last comma
  if (startIndex < values.length() && index < NUM_DRIVERS) {
    String value = values.substring(startIndex);
    value.trim();
    targetCurrents[index] = value.toFloat();
  }

  
 
}

void resetTargetCurrents(){
  memset(targetCurrents, 0, sizeof(targetCurrents));
}


// Function to print target currents
// Command: GET TARGET CURRENTS
void printTargetCurrents() {
  Serial.print("Target Currents = ");
  for (int i = 0; i < NUM_DRIVERS; i++) {
    Serial.print(targetCurrents[i], 2);
    if (i < NUM_DRIVERS - 1) {
      Serial.print(",");
    }
  }
  Serial.println();
}
