import RPi.GPIO as GPIO
import time
from mfrc522 import SimpleMFRC522

reader = SimpleMFRC522()

try:
    from websocket import create_connection
    ws = create_connection("ws://10.211.55.4:8080")
    
    while 1:
        print("Place tag")
        id,text = reader.read()
        ws.send(text)
        time.sleep(1)
finally:
    GPIO.cleanup()
