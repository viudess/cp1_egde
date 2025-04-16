// C++ code

const int ldrPin = A0;
const int ledVermelho = 2;
const int ledVerde = 3;
const int ledAmarelo = 4;
const int buzzerPin =  5; 

const int LIMITE_IDEAL = 300;
const int LIMITE_ALERTA = 400;

unsigned long TEMPO_INICIO = 0;
const long DURACAO_BUZZER = 3000;

bool BUZZER_ATIVO = false;
bool BUZZER_FINALIZADO = false;

void setup()
{
	Serial.begin(9600);
  	
  	pinMode(ledVermelho, OUTPUT);
  	pinMode(ledVerde, OUTPUT);
  	pinMode(ledAmarelo, OUTPUT);
  	pinMode(buzzerPin, OUTPUT);
  	pinMode(ldrPin, INPUT);
  
  	Serial.println("Monitorando Luminosidade");
  	
}

void loop()
{
	  int valorLdr = analogRead(ldrPin);
    Serial.println(valorLdr);
  if(valorLdr < LIMITE_IDEAL){
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, LOW);
    BUZZER_FINALIZADO = false;
  }
  else if(valorLdr < LIMITE_ALERTA) {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, HIGH);
	digitalWrite(ledVermelho, LOW);
  }
  else{
  	digitalWrite(ledVerde, LOW);
   digitalWrite(ledAmarelo, LOW);
	digitalWrite(ledVermelho, HIGH);
    if(!BUZZER_ATIVO && !BUZZER_FINALIZADO){
    	TEMPO_INICIO = millis();
      	BUZZER_ATIVO = true;
      	digitalWrite(buzzerPin, HIGH);
      Serial.println("Crítico");
    }
  }
    if (BUZZER_ATIVO && (millis() - TEMPO_INICIO >= DURACAO_BUZZER)) {
    digitalWrite(buzzerPin, LOW);
    BUZZER_ATIVO = false;
    BUZZER_FINALIZADO = true;
  }
}