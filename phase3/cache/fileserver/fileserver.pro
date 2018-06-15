QT       += core websockets
QT       -= gui

TARGET = fileserver
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    filereader.cpp \
    fileserver.cpp \
    main.cpp \
    readerwritercache.cpp \
    readerwriterlock.cpp \
    requesthandler.cpp \
    responsedispatcherthread.cpp

HEADERS += \
    abstractbuffer.h \
    filereader.h \
    fileserver.h \
    option.h \
    producerconsumerbuffer.h \
    readerwritercache.h \
    readerwriterlock.h \
    request.h \
    requestdispatcherthread.h \
    requesthandler.h \
    response.h \
    responsedispatcherthread.h \
    runnable.h \
    threadpool.h


EXAMPLE_FILES += fileclient.html

