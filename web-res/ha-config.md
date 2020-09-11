# Home-assistant configuration:

honeypot.yaml:

```yaml
sensor:
  - platform: mqtt
    name: "attack_ip"
    state_topic: "/security/honeypot/attackerip"
    value_template: "{{ value }}"

binary_sensor:
  - platform: mqtt
    name: "attack_status"
    state_topic: "/security/honeypot/attackinprogress"
    device_class: "problem"
    payload_on: "True"
    payload_off: "False"

  - platform: ping
    name: ping_honeypot
    count: 2
    scan_interval: 60
    host: 192.168.1.1

automation:
  - alias: network_breach
    initial_state: 'true'
    trigger:
      entity_id: binary_sensor.attack_status
      platform: state
      to: 'on'

    action:
      - service: notify.telegram
        data:
          title: "Network breach"
          message: "Netowrk Breach!!!"
```          

ui-lovelace.yaml:

```yaml
  - type: glance
    title: Honeypot
    show_name: false
    show_state: false
    entities:
        - binary_sensor.attack_status
        - entity: sensor.attack_ip
        icon: mdi:ip
        - entity: automation.network_breach
        icon: mdi:robot-industrial
        - entity: binary_sensor.ping_honeypot
        icon: mdi:beehive-outline
```