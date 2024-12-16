void processCommand(String command) {
  command.trim();  // Remove leading/trailing whitespace

  // Output percentage commands
  if (command.startsWith("SET PERCENT OUTPUTS:")) {
    setOutputPercentages(command);
    Serial.println(command);

  } else if (command.startsWith("GET PERCENT OUTPUTS:")) {
    printOutputPercent();
    Serial.println(command);

  }

  // Measured currents commands
  else if (command.startsWith("GET MEASURED CURRENTS:")) {
    printMeasuredCurrents();
    Serial.println(command);

  }
  // Target currents commands
  else if (command.startsWith("SET TARGET CURRENTS:")) {
    setTargetCurrents(command);
    Serial.println(command);

  } else if (command.startsWith("GET TARGET CURRENTS:")) {
    printTargetCurrents();
    Serial.println(command);

  } else if (command.startsWith("RESET:"))
  {
    resetAll();
    Serial.println(command);

  }

  // Unknown command handling
  else {
    Serial.println("Unknown Command");
  }



}

void serialEvent() {
  if (Serial.available() > 0) {
    previousWatchDogTime = millis(); // Reset the timer

    String command = Serial.readStringUntil('\n');  // Read the incoming string until newline
    command.trim();           // Remove leading or trailing whitespace
    processCommand(command);  // Process the command

  }
}
/*
  Measured Currents = 1.02,1.96,3.23,4.16
  Measured Currents = 1.06,1.84,3.29,4.16
  Measured Currents = 1.10,1.81,3.34,4.19
  Measured Currents = 1.11,1.87,3.17,4.17
  Measured Currents = 1.05,1.93,3.16,4.22
  Measured Currents = 1.00,1.91,3.20,4.17
  Measured Currents = 1.06,1.86,3.32,4.14
  -----
  Measured Currents = 1.05,1.92,3.24,4.21
  Measured Currents = 1.03,1.90,3.23,4.19
  Measured Currents = 1.00,1.85,3.23,4.19
  Measured Currents = 1.03,1.90,3.27,4.21
  Measured Currents = 1.07,1.94,3.26,4.19
  Measured Currents = 1.04,1.88,3.21,4.14
  Measured Currents = 1.01,1.84,3.17,4.09
  Measured Currents = 0.99,1.80,3.21,4.12
  Measured Currents = 1.02,1.85,3.26,4.15

*/
