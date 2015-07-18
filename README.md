# ESP8266
Experimentos con ESP8266 en Linux

## Cargar el firmware NodeMCU al ESP-201

1. Realizar las conexiones siguientes entre el ESP-201 y el TTL USB (debe estar configurado para 3.3V):

    * (ESP-201) RX  <-> TX  (TTL USB)
    * (ESP-201) TX  <-> TX  (TTL USB)
    * (ESP-201) GND <-> GND (TTL USB)

2. Conectar los pines del ESP-201 de la siguiente manera:

    * (ESP-201) IO0 -> GND (externa) - Sólo utilizado cuando se graba un nuevo firmware
    * (ESP-201) 3.3V -> 3.3V (externa)
    * (ESP-201) GND -> GND (externa)
    * (ESP-201) CHP_EN -> 3.3V (externa)
    * (ESP-201) IO15 -> GND (externa)

3. Descargar **esptool** desde https://github.com/themadinventor/esptool/

4. Descargar la última versión del firmware NodeMCU desde https://github.com/nodemcu/nodemcu-firmware/tree/master/pre_build/latest o bien
construir y descargar una versión propia desde hhttp://frightanic.com/nodemcu-custom-build/

5. Encender el ESP-201

6. Instalar el nuevo firmware con el comando: python esptool.py -p /dev/ttyUSB0 -b 115200 write_flash 0x00000 nodemcu_latest.bin

7. Al finalizar la grabación pagar el ESP-201

8. Desconectar el pin IO0 del ESP-201

## Pruebas con el ESP-201

1. Recordar desdonectar de GND el pin IO0.

2. Conectar al ESP-21 con un software de terminal (GtkTerm) a 9600,8, N, 1

3. Encender el ESP-201. El interpete LUA debería responder con un mensaje parecido a "NodeMCU 0.9.6 build 20150216  powered by Lua 5.1.4"

4. Probar los ejemplos de http://www.nodemcu.com/index_en.html


Documentación del firmware en https://github.com/nodemcu/nodemcu-firmware

