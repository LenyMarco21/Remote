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
pygame.display.set_caption("gyroscope")
screen = pygame.display.set_mode((window_width, window_height), pygame.NOFRAME)

# Couleur pré-configurées
background_color = (255, 255, 255)
line_color = (0, 0, 0)
gyroscope_color = (128, 255, 128)

# Informations graphiques du joystick
gyroscope_width = 20
gyroscope_height = 20
gyroscope_X = window_width / 2 - gyroscope_width / 2
gyroscope_Y = window_height / 2 - gyroscope_height / 2

# Affiche le joystick en fonction de la position absolue ou relative
def displayGyroscope(data = list): 

        global gyroscope_X, gyroscope_Y

        gyroscope_X = np.int16(data[0] +(data[1] << 8))/131 + 250
        gyroscope_Y = np.int16(data[2] +(data[3] << 8))/131 + 250

        print(gyroscope_X, ':', gyroscope_Y)

        if gyroscope_X < 0:
            gyroscope_X = 0
        elif gyroscope_X > window_width - gyroscope_width:
            gyroscope_X = window_width - gyroscope_width

        if gyroscope_Y < 0:
            gyroscope_Y = 0
        elif gyroscope_Y > window_height - gyroscope_height:
            gyroscope_Y = window_height - gyroscope_height

        # Axe vertical
        pygame.draw.rect(screen, line_color, pygame.Rect(window_width / 2, 0, 2, window_height))

        # Axe horizontal
        pygame.draw.rect(screen, line_color, pygame.Rect(0, window_height / 2, window_width, 2))

        # Joystick
        pygame.draw.rect(screen, gyroscope_color, pygame.Rect(gyroscope_X, gyroscope_Y, gyroscope_width, gyroscope_height))


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
        print(data)
        displayGyroscope(data)
        pygame.display.flip()
        print(gyroscope_X, ':', gyroscope_Y)
    
    #else:
    #    displayError('Pas de données reçues')

    # Attends 200ms avant de reboucler
    time.sleep(0.05);
