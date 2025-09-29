##########################################################################
#
#   File:
#       thermo-logger-server.py
#
#   Description:
#       Takes an arduino serial output and writes it to a file.
#
##########################################################################

import serial
import time

# Configure the serial port
# Replace 'COM3' with the actual port the Arduino is connected to (e.g., '/dev/ttyUSB0' on Linux)
# Ensure the baud rate matches the one set in the Arduino sketch
ser = serial.Serial('COM3', 57600, timeout=1) 

time.sleep(2) # Give some time for the serial connection to establish
t0 = time.time() # Record the start time

with open("output.csv", "w") as out:
    try:
        while True:
            if ser.in_waiting > 0: # Check if there's data available to read
                line = ser.readline().decode('utf-8').strip() # Read a line, decode it, and remove whitespace
                tDelta = time.time() - t0
                out.write(f"{tDelta},{line}") 

    except KeyboardInterrupt:
        print("\nExiting program.")
    finally:
        out.close() # Close the file stream
        ser.close() # Close the serial port when done