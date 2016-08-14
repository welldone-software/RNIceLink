import React from 'react'
import { View, StyleSheet, requireNativeComponent } from 'react-native'

const IceLinkConferenceView = requireNativeComponent('IceLinkConference', null)

const styles = StyleSheet.create({
  container: {
    flex: 1,
  },
})

export class IceLinkConference extends React.Component {
  ComponentShouldUpdate() {
    return true
  }

  render() {
    return (<View style={styles.container}>
      <IceLinkConferenceView />
    </View>)
  }
}

IceLinkConference.propTypes = {
}
