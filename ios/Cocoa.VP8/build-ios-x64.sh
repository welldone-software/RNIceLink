
xcodebuild -project ../Cocoa.VP8-iOS.xcodeproj -sdk iphonesimulator -arch x86_64 -configuration Release clean build

mv ../build/Release-iphonesimulator/libCocoa.VP8.a libCocoa.VP8-ios-x64.a
