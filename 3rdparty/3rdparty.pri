INCLUDEPATH += $$PWD/libssh2/include

win32-msvc* {
    win32-msvc2015 {
        message("msvc2015 detected")
        WIN_DEPS_VERSION = v140
    } else {
        error("Your msvc version is not suppoted. qredisclient requires msvc2015")
    }
    
    LIBSSH_LIB_PATH = $$PWD/libssh2/build/src/release

    defined(OPENSSL_STATIC) {
      OPENSSL_LIB_PATH = C:\OpenSSL-Win32\lib\VC\static
    } else {
      OPENSSL_LIB_PATH = C:\OpenSSL-Win32\lib\VC
    }

    LIBS += -L$$LIBSSH_LIB_PATH -L$$OPENSSL_LIB_PATH -llibssh2 -llibeay32MD -lgdi32 -lws2_32 -lkernel32 -luser32 -lshell32 -luuid -lole32 -ladvapi32
} else {
    LIBS += /usr/local/lib/libssh2.a -lz -lssl -lcrypto

    unix:mac {
        INCLUDEPATH += /usr/local/opt/openssl/include
        LIBS += -L/usr/local/opt/openssl/lib
    } else {
        INCLUDEPATH += /usr/local/include/
    }
}
