/*
Código para el control del Robot Sumo
Curso: Máquinas Digitales con Laboratorio
Escrito por Pichardo Rico Cristian Eduardo
Última Modificación: 01 de diciembre 2023
*/

 
 //Declaramos pines del sensor ultrasónico
 #define Trigger 12
 #define Echo 11
 
 //Declaramos pines para los sensores infrarrojos
 #define Sensor_1 A0
 #define Sensor_2 A1
 #define Sensor_3 A2
 
 //DDeclaramos pines de los motores
 //Motor A
 #define ENA 5
 #define IN1 7
 #define IN2 6
 //Motor B
 #define ENB 10
 #define IN3 8
 #define IN4 9
 
 //Definimos el umbral del color blanco para el IR
 #define blanco 60
 //Definimos la distancia de la pista
 #define DisMe 50

void setup(){
 //Definimos los pines para los sensores IR:
 pinMode(Sensor_1,INPUT);
 pinMode(Sensor_2,INPUT);
 pinMode(Sensor_3,INPUT);
 
 //Definimos pines del sensor ultrasónico
 pinMode(Trigger, OUTPUT); //Trigger como salida
 pinMode(Echo, INPUT);  //Echo como entrada
 digitalWrite(Trigger, LOW);//Inicializamos el pin con 0
 
 //Definimos pines del motor como:
 pinMode (ENA, OUTPUT);
 pinMode (ENB, OUTPUT);
 pinMode (IN1, OUTPUT);
 pinMode (IN2, OUTPUT);
 pinMode (IN3, OUTPUT);
 pinMode (IN4, OUTPUT);
 
 //Tiempo de espera
 delay(5000);
}

void loop() {
 //Leemos la entrada analógica de los sensores infrarrojos
  int S_izquierda=analogRead(Sensor_1);
  int S_centro=analogRead(Sensor_2);
  int S_derecha=analogRead(Sensor_3);
  
  //Configuramos el valor de la distancia del sensor ultrasónico
  long t; //variable del tiempo que demora en llegar el eco
  long d; //variable de distancia en centimetros

  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10); //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  
  t = pulseIn(Echo, HIGH); //obtenemos el pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm

  //Condiciones según la distancia  
  if(d<=DisMe){  //Si detecta un objeto en un rango
    //Comprueba que está en la pista
    if(S_izquierda>blanco && S_centro>blanco && S_derecha>blanco){
      adelante();
    }
    //Sensor izquierdo detecta blanco
    else if(S_izquierda<=blanco && S_centro>blanco && S_derecha>blanco){
      atras();
      delay(500);
      }
    //Sensor centro detecta blanco
    else if(S_izquierda>blanco && S_centro<=blanco && S_derecha>blanco){
      adelante();
      delay(500);
      }
    //Sensor derecha detecta blanco
    else if(S_izquierda>blanco && S_centro>blanco && S_derecha<=blanco){
      atras();
      delay(500);
      }
    //Otros casos; detecte dos sensores en blanco
    else{
      atras();
      delay(500);
      }
  }
  //Si no detecta un objeto dentro de la distancia media
  else if(d>DisMe){
    //Comprueba que está en la pista
    if(S_izquierda>blanco && S_centro>blanco && S_derecha>blanco){
      vueltas();
    }
    //Sensor izquierdo detecta blanco
    else if(S_izquierda<=blanco && S_centro>blanco && S_derecha>blanco){
      atras();
      delay(500);
      }
    //Sensor centro detecta blanco
    else if(S_izquierda>blanco && S_centro<=blanco && S_derecha>blanco){
      adelante();
      delay(500);
      }
    //Sensor derecha detecta blanco
    else if(S_izquierda>blanco && S_centro>blanco && S_derecha<=blanco){
      atras();
      delay(500);
      }
    //Otros casos; detecte dos sensores en blanco
    else{
      atras();
      delay(500);
      }
  }
  //Si no detecta nada
  else{
    parar();
    delay(500);
    }
}

//Instrucciones de los motores
void adelante ()
{
 //Direccion motor A
 digitalWrite (IN1, HIGH);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 255); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, HIGH);
 digitalWrite (IN4, LOW);
 analogWrite (ENB, 255); //Velocidad motor B
}

void atras ()
{
 //Direccion motor A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, HIGH);
 analogWrite (ENA, 255); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, HIGH);
 analogWrite (ENB, 255); //Velocidad motor B
}

void vueltas ()
{
 //Direccion motor A
 digitalWrite (IN1, HIGH);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 150); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, HIGH);
 analogWrite (ENB, 150); //Velocidad motor A
}

void derecha()
{
 //Direccion motor A
 digitalWrite (IN1, HIGH);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 255); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, HIGH);
 analogWrite (ENB, 255); //Velocidad motor A
}

void izquierda()
{
 //Direccion motor A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, HIGH);
 analogWrite (ENA, 255); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, HIGH);
 digitalWrite (IN4, LOW);
 analogWrite (ENB, 255); //Velocidad motor A
}

void parar ()
{
 //Direccion motor A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 0); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, LOW);
 analogWrite (ENB, 0); //Velocidad motor A
}
