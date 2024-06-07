import serial

# Retourne la data reçue sur le port COM spécifié
def tryToGetData(port_name : str, baudrate : int):

    # Instanciation du port COM
    try:
        ser = serial.Serial(port_name, baudrate)
        #ser.timeout = 1
    except serial.SerialException:
        return None

    # Si le port est ouvert
    if ser.is_open:
        try:
            data = ser.read(5)  # Attente bloquante
        except serial.SerialTimeoutException:
            print('timeout du port série')
        finally:
            ser.close()

        # Renvoie la data uniquement si la trame est valide
        if (data.find(ord('\n')) == 4):
            return data

    # Retour par défaut
    return None


# Cherche l'index de la dernière occurence du caractère spécifié dans la liste
def findLastOccurenceIndex(bufferList : list, char : str):
    if bufferList == None:
        return None

    index = len(bufferList) - 1
    while(index > 0):
        if bufferList[index] == ord(char):
            return index
        else:
            index -= 1
    return None


# Retournes la dernière trame reçue dans le buffer d'entrée du port COM
def readLastLine(lines : list):
    # Cherche la position du dernière caractère fin de ligne
    last_index = findLastOccurenceIndex(lines, '\n')

    # Si la trame le précédant est complète, on la retourne
    if last_index != None and last_index >= 4:
        return lines[last_index-4:last_index]
    else:
        return None