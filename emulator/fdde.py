#!/usr/bin/env python3

import tkinter as tk
from tkinter import ttk
from threading import Thread
from time import sleep

import serial
import json


win = tk.Tk()

win.title("Section77 Flip-Dot-Display-Emulator")
win.resizable(False, False)

WIDTH = 126
HEIGHT = 16

display = tk.Canvas(win, width = WIDTH * 10, height = HEIGHT * 10, bg='black')
display.pack(anchor=tk.CENTER, expand=True)


def connectToUSB():
    ser = None
    for port in range(9):
        try:
            ser = serial.Serial(f'/dev/ttyUSB{port}', 115200)
        except serial.serialutil.SerialException:
            sleep(5)
            continue
        print(f'connected to USB port {port}')
        break
    ser.flushInput()
    ser.flushOutput()
    return ser

# -----------------------------------------------
# MAIN LOOP
# -----------------------------------------------
def readSerial():

    sleep(2)

    print ('Searching for ESP')
    ser = connectToUSB()

    # Liest die Daten von der seriellen Schnittstelle
    # Beispiel: {"row": 2, "column": 25, "status": 1}
    # und setzt das entsprechende Pixel auf an oder aus
    i = 0
    while True:
        data_raw = None
        while data_raw == None:
            try:
                data_raw = ser.readline()
            except serial.serialutil.SerialException:
                print("Connection lost")
                ser = None
                while (ser == None):
                    ser = connectToUSB()
                continue

        if len(data_raw) > 0:
            try:
                data = json.loads(data_raw)
            except:
                continue
            x = data['column']
            y = data['row']
            if data['status'] == 1:
                color = 'yellow'
            else:
                color = 'black'

            display.create_rectangle((x * 10 + 1, y * 10 + 1), (x * 10 + 9, y * 10 + 9), fill = color)
        i += 1


run_thread = Thread(target=readSerial)
run_thread.start()

win.mainloop()
