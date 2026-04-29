//Les variables pour commander le moteur à son tour qui entraine le ventillateur
const int pinEN1 = 3;  // la broche qui modifie la largeur d'impulsion pour reguler la tension au niveau du moteur
const int pinIN1 = 4;  // Pour faire tourner le moteur dans un sens on envoie la réponse sur la broche 4
const int pinIN2 = 5;  // Pour faire tourner le moteur dans l'autre sens on envoie la réponse sur la broche 5

// les variables pour commander les lampes dans mon circuit
const int pinL1 = 13;  // la broche 13 c'est pour la commande de la lampe L1
const int pinL2 = 12;  // la broche 12 c'est pour la commande de la lampe L2
const int pinL3 = 11;  // la broche 11 c'est pour la commande de la lampe L3

// Les entrées manuelles de l'utilisateurs
const int sw1 = 2;     // bouton d'emmergence pour le moteur
const int btnB1 = 8;   // Bouton poussoir pour la lampe L1 (en allumage manuel)
const int btnB2 = 9;   // Bouton poussoir pour la lampe L2 (en allumage manuel)
const int btnB3 = 10;  // Bouton poussoir pour la lampe L3 (en allumage manuel)
const int pot = A0;    // Potentiomètre RV1 celui qui vient reguler la vitesse du moteur pour le ventillateur

//Definir les etats de toutes les lampes, nous les laissons à false pour dire qu'au repos elles sont toutes fermées
bool etatL1=false;
bool etatL2=false;
bool etatL3=false;

//Variables pour eviter les effets rebonds...
bool dernierEtatB1 = HIGH;
bool dernierEtatB2 = HIGH;
bool dernierEtatB3 = HIGH;

void setup() {
  Serial.begin(9600); // communication Bluetooth et ma carte arduino
  
  // Declaration des ports des sorties de ma carte Arduino UNO
  pinMode(pinEN1, OUTPUT); //la sortie prise pour aller reguler la vitesse du ventilateur
  pinMode(pinIN1, OUTPUT); //la sortie prise pour aller faire tourner le moteur dans un sens
  pinMode(pinIN2, OUTPUT); //la sortie prise pour aller faire tourner le moteur de le sens inverse
  pinMode(pinL1, OUTPUT); //la sotie pour alimenter la lampe1
  pinMode(pinL2, OUTPUT); //la sortie pour allumer la lampe 2
  pinMode(pinL3, OUTPUT);//la sortie pour allumer la lampe 3
  
  // Declartions des ports des ENtrées de ma carte Aduino UNO, j'utilise PULLUP pcq ils sont reliées au GND (profite de l'anti rebond)
  pinMode(sw1, INPUT_PULLUP); //le bouton d'emmergence qui donne les entrées à la carte Arduino
  pinMode(btnB1, INPUT_PULLUP); //le bouton qui donne l'ordre à la carte arduino pour allumer la L1
  pinMode(btnB2, INPUT_PULLUP); //le bouton qui donne l'ordre à la carte arduino pour allumer la L1
  pinMode(btnB3, INPUT_PULLUP);//le bouton qui donne l'ordre à la carte arduino pour allumer la L1

  //je declare comment mon moteur va tourner... si l'un sur high l'autre sur low pour changer le sens on met le premier sur low et le second sur high
  digitalWrite(pinIN1, HIGH);//les deux lignes c'est pour le sens direct
  digitalWrite(pinIN2, LOW);
}
//commençons alors la partie importante
void loop() {
  // 1. RECEVOIR LES INFORMATIONS VENANT DE KODULAR OU DU SON VOCAL
  if (Serial.available() > 0) {
    String voix = Serial.readStringUntil('\n'); //lecture de la voix en la convertissant en ecriture
    voix.trim();
    voix.toLowerCase();//conversion de l'ecriture en minuscule pour trouver la même ecriture avec celui qui est dans mon code

    // commandes pour l'allumage des lampes et leurs exteintions
        
    if (voix == "Allimer lampe 1") digitalWrite(pinL1, HIGH); //la requête qui allume la lampe 1
    if (voix == "Eteidre lampe 1") digitalWrite(pinL1, LOW); //la requête qui etteint la lampe 1
    if (voix == "L2_ON") digitalWrite(pinL2, HIGH); //la requête qui allume la lampe 2
    if (voix == "L2_OFF") digitalWrite(pinL2, LOW); //la requête qui etteint la lampe 2
    if (voix == "L3_ON") digitalWrite(pinL3, HIGH); //la requête qui allume la lampe 3
    if (voix == "L3_OFF") digitalWrite(pinL3, LOW); //la requête qui etteint la lampe 3
    if (voix == "Allumer toutes les lampes") { // pour allumer toutes les lampes de la maison 
      digitalWrite(pinL1, HIGH); digitalWrite(pinL2, HIGH); digitalWrite(pinL3, HIGH);
    }
    if (voix="Eteindre toutes les lampes"){//Eteindre toutes les lampes
      digitalWrite(pinL1, LOW); digitalWrite(pinL2, LOW); digitalWrite(pinL3, LOW);
    }
    //COMMANDE POUR LE VOCAL DU VENTILLATEUR
    if (voix.startsWith("Allumer ventillateur")){
      int vitesse=voix.substring(2).toInt();
      analogWrite(pinEN1,vitesse);
    }
  }
  // 2. BOUTONS PHYSIQUES en cliquant sur un BP si la lampe est etteinte alors elle s'allume
  if (digitalRead(btnB1) == LOW) digitalWrite(pinL1, HIGH);
  // if (digitalRead(btnB1) == )
  if (digitalRead(btnB2) == LOW) digitalWrite(pinL2, HIGH);
  if (digitalRead(btnB3) == LOW) digitalWrite(pinL3, HIGH);
  // 3. VENTILATEUR (Potentiomètre actif seulement si SW1 est fermé)
  if (digitalRead(sw1) == HIGH) {
    analogWrite(pinEN1, 0);
  }
   
  if(digitalRead(btnB1) == LOW){
    etatL1 =! etatL1;
    digitalWrite(pinL1, etatL1);
    while (digitalRead(btnB1)==LOW);
    delay(50);
   }
   
    if(digitalRead(btnB2) == LOW){
    etatL2 =! etatL2;
    digitalWrite(pinL2, etatL2);
    while (digitalRead(btnB2)==LOW);
    delay(50);
   }
   if(digitalRead(btnB3) == LOW){
    etatL3 =! etatL3;
    digitalWrite(pinL3, etatL3);
    while (digitalRead(btnB3)==LOW);
    delay(50);
   }
}
  

