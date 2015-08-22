# ESP8266
Experimentos con ESP8266 en Linux

## ESP-201 ##

![](images/ESP201-1.jpg "" "width:300px;")

1. Realizar las conexiones siguientes entre el ESP-201 y el TTL USB (debe estar configurado para 3.3V):

    * (ESP-201) RX  <-> TX  (TTL USB)
    * (ESP-201) TX  <-> TX  (TTL USB)
    * (ESP-201) GND <-> GND (TTL USB)

2. Conectar los pines del ESP-201 de la siguiente manera:

    * (ESP-201) IO0 -> GND (externa) - Sólo en modo flash
    * (ESP-201) 3.3V -> 3.3V (externa)
    * (ESP-201) GND -> GND (externa)
    * (ESP-201) CHP_EN -> 3.3V (externa)
    * (ESP-201) IO15 -> GND (externa)

![](images/ESP201-2.jpg "" "width:300px;")

## NodeMCU DevKit de Amica ##

![](images/NodeMCU DevKit Amica.jpg "" "width:300px;")

No se requiere ningún tipo de conexión especial

## Instalar Firmarware ##

1. Descargar **esptool** desde [github.com/themadinventor](https://github.com/themadinventor/esptool/).

2. Descargar la última versión del firmware NodeMCU desde [github.com/themadinventor](https://github.com/nodemcu/nodemcu-firmware/releases) o bien construir y descargar una versión propia desde [frightanic.com](http://frightanic.com/nodemcu-custom-build/)

3. Colocar el dispositivo en modo Flash:
	1. ESP-201: conectar a GND el pin IO0 y energizarlo el dispositivo
	2. NodeMCU DevKit: estando energizado presionar botón FLASH y sin soltar presionar el botón RST. Soltar ambos botones

4. Instalar el nuevo firmware con el comando: 
```
python esptool.py -p /dev/ttyUSBXX -b 115200 write_flash 0x00000 nodemcu_XXX.bin
```
En el caso del NodeMCU de Amica se requiere de parámetros adicionales (gracias a [Vext01](http://bbs.nodemcu.com/t/nodemcu-devkit-bricked-cant-recover-reset-whats-the-proper-method/385/3) por el tip)
```
python esptool.py -p /dev/ttyUSB0 -b 115200 write_flash 0x00000 nodemcu_XXX.bin -fs 32m -fm dio -ff 40m
```

7. Al finalizar el flasheo resetar los dispositivos. En el caso del ESP201 apagar, desconectar pin IO0 y encender nuevamente


## Pruebas con el ESP-201

1. Conectarse al dispositivo desde un software de terminal (GtkTerm) a 9600,8, N, 1

2. Encender el ESP-201. El interpete LUA debería responder con un mensaje parecido a "NodeMCU 0.9.6 build 20150216  powered by Lua 5.1.4"

3. Probar los ejemplos de http://www.nodemcu.com/index_en.html


## Referencias ##

- Documentación del firmware en [https://github.com/nodemcu/nodemcu-firmware](https://github.com/nodemcu/nodemcu-firmware)
- Integrated Development Environment (IDE) for ESP8266 developers ([ESplorer](http://esp8266.ru/esplorer/))

