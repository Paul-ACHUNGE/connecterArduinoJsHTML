/*
 * This file receives a Serial value of "1" or "0" and changes the light based on
 * that value. 
 */  

// Define the port for the LED
int lightPin = 2;
 
void setup() 
{ 
  
  // Initialize the light pin
  pinMode(lightPin, OUTPUT);
  
  // Initialize the Serial
  Serial.begin(9600);
  
}

void loop() {
  
  // CHeck to see if Serial data is being received
  if (Serial.available() > 0) {
    
    // Create a new string variable to receive Serial data
    String receivedString = "";
    
    // Loop through received data and append to the receivedString variable
    while (Serial.available() > 0) {
      receivedString += char(Serial.read ());
    }
    
    // Print received Serial data
    Serial.println(receivedString);
    
    // Change LED status based on received data
    if(receivedString == "1")
      digitalWrite(lightPin,HIGH);  
    else
      digitalWrite(lightPin,LOW);
    
  }

}


//GESTION DE 4 SOURCES D'ALIMENTATION
//Declaration des broches des mes 4sources, Virunga sur la broche 4, SNEL sur 5, Panneau Solaire sur 6, Nuru sur 7
const int virunga=4;
const int SNEL=5;
const int panneau=6;
const int NURU=7;

//declaration des broches de capteur de presence de mes sources, Presence virunga 8, presence SNEL 9, presence panneau 10, presence Nuru 11
const int presVirunga=8;
const int presSNEL=9;
const int presPanneau=10;
const int presNuru=11;

//Declaration de mes functions
void setup() {
  Serial.begin(9600);
  //Ces broches send l'ifo au relais (une petite tension)
  pinMode(virunga, OUTPUT);
  pinMode(SNEL, OUTPUT);
  pinMode(panneau, OUTPUT);
  pinMode(NURU, OUTPUT);

  //ces broches recoivent l'info sur la presence ou l'absence du courant
  pinMode(presVirunga, INPUT_PULLUP);
  pinMode(presSNEL, INPUT_PULLUP);
  pinMode(presPanneau, INPUT_PULLUP);
  pinMode(presNuru, INPUT_PULLUP);

  EteindreTout(); //comme le schema se fait au repos j'éteins toutes les sources...
}

void loop() { //pour moi Low=source presente car j'ai utilisé PULLUP qui envoit HIGH avec rien et LOW avec presence de tension
  bool VirungaDispo=(digitalRead(presVirunga)==LOW); //envoi un boolean Vrai si presVirunga donne LOW donc (virunga est disponible) sinon Faux
  bool snelDispo=(digitalRead(presSNEL)==LOW);
  bool panneauDispo=(digitalRead(presPanneau)==LOW);
  bool nuruDispo=(digitalRead(presNuru)==LOW);

  //je commence par prioriser panneau solaire car c'est presque gratuit...
  if(panneauDispo){ //si panneauDispo renvoi Vrai alors  faire
      activersource(panneau, "Vous utilisez le panneau solaire comme source");
  }
  else if(snelDispo){ //sinon si snel est dispo alors 
      activersource(SNEL, "Vous utilisez la source SNEL");
  }
  else if(nuruDispo){
      activersource(NURU, "Vous êtes sur NURU comme source");
  }
  else if(VirungaDispo){
      activersource(virunga, "Virung vous alimente, prenez soin d'économiser la source");
  }
  else{
    EteindreTout();
    Serial.println("Aucune source n'est disponible désolé");
  }
delay(1000); //1 seconde pour passer d'une source à une autre
}

//mes fonctions utilisées ci-haut
void activersource(int pinRelais, String message){
  //pour ne pas faire de court-circuit je coupe tout en premier
  EteindreTout();
  //j'active alors celui envoyé dans par priorité
  digitalWrite(pinRelais, HIGH);
  //j'affiche le msg en utulisant
  Serial.println(message);
}
void EteindreTout(){
  digitalWrite(virunga, LOW);
  digitalWrite(SNEL,LOW);
  digitalWrite(panneau, LOW);
  digitalWrite(NURU, LOW);
}