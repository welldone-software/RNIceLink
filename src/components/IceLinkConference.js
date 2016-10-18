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
  constructor() {
    super()
    this.onOfferAnswer = this.onOfferAnswer.bind(this)
  }

  onOfferAnswer(event) {
    if (this.props.onOfferAnswer) {
      this.props.onOfferAnswer(event.nativeEvent)
    }
  }

  render() {
    return (<IceLinkConferenceView
      style={styles.container}
      sessionId={this.props.sessionId}
      peerId={this.props.peerId}
      iceLinkServerAddress={this.props.iceLinkServerAddress}
      onOfferAnswer={this.onOfferAnswer}
    />)
  }
}

IceLinkConference.propTypes = {
  sessionId: React.PropTypes.string,
  peerId: React.PropTypes.string,
  iceLinkServerAddress: React.PropTypes.string,
  onOfferAnswer: React.PropTypes.func,
}
