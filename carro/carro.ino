// ================================================================
// ========================SERGIPE-TEC=============================

// Este codigo foi desenvolvido por @guilherme_5547 para fins de estudos.
// Para mais informações a documentação do codigo está disponivel no github: https://github.com/LuizGuilhermeSilvaa/carro-SergipeTec
// Saiba mais sobre o SergipeTec: https://sergipetec.org.br/

// ================================================================

// Importando biblioteca Servo.h.
// Para mais informações: https://www.arduino.cc/reference/en/libraries/servo/
#include <Servo.h>

// Definindo nome do servo.
// Obs: A varivel que pode ser modificada é o "servo".
Servo servo;

//Motor.
const int motorB_IN3 = 3;
const int motorB_IN4 = 5;

//Iluminação.
const int farol1 = 10;
const int farol2 = 7;
 
//Sensor frontal.
const int trigPin = 8;
const int echoPin = 9;

const int distanceMax = 25; // Definindo a distancia maxima para não bater

void setup() {

  Serial.begin(9600); // Definindo a taxa de comunicação do serial

  // Definindo as portas como OUTPUT(Saida) e INPUT (Entrada).
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  pinMode(motorB_IN3, OUTPUT); 
  pinMode(motorB_IN4, OUTPUT);
  pinMode(farol1, OUTPUT);
  pinMode(farol2, OUTPUT);

  servo.attach(2); // Porta digital do servo de direção
  servo.write(90); // Deixando a direção alinhada

  // Script que faz farol piscar ao ligar.
  digitalWrite(farol1, HIGH);
  digitalWrite(farol2, HIGH);
  delay(50); 
  digitalWrite(farol1, LOW);
  digitalWrite(farol2, LOW);
  delay(50); 
  digitalWrite(farol1, HIGH);
  digitalWrite(farol2, HIGH);
  delay(50);
  digitalWrite(farol1, LOW);
  digitalWrite(farol2, LOW);
  delay(2000);  // Espera 2 segundos antes de andar
  }

void loop() {
  long duration, distance;               // Declara duas variáveis do tipo long: 'duration' para armazenar o tempo e 'distance' para armazenar a distância calculada
  digitalWrite(trigPin, LOW);            // Define o pino de trigger (trigPin) como LOW para garantir que não haja pulso anterior
  delayMicroseconds(2);                  // Aguarda 2 microsegundos para estabilizar o pino de trigger
  digitalWrite(trigPin, HIGH);           // Define o pino de trigger como HIGH para iniciar o pulso ultrassônico
  delayMicroseconds(10);                 // Mantém o pino de trigger em HIGH por 10 microsegundos para enviar o pulso
  digitalWrite(trigPin, LOW);            // Define o pino de trigger como LOW para finalizar o pulso
  duration = pulseIn(echoPin, HIGH);     // Mede o tempo (em microsegundos) que o pino de eco (echoPin) permanece em HIGH após receber o pulso refletido
  distance = duration * 0.034 / 2;       // Converte o tempo medido em distância (em centímetros) usando a fórmula (velocidade do som é aproximadamente 0.034 cm/us)
                                         // O tempo é dividido por 2 porque o pulso viaja até o obstáculo e volta, lembre-se, é um sensor "ULTRASSONICO"

  Serial.println(distance); // Envia a distância calculada para o monitor serial, permitindo a visualização da distância medida pelo sensor

  if (distance <= distanceMax) {   // Se a distancia for menor que a distancia definida entra no IF.
    // Dar ré
    analogWrite(motorB_IN3, 0);
    analogWrite(motorB_IN4, 60);
    servo.write(55);  // Vira a direção.
    delay(350);
  }else{
    servo.write(90); // Alinha a direção.
    //Anda para frente.
    analogWrite(motorB_IN3, 90);
    analogWrite(motorB_IN4, 0);
    //Liga o farol.
    digitalWrite(farol1, HIGH);
    digitalWrite(farol2, HIGH);
  }
   delay(10);
  }
