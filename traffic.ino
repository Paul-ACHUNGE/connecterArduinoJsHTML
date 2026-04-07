/* CE CODE PERMET LE FONCTIONNEMENT D'UN FEU DE CIRCULATION
ROUTIERE ET SA MISE HORS SERVICE*/
//definir la broche 4 comme sortie du feu rouge
int ledred=4; 
int ledred2=6; 
//definir la broche 3 comme sortie du feu jaune
int ledyellow=3;
//definir la broche 2 comme sortie du feu vert 
int ledgreen=13;
int ledgreen2=8; 
int ledPieton =5;
int switchPin = 2;

volatile int state = HIGH;
int OnOff = 1;//pour détecter la fin de l'interruption

void setup()
{
   pinMode(ledred,OUTPUT);//definir la broche ledred comme sortie
   pinMode(ledyellow,OUTPUT);
   pinMode(ledgreen,OUTPUT);
   pinMode(ledred2,OUTPUT);//definir la broche ledred comme sortie
   pinMode(ledgreen2,OUTPUT);
   pinMode(ledPieton,OUTPUT);
   pinMode(switchPin, INPUT_PULLUP);
   Serial.begin(9600);
   attachInterrupt(0, arret, FALLING);
}

void arret(){
  state = !state;//routine d'interruption
  }

void loop()
{
  if(state == HIGH){
    Serial.println("En Fonctionnement...");
    digitalWrite(ledPieton, LOW);
    digitalWrite(ledgreen,HIGH);
    digitalWrite(ledgreen2,LOW);
    digitalWrite(ledred,LOW);
    digitalWrite(ledred2,HIGH);
    digitalWrite(ledyellow,LOW);
   delay(3000);
   digitalWrite(ledyellow,HIGH);
   delay(2000);
   //circulation deuxieme artere
   digitalWrite(ledPieton, LOW);
    digitalWrite(ledgreen,LOW);
    digitalWrite(ledgreen2,HIGH);
    digitalWrite(ledred,HIGH);
    digitalWrite(ledred2,LOW);
    digitalWrite(ledyellow,LOW);
   delay(3000);
   digitalWrite(ledyellow,HIGH);
   delay(2000);
   OnOff = 1;
  }  
  else if (state == LOW){
   
    if (OnOff == 1){
    Serial.println("PASSAGE PIETON...");
    digitalWrite(ledgreen, LOW);
    digitalWrite(ledgreen2, LOW);
    digitalWrite(ledred, HIGH);
    digitalWrite(ledred2, HIGH);
    digitalWrite(ledyellow, LOW);
    digitalWrite(ledPieton, HIGH);
    delay(5000);
    digitalWrite(ledred, LOW);
    digitalWrite(ledred2, LOW);
    digitalWrite(ledPieton, LOW);
    OnOff = 0;
    state=HIGH;
    }
    }
}
