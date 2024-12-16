// Function to compute errors
void computeErrors() {

  for (int i = 0; i < NUM_DRIVERS; i++) {
    errors[i] = targetCurrents[i] - measuredCurrents[i];  // Calculate error
  }
}
// Function to compute PID outputs
void computeOutputs() {
  for (int i = 0; i < NUM_DRIVERS; i++) {
    // Proportional term
    float proportional = Kp * errors[i];

    // Integral term
    integrals[i] += errors[i];  // Accumulate integral
    float integral = Ki * integrals[i];

    // Derivative term
    float derivative = Kd * (errors[i] - previousErrors[i]);

    // Compute total output
    float output = proportional + integral + derivative;

    // Constrain the output within desired limits
    outputPercents[i] = constrain(output, -50, 50);  // Adjust range as needed

    // Rate limiting (in terms of percentage)
    //outputPercents[i] = constrain(output, outputPercents[i], outputPercents[i]);

    // Store the previous error for the next iteration
    previousErrors[i] = errors[i];
  }
}



void controlLoop() {
  readMeasuredCurrents();   
  computeErrors();
  computeOutputs();  
  applyPercentOutput();
  
}
