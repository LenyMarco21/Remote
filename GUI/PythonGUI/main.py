from serial_utils import tryToGetData
import time
import pygame
import math

DISPLAY_ABS_POS, DISPLAY_DELTA = 'ABSOLUTE', 'DELTA'
DISPLAY_MODES = (DISPLAY_DELTA, DISPLAY_ABS_POS)

# Dimensions de la fenêtre graphiqu
window_width = 600
window_height = 600

# Fenêtre graphique
pygame.init()
pygame.display.set_caption("joystick")
screen = pygame.display.set_mode((window_width, window_height), pygame.NOFRAME)

# Couleur pré-configurées
background_color = (255, 255, 255)
line_color = (0, 0, 0)
joystick_color = (128, 255, 128)

# Informations graphiques du joystick
joystick_width = 20
joystick_height = 20
joystick_X = window_width / 2 - joystick_width / 2
joystick_Y = window_height / 2 - joystick_height / 2


# Retournes un tuple décrivant la position XY du joystick
def convertIntoXY(raw_data):
    x = raw_data[0] + (raw_data[1] << 8)
    y = raw_data[2] + (raw_data[3] << 8)
    return (x, y)


# Affiche le joystick en fonction de la position absolue ou relative
def displayJoystick(data = list, speed : int = 1, mode : str = DISPLAY_ABS_POS): 
    pos = convertIntoXY(data)

    if (pos[0] != None and pos[1] != None):

        global joystick_X, joystick_Y

        if mode == DISPLAY_DELTA:
            joystick_X += ((math.floor(pos[0] / 64) - 32) * speed)
            joystick_Y += ((math.floor(pos[1] / 64) - 32) * speed)
        else:
            joystick_X = ((pos[0] / 4096) * (window_width - 2 * joystick_width)) + joystick_width / 2
            joystick_Y = ((pos[1] / 4096) * (window_height - 2 * joystick_height)) + joystick_height / 2

        if joystick_X < 0:
            joystick_X = 0
        elif joystick_X > window_width - joystick_width:
            joystick_X = window_width - joystick_width

        if joystick_Y < 0:
            joystick_Y = 0
        elif joystick_Y > window_height - joystick_height:
            joystick_Y = window_height - joystick_height

        pygame.draw.rect(screen, joystick_color, pygame.Rect(joystick_X, joystick_Y, joystick_width, joystick_height))


# Boucle principale
while(1):
    pygame.event.pump()

    # Mise à jour graphique
    screen.fill(background_color)
    
    # Axe vertical
    pygame.draw.rect(screen, line_color, pygame.Rect(window_width / 2, 0, 2, window_height))

    # Axe horizontal
    pygame.draw.rect(screen, line_color, pygame.Rect(0, window_height / 2, window_width, 2))

    # Récupère la donnée utile sur le port série
    data = tryToGetData('COM4', 115200)

    # Si des données existent
    if data != None:
        time.sleep(0.02);
        displayJoystick(data, 0.2, DISPLAY_DELTA)
        print(joystick_X, ',', joystick_Y)
    
    pygame.display.flip()