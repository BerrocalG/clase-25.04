/*
//prende led con interruptor D(eje1)
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>

void config_IE0(void){
  EIMSK|=(1<<INT0); //habilita interrupciones externas
  EICRA|=(1<<ISC01); //Configura INT0 para activarse con flanco de bajada (ISC01 = 1, ISC00 = 0)
  DDRD&=~0X04;
  PORTD|= 0X04;
}
ISR(INT0_vect){
  _delay_ms(200);
  if(PORTB&0X01){
    PORTB&=~0X01;
  }
  else{
      PORTB|=0X01;
      _delay_ms(200);
      }
  }
int main(void){
  DDRB|=0X01;
  PORTB&=~0X01;
  config_IE0();
  sei();
  while(1){

  }
}
*/


/*
//sube baja con interrupcion d (eje2)
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>

char cuenta=0; //variable global

void config_IE0(void){
  EIMSK |= (1 << INT0)|(1 << INT1);
  EICRA|=(1<<ISC01)|(1 << ISC11);
    
  DDRD &= ~0x0C;  // pulsadores
  PORTD |= 0x0C;  //PULSADORES
}

ISR(INT0_vect){
    cuenta++; //aumenta 1 unidad
    if (cuenta > 99){
    cuenta = 0; //la suma no va sobre pasar los 99
    }
    
}

ISR(INT1_vect){
  cuenta--;
  if(cuenta<0){
    cuenta=99;
  }
}

int main(void) {
    DDRD |= 0xF0;   // PD4 a PD7 como salida (datos al display)
    DDRB |= 0x03;   // PB0 y PB1 como salida (selección de display)

    config_IE0();
    sei();
    while (1) {
        
        PORTB &= ~0x01;     // par apagar el display de decenas
        PORTB |= 0x02;      // para prender el display de unidades
        PORTD = (PORTD & 0x0F) | ((cuenta % 10) << 4); // para "desplazar" las unidades a losp ines del deco
        _delay_ms(8); //display

        // Mostrar decenas
        PORTB &= ~0x02;     // para apagar el display de unidades
        PORTB |= 0x01;      // para prender e display de decenas
        PORTD = (PORTD & 0x0F) | ((cuenta / 10) << 4); 
        _delay_ms(8);
  }
}

*/
/*
//interrupcion b (eje3

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>


void config_PCI(void){
  PCICR|=0X01; //pinb
  PCMSK0|=(0X02);
  DDRB&=~0X02;
  PORTB|= 0X02;
}
ISR(PCINT0_vect){ //puerto b  
  _delay_ms(200);
  if(PORTB&0X01){
    PORTB&=~0X01; //pin del b
  }
  else{
      PORTB|=0X01;
      }
  }
int main(void){
  DDRB|=0X01;
  PORTB&=~0X01;
  config_PCI();
  sei();
  while(1){
  }
}

  void config_PCI(void){
  PCICR|=0x01;
  PCMSK0|=0x06;
  DDRB&=~0x06;
  PORTB|=0x06;
}
ISR(PCINT0_vect){
  _delay_ms(200);
  if(PORTB&0x01){
    PORTB&=~0x01;
  }
  else{
    PORTB|=0x01;
  }
}
int main(void){
  DDRB|=0x01;
  PORTB&=~0x01;
  config_PCI();
  sei();
  while(1){
  } 
  */

 
//ultimo ejercicio
//subir bajar con dos pulsadores usando 2 tipos de interrupciones (eje4)
 
// subir bajar con dos botones 0 a 99 interrupcion en c y b
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>

double enumeracion = 0;

void config_PCI(void) {
  PCICR |= 0x01;  // habilitar interrupcion para pinb
  PCICR |= 0x02;  // habilitar interrupcicon para pinc

  PCMSK0 |= 0x01; // habilitar el pon 0x01 del puertob
  DDRB &= ~0x01;   
  PORTB |= 0x01;  

  PCMSK1 |= 0x01; // habilitar el pin 0x01 del puerto c
  DDRC &= ~0x01;  
  PORTC |= 0x01;  
}

ISR(PCINT0_vect) {
  _delay_ms(8);  
  if ((int)enumeracion < 99) {
    enumeracion += 0.5;
  }
}

ISR(PCINT1_vect) {
  _delay_ms(8);  
  if ((int)enumeracion > 0) {
    enumeracion -= 0.5;
  }
}

int main(void) {
  DDRD |= 0xF0; // del deco
  DDRC |= 0x06; // salidas para display
  PORTC &= ~0x06;   

  config_PCI();
  sei();            

  while (1) {
    PORTC &= ~0x02;// apaga decenas
    PORTC |= 0x04;           
    PORTD |= ((int)enumeracion % 10) << 4;
    PORTD &= (((int)enumeracion % 10) << 4) | 0x0F;
    _delay_ms(8);

    PORTC &= ~0x04;// apaga unidades
    PORTC |= 0x02;            
    PORTD |= ((int)enumeracion / 10) << 4;
    PORTD &= (((int)enumeracion / 10) << 4) | 0x0F;
    _delay_ms(8);
  }
}
