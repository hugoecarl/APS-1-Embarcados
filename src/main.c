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
#include "musicas.h"

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




/************************************************************************/
/* prototypes                                                           */
/************************************************************************/

/************************************************************************/
/* interrupcoes                                                         */
/************************************************************************/

/************************************************************************/
/* funcoes                                                              */
/************************************************************************/


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
			
				if (pio_get(BUT1_PIO, PIO_INPUT, BUT1_PIO_IDX_MASK) == 0) {
				break;
			}
			while(h<duratio/delay && pio_get(BUT_PIO, PIO_INPUT, BUT_PIO_IDX_MASK) == 1){
				
				pio_clear(LED_PIO, LED_IDX_MASK);
				pio_set(BUZ_PIO, BUZ_PIO_IDX_MASK);
				delay_us(delay/2);
				
				pio_clear(BUZ_PIO, BUZ_PIO_IDX_MASK);
				pio_set(LED_PIO, LED_IDX_MASK);
				delay_us(delay/2);
				
				h++;
		
			}
			if (pio_get(BUT_PIO, PIO_INPUT, BUT_PIO_IDX_MASK) == 0){
				delay_s(0.5);
				while(pio_get(BUT_PIO, PIO_INPUT, BUT_PIO_IDX_MASK) == 1){
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
	
	if(pio_get(BUT_PIO, PIO_INPUT, BUT_PIO_IDX_MASK) == 0 || pio_get(BUT1_PIO, PIO_INPUT, PIO_PD22) == 0){
		int num = sizeof(notes) / sizeof(notes[0]);
		play(duration, notes, num);
		}
	
	if(pio_get(BUT1_PIO, PIO_INPUT, BUT1_PIO_IDX_MASK) == 0){	
		int num = sizeof(melody) / sizeof(melody[0]);
		play(tempo, melody, num);
	}
	
	if(pio_get(BUT1_PIO, PIO_INPUT, BUT1_PIO_IDX_MASK) == 0){
		int num = sizeof(underworld_melody) / sizeof(underworld_melody[0]);
		play(underworld_tempo, underworld_melody, num);
	
	}
  }
  return 0;
}
