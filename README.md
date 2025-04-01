# Projeto Enigma

## Introdução
Este repositório apresenta um projeto que visa simular o funcionamento da lendária máquina Enigma, utilizando a liguagem C. A Enigma foi uma máquina de criptografia rotor utilizada pelos alemães durante a Segunda Guerra Mundial, famosa por sua complexidade e importância histórica.

## Objetivo
Os objetivos desse projeto são:
  1. Educação: Oferecer uma plataforma para aprender sobre criptografia clássica e os princípios de funcionamento da máquina Enigma;
  2. Prática: Demonstrar a aplicação  em projetos de criptografia e comunicação;
  3. Entretenimento: Proporcionar uma experiência interativa para entusiastas de criptografia e eletrônica.

## Rotores
A ação de embaralhamento dos rotores Enigma mostrada por duas letras consecutivas a corrente é passada pelos rotores, ao redor do refletor e de volta pelos rotores novamente. As linhas acinzentadas representam outros circuitos possíveis dentro de cada rotor, que são conectados fisicamente aos contatos em cada rotor.
![Ligação dos rotores juntamento com o refletor.](https://atitudereflexiva.wordpress.com/wp-content/uploads/2015/12/image022.jpg)

## Configuração
A configuração da máquina Enigma mudava diariamente à meia-noite. Os operadores escolhiam uma "configuração de indicador" e um "indicador" aleatoriamente, cada um com três letras. A configuração indicadora era enviada em Morse em claro. 
A máquina Enigma era usada pelos nazistas para transmitir ordens de guerra criptografadas durante a Segunda Guerra Mundial. O aparelho tinha 129 trilhões de possibilidades de regulagem. 
![Configuração diáia de rotores, deslocamento e tomadas.](https://www.chargebee.com/blog/images/posts/morse-code.png)
Configuração para o dia 01:
  * Rotores: III, I e IV;
  * Deslocamentos: 18, 24 e 15;
  * Tomadas: NP, JV, LY, IX, KQ, AO, DZ, CR, FT e EM.

## Exemplo
A mensagem `ENCONTRO MARCADO PARA AMANHA AO MEIO DIA NA PRACA CENTRAL` dia 01 do mês resulta em `YCXSGAYP ASEUGVB KPCS BFKPGL DS BPND LLK PE YNBWL BWDZMKF`.