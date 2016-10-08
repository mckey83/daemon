TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    sniffer/sniffer.c \
    test/maintest.c \
    store/initialize_store.c \
    command/commands.c \
    show/show.c \
    command/is_command.c \
    store/store_simple.c

DISTFILES +=

HEADERS += \
    sniffer/sniffer.h \
    store/store.h \
    data/record.h \
    test/maintest.h \
    data/initialize_data.h \
    store/initialize_store.h \
    macro/ip_to_d_d_d_d.h \
    command/commands.h \
    show/show.h \
    command/is_command.h \
    data/data.h \
    store/store_simple.h

INCLUDEPATH += /usr/include/nptl
LIBS += -L/usr/lib/nptl -lpthread
