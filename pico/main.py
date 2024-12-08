# import libraries
import time
from servo import Servo, servo_Angle
from display import *
from machine import UART, Pin

# initialize UART networking connection
uart = UART(0, 9600, tx=Pin(0), rx=Pin(1))
uart.init(9600, bits=8, parity=None, stop=1)

display_is_retracted = False

# initialize servo on pin 21
s1 = Servo(21)

# write message over UART to HM-10 module
def send_command(cmd):
    uart.write(cmd + '\r\n')
    time.sleep(0.5) # time for command to execute on HM-10

# set up the HM-10 BLE module
def bluetooth_setup():
    send_command('wakeup') # ensure HM-10 is being responsive
    response = uart.read()
    print(response)

    # log HM-10 status
    if response == 'OK':
        print('HM-10 is responding')
    else:
        print('HM-10 not responding')

    # set the HM-10 module to the central role
    send_command('AT+ROLE1')

    # send the address of the peripheral (the ESP32C3)
    send_command('AT+CON348518008C98\n')  

# constantly read UART signals from HM-10 and when there is a message call a function
def bluetooth_loop(func_arg):
    while True:
        if uart.any():
            func_arg(uart.readline())

# retract the display
def move_up():
    global display_is_retracted
    servo_Angle(100)
    display_is_retracted = True

# move the display down and display the message to the officer
def move_down():
    global display_is_retracted
    servo_Angle(0)
    display_is_retracted = False
    display_image()

## based on the command read by the HM-10 module, either retract or move down the display
def process_data(bytes_recieved):
    print(bytes_recieved)
    try:
        i = ord(bytes_recieved)
    except:
        print("Error processing bytes")
        return
    print(f"Recieved: {i}")
    if i == 1 and not display_is_retracted: # UP command recieved & not currently up
        move_up()
    elif i == 2 and display_is_retracted: # DOWN command recieved & currently up
        move_down()
    else:
        print(f"Code not recognized")

if __name__ == '__main__':
    # initialize epaper and bluetooth connection
    initialize_epaper()
    bluetooth_setup()

    # main loop
    bluetooth_loop(process_data)