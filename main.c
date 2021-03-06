#include "p30f4013.h"
#include "common.h"

//RUTINA DE RETARDOS
#ifndef __DELAY_H
#define delay_us(x) __delay32(((x*FCY)/1000000L)) //delay x us
#define delay_ms(x) __delay32(((x*FCY)/1000L)) //delay x us
#define delay_s(x) __delay32(((x*FCY)/1L))
#define __DELAY_H 1
#endif

int main(){
TRISB=0X00F;
TRISF=0;		//DEFINIMOS LA SALIDA
//DEFINIR ENTRADAS ANALOGICAS O DIGITALES
ADPCFG = 0xFFFC; //RB1y RB2 ANA; TODO LO DEMAS DIGITAL
//CONFIGURACION GENERAL DEL ADC
ADCON1=0; 		//ADON=0		ADC off	
				//FORM=0    	formato salida= entero
				//SSRC=0  		INICIO DE CONVERSI�N
				//SIMSAM=0 		muestras secuenciales
				//ASAM=0		MUESTRO EMPIEZA CON SAMP1
				//SAMP=0		MUESTREO DESAHIBLITADO (INICIAN CUANDO SAMP=1)
				//DONE=0		CONVERSI�N NO TERMINADA
//CONFIGURACI�N DE CANALES A/D DE ENTRADA
ADCHS=0;		//CH0NA=0		CHANNEL 0 NEGATIVE INPUT IS VREF
				//CH0SA=0000	RB0/AN0=CH0  SE CONFIGUR� RB0/AN0 
				//				COMO CANAL DE ENTRADA
//SCAN
ADCSSL=0;		//SKIP SCAN DE TODOS LOS CANALES
//TIEMPOS
ADCON3=0X0101;	//1 TAD Y RELOJ DERIVADO DEL SISTEMA
//BUFFERS
ADCON2=0;		//VCFG=0		REFERENCIA AVss=NEGATIVA AVdd=POSITIVA
				//CSCNA=0		NO SCAN
				//CHPS=0		CONVERTIR CH0
				//BUFS=0		NO APLICA PUES NO DIVIDIREMOS EL RESULTADP
				
				//SMPI=0		INTERRUMPIR CUANDO SE COMPLETE LA CONVERSION
				//BUFM=0		TRABAJAR COMO BUFFER DE PALABRA DE 16 BITS
				//ALTS=0		USAR UNICAMENTE MUXA (MURSTREO SIMPLE)

ADCON1bits.ADON=1;	//ADC ON
while(1){
PORTBbits.RB9=1;

ADCON1bits.SAMP=1;	//iniciar muestreo
delay_us(200);		//esperar 100 us

ADCON1bits.SAMP=0;	//DETENER MUESTREO, INICIA CONVERSI�N
while(ADCON1bits.DONE); //CONVERSION LISTA?
int VADC=ADCBUF0;		//CAPTURAR VALOR EN LA VARIABLE
	
PORTF=VADC;
delay_us(500);
if ((ADCBUF0&0b100000000000)==0b100000000000){
PORTBbits.RB12=1;
}
else{
PORTBbits.RB12=0;
}
if ((ADCBUF0&0b010000000000)==0b010000000000){
PORTBbits.RB11=1;
}
else{
PORTBbits.RB11=0;
}
if ((ADCBUF0&0b001000000000)==0b001000000000){
PORTBbits.RB10=1;
}
else{
PORTBbits.RB10=0;
}
if ((ADCBUF0&0b000100000000)==0b000100000000){
PORTBbits.RB5=1;
}
else{
PORTBbits.RB5=0;
}		
if ((ADCBUF0&0b000010000000)==0b000010000000){
PORTBbits.RB8=1;
}
else{
PORTBbits.RB8=0;
}		
	
}
return 0;
}



