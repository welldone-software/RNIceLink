
bash build-mac-x86.sh
bash build-mac-x64.sh

lipo -create libCocoa.VP8-mac-x86.a libCocoa.VP8-mac-x64.a -output libCocoa.VP8-mac.a
