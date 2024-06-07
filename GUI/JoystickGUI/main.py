from serial_utils import tryToGetData
import numpy as np
import time
import pygame
import math

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

# Affiche le joystick en fonction de la position absolue ou relative
def displayJoystick(data = list, speed : int = 1): 

        global joystick_X, joystick_Y

        print(np.int8(data[0]), ',', np.int8(data[1]))

        joystick_X += math.floor(np.int8(data[0]) * speed)
        joystick_Y += math.floor(np.int8(data[1]) * speed)

        if joystick_X < 0:
            joystick_X = 0
        elif joystick_X > window_width - joystick_width:
            joystick_X = window_width - joystick_width

        if joystick_Y < 0:
            joystick_Y = 0
        elif joystick_Y > window_height - joystick_height:
            joystick_Y = window_height - joystick_height

        # Axe vertical
        pygame.draw.rect(screen, line_color, pygame.Rect(window_width / 2, 0, 2, window_height))

        # Axe horizontal
        pygame.draw.rect(screen, line_color, pygame.Rect(0, window_height / 2, window_width, 2))

        # Joystick
        pygame.draw.rect(screen, joystick_color, pygame.Rect(joystick_X, joystick_Y, joystick_width, joystick_height))


# Affiche un message d'erreur
def displayError(message : str):
    font = pygame.font.SysFont('Arial', 30)
    text_surface = font.render(message, False, (0,0,0))
    screen.blit(text_surface, (int(window_width / 2 - text_surface.get_width() / 2), int(window_height / 2 - text_surface.get_height() / 2)))


# Boucle principale
while(1):
    pygame.event.pump()

    # Mise à jour graphique
    screen.fill(background_color)
    
    # Récupère la donnée utile sur le port série
    data = tryToGetData('COM5', 115200)

    # Si des données existent
    if data != None:
        displayJoystick(data, 0.5)
        print(joystick_X, ':', joystick_Y)
    
    else:
        displayError('Pas de données reçues')

    # Attends 200ms avant de reboucler
    time.sleep(1);

    pygame.display.flip()