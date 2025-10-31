
// braccio_vertical.ino
#include <Braccio.h>
#include <Servo.h>

// Trajectòria generada des de la simulació Python
const int TRAJECTORY_SIZE = 7;
const float trajectory[TRAJECTORY_SIZE][5] = {
  {90.0, 75.0, 92.0, 90.0, 90.0},
  {90.0, 60.0, 94.0, 90.0, 90.0},
  {90.0, 45.0, 96.0, 90.0, 90.0},
  {90.0, 30.0, 98.0, 90.0, 90.0},
  {90.0, 45.0, 96.0, 90.0, 90.0},
  {90.0, 60.0, 94.0, 90.0, 90.0},
  {90.0, 75.0, 92.0, 90.0, 90.0}
};

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_ver;
Servo wrist_rot;
Servo gripper;

void setup() {
  // Inicialitza el braç Braccio
  Braccio.begin();
  
  // Obre el gripper al començament
  Braccio.ServoMovement(20, 90, 90, 90, 90, 90, 10);
  delay(1000);
  
  Serial.begin(9600);
  Serial.println("Braccio Vertical Movement - READY");
}

void loop() {
  Serial.println("🎬 Iniciant moviment vertical...");
  
  for(int i = 0; i < TRAJECTORY_SIZE; i++) {
    Serial.print("Posició ");
    Serial.print(i + 1);
    Serial.print("/");
    Serial.println(TRAJECTORY_SIZE);
    
    // Executa el moviment amb velocitat moderada
    Braccio.ServoMovement(
      30,  // Velocitat (delay entre passos)
      trajectory[i][0],  // base
      trajectory[i][1],  // shoulder
      trajectory[i][2],  // elbow
      trajectory[i][3],  // wrist_ver
      trajectory[i][4],  // wrist_rot
      73   // gripper (tancat)
    );
    
    delay(1000);  // Pausa entre posicions
  }
  
  Serial.println("✅ Moviment completat! Repetint en 3 segons...");
  delay(3000);
}
