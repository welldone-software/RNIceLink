/* global Paho */
import { initMqtt } from 'react_native_mqtt'

initMqtt({
  size: 10000,
  defaultExpires: 1000 * 3600 * 24,
  enableCache: true,
  sync: {},
})

export const createMqttClient = (host, port, clientId) => {
  const client = new Paho.MQTT.Client(host, port, clientId)

  const onConnect = () => {

  }

  client.connect({
    onSuccess: onConnect,
  })

  const connect = () => {

  }


}

