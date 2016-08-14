import UIKit

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {
  var window: UIWindow?

  func application(
    application: UIApplication,
    didFinishLaunchingWithOptions launchOptions: [NSObject:AnyObject]?) -> Bool {


    var jsCodeLocation: NSURL?

    /**
     * Loading JavaScript code - uncomment the one you want.
     *
     * OPTION 1
     * Load from development server. Start the server from the repository root:
     *
     * $ npm start
     *
     * To run on device, change `localhost` to the IP address of your computer
     * (you can get this by typing `ifconfig` into the terminal and selecting the
     * `inet` value under `en0:`) and make sure your computer and iOS device are
     * on the same Wi-Fi network.
     */

    #if DEBUG
      jsCodeLocation = NSURL(
        string: "http://localhost:8081/index.ios.bundle?platform=ios&dev=true");

    #else

      /**
       * OPTION 2
       * Load from pre-bundled file on disk. The static bundle is automatically
       * generated by the "Bundle React Native code and images" build step when
       * running the project on an actual device or running the project on the
       * simulator in the "Release" build configuration.
       */

      jsCodeLocation = NSBundle.mainBundle().URLForResource("main", withExtension: "jsbundle")
    #endif


    let rootView = RCTRootView(
      bundleURL: jsCodeLocation!,
      moduleName: "App",
      initialProperties: nil,
      launchOptions: launchOptions)

    window = UIWindow(frame: UIScreen.mainScreen().bounds)
    let rootViewController = UIViewController()
    rootViewController.view = rootView
    window!.rootViewController = rootViewController;
    window?.makeKeyAndVisible()
    return true
  }
}
