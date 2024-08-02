import pygame
import serial 
import time

pygame.init()
pygame.joystick.init()
joysticks = [pygame.joystick.Joystick(x) for x in range(pygame.joystick.get_count())]

for joystick in joysticks: 
    if joystick.get_button(0):
        print("We have pressed a button")

def send_serial(char):
    SerialObj = serial.Serial('COM7') # COMxx  format on Windows
    SerialObj.baudrate = 115200  # set Baud rate to 9600
    SerialObj.bytesize = 8   # Number of data bits = 8
    SerialObj.parity  ='N'   # No parity
    SerialObj.stopbits = 1   # Number of Stop bits = 1
    time.sleep(0.1)
    SerialObj.write(str.encode(char))    #transmit 'A' (8bit) to micro/Arduino
    SerialObj.close()

run = True
while run:

    for joystick in joysticks: 
        if joystick.get_button(0):
            print('We have pressed button: A')
            char = 'A'
            send_serial(char)

        if joystick.get_button(1):
            print("We have pressed button: 'B'" )
            char = 'B'
            send_serial(char)

        if joystick.get_button(2):
            print("We have pressed button: 'X'" )   
            char = 'X'
            send_serial(char) 

        if joystick.get_button(3):
            print("We have pressed button: 'Y'" )
            char = 'Y'
            send_serial(char)

        if joystick.get_button(5):
            print("Button 5 has been pressed")
            char = 'q'
            send_serial(char)

    for event in pygame.event.get():
        if event.type == pygame.JOYDEVICEADDED:
            joy = pygame.joystick.Joystick(event.device_index)
            joysticks.append(joy)

            print(event)

