/** 
 ** Aluno:
 **  - Hugo Ebert Carl
 **  
 ** 
 **  - https://youtu.be/zMPv8yqcKOQ
 **/
/************************************************************************/
/* includes                                                             */
/************************************************************************/

#include "asf.h"

/************************************************************************/
/* defines                                                              */
/************************************************************************/

#define BUZ_PIO           PIOD                  // periferico que controla o BUZZER
#define BUZ_PIO_ID        ID_PIOD                    // ID do periférico PIOC (controla LED)
#define BUZ_PIO_IDX       21u                    // ID do LED no PIO
#define BUZ_PIO_IDX_MASK  (1u << BUZ_PIO_IDX)   // Mascara para CONTROLARMOS o LED

#define LED_PIO      PIOC					// periferico que controla o LED
#define LED_PIO_ID   ID_PIOC				// ID do periférico PIOC (controla LED)
#define LED_IDX      8						// ID do LED no PIO
#define LED_IDX_MASK (1 << LED_IDX)			// Mascara para CONTROLARMOS o LED

#define BUT_PIO           PIOD                  // periferico que controla o BOTAO VERDE
#define BUT_PIO_ID        ID_PIOD                    // ID do periférico PIOD (controla BOT)
#define BUT_PIO_IDX       25u                    // ID do BOT no PIO
#define BUT_PIO_IDX_MASK  (1u << BUT_PIO_IDX)   // Mascara para CONTROLARMOS o BOT

#define BUT1_PIO           PIOD                  // periferico que controla o BOTAO VERMELHO
#define BUT1_PIO_ID        ID_PIOD                    // ID do periférico PIOD (controla BOT1)
#define BUT1_PIO_IDX       22u                    // ID do BOT1 no PIO
#define BUT1_PIO_IDX_MASK  (1u << BUT1_PIO_IDX)   // Mascara para CONTROLARMOS o BOT1


#define NOTE_C4  262   //Defining note frequency
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  784
#define NOTE_A5  880
#define NOTE_B5  988
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

/************************************************************************/
/* constants                                                            */
/************************************************************************/

/************************************************************************/
/* variaveis globais                                                    */
/************************************************************************/

int notes[] = {       
	NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
	NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
	NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
	NOTE_A4, NOTE_G4, NOTE_A4, 0,
	
	NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
	NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
	NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
	NOTE_A4, NOTE_G4, NOTE_A4, 0,
	
	NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
	NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
	NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
	NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
	
	NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
	NOTE_D5, NOTE_E5, NOTE_A4, 0,
	NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
	NOTE_C5, NOTE_A4, NOTE_B4, 0,

	NOTE_A4, NOTE_A4,
	//Repeat of first part
	NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
	NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
	NOTE_A4, NOTE_G4, NOTE_A4, 0,

	NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
	NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
	NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
	NOTE_A4, NOTE_G4, NOTE_A4, 0,
	
	NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
	NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
	NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
	NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
	
	NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
	NOTE_D5, NOTE_E5, NOTE_A4, 0,
	NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
	NOTE_C5, NOTE_A4, NOTE_B4, 0,
	//End of Repeat

	NOTE_E5, 0, 0, NOTE_F5, 0, 0,
	NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
	NOTE_D5, 0, 0, NOTE_C5, 0, 0,
	NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4,

	NOTE_E5, 0, 0, NOTE_F5, 0, 0,
	NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
	NOTE_D5, 0, 0, NOTE_C5, 0, 0,
	NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4
};

int duration[] = {         
	125, 125, 250, 125, 125,
	125, 125, 250, 125, 125,
	125, 125, 250, 125, 125,
	125, 125, 375, 125,
	
	125, 125, 250, 125, 125,
	125, 125, 250, 125, 125,
	125, 125, 250, 125, 125,
	125, 125, 375, 125,
	
	125, 125, 250, 125, 125,
	125, 125, 250, 125, 125,
	125, 125, 250, 125, 125,
	125, 125, 125, 250, 125,

	125, 125, 250, 125, 125,
	250, 125, 250, 125,
	125, 125, 250, 125, 125,
	125, 125, 375, 375,

	250, 125,
	//Rpeat of First Part
	125, 125, 250, 125, 125,
	125, 125, 250, 125, 125,
	125, 125, 375, 125,
	
	125, 125, 250, 125, 125,
	125, 125, 250, 125, 125,
	125, 125, 250, 125, 125,
	125, 125, 375, 125,
	
	125, 125, 250, 125, 125,
	125, 125, 250, 125, 125,
	125, 125, 250, 125, 125,
	125, 125, 125, 250, 125,

	125, 125, 250, 125, 125,
	250, 125, 250, 125,
	125, 125, 250, 125, 125,
	125, 125, 375, 375,
	
	
	250, 125, 375, 250, 125, 375,
	125, 125, 125, 125, 125, 125, 125, 125, 375,
	250, 125, 375, 250, 125, 375,
	125, 125, 125, 125, 125, 500,

	250, 125, 375, 250, 125, 375,
	125, 125, 125, 125, 125, 125, 125, 125, 375,
	250, 125, 375, 250, 125, 375,
	125, 125, 125, 125, 125, 500
};

