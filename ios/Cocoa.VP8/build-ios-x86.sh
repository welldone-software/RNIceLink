
xcodebuild -project ../Cocoa.VP8-iOS.xcodeproj -sdk iphonesimulator -arch i386 -configuration Release clean build

mv ../build/Release-iphonesimulator/libCocoa.VP8.a libCocoa.VP8-ios-x86.a
