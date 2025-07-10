# ARM-OTA_Project

This project implements an Over-The-Air (OTA) update system for ARM-based 
microcontroller. It allows users to upload a new application code (.hex file) through a web 
interface, which is stored on a server. Upon triggering a reset on the microcontroller, an 
attached ESP8266 module sends an HTTP request to retrieve the latest .hex file and 
forwards it via UART to the microcontroller. A custom bootloader on the microcontroller 
receives the file and flashes it to memory, replacing the previous application. This system 
enables reliable, remote delivery of updated code with minimal hardware interaction. 

![image](https://github.com/user-attachments/assets/a774f08d-ef8a-476e-9420-53a6d55f5a7e)
