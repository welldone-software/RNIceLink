import React, { Component } from 'react'
import { AppRegistry, StyleSheet, View } from 'react-native'
import { IceLinkConference } from 'components/IceLinkConference'

const styles = StyleSheet.create({
  container: {
    flex: 1,
    marginTop: 20,
  },
})

class RNIceLink extends Component {
  componentWillMount() {
    this.setState({
      sessionId: 'session-01',
      peerId: 'peer-01',
    })
  }

  render() {
    return (<View style={styles.container}>
      <IceLinkConference
        sessionId={this.state.sessionId}
        peerId={this.state.peerId}
        iceLinkServerAddress='54.172.172.6:3478'
      />
    </View>)
  }
}

AppRegistry.registerComponent('RNIceLink', () => RNIceLink)
