// Motor tracción
int motorA1 = 5;
int motorA2 = 6;

// Motor dirección
int motorB1 = 9;
int motorB2 = 10;

char comando;

void setup() {
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);

  Serial1.begin(9600); // HC-06
}

void loop() {

  if (Serial1.available()) {
    comando = Serial1.read();

    switch(comando) {

      case 'F': // Adelante
        digitalWrite(motorA1, HIGH);
        digitalWrite(motorA2, LOW);
        break;

      case 'B': // Atrás
        digitalWrite(motorA1, LOW);
        digitalWrite(motorA2, HIGH);
        break;

      case 'L': // Izquierda
        digitalWrite(motorB1, HIGH);
        digitalWrite(motorB2, LOW);
        delay(50);
        detenerDireccion();
        break;

      case 'R': // Derecha
        digitalWrite(motorB1, LOW);
        digitalWrite(motorB2, HIGH);
        delay(25);
        detenerDireccion();
        break;

      case 'S': // Stop
        detenerTodo();
        break;
    }
  }
}

void detenerTodo() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
}

void detenerDireccion() {
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
}
