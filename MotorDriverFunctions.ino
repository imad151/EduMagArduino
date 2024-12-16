// Function to set PWM direction and output percentage

void setPWMDirection(int channel, int pwmPercentage) {
  if (channel < 0 || channel >= NUM_DRIVERS) {
    Serial.println(F("Invalid channel"));
    return;
  }

  pwmPercentage = constrain(pwmPercentage, -50, 50);  // Adjust range as needed

  bool direction = pwmPercentage < 0;
  digitalWrite(pinDIR[channel], direction);
  int pwmValue = map(abs(pwmPercentage), 0, 100, 0, 255);
  analogWrite(pinPWM[channel], pwmValue);
}

// Function to set output percentages
// Command: SET PERCENT OUTPUTS:
void setOutputPercentages(String command) {
  String values = command.substring(20); // Adjusted to 20 for "SET PERCENT OUTPUTS:"
  values.trim();
  int index = 0;

  int startIndex = 0;
  int commaIndex = values.indexOf(',');

  while (commaIndex != -1 && index < NUM_DRIVERS) {
    String value = values.substring(startIndex, commaIndex);
    outputPercents[index++] = value.toFloat();
    startIndex = commaIndex + 1;
    commaIndex = values.indexOf(',', startIndex);
  }

  if (startIndex < values.length() && index < NUM_DRIVERS) {
    String value = values.substring(startIndex);
    value.trim();
    outputPercents[index] = value.toFloat();
  }

  applyPercentOutput();
}

void resetOutputPercentages()
{
  memset(outputPercents, 0, sizeof(outputPercents));
}
// Function to print output percentages for each driver
// Command: GET PERCENT OUTPUTS:
void printOutputPercent() {
  Serial.print("Output Percent = ");
  for (int i = 0; i < NUM_DRIVERS; i++) {
    Serial.print(outputPercents[i], 2); // Print output percentage with 2 decimal places
    if (i < NUM_DRIVERS - 1) {
      Serial.print(","); // Print comma between values
    }
  }
  Serial.println(); // New line at the end
}


// Function to apply percent output to PWM
void applyPercentOutput() {
  for (int i = 0; i < NUM_DRIVERS; i++)
  {
    if (targetCurrents[i] == 0)
    {
      setPWMDirection(i, 0);
    }
    else
    {
      setPWMDirection(i, outputPercents[i]);

    }
  }
}
