// -----------------------------
// Déclaration des broches
// -----------------------------
int BP = 3;                 // Bouton poussoir connecté à la broche 3
int LED1_rouge = 4;         // LED rouge sur la broche 4
int LED_verte = 5;          // LED verte sur la broche 5

// -----------------------------
// Variables de gestion du temps
// -----------------------------
unsigned long tempsAppui = 0;     // Stocke le moment où le bouton est pressé
unsigned long dernierTempsRebond=0; //pour mon anti-rebond
unsigned long delaiAntiRebond=80; //Délai de 50ms pour l'Anti-rebond
unsigned long dureeAppui = 0;     // Durée pendant laquelle le bouton est maintenu appuyé
bool boutonAppuye = false;        // Indique si le bouton est en cours d'appui

void setup() {
  // Initialisation des broches
  pinMode(BP, INPUT_PULLUP);      // Bouton en entrée avec résistance interne (actif à LOW)
  pinMode(LED1_rouge, OUTPUT);    // LED rouge en sortie
  pinMode(LED_verte, OUTPUT);     // LED verte en sortie

  // Initialisation de la communication série
  Serial.begin(9600);             // Démarrage du moniteur série à 9600 bauds
  Serial.println("Initialisation...");
}

void loop() {

  // -----------------------------
  // Détection de l'appui du bouton
  // -----------------------------
  if (digitalRead(BP) == LOW && boutonAppuye == false && (millis()-dernierTempsRebond)>delaiAntiRebond) {
    // Si le bouton vient d'être pressé (front descendant)
    boutonAppuye = true;               // On indique que le bouton est maintenant appuyé
    tempsAppui = millis();             // On enregistre le temps de début d'appui
    dernierTempsRebond=millis();        //la réinitialisation du miniteur de rebond  pour le prochain appuis
  }

  // -----------------------------
  // Détection du relâchement
  // -----------------------------
  if (digitalRead(BP) == HIGH && boutonAppuye == true && (millis()-dernierTempsRebond)>delaiAntiRebond) {
    // Si le bouton vient d'être relâché (front montant)
    boutonAppuye = false;              // On indique que le bouton n'est plus appuyé
    dernierTempsRebond=millis()-tempsAppui;

    // Calcul de la durée d'appui
    dureeAppui = millis() - tempsAppui;

    // Affichage de la durée dans le moniteur série
    Serial.print("Durée appui (ms) = ");
    Serial.println(dureeAppui);

    // -----------------------------
    // Décision selon la durée
    // -----------------------------
    if (dureeAppui > 0 && dureeAppui < 1000) {
      // Si appui court (< 1 seconde)
      
      digitalWrite(LED1_rouge, HIGH);   // Allumer la LED rouge
      delay(2000);                      // La laisser allumée pendant 2 secondes
      digitalWrite(LED1_rouge, LOW);    // Éteindre la LED rouge
    }
    else if (dureeAppui >= 1000) {
      // Si appui long (>= 1 seconde)
      
      digitalWrite(LED_verte, HIGH);    // Allumer la LED verte
      delay(4000);                      // La laisser allumée pendant 4 secondes
      digitalWrite(LED_verte, LOW);     // Éteindre la LED verte
    }
  }
}