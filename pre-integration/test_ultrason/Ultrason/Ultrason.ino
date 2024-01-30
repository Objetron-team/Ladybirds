/* 
 * Code d'exemple pour un capteur à ultrasons HC-SR04.
 */

/* Constantes pour les broches */
const byte TRIGGER_PIN = 9; // Broche TRIGGER
const byte ECHO_PIN = 8;   // Broche ECHO
 
/* Constantes pour le timeout */
const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = ~8m à 340m/s

/* Vitesse du son dans l'air en mm/us */
const float SOUND_SPEED = 340.0 / 1000;

/** Fonction setup() */
void setup() {
   
  /* Initialise le port série */
  Serial.begin(38400);
   
  /* Initialise les broches */
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW); // La broche TRIGGER doit être à LOW au repos
  pinMode(ECHO_PIN, INPUT);
}
 
/** Fonction loop() */
void loop() {
  
  /* 1. Lance une mesure de distance en envoyant une impulsion HIGH de 10µs sur la broche TRIGGER */
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
  /* 2. Mesure le temps entre l'envoi de l'impulsion ultrasonique et son écho (si il existe) */
  long measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);
   
  /* 3. Calcul la distance à partir du temps mesuré */
  float distance_mm = measure / 2.0 * SOUND_SPEED;
   
  Serial.print(F("Base:"));
  Serial.print(0);
  Serial.print(',');

  Serial.print(F("Max:"));
  Serial.print(3000);
  Serial.print(',');


  /* Affiche les résultats en mm, cm et m */
  Serial.print(F("Distance:"));
  Serial.println(distance_mm);

   /* Vérifie si la distance est supérieure à 10 cm */
  if (distance_mm < 1) {
    Serial.println(F("Arrêt du programme"));
    while (true) {
      // Boucle infinie pour arrêter le programme
    }
  }
  /* Délai d'attente pour éviter d'afficher trop de résultats à la seconde */
  //delay(500);
}