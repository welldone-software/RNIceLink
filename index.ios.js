import React from 'react'
import { AppRegistry, StyleSheet, View } from 'react-native'
import { IceLinkConference } from 'components/IceLinkConference'

const styles = StyleSheet.create({
  container: {
    flex: 1,
    marginTop: 20,
  },
})

class RNIceLink extends React.Component {
  ComponentShouldUpdate() {
    return true
  }

  render() {
    return (<View style={styles.container}>
      <IceLinkConference />
    </View>)
  }
}

AppRegistry.registerComponent('App', () => RNIceLink)
