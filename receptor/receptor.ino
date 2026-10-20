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


// Tabela inversa S-box
static const uint8_t rsbox[256] = {
  0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
  0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
  0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
  0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
  0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
  0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
  0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
  0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
  0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
  0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
  0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
  0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
  0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
  0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
  0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
  0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
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


// Função parar emitir o texto em hexadecimal no monitor serial
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


// Função para expandir a chave original
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


// Função para aplicar a etapa inversa do SubBytes, substitui os bytes da matriz estado segundo a tabela inversa da S-box
inline void invSubBytes(uint8_t estado[4][4]) {
  for(int l = 0; l < 4; l++) {
    for(int c = 0; c < 4; c++) {
      estado[l][c] = rsbox[estado[l][c]];
    }
  }
}


// Função para aplicar a etapa inversa do ShiftRows, redesloca as linhas da matriz estado
inline void invShiftRows(uint8_t estado[4][4]) {
  uint8_t temporario;
  // linha 1, desloca 1 casa para direita
  temporario = estado[1][3];
  estado[1][3] = estado[1][2];
  estado[1][2] = estado[1][1];
  estado[1][1] = estado[1][0];
  estado[1][0] = temporario;
  // linha 2, desloca 2 casa para direita
  temporario = estado[2][0];
  estado[2][0] = estado[2][2];
  estado[2][2] = temporario;
  temporario = estado[2][1];
  estado[2][1] = estado[2][3];
  estado[2][3] = temporario;
  // linha 3, desloca 3 casa para direita
  temporario = estado[3][0];
  estado[3][0] = estado[3][1];
  estado[3][1] = estado[3][2];
  estado[3][2] = estado[3][3];
  estado[3][3] = temporario;
}


// Função para aplicar a etapa inversa do MixColumns, multiplica a matriz estado pela matriz InvMixColumns, matriz InvMixColumns x matriz estado
// A matriz InvMixColumns é resultante de d(x) * modulo(x^4 + 1), sendo d(x) = {0B}x^3 + {0D}x^2 + {09}x + {0E}
inline void invMixColumns(uint8_t estado[4][4]) {
  uint8_t coluna[4];
  // Percorre cada coluna da matriz estado
  for(int i = 0; i < 4; i++) {
    // Guarda os valores da coluna atual
    coluna[0] = estado[0][i];
    coluna[1] = estado[1][i];
    coluna[2] = estado[2][i];
    coluna[3] = estado[3][i];
    // Realiza a multiplicação entre a coluna atual da matriz estado com a respectiva coluna atual da matriz InvMixColumns 
    estado[0][i] = multiplicacaoGF(coluna[0], 0x0e) ^ multiplicacaoGF(coluna[1], 0x0b) ^ multiplicacaoGF(coluna[2], 0x0d) ^ multiplicacaoGF(coluna[3], 0x09);
    estado[1][i] = multiplicacaoGF(coluna[0], 0x09) ^ multiplicacaoGF(coluna[1], 0x0e) ^ multiplicacaoGF(coluna[2], 0x0b) ^ multiplicacaoGF(coluna[3], 0x0d);
    estado[2][i] = multiplicacaoGF(coluna[0], 0x0d) ^ multiplicacaoGF(coluna[1], 0x09) ^ multiplicacaoGF(coluna[2], 0x0e) ^ multiplicacaoGF(coluna[3], 0x0b);
    estado[3][i] = multiplicacaoGF(coluna[0], 0x0b) ^ multiplicacaoGF(coluna[1], 0x0d) ^ multiplicacaoGF(coluna[2], 0x09) ^ multiplicacaoGF(coluna[3], 0x0e);
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


// Função para descriptografar a mensagem
inline void descriptografar(const uint8_t* entrada, uint8_t* saida, const uint8_t* w) {
  // Guarda a mensagem de entrada na matriz estado
  uint8_t estado[4][4];
  for(int c = 0; c < 4; c++) {
    for(int r = 0; r < 4; r++) {
      estado[r][c] = entrada[c*4 + r];
    }
  }

  // Inverte a rodada 10
  addRoundKey(estado, w + 10*16);
  invShiftRows(estado);
  invSubBytes(estado);

  // Inverte as rodadas 9 a 1
  for (int rodada = 9; rodada > 0; rodada--) {
    addRoundKey(estado, w + rodada * 16);
    invMixColumns(estado);
    invShiftRows(estado);
    invSubBytes(estado);
  }

  // Inverte a rodada 0
  addRoundKey(estado, w);

  // Guarda a mensagem descriptografada na saida
  estadoParaLinear(estado, saida);
}


// Função para aplicar o despreenchimento pkcs#7
inline int pkcs7_desfazer(const uint8_t* entrada, int entradaTam) {
  // Verifica se tem dados de entrada
  if (entradaTam <= 0) {
    return entradaTam;
  }
  // Determina o valor de preenchimento
  uint8_t valorPreenchimento = entrada[entradaTam - 1];
  // Verifica se o valor de preenchimento está entre 1 a 16 e é menor que o tamanho da mensagem
  if(valorPreenchimento > 0 && valorPreenchimento <= 16 && valorPreenchimento <= entradaTam) {
    // Valida o preenchimento percorrendo o bloco
    for (int i = 0; i < valorPreenchimento; i++) {
      if (entrada[entradaTam - 1 - i] != valorPreenchimento) {
        Serial.println("Erro: Preenchimento PKCS#7 inválido (bytes inconsistentes).");
        return entradaTam; 
      }
    }
    return entradaTam - valorPreenchimento;
  }
  return entradaTam;
}


// Setagem dos pinos de comunicação
#define RXD2 16
#define TXD2 17


// Dados basicos
const char* chaveMatriculaA = "78440020";
const char* chaveMatriculaB = "78440026";


void setup() {
  // Inicia as conexões serial
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  Serial.println("A aguardar recepção de dados...");
}


void loop() {
  // Detecta dados no canal serial
  if (Serial2.available() > 0) {
    // Verifica byte de inicio da mensagem (0xAA)
    if (Serial2.read() == 0xAA) {
      delay(50);
      // Guarda os dados d
      if (Serial2.available() > 0) {
        // Determina a quantidade de bytes esperados
        uint8_t qntBlocos = Serial2.read();
        int bytesEsperados = qntBlocos * 16;
        
        // Guarda os dados do canal serial
        uint8_t msgCriptografada[64];
        int bytesRecebidos = 0;
        unsigned long inicio = millis();
        // Guarda os dados do canal serial enquanto estiver na faixa esperada e não ultrapassar o tempo limite
        while (bytesRecebidos < bytesEsperados && (millis() - inicio < 2000)) {
          if (Serial2.available() > 0) {
            msgCriptografada[bytesRecebidos++] = Serial2.read();
          }
        }

        // Se a quantidade de bytes esperados for igual a recebida
        if (bytesRecebidos == bytesEsperados) {
          Serial.println("\n--- [RECEPTOR] PACOTE RECEBIDO ---");
          Serial.print("Mensagem criptografada recebida: ");
          imprimirHex(msgCriptografada, bytesRecebidos);

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

          // Aplicação da expansão da chave original
          uint8_t w[176];
          keyExpansion(chave, w);
          Serial.print("Chave da rodada 0: ");
          imprimirHex(w, 16);
          Serial.print("Chave da rodada 1: ");
          imprimirHex(w + 16, 16);

          // Aplicação da descriptografia da mensagem
          uint8_t msgDescriptografada[64];
          for(int i = 0; i < qntBlocos; i++) {
            descriptografar(msgCriptografada + (i * 16), msgDescriptografada + (i * 16), w);
          }
          Serial.println("\n----------------------------------------------------------------------------------------------------");
          Serial.print("Mensagem descriptografada em bytes (com PKCS#7): ");
          imprimirHex(msgDescriptografada, bytesEsperados);

          // Aplicação do despreenchimento pkcs#7
          int finalTam = pkcs7_desfazer(msgDescriptografada, bytesEsperados);
          msgDescriptografada[finalTam] = '\0';
          Serial.print("Mensagem descriptografada em bytes: ");
          imprimirHex(msgDescriptografada, finalTam);

          // Emite a mensagem para o monitor serial
          Serial.print("Mensagem original decifrada: ");
          Serial.println((char*)msgDescriptografada);
          Serial.println("----------------------------------------------------------------------------------------------------\n");
        } else {
          Serial.println("Erro: Tempo limite de receção excedido ou dados incompletos.");
        }
      }
    }
  }
}