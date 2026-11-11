// --- Pin Definitions for 3 Optical Encoders on Arduino Mega ---
// Encoder 1
const int enc1_pinA = 2; 
const int enc1_pinB = 3; 

// Encoder 2
const int enc2_pinA = 18;
const int enc2_pinB = 19;

// Encoder 3
const int enc3_pinA = 20;
const int enc3_pinB = 21;

// --- Position Variables ---
// Marked 'volatile' because they are changed inside Interrupt Service Routines (ISRs)
volatile long enc1_pos = 0;
volatile long enc2_pos = 0;
volatile long enc3_pos = 0;

void setup() {
  Serial.begin(115200);
  
  // Set all encoder pins as inputs with internal pull-up resistors enabled
  pinMode(enc1_pinA, INPUT_PULLUP);
  pinMode(enc1_pinB, INPUT_PULLUP);
  
  pinMode(enc2_pinA, INPUT_PULLUP);
  pinMode(enc2_pinB, INPUT_PULLUP);
  
  pinMode(enc3_pinA, INPUT_PULLUP);
  pinMode(enc3_pinB, INPUT_PULLUP);

  // --- Attach Interrupts ---
  // We trigger on 'CHANGE' to catch both rising and falling edges for maximum resolution
  
  // Encoder 1 Interrupts
  attachInterrupt(digitalPinToInterrupt(enc1_pinA), isr_enc1A, CHANGE);
  attachInterrupt(digitalPinToInterrupt(enc1_pinB), isr_enc1B, CHANGE);
  
  // Encoder 2 Interrupts
  attachInterrupt(digitalPinToInterrupt(enc2_pinA), isr_enc2A, CHANGE);
  attachInterrupt(digitalPinToInterrupt(enc2_pinB), isr_enc2B, CHANGE);

  // Encoder 3 Interrupts
  attachInterrupt(digitalPinToInterrupt(enc3_pinA), isr_enc3A, CHANGE);
  attachInterrupt(digitalPinToInterrupt(enc3_pinB), isr_enc3B, CHANGE);

  Serial.println("Encoder System Initialized.");
}

void loop() {
  // Briefly disable interrupts to safely copy the volatile position variables
  noInterrupts();
  long pos1 = enc1_pos;
  long pos2 = enc2_pos;
  long pos3 = enc3_pos;
  interrupts();

  // Print the positions to the Serial Monitor
  Serial.print("E1: "); Serial.print(pos1);
  Serial.print(" | E2: "); Serial.print(pos2);
  Serial.print(" | E3: "); Serial.println(pos3);
  
  delay(100); // Small delay to make the serial output readable
}

// =========================================================================
// INTERRUPT SERVICE ROUTINES (ISRs)
// These functions run automatically in the background whenever a pin changes state.
// They determine direction by comparing the state of Pin A to Pin B.
// =========================================================================

// --- Encoder 1 ISRs ---
void isr_enc1A() {
  if (digitalRead(enc1_pinA) == digitalRead(enc1_pinB)) {
    enc1_pos++;
  } else {
    enc1_pos--;
  }
}
void isr_enc1B() {
  if (digitalRead(enc1_pinA) != digitalRead(enc1_pinB)) {
    enc1_pos++;
  } else {
    enc1_pos--;
  }
}

// --- Encoder 2 ISRs ---
void isr_enc2A() {
  if (digitalRead(enc2_pinA) == digitalRead(enc2_pinB)) {
    enc2_pos++;
  } else {
    enc2_pos--;
  }
}
void isr_enc2B() {
  if (digitalRead(enc2_pinA) != digitalRead(enc2_pinB)) {
    enc2_pos++;
  } else {
    enc2_pos--;
  }
}

// --- Encoder 3 ISRs ---
void isr_enc3A() {
  if (digitalRead(enc3_pinA) == digitalRead(enc3_pinB)) {
    enc3_pos++;
  } else {
    enc3_pos--;
  }
}
void isr_enc3B() {
  if (digitalRead(enc3_pinA) != digitalRead(enc3_pinB)) {
    enc3_pos++;
  } else {
    enc3_pos--;
  }
}