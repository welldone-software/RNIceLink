
xcodebuild -project ../Cocoa.Opus-iOS.xcodeproj -sdk iphonesimulator -arch x86_64 -configuration Release clean build

mv ../build/Release-iphonesimulator/libCocoa.Opus.a libCocoa.Opus-ios-x64.a
