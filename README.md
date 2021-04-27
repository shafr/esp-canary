![ESP Build](https://github.com/shafr/esp-honeypot/workflows/ESP%20Build/badge.svg)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/5068cf10df544dc5acb4ff90d2e794d4)](https://www.codacy.com/gh/shafr/esp-honeypot/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=shafr/esp-honeypot&amp;utm_campaign=Badge_Grade)

# esp-honeypot

![LOGO](web-res/logo/logo-mid.jpg)

## What 

This is simple `ESP-8266` or `ESP-32`-based honeypot application that acts as a server on local network and notifies you if it is being accessed or scanned.

Ideally Nmap scan of services should return same results as real server. Any type of scan or connection attempt should notify you.

## Why
My home network had grown exponentially with each added device: laptops, phones, nas, RPi's, smart-home devices. Even with correctly configured firewall - each of them poses a security threat. 

I was looking for some simple bash script / application that would notify me when network is breached since first thing after getting in would be scanning the network.

The question was not `if` but `when` this would happen.

### How to use:

* Clone project
* Update `src/user_config.h` contents with your settings
* Upload file system image using platformio - `PlatformIO: Upload file system image` or `pio run -t uploadfs`
* Upload sketch using `PlatformIO: upload`

[Home-Assitant configuration](web-res/ha-config.md)

## Nmap scan Status

It does reacts on NMap -A scan.



# TODOs:
[See TODO List](web-res/TODO.md)


# Credits:
Logo was generated using https://photofunia.com/ website. I would gladly accept any other.
