
xcodebuild -project ../Cocoa.Opus-Mac.xcodeproj -sdk macosx -arch i386 -configuration Release clean build

mv ../build/Release/libCocoa.Opus.a libCocoa.Opus-mac-x86.a
