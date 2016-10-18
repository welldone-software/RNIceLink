import React, { Component } from 'react'
import { StyleSheet, View } from 'react-native'
import { IceLinkConference } from 'components/IceLinkConference'


const styles = StyleSheet.create({
  container: {
    flex: 1,
    marginTop: 20,
  },
})

export class App extends Component {
  constructor() {
    super()
    this.onOfferAnswer = this.onOfferAnswer.bind(this)

  }

  componentWillMount() {
    this.setState({
      sessionId: 'session-01',
      iceLinkServerAddress: '54.172.172.6:3478',
    })
  }

  componentDidMount() {

  }

  onOfferAnswer(offerAnswer) {
    const message = new Paho.MQTT.Message(offerAnswer)
    message.destinationName = 'RNIceLinkSession'
    this.mqttClient.send(message)
  }

  render() {
    return (<View style={styles.container}>
      <IceLinkConference
        sessionId={this.state.sessionId}
        peerId={this.state.peerId}
        iceLinkServerAddress={this.state.iceLinkServerAddress}
        onOfferAnswer={this.onOfferAnswer}
      />
    </View>)
  }
}
