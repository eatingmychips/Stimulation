import pygame
import serial 
import time

pygame.init()
pygame.joystick.init()
joysticks = [pygame.joystick.Joystick(x) for x in range(pygame.joystick.get_count())]

# Initialize the previous button states correctly
if joysticks:
    previous_button_states = [False] * joysticks[0].get_numbuttons()

SerialObj = serial.Serial('COM12')  # Open serial port once at the beginning
SerialObj.baudrate = 115200  # Set Baud rate to 115200

def send_serial(char):
    SerialObj.write(str.encode(char))  # Transmit the character to Arduino


run = True
while run:
    for joystick in joysticks:
        # Iterate through each button to track state changes
        for button in range(joystick.get_numbuttons()):
            current_button_state = joystick.get_button(button)

            if current_button_state and not previous_button_states[button]:
                # Button was pressed (transition from not pressed to pressed)
                if button == 0:
                    print('We have pressed button: A')
                    char = 'A'
                    send_serial(char)

                elif button == 1:
                    print("We have pressed button: B")
                    char = 'B'
                    send_serial(char)

                elif button == 2:
                    print("We have pressed button: 'X'")
                    char = 'X'
                    send_serial(char)

                elif button == 3:
                    print("We have pressed button: 'Y'")
                    char = 'Y'
                    send_serial(char)

                elif button == 5:
                    print("Button 5 has been pressed")
                    char = 'q'
                    send_serial(char)

            # Update the previous state for the next iteration
            previous_button_states[button] = current_button_state

    for event in pygame.event.get():
        if event.type == pygame.JOYDEVICEADDED:
            joy = pygame.joystick.Joystick(event.device_index)
            joysticks.append(joy)
            print(event)