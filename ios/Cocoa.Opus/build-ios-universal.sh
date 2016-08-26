
bash build-ios-x86.sh
bash build-ios-x64.sh
bash build-ios-armv7.sh
bash build-ios-armv7s.sh
bash build-ios-arm64.sh

lipo -create libCocoa.Opus-ios-x86.a libCocoa.Opus-ios-x64.a libCocoa.Opus-ios-armv7.a libCocoa.Opus-ios-armv7s.a libCocoa.Opus-ios-arm64.a -output libCocoa.Opus-ios.a
