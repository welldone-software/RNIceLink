
xcodebuild -project ../Cocoa.VP8-iOS.xcodeproj -sdk iphoneos -arch arm64 -configuration Release clean build

mv ../build/Release-iphoneos/libCocoa.VP8.a libCocoa.VP8-ios-arm64.a
