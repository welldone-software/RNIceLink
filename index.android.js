import React, { Component } from 'react'
import { AppRegistry } from 'react-native'
import { App } from 'components'

class RNIceLink extends Component {
  render() {
    return (<App />)
  }
}

AppRegistry.registerComponent('RNIceLink', () => RNIceLink)
