# Plantagochi
Atividade Cesar School

O Plantagochi é um projeto de vaso inteligente utilizando Arduino que visa resolver o problema de esquecimento ou desconhecimento sobre as necessidades de rega das plantas. Ele serve como um "digital pet" no mundo real, monitorando a umidade do solo e indicando visualmente o estado da planta.


# Canva de Modelagem Prática
## Descrição
O Plantagochi é um projeto de vaso inteligente que visa resolver o problema de esquecimento ou desconhecimento sobre as necessidades de rega das plantas. Ele serve como um "digital pet" no mundo real, monitorando a umidade do solo e indicando visualmente o estado da planta.
A ideia é misturar características de pets digitais e colecionáveis digitais com o mundo real. Para o MVP (Mínimo Produto Viável), o projeto se concentra em fornecer uma interface local de monitoramento e rega. Futuramente, o conceito pode ser expandido para modelar diversas espécies de plantas e incluir comunicação à distância.


## Objetivos
- Monitorar continuamente a umidade do solo da planta.
- Indicar o estado de saúde/hidratação da planta de forma visual (LEDs).
- Permitir a rega manual sob demanda através de um botão.
- Servir como um MVP funcional para a ideia central de pet digital botânico.
- Resolver o problema de rega inadequada ou esquecimento por parte do usuário.

## Funcionamento
### 1. Inicialização:
O Arduino inicia, garantindo que a bomba está desligada e configurando os pinos necessários.

### 2. Monitoramento:
- O Arduino lê continuamente o valor do Sensor de Umidade do Solo.
- Indicação de Estado (LEDs): O valor lido é comparado com limiares definidos:
LED VERDE: Solo úmido (Planta feliz/satisfeita).
LED AMARELO/LARANJA: Solo seco (Planta com sede).
LED VERMELHO: Solo enxarcada (Planta sobrecarregada).

### 3. Rega:
- O Arduino monitora o estado do Botão.
- Se o Botão for pressionado, o Arduino aciona o módulo relé/transistor para ligar a Bomba de Água.
- A bomba permanece ligada por um tempo pré-definido (ou até o sensor detectar umidade suficiente).
- Após o tempo, a bomba é desligada.
- O sistema volta ao ciclo de monitoramento.

## Competências
- Programação em C/C++ (ambiente Arduino IDE).
- Eletrônica básica (leitura de esquemas, uso de resistores, LEDs, botões).
- Utilização de Sensores e Atuadores (Sensor de Umidade e Bomba d'água via Relé/Transistor).
- Pensamento Lógico (para definir a lógica de funcionamento e o código).
- Resolução de Problemas (Debug de hardware e software).

## Componentes
### Eletrônicos:
- Placa Arduino Uno
- Sensor de umidade do solo
- Bomba de água submersível (mini bomba)
- Módulo relé (para acionar a bomba)
- 3 x LEDs (Vermelho, Amarelo/Laranja, Verde)
- 3 x Resistores (para os LEDs)
- 1 x Botão (push-button)
- Jumpers e Fios
- Protoboard
- Fonte de alimentação
### Mecânicos/Estruturais:
- Vaso de planta
- Reservatório de água
- Mangueira fina (4mm)

## Protótipo
// falta colocar um esquema do prototipo (tipo print do tinkercad)

## Equipe
- Lucas Bonfim (Líder Técnico) | [Linkedin](https://br.linkedin.com/in/l-bonfim), [Github](https://github.com/l-bonfim)
- Lucas Carvalho | [Linkedin](), [Github](https://github.com/J4keless)
- Lucas Valença | [Linkedin](), [Github](https://github.com/LucasGuilhermeValenca)
- Leo Sk8 | [Linkedin](), [Github]()
- Miguel Duarte | [Linkedin](https://br.linkedin.com/in/miglitopictures), [Github](https://github.com/miglitopictures)