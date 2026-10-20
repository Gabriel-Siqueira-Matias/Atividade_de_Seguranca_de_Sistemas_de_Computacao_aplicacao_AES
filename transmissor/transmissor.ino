#include <Arduino.h>
#include <stdint.h>
#include <string.h>


// Tabela S-box
static const uint8_t sbox[256] = {
  0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
  0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
  0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
  0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
  0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
  0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
  0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
  0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
  0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
  0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
  0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
  0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
  0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
  0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
  0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
  0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};


// Tabela Rcon
static const uint8_t rcon[11] = {
  0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36
};


// Função para aplicar a multiplicação em xtime (multiplica um byte por 2)
inline uint8_t xtime(uint8_t a) {
  // Guarda se o byte 'a', possui no bit mais a esquerda o valor 1
  uint8_t verificacao = (a & 0x80);
  // Desloca todos os bits do byte 'a', uma para casa para esquerda
  a <<= 1;
  // Verifica se o byte 'a' antes do deslocamento tinha no bit mais a esquerda o valor 1
  if (verificacao) {
    // Soma o byte 'a' ao byte 0x1b
    a ^= 0x1b;
  }
  return a;
}


// Função para aplicar a multiplicação no corpo de Galois GF(2^8) (serve para aplicar a multiplicação entre dois bytes)
inline uint8_t multiplicacaoGF(uint8_t a, uint8_t b) {
  // Guarda o valor final
  uint8_t f = 0;
  // multiplicação do byte 'a' por cada bit do byte 'b'
  for (int i = 0; i < 8; i++) {
    // Verifica se o byte 'b' é impar (possui no bit mais a direita o valor 1)
    if (b & 1) {
      // Soma o byte 'a' anterior ao byte 'f'
      f ^= a;
    }
    // Aplicação do xtime ao byte 'a'
    a = xtime(a);
    // Desloca todos os bits do byte 'b', uma para casa para direita
    b >>= 1;
  }
  return f;
}


// Função para emitir o texto em hexadecimal no monitor serial
void imprimirHex(const uint8_t* texto, int tam) {
  for (int i = 0; i < tam; i++) {
    // Verifica se o byte tem valor abaixo de 0x10
    if (texto[i] < 0x10) {
      Serial.print("0");
    }
    // Emite o texto
    Serial.print(texto[i], HEX);
  }
  Serial.println();
}


// Função para aplicar a etapa rotWord do keyExpansion, desloca todos os bytes da palavra uma casa para esquerda
inline void rotWord(uint8_t* word) {
  uint8_t t = word[0];
  word[0] = word[1];
  word[1] = word[2];
  word[2] = word[3];
  word[3] = t;
}


// Função para aplicar a etapa subWord do keyExpansion, substitui os bytes da palavra segundo a tabela S-box
inline void subWord(uint8_t* word) {
  word[0] = sbox[word[0]];
  word[1] = sbox[word[1]];
  word[2] = sbox[word[2]];
  word[3] = sbox[word[3]];
}


// Função para aplicar a etapa XOR com Rcon do keyExpansion, faz XOR entre o primeiro byte da palavra pelo byte Rcon da rodada
inline void aplicaXorRcon(uint8_t* word, int i) {
  word[0] ^= rcon[i / 4];
}


// Função para expansão da chave original
inline void keyExpansion(const uint8_t* chave, uint8_t* w) {
  // Formação da word 0 (w[0-3]) a word 3 (w[12-15])
  for(int i = 0; i < 16; i++) {
    w[i] = chave[i];
  }
  // Formação das demais words (de 4 a 43)
  uint8_t temporario[4];
  for(int i = 4; i < 44; i++) {
    // Guarda a word anterior (i-1)
    temporario[0] = w[(i-1)*4 + 0];
    temporario[1] = w[(i-1)*4 + 1];
    temporario[2] = w[(i-1)*4 + 2];
    temporario[3] = w[(i-1)*4 + 3];
    // Verifica se é a primeira word de uma nova chave
    if(i % 4 == 0) {
      // Aplica as etapas para gerar os dados para forma a primeira palavra de uma nova chave
      rotWord(temporario);
      subWord(temporario);
      aplicaXorRcon(temporario, i);
    }
    // Formação de uma nova word aplicando XOR com a word de 4 posições atrás (i-4)
    w[i*4 + 0] = w[(i-4)*4 + 0] ^ temporario[0];
    w[i*4 + 1] = w[(i-4)*4 + 1] ^ temporario[1];
    w[i*4 + 2] = w[(i-4)*4 + 2] ^ temporario[2];
    w[i*4 + 3] = w[(i-4)*4 + 3] ^ temporario[3];
  }
}


// Função para aplicar a etapa AddRoundKey do AES, faz XOR entre a matriz estado e a chave da rodada
inline void addRoundKey(uint8_t estado[4][4], const uint8_t* roundKey) {
  for(int c = 0; c < 4; c++) {
    for(int l = 0; l < 4; l++) {
      estado[l][c] ^= roundKey[c*4 + l];
    }
  }
}


