#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

#define pino_sinal_analogico A0
#define pino_led_vermelho 12
#define pino_led_amarelo 11
#define pino_led_verde 10

int valor_analogico;
float valor_ana_porcentagem;
float valor_ana_porcentagem_2;
 
void setup()
{
  Serial.begin(9600);
  pinMode(pino_sinal_analogico, INPUT);
  pinMode(pino_led_vermelho, OUTPUT);
  pinMode(pino_led_amarelo, OUTPUT);
  pinMode(pino_led_verde, OUTPUT);

  lcd.begin(16, 2); 
  lcd.setBacklight(HIGH);
  Serial.begin(9600);
  lcd.setCursor(0,0);
  lcd.print("Um. Rel.: ");
  lcd.setCursor(0,1);
  lcd.print("Status: ");
}
 
void loop()
{
  valor_analogico = analogRead(pino_sinal_analogico);
  valor_ana_porcentagem = map(valor_analogico, 1023, 0, 0, 100);
  valor_ana_porcentagem_2 = map(valor_ana_porcentagem, 65, 0, 100, 0);

  Serial.print(" Parte decimal: ");
 
  Serial.print("Porta analogica: ");
  Serial.print(valor_analogico);
  Serial.print(" Porcentagem Relativa: ");
  Serial.print(valor_ana_porcentagem_2, 0); 
  Serial.println("%"); 

 
  if (valor_analogico > 0 && valor_analogico < 400)
  {
    Serial.println("Status: Solo encharcado");
    apagaleds();
    digitalWrite(pino_led_verde, HIGH);
    respostaLcd(valor_ana_porcentagem_2, "Encharcado");
  }
 
  if (valor_analogico > 400 && valor_analogico < 800)
  {
    Serial.println("Status: Solo umido");
    apagaleds();
    digitalWrite(pino_led_amarelo, HIGH);
    respostaLcd(valor_ana_porcentagem_2, "Umido");
  }
 
  if (valor_analogico > 800 && valor_analogico < 1024)
  {
    Serial.println("Status: Solo seco");
    apagaleds();
    digitalWrite(pino_led_vermelho, HIGH);
    respostaLcd(valor_ana_porcentagem_2, "Seco");
  }
  delay(1000);
}
 
void apagaleds()
{
  digitalWrite(pino_led_vermelho, LOW);
  digitalWrite(pino_led_amarelo, LOW);
  digitalWrite(pino_led_verde, LOW);
}

void respostaLcd(int porcentagem, String estado) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Um. Rel.: ");
  lcd.print(porcentagem);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("Status: ");
  lcd.print(estado);
}