/**
  ******************************************************************************
  * @file    main.c
  * @author  Nirgal
  * @date    03-July-2019
  * @brief   Default main function.
  ******************************************************************************
*/


/* Includes =============================================================== */

#include <emitter.h>
#include "stm32f1xx_hal.h"
#include "stm32f1_uart.h"
#include "stm32f1_sys.h"
#include "stm32f1_gpio.h"
#include "macro_types.h"
#include "systick.h"

/* Define ================================================================= */

#define REFRESH_RATE_50_Hz 		20
#define REFRESH_RATE_40_Hz 		25
#define REFRESH_RATE_20_Hz 		50
#define REFRESH_RATE_10_Hz 		100
#define REFRESH_RATE_1_Hz 		1000

/* Enumeration ============================================================*/

/* Structure ============================================================== */

/* Static variables ======================================================= */

/* Static function prototype =============================================== */

/* Function  ============================================================== */

void writeLED(bool_e b)
{
	HAL_GPIO_WritePin(LED_GREEN_GPIO, LED_GREEN_PIN, b);
}

bool_e readButton(void)
{
	return !HAL_GPIO_ReadPin(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN);
}

static volatile uint32_t t = 0;
void process_ms(void)
{
	if(t)
		t--;
}


int main(void)
{
	//Initialisation de la couche logicielle HAL (Hardware Abstraction Layer)
	//Cette ligne doit rester la premi�re �tape de la fonction main().
	HAL_Init();

	//Initialisation de l'UART1 � la vitesse de 4000 bauds/secondes (3.2kbits/s) PB6 : Tx  | PB7 : Rx.
	EMITTER_init(UART1_ID, 4000);

	//Initialisation de l'UART2 � la vitesse de 115200 bauds/secondes (92kbits/s) PA2 : Tx  | PA3 : Rx.
	//Attention, les pins PA2 et PA3 ne sont pas reli�es jusqu'au connecteur de la Nucleo.
	//Ces broches sont redirig�es vers la sonde de d�bogage, la liaison UART �tant ensuite encapsul�e sur l'USB vers le PC de d�veloppement.
	UART_init(UART2_ID,115200);

	//"Indique que les printf sortent vers le p�riph�rique UART2."
	SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);

	//Initialisation du port de la led Verte (carte Nucleo)
	BSP_GPIO_PinCfg(LED_GREEN_GPIO, LED_GREEN_PIN, GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH);

	//Initialisation du port du bouton bleu (carte Nucleo)
	BSP_GPIO_PinCfg(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN, GPIO_MODE_INPUT,GPIO_PULLUP,GPIO_SPEED_FREQ_HIGH);

	// Initialisation du module ADC
	ADC_init();

	//On ajoute la fonction process_ms � la liste des fonctions appel�es automatiquement chaque ms par la routine d'interruption du p�riph�rique SYSTICK
	Systick_add_callback_function(&process_ms);

	while(1)
	{
		if(!t)
		{
			// Recharge le compteur
			t = REFRESH_RATE_40_Hz;

			// Toggle la led verte
			HAL_GPIO_TogglePin(LED_GREEN_GPIO, LED_GREEN_PIN);

			// Envoie des valeurs par d�faut sur l'UART1
			EMITTER_routine(DATA_TRANSMIT_REFRESHED_VALUES);
		}

	}
}