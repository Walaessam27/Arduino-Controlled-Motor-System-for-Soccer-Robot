import serial
import time

# Set up the serial connection (for Raspberry Pi, use '/dev/ttyACM0')
arduino = serial.Serial(port='/dev/ttyACM0', baudrate=9600, timeout=1)  # Update to your port if it's different

def send_command(command):
    arduino.write(command.encode())  # Send command as bytes
    time.sleep(0.1)  # Allow some time for Arduino to process
    response = arduino.readline().decode('utf-8').strip()  # Read response from Arduino
    return response

# Example usage
try:
    while True:
        command = input("Enter command for Arduino: ")
        if command.lower() == 'exit':
            break
        print("Arduino says:", send_command(command))
except KeyboardInterrupt:
    print("Exiting...")
except serial.SerialException as e:
    print(f"Error with serial connection: {e}")
finally:
    arduino.close()  # Make sure to close the serial connection when done
