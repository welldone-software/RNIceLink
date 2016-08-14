
bash build-mac-x86.sh
bash build-mac-x64.sh

lipo -create libCocoa.Opus-mac-x86.a libCocoa.Opus-mac-x64.a -output libCocoa.Opus-mac.a
