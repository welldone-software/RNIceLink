
xcodebuild -project ../Cocoa.Opus-MacDynamic.xcodeproj -sdk macosx -arch x86_64 -configuration Release clean build

mv ../build/Release/Cocoa.Opus.dylib Cocoa.Opus-mac-x64.dylib
