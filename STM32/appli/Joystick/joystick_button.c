/*
 * joystick_button.c
 *
 *  Created on: May 9, 2024
 *  Author: l.marcolini ESEO E3A
 */


/* Includes =============================================================== */

#include "joystick_button.h"

/* Define ================================================================= */

/* Enumeration ============================================================*/

/* Structure ============================================================== */

/* Static variables ======================================================= */

/* Static function prototype =============================================== */

static e_joystick_btn_status JOYSTICK_BTN_check_config(st_joystick_btn * btn);

/* Function  ============================================================== */

static e_joystick_btn_status JOYSTICK_BTN_check_config(st_joystick_btn * btn)
{
	if (btn->gpio_port == NULL)
	{
		btn->status = JOYSTICK_BTN_GPIO_PORT_ERROR;
	}
	else if (btn->gpio_pin_mask == 0)
	{
		btn->status = JOYSTICK_BTN_GPIO_PIN_ERROR;
	}
	else
	{
		btn->status = JOYSTICK_BTN_STATUS_OK;
	}

	return btn->status;
}


/**
 * @brief Obtient la position sur l'axe passé en entrée
 * @param pointeur sur une structure st_joystick_axis décrivant un axe
 */
e_joystick_btn_status JOYSTICK_BTN_get_value(st_joystick_btn * btn)
{
	btn->has_changed = 0;

	if (JOYSTICK_btn_check_config(btn) == JOYSTICK_BTN_STATUS_OK)
	{
		BSP_GPIO_PinCfg(btn->gpio_port, btn->gpio_pin_mask, GPIO_MODE_INPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW);

		uint8_t pin_value = btn->gpio_port->IDR & btn->gpio_pin_mask;

		if (pin_value != btn->value)
		{
			btn->value = pin_value;
			btn->has_changed = 1;
		}
	}

	return btn->status;
}
