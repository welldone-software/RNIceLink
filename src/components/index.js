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
  componentWillMount() {
    this.setState({
      sessionId: 'session-01',
      peerId: 'peer-01',
      iceLinkServerAddress: '54.172.172.6:3478',
    })
  }

  render() {
    return (<View style={styles.container}>
      <IceLinkConference
        sessionId={this.state.sessionId}
        peerId={this.state.peerId}
        iceLinkServerAddress={this.state.iceLinkServerAddress}
      />
    </View>)
  }
}
