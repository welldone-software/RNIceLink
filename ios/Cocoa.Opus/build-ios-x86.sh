
xcodebuild -project ../Cocoa.Opus-iOS.xcodeproj -sdk iphonesimulator -arch i386 -configuration Release clean build

mv ../build/Release-iphonesimulator/libCocoa.Opus.a libCocoa.Opus-ios-x86.a
