
xcodebuild -project ../Cocoa.VP8-Mac.xcodeproj -sdk macosx -arch i386 -configuration Release clean build

mv ../build/Release/libCocoa.VP8.a libCocoa.VP8-mac-x86.a
