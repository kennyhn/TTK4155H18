# TTK4155 - Industrielle og innbygde datasystemers konstruksjon "Bygger'n"
Laget av Jørgen Skinnes, Iver Myklebust og Kenny Hoang Nguyen høsten 2018

### Node 1
Mikrokontrolleren styrer skjerm og kontroller som skal brukes for det fysiske ping-pong-spillet. <br />

##### mcp2515.c
Initialiserer delen av kretsen som styrer SPI-bussen. Denne her brukes for å sette opp kommunikasjon opp mot CAN-bussen og SPI-bussen som skal kommunisere vider med perifere enheter

##### spi.c
Setter opp SPI-kommunikasjon som brukes for å kommunisere med f.eks. skjermen

##### can.c
Setter opp CAN og har moduler for å bruke CAN-bussen. Setter opp kommunikasjon til node 2.

##### uart.c
Setter opp UART-kommunikasjon som brukes for å kommunisere med datamaskinen for debugging.

##### adc.c
Setter opp delen av kretsen som konverterer analoge signaler fra enheter som styres fra den "fysiske verden" til digitale signaler som kan brukes i mikrokontrolleren.

##### oled.c
Setter opp skjermen og har moduler for å bruke LED-skjermen.

##### sram.c
Initialiserer SRAM og har moduler for å utnytte denne.

##### menu.c
Interface for menyen som vises på LED-skjermen

##### timer.c
Setter opp timere som brukes for å få riktig timing i forhold til node 2 samtidig og redusere mikrokontrollerens aktiv tid

##### game.c
Ping-pong spillet

### Node 2
Denne mikrokontrolleren styrer det fysiske ping-pong-spillet.

##### mcp2515.c
Initialiserer delen av kretsen som styrer SPI-bussen. Denne her brukes for å sette opp kommunikasjon opp mot CAN-bussen og SPI-bussen som skal kommunisere vider med perifere enheter

##### spi.c
Setter opp SPI-kommunikasjon som brukes for å kommunisere med f.eks. skjermen

##### can.c
Setter opp CAN og har moduler for å bruke CAN-bussen. Setter opp kommunikasjon til node 1.

##### uart.c
Setter opp UART-kommunikasjon som brukes for å kommunisere med datamaskinen for debugging.

##### adc.c
Setter opp delen av kretsen som konverterer analoge signaler fra enheter som styres fra den "fysiske verden" til digitale signaler som kan brukes i mikrokontrolleren.

##### TWI.c
Utdelt kode. Brukes for å kommunisere med perifere enheter som motorene til spillet.

##### motor.c
Brukes for å styre motoren til ping-pong-spillet. (slider frem og tilbake)

##### pwm.c
Brukes for å styre servomotoren til ping-pong-spillet samt solenoide-kontroll.
