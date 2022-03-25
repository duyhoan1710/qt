import RPi.GPIO as GPIO
from mfrc522 import SimpleMFRC522

reader = SimpleMFRC522()

text = input("new text: ")

print("place tag")

try:
	reader.write(text)
	print("write")
finally:
	GPIO.cleanup()
