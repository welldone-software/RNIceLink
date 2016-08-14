
bash build-ios-x86.sh
bash build-ios-x64.sh
bash build-ios-armv7.sh
bash build-ios-armv7s.sh
bash build-ios-arm64.sh

lipo -create libCocoa.VP8-ios-x86.a libCocoa.VP8-ios-x64.a libCocoa.VP8-ios-armv7.a libCocoa.VP8-ios-armv7s.a libCocoa.VP8-ios-arm64.a -output libCocoa.VP8-ios.a