// Função para aplicar a etapa SubBytes do AES, substitui os bytes da matriz estado segundo a tabela S-box
inline void subBytes(uint8_t estado[4][4]) {
  for(int l = 0; l < 4; l++) {
    for(int c = 0; c < 4; c++) {
      estado[l][c] = sbox[estado[l][c]];
    }
  }
}


// Função para aplicar a etapa ShiftRows do AES, desloca as linhas da matriz estado
inline void shiftRows(uint8_t estado[4][4]) {
  uint8_t temporario;
  // linha 1, desloca 1 casa para esquerda
  temporario = estado[1][0];
  estado[1][0] = estado[1][1];
  estado[1][1] = estado[1][2];
  estado[1][2] = estado[1][3];
  estado[1][3] = temporario;
  // linha 2, desloca 2 casa para esquerda
  temporario = estado[2][0];
  estado[2][0] = estado[2][2];
  estado[2][2] = temporario;
  temporario = estado[2][1];
  estado[2][1] = estado[2][3];
  estado[2][3] = temporario;
  // linha 3, desloca 3 casa para esquerda
  temporario = estado[3][3];
  estado[3][3] = estado[3][2];
  estado[3][2] = estado[3][1];
  estado[3][1] = estado[3][0];
  estado[3][0] = temporario;
}


// Função para aplicar a etapa MixColumns do AES, multiplica a matriz estado pela matriz MixColumns, matriz MixColumns x matriz estado
// A matriz MixColumns é resultante de a(x) * modulo(x^4 + 1), sendo a(x) = {03}x^3 + {01}x^2 + {01}x + {02}
inline void mixColumns(uint8_t estado[4][4]) {
  uint8_t coluna[4];
  // Percorre cada coluna da matriz estado
  for(int i = 0; i < 4; i++) {
    // Guarda os valores da coluna atual
    coluna[0] = estado[0][i];
    coluna[1] = estado[1][i];
    coluna[2] = estado[2][i];
    coluna[3] = estado[3][i];
    // Realiza a multiplicação entre a coluna atual da matriz estado com a respectiva coluna atual da matriz MixColumns 
    estado[0][i] = multiplicacaoGF(coluna[0], 0x02) ^ multiplicacaoGF(coluna[1], 0x03) ^ coluna[2] ^ coluna[3];
    estado[1][i] = coluna[0] ^ multiplicacaoGF(coluna[1], 0x02) ^ multiplicacaoGF(coluna[2], 0x03) ^ coluna[3];
    estado[2][i] = coluna[0] ^ coluna[1] ^ multiplicacaoGF(coluna[2], 0x02) ^ multiplicacaoGF(coluna[3], 0x03);
    estado[3][i] = multiplicacaoGF(coluna[0], 0x03) ^ coluna[1] ^ coluna[2] ^ multiplicacaoGF(coluna[3], 0x02);
  }
}


// Função para converter a matriz de estado para vetor linear
void estadoParaLinear(uint8_t estado[4][4], uint8_t* saida) {
  for(int c = 0; c < 4; c++) {
    for(int l = 0; l < 4; l++) {
      saida[c*4 + l] = estado[l][c];
    }
  }
}


// Função para criptografar a mensagem
inline void criptografar(const uint8_t* entrada, uint8_t* saida, const uint8_t* w, bool bloco0) {
  // Guarda a mensagem de entrada na matriz estado
  uint8_t estado[4][4];
  for(int c = 0; c < 4; c++) {
    for(int l = 0; l < 4; l++) {
      estado[l][c] = entrada[c*4 + l];
    }
  }

  // Executa a rodada 0
  addRoundKey(estado, w);
  // Guarda a versão vetor linear da matriz estado
  uint8_t temporarioLinear[16];
  // Verifica se é o primeiro bloco da msg
  if(bloco0) {
    // Emite mensagem para o monitor serial
    Serial.println("\n--- TRANSFORMAÇÃO DA RODADA 0 E RODADA 1 DO BLOCO 0 ---");
    estadoParaLinear(estado, temporarioLinear);
    Serial.print("(1) AddRoundKey (rodada 0) (chave 0): ");
    imprimirHex(temporarioLinear, 16);
  }

  // Executa a rodada 1
  subBytes(estado);
  // Verifica se é o primeiro bloco da msg
  if(bloco0) {
    // Emite mensagem para o monitor serial
    estadoParaLinear(estado, temporarioLinear);
    Serial.print("(2) SubBytes (rodada 1):              ");
    imprimirHex(temporarioLinear, 16);
  }
  shiftRows(estado);
  // Verifica se é o primeiro bloco da msg
  if(bloco0) {
    // Emite mensagem para o monitor serial
    estadoParaLinear(estado, temporarioLinear);
    Serial.print("(3) ShiftRows (rodada 1):             ");
    imprimirHex(temporarioLinear, 16);
  }
  mixColumns(estado);
  // Verifica se é o primeiro bloco da msg
  if(bloco0) {
    // Emite mensagem para o monitor serial
    estadoParaLinear(estado, temporarioLinear);
    Serial.print("(4) MixColumns (rodada 1):            ");
    imprimirHex(temporarioLinear, 16);
  }
  addRoundKey(estado, w + 16);
  // Verifica se é o primeiro bloco da msg
  if(bloco0) {
    // Emite mensagem para o monitor serial
    estadoParaLinear(estado, temporarioLinear);
    Serial.print("(5) AddRoundKey (rodada 1) (chave 1): ");
    imprimirHex(temporarioLinear, 16);
    Serial.println("\n----------------------------------------------------------------------------------------------------");
  }

  // Executa as rodadas 2 a 9
  for(int rodada = 2; rodada < 10; rodada++) {
    subBytes(estado);
    shiftRows(estado);
    mixColumns(estado);
    addRoundKey(estado, w + rodada*16);
  }

  // Executa a rodada 10
  subBytes(estado);
  shiftRows(estado);
  addRoundKey(estado, w + 10*16);

  // Guarda a mensagem criptografada na saida
  estadoParaLinear(estado, saida);
}


