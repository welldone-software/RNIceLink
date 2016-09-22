import React, { Component } from 'react'
import { StyleSheet, requireNativeComponent } from 'react-native'

const IceLinkConferenceView = requireNativeComponent('IceLinkConference', null)

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: 'black',
  },
})

export class IceLinkConference extends Component {
  render() {
    return (<IceLinkConferenceView
      style={styles.container}
      sessionId={this.props.sessionId}
      peerId={this.props.peerId}
      iceLinkServerAddress={this.props.iceLinkServerAddress}
    />)
  }
}

IceLinkConference.propTypes = {
  sessionId: React.PropTypes.string,
  peerId: React.PropTypes.string,
  iceLinkServerAddress: React.PropTypes.string,
}
