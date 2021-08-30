![ESP Build](https://github.com/shafr/esp-canary/workflows/ESP%20Build/badge.svg)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/5068cf10df544dc5acb4ff90d2e794d4)](https://www.codacy.com/gh/shafr/esp-canary/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=shafr/esp-canary&amp;utm_campaign=Badge_Grade)

# esp-canary

![LOGO](web-res/logo/logo-mid.jpg)

## What 

This is simple `ESP-8266` or `ESP-32`-based canary application that:
* connects to a local Wifi:
* acts as a Tomcat server 
* listens to a different Ping type requests on local network
* notifies you if it is being accessed or scanned via `Telegram`

Before [#27](https://github.com/shafr/esp-canary/pull/27) it had also MQTT / E-mail capabilities, but I found that unused on one side and uses to much memory & there were no sense of having canary that would store access attempts for later investigation. It has to be instant - so you can react as soon as something happens.

## Why
My home network had grown exponentially with each added device: laptops, phones, nas, RPi's, smart-home devices. Even with correctly configured firewall - each of them poses a security threat. 

I was looking for some simple bash script / application that would notify me when network is breached since first thing after getting in would be scanning the network.

The question was not `if` but `when` this would happen.

### Prerequisite:
* Any of `ESP8266` or `ESP32` based boards.
* `Visual Studio Code` + `Platformio plugin` in order to build and upload project

### How to use:
* Clone project
* Update `src/user_config.h` contents with your settings
* Upload file system image using platformio - `PlatformIO: Upload file system image` or `pio run -t uploadfs`
* Upload sketch using `PlatformIO: upload`

Configuration:
[Home-Assistant configuration](web-res/ha-config.md)

## Scanner tools status:

NMap:                         
- Reacts to a NMap -A scan.
- Does not react to a ping scan (nmap -sn), regular scan (nmap) or quick scan (nmap -T4 -F)
- Reacts to quick scan plus (-sV -T4 -O -F --version-light ) or higher (intense or slow)

Advanced IP Scanner (2.4):    
- Reacts to a standard scan

Network Analyzer 7.7 (iOS):
- Does not react to port scan.

# TODOs:
[See TODO List](web-res/TODO.md)


# Credits:
* Logo was generated using [PhotoFunia](https://photofunia.com/categories/all_effects/retro-wave) website. I would gladly accept any other.
* Thanks to @fanuch for pointing out that [this is canary, not sandbox](https://www.reddit.com/r/esp32/comments/n611uu/secure_your_home_network_with_esp8266_esp32/gx53l6t?utm_source=share&utm_medium=web2x&context=3)
