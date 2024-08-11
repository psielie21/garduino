# Garduino
Minimalistic IoT gardening project for keeping track of environmental conditions such as temperature and humidity, visualized by a grafana dashboard.

![Garduino Diagram](/assets/Garduino.png "Garduino Schematic")

# Devices
 - ESP12 (NodeMCU)
 - (Arduino) Nano
 - Raspberry Pi
 - HDC1080 Temperature and humidity sensor
 - Capacitive soil moisture sensors

# Get started
## Software
 - Include the `config.h` file in the arduino environment via Sketch>Include Library>Add .ZIP Library
 - Flash the `nano_garduino.ino` script on the Nano, choose Board: Arduino Nano, Processor: AtMega328P Old Bootloader (depending on your hardware)
 - Flash the `esp12_garduino.ino` script on the ESP12, choose Board:NodeMCU 1.0 ESP12e board (you might need to install the 8266 Boards package)
 - Setup the raspberry
   - Complete the default setup and make sure it is accessible on the local net as `raspberrypi`
   - Setup the server
     - Run `rsync garduino_server.py garduino_launcher.sh pi@raspberrypi:/home/pi/garduino`
     - Run `rsync garduino_launcher.service pi@raspberrypi:/etc/systemd/system`
   - Setup the database
     - Follow the steps [here](https://docs.influxdata.com/influxdb/v2/install/?t=Linux) and setup InfluxDB
     - Create retention policies and continuous queries as shown in [this markdown](InfluxDB_setup.md)
   - Setup Grafana dashboard:
     - TODO

## Wiring
Show wiring

