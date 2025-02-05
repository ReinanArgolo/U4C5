# Projeto U4C5

## Descrição
Este projeto é parte do curso CEPEDI e está localizado na unidade 4, capítulo 5. O objetivo do projeto é projetar um sistema de temporização para o acionamento de LEDs, que atua a partir do clique em um botão (pushbutton). Esta atividade foi elaborada para o curso Embarcatech, um curso de desenvolvimento de software embarcados.

## Como Executar
1. Clone o repositório:
    ```bash
    git clone <URL_DO_REPOSITORIO>
    ```
2. Navegue até o diretório do projeto:
    ```bash
    cd U4C5
    ```
3. Configure o ambiente SDK do Pico:
    ```bash
    export PICO_SDK_PATH=/caminho/para/pico-sdk
    ```
4. Compile o projeto:
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```
5. Execute o projeto:
    ```bash
    ./nome_do_executavel
    ```

## Instruções de Uso
1. Caso o usuário clique no botão (pushbutton), os três LEDs serão ligados (todos em nível alto). A partir da primeira rotina de atraso, ocorrerá uma mudança de estado para dois LEDs ligados e, em seguida, apenas um. Obs.: veja o vídeo associado a esta prática no link presente na Figura 3.
2. O temporizador do alarme deve ser ajustado para um atraso de 3 segundos (3.000ms), entre os estados de acionamento dos LEDs.
3. A mudança de estado dos LEDs deve ser implementada em funções de call-back do temporizador, utilizando a função `add_alarm_in_ms()` do Pico SDK, a exemplo da rotina trabalhada na aula síncrona - `turn_off_callback()`.
4. O botão só pode alterar o estado dos LEDs quando o último LED for desligado. Deste modo, durante a execução das rotinas de temporização, o botão não pode iniciar uma nova chamada da função call-back.
5. Com o emprego da Ferramenta Educacional BitDogLab, faça um experimento com o código deste exercício utilizando o LED RGB – GPIOs 11, 12 e 13 e o Botão A, GPIO 05.




