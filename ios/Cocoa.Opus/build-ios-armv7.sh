
xcodebuild -project ../Cocoa.Opus-iOS.xcodeproj -sdk iphoneos -arch armv7 -configuration Release clean build

mv ../build/Release-iphoneos/libCocoa.Opus.a libCocoa.Opus-ios-armv7.a
