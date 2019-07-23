#! /usr/bin/env python3
import serial
import serial.tools.list_ports
import timeit
import os, random

print("FlashMode started...")

ports = serial.tools.list_ports.comports()
print("Connecting to arduino...")

for port in ports:
    print("Trying " + port.device + "...")
    with serial.Serial(port.device, 9600, timeout=10) as ser:
        try:
            ser.write(b"t\n")  # as in "time"
            ser.flush()
            answer = ser.readline()
            print("Got answer:")
            print(answer)
            if answer != b"timing started\n":
                continue

            print("Connection established. Timer started.")

            while(True):
                n=0
                random.seed();
                for root, dirs, files in os.walk('/home/dominik/RedButton/media/flash_samples/'):
                    for name in files:
                        n=n+1
                        if random.uniform(0, n) < 1: rfile=os.path.join(root, name)
                print(rfile)
                old_time = timeit.default_timer()
                key = input("Waiting for return...")
                new_time = timeit.default_timer()
                elapsed = new_time - old_time
                if elapsed > 1 and len(key) < 1 :
                    print("Elapsed: \033[91m{:.2f}s\033[0m".format(new_time - old_time))
                    os.system("ffplay {} -nodisp -autoexit".format(rfile))
                else:
                    print("Elapsed: {:.2f}s".format(new_time - old_time))
                print("")
        except KeyboardInterrupt:
            pass
        finally:
            ser.write(b"n\n")  # as in "normal"
            ser.flush()
