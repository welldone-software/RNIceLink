
bash build-macdynamic-x86.sh
bash build-macdynamic-x64.sh

lipo -create Cocoa.Opus-mac-x86.dylib Cocoa.Opus-mac-x64.dylib -output Cocoa.Opus-mac.dylib
