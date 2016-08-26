
xcodebuild -project ../Cocoa.Opus-iOS.xcodeproj -sdk iphoneos -arch arm64 -configuration Release clean build

mv ../build/Release-iphoneos/libCocoa.Opus.a libCocoa.Opus-ios-arm64.a
