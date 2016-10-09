TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    sniffer/sniffer.c \
    store/initialize_store.c \
    command/commands.c \
    show/show.c \
    command/is_command.c \
    store/store_simple.c \
    test/coretest.c \
    test/timer/timer.c \
    daemon/daemon.c \
    test/store_test.c

DISTFILES +=

HEADERS += \
    sniffer/sniffer.h \
    store/store.h \
    data/record.h \
    data/initialize_data.h \
    store/initialize_store.h \
    macro/ip_to_d_d_d_d.h \
    command/commands.h \
    show/show.h \
    command/is_command.h \
    data/data.h \
    store/store_simple.h \
    test/coretest.h \
    test/timer/timer.h \
    test/test_macro.h \
    daemon/daemon.h \
    test/store_test.h

INCLUDEPATH += /usr/include/nptl
LIBS += -L/usr/lib/nptl -lpthread
