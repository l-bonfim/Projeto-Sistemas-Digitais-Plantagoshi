// Plantagochi MVP
// Para a entrega de Sistemas Digitais, decidimos limitar Plantagochi a um MVP.
// Nele, vamos utilizar (a principio) apenas um sensor de umidade de solo.
// Alem disso, tambem dispensaremos a conexao com o celular.

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 colunas e 2 linhas

// PINS
int PINO_BOMBA = 9; // NPN
int PINO_SENSOR = A1;
int PINO_BOTAO_REGA = 13;


// VARIAVEIS
// considerando a umidade mapeada de 0 a 100
int umidade_atual = 50;
// 1 = SECO / 2 = SAUDAVEL / 3 = AFOGANDO
int estado_atual = 2; // 

// variaveis da funcao de regar
unsigned long ultima_rega = 0;
unsigned long intervalo = 60000 * 15; // 15 minutos
int tempo_rega = 8000; // 5 segundos

void setup() {
  Serial.begin(9600);
  // SETUP DOS PINS
  pinMode(PINO_SENSOR, INPUT);
  pinMode(PINO_BOMBA, OUTPUT);
  pinMode(PINO_BOTAO_REGA, INPUT);
  
  // GARANTIR QUE A BOMBA COMEÇA DESLIGADA
  digitalWrite(PINO_BOMBA, LOW);

  lcd.init(); // initialize the lcd
  lcd.backlight();
  lcd.clear();                 // clear display
  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("Umidade: ");        // print message at (0, 0)

}

void loop() {
  
  umidade_atual = lerUmidade();
  // 1. Exibir Umidade e Porcentagem na Linha 0
  lcd.setCursor(0, 0);
  lcd.print("Umidade: ");
  lcd.print(umidade_atual);
  lcd.print("    ");

  estado_atual = atualizarEstado();
  enviarEstadoParaApp();
  verificarComandos(); // checa se o user apertou o BOTAO_REGA e liga a bomba dagua

  delay(500);
}

int atualizarEstado() {
  int estado;
  if (umidade_atual < 20) {
    estado = 1;          // SECO
  } else if (umidade_atual < 60) {
    estado = 2;          // SAUDAVEL
  } else {
    estado = 3;          // AFOGANDO
  }
  return estado;
}

void enviarEstadoParaApp() {

  lcd.setCursor(0, 1); // Move o cursor para o início da linha 1 (Linha de Estado)
  lcd.print("Estado: "); // Rótulo para o estado
  // Essa funcao indica o estado da planta com o lcd, em vez de indicar via notficacao no celular.

  switch (estado_atual) {
    case 1: // SECO
      lcd.setCursor(0, 1);     
      lcd.print("SECO      ");
      break;

    case 2: // SAUDAVEL
      lcd.setCursor(0, 1);     
      lcd.print("SAUDAVEL  ");
      break;

    case 3: // AFOGANDO
      lcd.setCursor(0, 1);    
      lcd.print("AFOGANDO  ");
      break;
  }
}

int lerUmidade() {
  // ler o sensor e mapear a umidade para um valor utilizavel
  int umidade_cru = analogRead(PINO_SENSOR);
  int umidade = map(umidade_cru, 0, 1023, 255, 0);
  return umidade;
}

void verificarComandos() {
  // aqui a gente le o estado do BOTAO_REGA e inicia a rega se tiver apertado
  int botao_rega_estado = digitalRead(PINO_BOTAO_REGA);
  
  if (botao_rega_estado == LOW) {
    Serial.println("Apertou o botao");
    iniciarRega();
  }
}

void iniciarRega() {
  // inicia o ciclo de rega
  if (estado_atual == 1) { // checa se foi regado a pouco tempo ou se a planta esta seca, para nao enxarcar
    ligarBomba();
    delay(tempo_rega);
    desligarBomba();
  }
}

void ligarBomba() {
  // Serial.println(" deviria ligar a bomba ");
  digitalWrite(PINO_BOMBA, HIGH);
}

void desligarBomba() {
  // Serial.println(" desligar a bomba ");
  digitalWrite(PINO_BOMBA, LOW);
}