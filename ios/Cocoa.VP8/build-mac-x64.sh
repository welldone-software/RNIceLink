
xcodebuild -project ../Cocoa.VP8-Mac.xcodeproj -sdk macosx -arch x86_64 -configuration Release clean build

mv ../build/Release/libCocoa.VP8.a libCocoa.VP8-mac-x64.a
