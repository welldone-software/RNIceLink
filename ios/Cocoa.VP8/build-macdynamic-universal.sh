
bash build-macdynamic-x86.sh
bash build-macdynamic-x64.sh

lipo -create Cocoa.VP8-mac-x86.dylib Cocoa.VP8-mac-x64.dylib -output Cocoa.VP8-mac.dylib
