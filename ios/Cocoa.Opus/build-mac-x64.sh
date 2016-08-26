
xcodebuild -project ../Cocoa.Opus-Mac.xcodeproj -sdk macosx -arch x86_64 -configuration Release clean build

mv ../build/Release/libCocoa.Opus.a libCocoa.Opus-mac-x64.a
