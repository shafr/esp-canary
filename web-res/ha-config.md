# Home-assistant configuration:


```yaml
sensor:
  - platform: mqtt
    name: "attack_ip"
    state_topic: "security/canary/attackerip"
    value_template: "{{ value }}"

binary_sensor:
  - platform: mqtt
    name: "attack_status"
    state_topic: "security/canary/attackinprogress"
    device_class: "problem"
    payload_on: "True"
    payload_off: "False"

  - platform: ping
    name: ping_canary
    count: 2
    scan_interval: 60
    host: 192.168.0.66

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
          message: "Someone is scanning the network"
```          

ui-lovelace.yaml:

```yaml
- type: glance
  title: Network Breach Canary
  entities:
    - entity: binary_sensor.attack_status
      name: Status
    - entity: sensor.attack_ip
      name: Last Attack IP
      icon: 'mdi:ip'
    - entity: binary_sensor.ping_canary
      name: Watchdog Status
      icon: 'mdi:bird'
```
