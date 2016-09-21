import React from 'react'
import { StyleSheet, requireNativeComponent } from 'react-native'

const IceLinkConferenceView = requireNativeComponent('IceLinkConference', null)

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: 'black',
  },
})

export class IceLinkConference extends React.Component {
  ComponentShouldUpdate() {
    return true
  }

  render() {
    return (<IceLinkConferenceView
      style={styles.container}
      sessionId={this.props.sessionId}
    />)
  }
}

IceLinkConference.propTypes = {
  sessionId: React.PropTypes.string,
}
