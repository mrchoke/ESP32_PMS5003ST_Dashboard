# ESP32 PMS5003ST Dashboard
ESP32 and PLANTOWER PMS5003ST Dashboard (VueJs + VuetifyJs) and WebSoket

![Dashboard](https://github.com/mrchoke/ESP32_PMS5003ST_Dashboard/raw/master/IMG_0103.jpg)


[DEMO](https://www.youtube.com/watch?v=4vR5PxSzSaQ)


[![DEMO](https://img.youtube.com/vi/4vR5PxSzSaQ/0.jpg)](https://www.youtube.com/watch?v=4vR5PxSzSaQ "DEMO")


## How to use

### Install PMS5003ST lib 

```
git clone https://github.com/i3water/Blinker_PMSX003ST

```
** copy to Arduino library

### Dashboard and Sketch

```
git clone https://github.com/mrchoke/ESP32_PMS5003ST_Dashboard

```

##### Sketch 
 * APMODE for Access Point
 * CLIENT join WiFi
 
 #### Dashboard
 
 ```
 yarn install
 
 ````
 
 ##### http://localhost:8080
 
 ```
 yarn dev
 
 ```
 
 ##### Directory dist
 ```
 yarn build
 
 ```
 copy files in dist to Sketch data dir gzip  static
 
 ```
 cd data
 
 gzip -9 -r static
 
 ```
 #### add ESP32 file upload tool
 
 ##### git clone
 
 ```
 git clone https://github.com/me-no-dev/arduino-esp32fs-plugin
 
 ```
 ** Copy to Arduino tools directory
 
 #### add ESPASyncWebServer
 
 ```
 git clone https://github.com/me-no-dev/ESPAsyncWebServer
 git clone https://github.com/me-no-dev/ESPAsyncTCP
 
 ```