// Função para aplicar o preenchimento pkcs#7
inline int pkcs7Fazer(const uint8_t* entrada, int entradaTam, uint8_t* saida) {
  // Determina quantos bytes faltam para formar um bloco de 16 bytes
  int valorPreenchimento = 16 - (entradaTam % 16);
  // Determina o total de bytes após preencher
  int saidaTam = entradaTam + valorPreenchimento;
  // Determina o tamanho da saida e guarda a mensagem de entrada nela
  memcpy(saida, entrada, entradaTam);
  // Aplica o preenchimento na saida
  for(int i = entradaTam; i < saidaTam; i++) {
    saida[i] = valorPreenchimento;
  }
  return saidaTam;
}


// Setagem dos pinos de comunicação
#define RXD2 16
#define TXD2 17


// Dados basicos
const char* matriculaA = "2023278440020";
const char* matriculaB = "2023278440026";
const char* chaveMatriculaA = "78440020";
const char* chaveMatriculaB = "78440026";


void setup() {
  // Inicia as conexões serial
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  Serial.println("====================================================================================================");
  Serial.println("                                     Transmissor AES pronto.");
  Serial.println("                       Digite 'enviar' no Monitor Serial e aperte Enter.");
  Serial.println("====================================================================================================");
}


void loop() {
  // Verifica se tem dados no canal serial
  if (Serial.available() > 0) {
    String comando = Serial.readStringUntil('\n');
    comando.trim();
    // Verifica se o comando digitado for "enviar"
    if (comando.equalsIgnoreCase("enviar")) {
      Serial.println("\n--- [TRANSMISSOR] PROCESSANDO E ENVIANDO DADOS ---");

      // Cria a chave original
      char chaveTexto[17];
      memcpy(chaveTexto, chaveMatriculaA, 8);
      memcpy(chaveTexto + 8, chaveMatriculaB, 8);
      chaveTexto[16] = '\0';
      Serial.print("Chave em texto: ");
      Serial.println(chaveTexto);
      // Converte a chave de texto para um formato de bytes
      uint8_t chave[16];
      memcpy(chave, chaveTexto, 16);
      Serial.print("Chave em bytes: ");
      imprimirHex(chave, 16);

      // Guarda a mensagem
      char msg[64];
      int msgTam = sprintf(msg, "A:%s;B:%s", matriculaA, matriculaB);
      Serial.print("Mensagem: ");
      Serial.println(msg);
      Serial.print("Mensagem em bytes: ");
      imprimirHex((uint8_t*)msg, msgTam);

      // Aplicação do preenchimento pkcs#7
      uint8_t msgPreenchida[64];
      int msgPreenchidaTam = pkcs7Fazer((uint8_t*)msg, msgTam, msgPreenchida);
      int qntBlocos = msgPreenchidaTam / 16;
      Serial.print("Mensagem em bytes (com PKCS#7): ");
      imprimirHex(msgPreenchida, msgPreenchidaTam);

      // Aplicação da expansão da chave original
      uint8_t w[176];
      keyExpansion(chave, w);
      Serial.print("Chave da rodada 0: ");
      imprimirHex(w, 16);
      Serial.print("Chave da rodada 1: ");
      imprimirHex(w + 16, 16);

      // Aplicação da criptografia da mensagem
      uint8_t msgCriptografada[64];
      for(int i = 0; i < qntBlocos; i++) {
        criptografar(msgPreenchida + (i * 16), msgCriptografada + (i * 16), w, (i == 0));
      }
      Serial.print("Mensagem criptografada: ");
      imprimirHex(msgCriptografada, msgPreenchidaTam);

      // Transmite a mensagem
      Serial2.write(0xAA);
      Serial2.write((uint8_t)qntBlocos);
      Serial2.write(msgCriptografada, msgPreenchidaTam);
      Serial.println("Mensagem enviada com sucesso");
      Serial.println("----------------------------------------------------------------------------------------------------");
    } else {
      // Emite mensagem de aviso para comandos inválidos
      Serial.println("Comando desconhecido. Digite 'enviar' para transmitir.");
    }
  }
}