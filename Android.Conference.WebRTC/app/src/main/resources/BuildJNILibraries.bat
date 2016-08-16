set SYSROOT=..\..\..\..\..\android-ndk-r10e\platforms\android-16\arch-arm

..\..\..\..\..\android-ndk-r10e\toolchains\arm-linux-androideabi-4.9\prebuilt\windows\bin\arm-linux-androideabi-g++ -fno-exceptions --sysroot=%SYSROOT% -shared -mcpu=cortex-a8 -mthumb -mfpu=neon -mfloat-abi=softfp -march=armv7-a -I..\include\jni -I..\include\jni\linux -L..\libs\armeabi-v7a -llog -lopus -o ..\libs\armeabi-v7a\libopusJNI.so aopus_OpusLibrary.c

set SYSROOT=..\..\..\..\..\android-ndk-r10e\platforms\android-16\arch-x86

..\..\..\..\..\android-ndk-r10e\toolchains\x86-4.9\prebuilt\windows\bin\i686-linux-android-g++ -fno-exceptions --sysroot=%SYSROOT% -shared -mtune=i686 -march=i686 -I..\include\jni -I..\include\jni\linux -L..\libs\x86 -llog -lopus -o ..\libs\x86\libopusJNI.so aopus_OpusLibrary.c

set SYSROOT=..\..\..\..\..\android-ndk-r10e\platforms\android-21\arch-arm64

..\..\..\..\..\android-ndk-r10e\toolchains\aarch64-linux-android-4.9\prebuilt\windows\bin\aarch64-linux-android-g++ -fno-exceptions --sysroot=%SYSROOT% -shared -I..\include\jni -I..\include\jni\linux -L..\libs\arm64-v8a -llog -lopus -o ..\libs\arm64-v8a\libopusJNI.so aopus_OpusLibrary.c

set SYSROOT=..\..\..\..\..\android-ndk-r10e\platforms\android-16\arch-arm

..\..\..\..\..\android-ndk-r10e\toolchains\arm-linux-androideabi-4.9\prebuilt\windows\bin\arm-linux-androideabi-g++ -fno-exceptions --sysroot=%SYSROOT% -shared -mcpu=cortex-a8 -mthumb -mfpu=neon -mfloat-abi=softfp -march=armv7-a -I..\include\jni -I..\include\jni\linux -L..\libs\armeabi-v7a -llog -laudioprocessing -o ..\libs\armeabi-v7a\libaudioprocessingJNI.so aaudioprocessing_AudioProcessingLibrary.c

rem set SYSROOT=..\..\..\..\..\android-ndk-r10e\platforms\android-16\arch-x86

rem ..\..\..\..\..\android-ndk-r10e\toolchains\x86-4.9\prebuilt\windows\bin\i686-linux-android-g++ -fno-exceptions --sysroot=%SYSROOT% -shared -mtune=i686 -march=i686 -I..\include\jni -I..\include\jni\linux -L..\libs\x86 -llog -laudioprocessing -o ..\libs\x86\libaudioprocessingJNI.so aaudioprocessing_AudioProcessingLibrary.c
