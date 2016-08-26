
xcodebuild -project ../Cocoa.VP8-iOS.xcodeproj -sdk iphoneos -arch armv7s -configuration Release clean build

mv ../build/Release-iphoneos/libCocoa.VP8.a libCocoa.VP8-ios-armv7s.a
