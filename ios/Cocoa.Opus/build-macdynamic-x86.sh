
xcodebuild -project ../Cocoa.Opus-MacDynamic.xcodeproj -sdk macosx -arch i386 -configuration Release clean build

mv ../build/Release/Cocoa.Opus.dylib Cocoa.Opus-mac-x86.dylib