int melody[] = {
	NOTE_E7, NOTE_E7, 0, NOTE_E7,
	0, NOTE_C7, NOTE_E7, 0,
	NOTE_G7, 0, 0,  0,
	NOTE_G6, 0, 0, 0,
	
	NOTE_C7, 0, 0, NOTE_G6,
	0, 0, NOTE_E6, 0,
	0, NOTE_A6, 0, NOTE_B6,
	0, NOTE_AS6, NOTE_A6, 0,
	
	NOTE_G6, NOTE_E7, NOTE_G7,
	NOTE_A7, 0, NOTE_F7, NOTE_G7,
	0, NOTE_E7, 0, NOTE_C7,
	NOTE_D7, NOTE_B6, 0, 0,
	
	NOTE_C7, 0, 0, NOTE_G6,
	0, 0, NOTE_E6, 0,
	0, NOTE_A6, 0, NOTE_B6,
	0, NOTE_AS6, NOTE_A6, 0,
	
	NOTE_G6, NOTE_E7, NOTE_G7,
	NOTE_A7, 0, NOTE_F7, NOTE_G7,
	0, NOTE_E7, 0, NOTE_C7,
	NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
int tempo[] = {
	120, 120, 120, 120,
	120, 120, 120, 120,
	120, 120, 120, 120,
	120, 120, 120, 120,
	
	120, 120, 120, 120,
	120, 120, 120, 120,
	120, 120, 120, 120,
	120, 120, 120, 120,
	
	90, 90, 90,
	120, 120, 120, 120,
	120, 120, 120, 120,
	120, 120, 120, 120,
	
	120, 120, 120, 120,
	120, 120, 120, 120,
	120, 120, 120, 120,
	120, 120, 120, 120,
	
	90, 90, 90,
	120, 120, 120, 120,
	120, 120, 120, 120,
	120, 120, 120, 120,
};

int underworld_melody[] = {
	NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
	NOTE_AS3, NOTE_AS4, 0,
	0,
	NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
	NOTE_AS3, NOTE_AS4, 0,
	0,
	NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
	NOTE_DS3, NOTE_DS4, 0,
	0,
	NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
	NOTE_DS3, NOTE_DS4, 0,
	0, NOTE_DS4, NOTE_CS4, NOTE_D4,
	NOTE_CS4, NOTE_DS4,
	NOTE_DS4, NOTE_GS3,
	NOTE_G3, NOTE_CS4,
	NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
	NOTE_GS4, NOTE_DS4, NOTE_B3,
	NOTE_AS3, NOTE_A3, NOTE_GS3,
	0, 0, 0
};
//Underworld tempo
int underworld_tempo[] = {
	120, 120, 120, 120,
	120, 120, 60,
	30,
	120, 120, 120, 120,
	120, 120, 60,
	30,
	120, 120, 120, 120,
	120, 120, 60,
	30,
	120, 120, 120, 120,
	120, 120, 60,
	60, 180, 180, 180,
	60, 60,
	60, 60,
	60, 60,
	180, 180, 180, 180, 180, 180,
	100, 100, 100,
	100, 100, 100,
	30, 30, 30
};

/************************************************************************/
/* prototypes                                                           */
/************************************************************************/

void init(void);

/************************************************************************/
/* interrupcoes                                                         */
/************************************************************************/

/************************************************************************/
/* funcoes                                                              */
/************************************************************************/
void pio_set_output (    Pio * 	p_pio,
const uint32_t  ul_mask,
const uint32_t  ul_default_level,
const uint32_t  ul_multidrive_enable,
const uint32_t  ul_pull_up_enable
);


// Função de inicialização do uC
void init(void)
{

// Initialize the board clock
sysclk_init();
  
// Desativa WatchDog Timer
WDT->WDT_MR = WDT_MR_WDDIS;
pmc_enable_periph_clk(BUZ_PIO_ID);
pio_configure(LED_PIO, PIO_OUTPUT_0, LED_IDX_MASK, PIO_DEFAULT);
pio_set_output(BUZ_PIO, BUZ_PIO_IDX_MASK, 0, 0, 0);
}

void play(int duration[], int notes[], int n){ 
		delay_s(0.5);
		for(int i = 0; i < n; i++){
			int delay = 1000000/notes[i];
			int duratio = duration[i] * 1000;
			int h;
			h = 0;
			
				if (pio_get(BUT1_PIO, PIO_INPUT, PIO_PD22) == 0) {
				break;
			}
			while(h<duratio/delay && pio_get(BUT_PIO, PIO_INPUT, PIO_PD25) == 1){
				
				pio_clear(LED_PIO, LED_IDX_MASK);
				pio_set(BUZ_PIO, BUZ_PIO_IDX_MASK);
				delay_us(delay/2);
				
				pio_clear(BUZ_PIO, BUZ_PIO_IDX_MASK);
				pio_set(LED_PIO, LED_IDX_MASK);
				delay_us(delay/2);
				
				h++;
		
			}
			if (pio_get(BUT_PIO, PIO_INPUT, PIO_PD25) == 0){
				delay_s(0.5);
				while(pio_get(BUT_PIO, PIO_INPUT, PIO_PD25) == 1){
				}
				delay_s(0.5);
			}	
			delay_us(65000);	
		}
	return;
}

/************************************************************************/
/* Main                                                                 */
/************************************************************************/

// Funcao principal chamada na inicalizacao do uC.
int main(void)
{
  init();

  // super loop
  // aplicacoes embarcadas não devem sair do while(1).
  while (1)
  {
	
	if(pio_get(BUT_PIO, PIO_INPUT, PIO_PD25) == 0 || pio_get(BUT1_PIO, PIO_INPUT, PIO_PD22) == 0){
		int num = sizeof(notes) / sizeof(notes[0]);
		play(duration, notes, num);
		}
	
	if(pio_get(BUT1_PIO, PIO_INPUT, PIO_PD22) == 0){	
		int num = sizeof(melody) / sizeof(melody[0]);
		play(tempo, melody, num);
	}
	
	if(pio_get(BUT1_PIO, PIO_INPUT, PIO_PD22) == 0){
		int num = sizeof(underworld_melody) / sizeof(underworld_melody[0]);
		play(underworld_tempo, underworld_melody, num);
	
	}
  }
  return 0;
}
