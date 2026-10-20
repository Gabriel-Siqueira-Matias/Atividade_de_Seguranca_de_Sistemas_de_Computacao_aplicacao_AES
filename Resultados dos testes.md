Dados dos alunos
Saída do Transmissor  
\--- \[TRANSMISSOR\] PROCESSANDO E ENVIANDO DADOS \---  
Chave em texto: 7844002078440026  
Chave em bytes: 37383434303032303738343430303236  
Mensagem: A:2023278440020;B:2023278440026  
Mensagem em bytes: 413A323032333237383434303032303B423A32303233323738343430303236  
Mensagem em bytes (com PKCS\#7): 413A323032333237383434303032303B423A3230323332373834343030323601  
Chave da rodada 0: 37383434303032303738343430303236  
Chave da rodada 1: 321B3130022B03003513373405230502

\--- TRANSFORMAÇÃO DA RODADA 0 E RODADA 1 DO BLOCO 0 \---  
(1) AddRoundKey (rodada 0\) (chave 0): 76020604020300070F0C00040002020D  
(2) SubBytes (rodada 1):              38776FF2777B63C576FE63F2637777D7  
(3) ShiftRows (rodada 1):             387B63D777FE77F276776FC5637763F2  
(4) MixColumns (rodada 1):            49BCE7E572FB6AEFDFEC8B13CEDADF4E  
(5) AddRoundKey (rodada 1\) (chave 1): 7BA7D6D570D069EFEAFFBC27CBF9DA4C

\----------------------------------------------------------------------------------------------------  
Mensagem criptografada: B1FB0F27DDF0D404A75EEFBF0A491FF66421AEA275359B5655382E6032BBBF4C  
Mensagem enviada com sucesso  
\----------------------------------------------------------------------------------------------------

Saída do Receptor  
\--- \[RECEPTOR\] PACOTE RECEBIDO \---  
Mensagem criptografada recebida: B1FB0F27DDF0D404A75EEFBF0A491FF66421AEA275359B5655382E6032BBBF4C  
Chave em texto: 7844002078440026  
Chave em bytes: 37383434303032303738343430303236  
Chave da rodada 0: 37383434303032303738343430303236  
Chave da rodada 1: 321B3130022B03003513373405230502

\----------------------------------------------------------------------------------------------------  
Mensagem descriptografada em bytes (com PKCS\#7): 413A323032333237383434303032303B423A3230323332373834343030323601  
Mensagem descriptografada em bytes: 413A323032333237383434303032303B423A32303233323738343430303236  
Mensagem original decifrada: A:2023278440020;B:2023278440026  
\----------------------------------------------------------------------------------------------------


Dados dos alunos com chave alterada 
Saída do Transmissor  
\--- \[TRANSMISSOR\] PROCESSANDO E ENVIANDO DADOS \---  
Chave em texto: 3844002078440026  
Chave em bytes: 33383434303032303738343430303236  
Mensagem: A:2023278440020;B:2023278440026  
Mensagem em bytes: 413A323032333237383434303032303B423A32303233323738343430303236  
Mensagem em bytes (com PKCS\#7): 413A323032333237383434303032303B423A3230323332373834343030323601  
Chave da rodada 0: 33383434303032303738343430303236  
Chave da rodada 1: 361B3130062B03003113373401230502

\--- TRANSFORMAÇÃO DA RODADA 0 E RODADA 1 DO BLOCO 0 \---  
(1) AddRoundKey (rodada 0\) (chave 0): 72020604020300070F0C00040002020D  
(2) SubBytes (rodada 1):              40776FF2777B63C576FE63F2637777D7  
(3) ShiftRows (rodada 1):             407B63D777FE77F276776FC5637763F2  
(4) MixColumns (rodada 1):            B9C49F6D72FB6AEFDFEC8B13CEDADF4E  
(5) AddRoundKey (rodada 1\) (chave 1): 8FDFAE5D74D069EFEEFFBC27CFF9DA4C

\----------------------------------------------------------------------------------------------------  
Mensagem criptografada: 8D27EFA8BB84817EE64E6F9172E1A5DEF16986569AC0AD2E7B1942C3803E50FF  
Mensagem enviada com sucesso  
\----------------------------------------------------------------------------------------------------

Saída do Receptor  
\--- \[RECEPTOR\] PACOTE RECEBIDO \---  
Mensagem criptografada recebida: 8D27EFA8BB84817EE64E6F9172E1A5DEF16986569AC0AD2E7B1942C3803E50FF  
Chave em texto: 3844002078440026  
Chave em bytes: 33383434303032303738343430303236  
Chave da rodada 0: 33383434303032303738343430303236  
Chave da rodada 1: 361B3130062B03003113373401230502

\----------------------------------------------------------------------------------------------------  
Mensagem descriptografada em bytes (com PKCS\#7): 413A323032333237383434303032303B423A3230323332373834343030323601  
Mensagem descriptografada em bytes: 413A323032333237383434303032303B423A32303233323738343430303236  
Mensagem original decifrada: A:2023278440020;B:2023278440026  
\----------------------------------------------------------------------------------------------------


Dados dos alunos com mensagem alterada
Saída do Transmissor  
\--- \[TRANSMISSOR\] PROCESSANDO E ENVIANDO DADOS \---  
Chave em texto: 7844002078440026  
Chave em bytes: 37383434303032303738343430303236  
Mensagem: A:1023278440020;B:2023278440026  
Mensagem em bytes: 413A313032333237383434303032303B423A32303233323738343430303236  
Mensagem em bytes (com PKCS\#7): 413A313032333237383434303032303B423A3230323332373834343030323601  
Chave da rodada 0: 37383434303032303738343430303236  
Chave da rodada 1: 321B3130022B03003513373405230502

\--- TRANSFORMAÇÃO DA RODADA 0 E RODADA 1 DO BLOCO 0 \---  
(1) AddRoundKey (rodada 0\) (chave 0): 76020504020300070F0C00040002020D  
(2) SubBytes (rodada 1):              38776BF2777B63C576FE63F2637777D7  
(3) ShiftRows (rodada 1):             387B63D777FE77F276776BC5637763F2  
(4) MixColumns (rodada 1):            49BCE7E572FB6AEFDBE08317CEDADF4E  
(5) AddRoundKey (rodada 1\) (chave 1): 7BA7D6D570D069EFEEF3B423CBF9DA4C

\----------------------------------------------------------------------------------------------------  
Mensagem criptografada: BDED792C2FB4EF9DB5A9512BC8BAC8C06421AEA275359B5655382E6032BBBF4C  
Mensagem enviada com sucesso  
\----------------------------------------------------------------------------------------------------

Saída do Receptor  
\--- \[RECEPTOR\] PACOTE RECEBIDO \---  
Mensagem criptografada recebida: BDED792C2FB4EF9DB5A9512BC8BAC8C06421AEA275359B5655382E6032BBBF4C  
Chave em texto: 7844002078440026  
Chave em bytes: 37383434303032303738343430303236  
Chave da rodada 0: 37383434303032303738343430303236  
Chave da rodada 1: 321B3130022B03003513373405230502

\----------------------------------------------------------------------------------------------------  
Mensagem descriptografada em bytes (com PKCS\#7): 413A313032333237383434303032303B423A3230323332373834343030323601  
Mensagem descriptografada em bytes: 413A313032333237383434303032303B423A32303233323738343430303236  
Mensagem original decifrada: A:1023278440020;B:2023278440026  
\----------------------------------------------------------------------------------------------------


Dados do professor
Saída do Transmissor  
\--- \[TRANSMISSOR\] PROCESSANDO E ENVIANDO DADOS \---  
Chave em texto: 2023100120231002  
Chave em bytes: 32303233313030313230323331303032  
Mensagem: A:20231001;B:20231002  
Mensagem em bytes: 413A32303233313030313B423A3230323331303032  
Mensagem em bytes (com PKCS\#7): 413A32303233313030313B423A32303233313030320B0B0B0B0B0B0B0B0B0B0B  
Chave da rodada 0: 32303233313030313230323331303032  
Chave da rodada 1: 373411F4060421C5343413F6050423C4

\--- TRANSFORMAÇÃO DA RODADA 0 E RODADA 1 DO BLOCO 0 \---  
(1) AddRoundKey (rodada 0\) (chave 0): 730A000303030101020109710B020000  
(2) SubBytes (rodada 1):              8F67637B7B7B7C7C777C01A32B776363  
(3) ShiftRows (rodada 1):             8F7B01637B7C637B7777637C2B677CA3  
(4) MixColumns (rodada 1):            EA1953366A5D4C646840427520C24A3B  
(5) AddRoundKey (rodada 1\) (chave 1): DD2D42C26C596DA15C74518325C669FF

\----------------------------------------------------------------------------------------------------  
Mensagem criptografada: 3A3784991AB0ACAA88D5FD94CB7B74ADCBEA1D9E3E1F39DA47111CF69064B166  
Mensagem enviada com sucesso  
\----------------------------------------------------------------------------------------------------

Saída do Receptor  
\--- \[RECEPTOR\] PACOTE RECEBIDO \---  
Mensagem criptografada recebida: 3A3784991AB0ACAA88D5FD94CB7B74ADCBEA1D9E3E1F39DA47111CF69064B166  
Chave em texto: 2023100120231002  
Chave em bytes: 32303233313030313230323331303032  
Chave da rodada 0: 32303233313030313230323331303032  
Chave da rodada 1: 373411F4060421C5343413F6050423C4

\----------------------------------------------------------------------------------------------------  
Mensagem descriptografada em bytes (com PKCS\#7): 413A32303233313030313B423A32303233313030320B0B0B0B0B0B0B0B0B0B0B  
Mensagem descriptografada em bytes: 413A32303233313030313B423A3230323331303032  
Mensagem original decifrada: A:20231001;B:20231002  
\----------------------------------------------------------------------------------------------------


Dados do apêndice B
Saída do Transmissor  
\--- \[TRANSMISSOR\] PROCESSANDO E ENVIANDO DADOS \---  
Chave em texto: 2b7e151628aed2a6abf7158809cf4f3c  
Chave em bytes: 2B7E151628AED2A6ABF7158809CF4F3C  
Mensagem: 3243f6a8885a308d313198a2e0370734  
Mensagem em bytes: 3243F6A8885A308D313198A2E0370734  
Mensagem em bytes (com PKCS\#7): 3243F6A8885A308D313198A2E037073410101010101010101010101010101010  
Chave da rodada 0: 2B7E151628AED2A6ABF7158809CF4F3C  
Chave da rodada 1: A0FAFE1788542CB123A339392A6C7605

\--- TRANSFORMAÇÃO DA RODADA 0 E RODADA 1 DO BLOCO 0 \---  
(1) AddRoundKey (rodada 0\) (chave 0): 193DE3BEA0F4E22B9AC68D2AE9F84808  
(2) SubBytes (rodada 1):              D42711AEE0BF98F1B8B45DE51E415230  
(3) ShiftRows (rodada 1):             D4BF5D30E0B452AEB84111F11E2798E5  
(4) MixColumns (rodada 1):            046681E5E0CB199A48F8D37A2806264C  
(5) AddRoundKey (rodada 1\) (chave 1): A49C7FF2689F352B6B5BEA43026A5049

\----------------------------------------------------------------------------------------------------  
Mensagem criptografada: 3925841D02DC09FBDC118597196A0B32A254BE88E037DDD9D79FB6411C3F9DF8  
Mensagem enviada com sucesso  
\----------------------------------------------------------------------------------------------------

Saída do Receptor  
\--- \[RECEPTOR\] PACOTE RECEBIDO \---  
Mensagem criptografada recebida: 3925841D02DC09FBDC118597196A0B32A254BE88E037DDD9D79FB6411C3F9DF8  
Chave em texto: 2b7e151628aed2a6abf7158809cf4f3c  
Chave em bytes: 2B7E151628AED2A6ABF7158809CF4F3C  
Chave da rodada 0: 2B7E151628AED2A6ABF7158809CF4F3C  
Chave da rodada 1: A0FAFE1788542CB123A339392A6C7605

\----------------------------------------------------------------------------------------------------  
Mensagem descriptografada em bytes (com PKCS\#7): 3243F6A8885A308D313198A2E037073410101010101010101010101010101010  
Mensagem descriptografada em bytes: 3243F6A8885A308D313198A2E0370734  
Mensagem original decifrada: 3243F6A8885A308D313198A2E0370734  
\----------------------------------------------------------------------------------------------------


Dados do apêndice C.1 
Saída do Transmissor  
\--- \[TRANSMISSOR\] PROCESSANDO E ENVIANDO DADOS \---  
Chave em texto: 000102030405060708090a0b0c0d0e0f  
Chave em bytes: 000102030405060708090A0B0C0D0E0F  
Mensagem: 00112233445566778899aabbccddeeff  
Mensagem em bytes: 00112233445566778899AABBCCDDEEFF  
Mensagem em bytes (com PKCS\#7): 00112233445566778899AABBCCDDEEFF10101010101010101010101010101010  
Chave da rodada 0: 000102030405060708090A0B0C0D0E0F  
Chave da rodada 1: D6AA74FDD2AF72FADAA678F1D6AB76FE

\--- TRANSFORMAÇÃO DA RODADA 0 E RODADA 1 DO BLOCO 0 \---  
(1) AddRoundKey (rodada 0\) (chave 0): 00102030405060708090A0B0C0D0E0F0  
(2) SubBytes (rodada 1):              63CAB7040953D051CD60E0E7BA70E18C  
(3) ShiftRows (rodada 1):             6353E08C0960E104CD70B751BACAD0E7  
(4) MixColumns (rodada 1):            5F72641557F5BC92F7BE3B291DB9F91A  
(5) AddRoundKey (rodada 1\) (chave 1): 89D810E8855ACE682D1843D8CB128FE4

\----------------------------------------------------------------------------------------------------  
Mensagem criptografada: 69C4E0D86A7B0430D8CDB78070B4C55A954F64F2E4E86E9EEE82D20216684899  
Mensagem enviada com sucesso  
\----------------------------------------------------------------------------------------------------

Saída do Receptor  
\--- \[RECEPTOR\] PACOTE RECEBIDO \---  
Mensagem criptografada recebida: 69C4E0D86A7B0430D8CDB78070B4C55A954F64F2E4E86E9EEE82D20216684899  
Chave em texto: 000102030405060708090a0b0c0d0e0f  
Chave em bytes: 000102030405060708090A0B0C0D0E0F  
Chave da rodada 0: 000102030405060708090A0B0C0D0E0F  
Chave da rodada 1: D6AA74FDD2AF72FADAA678F1D6AB76FE

\----------------------------------------------------------------------------------------------------  
Mensagem descriptografada em bytes (com PKCS\#7): 00112233445566778899AABBCCDDEEFF10101010101010101010101010101010  
Mensagem descriptografada em bytes: 00112233445566778899AABBCCDDEEFF  
Mensagem original decifrada: 00112233445566778899AABBCCDDEEFF  
\----------------------------------------------------------------------------------------------------


Teste pedido pelo professor
Saída do Transmissor  
\--- \[TRANSMISSOR\] PROCESSANDO E ENVIANDO DADOS \---  
Chave em texto: 2023100120231002  
Chave em bytes: 32303233313030313230323331303032  
Mensagem: LIGAR LED VERDE.DESLIGAR LED    LIGAR LED VERDE.  
Mensagem em bytes: 4C49474152204C45442056455244452E4445534C49474152204C4544202020204C49474152204C45442056455244452E  
Mensagem em bytes (com PKCS\#7): 4C49474152204C45442056455244452E4445534C49474152204C4544202020204C49474152204C45442056455244452E10101010101010101010101010101010  
Chave da rodada 0: 32303233313030313230323331303032  
Chave da rodada 1: 373411F4060421C5343413F6050423C4

\--- TRANSFORMAÇÃO DA RODADA 0 E RODADA 1 DO BLOCO 0 \---  
(1) AddRoundKey (rodada 0\) (chave 0): 7E79757263107C74761064766374751C  
(2) SubBytes (rodada 1):              F3B69D40FBCA109238CA4338FB929D9C  
(3) ShiftRows (rodada 1):             F3CA439CFBCA9D4038929D92FBB61038  
(4) MixColumns (rodada 1):            672500A47588D0C1D2292678048425C0  
(5) AddRoundKey (rodada 1\) (chave 1): 50111150738CF104E61D358E01800604

\----------------------------------------------------------------------------------------------------  
Mensagem criptografada: E0C22A6F02664F487DC9528642203DEC2B4D065EA65478B60696616244CD5070E0C22A6F02664F487DC9528642203DEC4488DDF55E6FBE3B324CDAEA9F7A4C79  
Mensagem enviada com sucesso  
\----------------------------------------------------------------------------------------------------

Saída do Receptor  
\--- \[RECEPTOR\] PACOTE RECEBIDO \---  
Mensagem criptografada recebida: E0C22A6F02664F487DC9528642203DEC2B4D065EA65478B60696616244CD5070E0C22A6F02664F487DC9528642203DEC4488DDF55E6FBE3B324CDAEA9F7A4C79  
Chave em texto: 2023100120231002  
Chave em bytes: 32303233313030313230323331303032  
Chave da rodada 0: 32303233313030313230323331303032  
Chave da rodada 1: 373411F4060421C5343413F6050423C4

\----------------------------------------------------------------------------------------------------  
Mensagem descriptografada em bytes (com PKCS\#7): 4C49474152204C45442056455244452E4445534C49474152204C4544202020204C49474152204C45442056455244452E10101010101010101010101010101010  
Mensagem descriptografada em bytes: 4C49474152204C45442056455244452E4445534C49474152204C4544202020204C49474152204C45442056455244452E  
Mensagem original decifrada: LIGAR LED VERDE.DESLIGAR LED    LIGAR LED VERDE.  
\----------------------------------------------------------------------------------------------------