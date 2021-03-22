### TODO General

- [X] Change mac address to correspond to random device (Synology NAS for example)
- [X] Set hostname that would correspond to something juicy
- [X] Show server that would have same web page contents (read from memory) and headers as Tomcat 
- [X] MQTT notification
- [X] Telegram notification
- [X] OTA updates
- [ ] signed OTA updates after reboot from Release section if new version is available
- [X] Move to LITTLEFS
- [ ] More MQTT messages - online, offline, etc
- [ ] Add watchdog. To prevent from hanging.
- [ ] Blink when there are some issues
- [ ] A way to reset attack state
- [X] Include IP and time in notification (mostly done through telegram)
- [X] Home-assistant example 
- [ ] OTA password

## Ease of use:
- [ ] Documentation!
- [ ] Configuration portal on first run ? 

### Emulations:
- [ ] SSH emulation
- [ ] Telnet emulation
- [ ] Add Ping handler

# Emulation part:

### TOMCAT:

Currently, only Apache Tomcat server resources are included. It looks and feels like Tomcat welcome page.

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