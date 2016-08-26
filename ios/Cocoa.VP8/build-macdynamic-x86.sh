
xcodebuild -project ../Cocoa.VP8-MacDynamic.xcodeproj -sdk macosx -arch i386 -configuration Release clean build

mv ../build/Release/Cocoa.VP8.dylib Cocoa.VP8-mac-x86.dylib
