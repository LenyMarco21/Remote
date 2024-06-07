/*
 * joystick_button.h
 *
 *  Author: l.marcolini ESEO E3A
 */

#ifndef BSP_JOYSTICK_JOYSTICK_BUTTON_H_
#define BSP_JOYSTICK_JOYSTICK_BUTTON_H_

/* Includes =============================================================== */

#include "macro_types.h"
#include "config.h"
#include "stm32f1_gpio.h"

/* Defines ================================================================ */

/* Enumerations ============================================================*/

/**
 * Enum�re les �tats du bouton
 */
typedef enum
{
	JOYSTICK_BTN_RELEASED = 0,
	JOYSTICK_BTN_PRESSED = 1
}
e_joystick_btn_state;


/**
 * Enum�re les status
 */
typedef enum
{
	JOYSTICK_BTN_STATUS_OK = 0,
	JOYSTICK_BTN_GPIO_PORT_ERROR = 1,
	JOYSTICK_BTN_GPIO_PIN_ERROR = 2
}
e_joystick_btn_status;


/* Structures ============================================================= */

/**
 * Structure mod�lisant un bouton de joystick
 */
typedef struct
{
	/***************************
	 * Variables en read-only *
	 ***************************/
	e_joystick_btn_state value;				// Etat du bouton
	uint8_t has_changed;					// Indique indiquant que la valeur a chang�
	e_joystick_btn_status status;			// Statut du bouton

	/***************************
	 * Variables en read-write *
	 ***************************/
	GPIO_TypeDef * gpio_port;				// R�f�rence du port GPIO utilis�
	uint16_t gpio_pin_mask;					// Num�ro de broche sur le port

}
st_joystick_btn;

/* External function prototypes =========================================== */

e_joystick_btn_status JOYSTICK_BTN_get_value(st_joystick_btn * btn);

#endif /* BSP_JOYSTICK_JOYSTICK_BUTTON_H_ */
