// ---------- Constants ----------
const int NUM_DRIVERS = 4;
const float NUM_SAMPLES = 10;

String command = " ";

// Current conversion constants
float Offsets[NUM_DRIVERS ] = {0};

const float ADC_TO_VOLTAGE = 5.0 / 1024;
const float CURRENT_FACTOR = ADC_TO_VOLTAGE / NUM_SAMPLES;

// ---------- Pin Configurations ----------
const int pinPWM[NUM_DRIVERS] = { 2, 3, 5, 6};
const int pinDIR[NUM_DRIVERS] = { 23, 25, 27, 29};
const int pinCURRENTSENSOR[NUM_DRIVERS] = { A0, A1, A2, A3};


// Measurement and control variables
float measuredCurrents[NUM_DRIVERS] = { 0 };
float targetCurrents[NUM_DRIVERS] = { 0 };
float outputPercents[NUM_DRIVERS] = { 0 };


// ---------- PID Control Variables ----------
float errors[NUM_DRIVERS] = { 0 };          // Current errors
float previousErrors[NUM_DRIVERS] = { 0 };  // Previous errors for derivative calculation
float integrals[NUM_DRIVERS] = { 0 };       // Integral of errors

// PID constants
float Kp = 5;  // Proportional gain
float Ki = 0.8;  // Integral gain
float Kd = 0.0;   // Derivative gain

// ---------- Function Declarations ----------
void setup();
void loop();

void readMeasuredCurrents();
void printMeasuredCurrents();

void resetTargetCurrents();
void setTargetCurrents();
void getTargetCurrents();



void setPWMDirection(int channel, int pwmPercentage);
void printOutputPercent();
void setOutputPercentages(String values);
void applyPercentOutput();

void processCommand(String command);

void controlLoop();
void resetAll();

unsigned long watchDogTimeout = 3000;
unsigned long previousWatchDogTime = 0; // stores the last time task A was executed
unsigned long currentWatchDogTime = 0;

void setup() {
  // Initialize pin modes


  Serial.begin(115200);
  Serial.setTimeout(5);
  TCCR4B = TCCR4B & B11111000 | B00000001;  //31kHz
  for (int i = 0; i < NUM_DRIVERS; i++) {
    pinMode(pinPWM[i], OUTPUT);
    pinMode(pinDIR[i], OUTPUT);
    pinMode(pinCURRENTSENSOR[i], INPUT);
    analogWrite(pinPWM[i], 0);
    digitalWrite(pinDIR[i], LOW);
  }
  readOffsets();

  previousWatchDogTime = millis();


}

void loop() {
  unsigned long currentWatchDogTime = millis(); // Get current time in milliseconds
  
  if (currentWatchDogTime - previousWatchDogTime <= watchDogTimeout)
  {
    controlLoop();
    
  }
  else
  {
    resetAll();
  }

}


void resetAll() {

  // Reset all arrays using memset
  resetTargetCurrents();
  resetOutputPercentages();
  applyPercentOutput();
}
