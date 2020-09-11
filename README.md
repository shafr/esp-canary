![ESP Build](https://github.com/shafr/esp-honeypot/workflows/ESP%20Build/badge.svg)

# esp-honeypot

![LOGO](web-res/logo/logo-mid.jpg)

This is simple ESP-based honeypot application that acts as a server on local network and notifies you if it is being accessed or scanned.

Ideally Nmap scan of services should return same results as real server. Any type of scan or connection attempt should notify you.

## Why
My home network had grown exponentially with each added device: laptops, phones, nas, RPi's, smart-home devices. Even with correctly configured firewall - each of them poses a security threat. 

I was looking for some simple bash script / application that would notify me when network is breached since first thing after getting in would be scanning the network.

The question was not `if` but `when` this would happen.

### How to use:

* Clone project
* Update `src/user_config.h` contents with your settings
* Upload file system image using platformio - `PlatformIO: Upload file system image`
* Upload sketch using `PlatformIO: upload`


[Home-Assitant configuration](web-res/ha-config.md)


## Status

It does reacts on NMap -A scan. Currently only Apache Tomcat server resources are included. It looks and feels like tomcat welcome page.

### Tomcat Server simulation

- [x] Index page with most links pointing to Tomcat site
- [x] Authentication page with default username and password `tomcat` and `tomcat`
- [x] 401 not authorized page if 3 times incorrect password
- [x] 404 not found page
- [x] Resolve IP address of attacker to be sent
- [x] add header `Date: Fri, 03 Jul 2020 13:06:51 GMT`
- [ ] Duplicate all headers
- [ ] Handle RTSPRequest with 400
- [ ] Handle FourOhFourRequest with 400 
- [ ] add header `Content-Type: text/html;charset=UTF-8`
- [ ] Test all one more time

# TODOs:

### TODO General

- [X] Change mac address to correspond to random device (Synology NAS for example)
- [X] Set hostname that would correspond to something juicy
- [X] Show server that would have same web page contents (read from memory) and headers as Tomcat 
- [X] MQTT notification
- [ ] Telegram notification (Through Home-assistant at the moment)
- [X] OTA updates
- [X] Home-assistant example 
- [ ] More MQTT messages - online, offline, etc
- [ ] Move to LITTLEFS
- [ ] Add watchdog. To prevent from hanging.
- [ ] Blink when there are some issues
- [ ] A way to reset attack state
- [ ] Include IP and time in notification 
- [ ] OTA password

## Ease of use:
- [ ] Documentation!
- [ ] Configuration portal on first run ? 

### Emulations:
- [ ] SSH emulation
- [ ] Telnet emulation
- [ ] Add Ping handler




Logo was generated using https://photofunia.com/ website.