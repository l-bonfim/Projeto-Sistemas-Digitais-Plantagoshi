// Plantagochi MVP
// Para a entrega de Sistemas Digitais, decidimos limitar Plantagochi a um MVP.
// Nele, vamos utilizar (a principio) apenas um sensor de umidade de solo.
// Alem disso, tambem dispensaremos a conexao com o celular.

// PINS
int PINO_BOMBA = 9;
int PINO_SENSOR = A1;
int PINO_BOTAO_REGA = 13;

int PINO_LED_1 = 1;
int PINO_LED_2 = 2;
int PINO_LED_3 = 3;

// VARIAVEIS
// considerando a umidade mapeada de 0 a 100
int umidade_atual = 50;
// 1 = SECO / 2 = SAUDAVEL / 3 = AFOGANDO
int estado_atual = 2; // 

// variaveis da funcao de regar
unsigned long ultima_rega = 0;
unsigned long intervalo = 60000 * 15; // 15 minutos
int tempo_rega = 5000; // 5 segundos

void setup() {
  Serial.begin(9600);
  // SETUP DOS PINS
  pinMode(PINO_SENSOR, INPUT);
  pinMode(PINO_BOMBA, OUTPUT);
  pinMode(PINO_LED_1, OUTPUT);
  pinMode(PINO_LED_2, OUTPUT);
  pinMode(PINO_LED_3, OUTPUT);
  pinMode(PINO_BOTAO_REGA, INPUT);
  
  // GARANTIR QUE A BOMBA COMEÇA DESLIGADA
  digitalWrite(PINO_BOMBA, LOW);
}

void loop() {
  umidade_atual = lerUmidade();
  estado_atual = atualizarEstado();
  enviarEstadoParaApp();
  verificarComandos(); // checa se o user apertou o BOTAO_REGA e liga a bomba dagua

  // Serial.print("Umidade Atual: ");
  // Serial.println(umidade_atual);

  // Serial.print("Estado atual: ");
  // Serial.println(estado_atual);

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
  // Essa funcao indica o estado da planta com leds, em vez de indicar via notficacao no celular.
  switch (estado_atual) {
    case 1: // SECO
      digitalWrite(PINO_LED_1, HIGH);
      digitalWrite(PINO_LED_2, LOW);
      digitalWrite(PINO_LED_3, LOW);
      break;

    case 2: // SAUDAVEL
      digitalWrite(PINO_LED_1, LOW);
      digitalWrite(PINO_LED_2, HIGH);
      digitalWrite(PINO_LED_3, LOW);
      break;

    case 3: // AFOGANDO
      digitalWrite(PINO_LED_1, LOW);
      digitalWrite(PINO_LED_2, LOW);
      digitalWrite(PINO_LED_3, HIGH);
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
  // if (umidade_atual < 50 && millis() - ultima_rega > intervalo) { // checa se foi regado a pouco tempo ou se a planta esta seca, para nao enxarcar
  //   ligarBomba();
  //   delay(tempo_rega);
  //   desligarBomba();
  //   ultima_rega = millis();
  // }
  ligarBomba();
  delay(5000);
  desligarBomba();
  ultima_rega = millis();
  // if (estado_atual == 1) { // checa se foi regado a pouco tempo ou se a planta esta seca, para nao enxarcar
  //   ligarBomba();
  //   delay(10000);
  //   desligarBomba();
  //   ultima_rega = millis();
  // }
}

void ligarBomba() {
  Serial.println(" deviria ligar a bomba ");
  digitalWrite(PINO_BOMBA, HIGH);
}

void desligarBomba() {
  Serial.println(" desligar a bomba ");
  digitalWrite(PINO_BOMBA, LOW);
}

