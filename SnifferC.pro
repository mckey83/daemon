TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    CliMode/command/commands.c \
    CliMode/command/is_command.c \
    CliMode/test/coretest.c \
    DaemonMode/daemonmode.c \
    DaemonMode/processidentifier/processidentifier.c \
    DaemonMode/daemon_keeper/daemon_keeper.c \
    DaemonMode/log/log.c \
    DaemonMode/sniffer/sniffer.c \
    DaemonMode/store/store_simple.c \
    DaemonMode/workwithfile/workwithfile.c \
    DaemonMode/daemon/daemon.c \
    CliMode/climode.c

DISTFILES += \
    startEth0.sh \
    startWlan0.sh \
    stop.sh

HEADERS += \
#    CliMode/data/record.h \
    CliMode/data/initialize_data.h \
    CliMode/command/commands.h \
    CliMode/command/is_command.h \
    CliMode/test/coretest.h \
    CliMode/test/test_macro.h \
    DaemonMode/daemonmode.h \
    DaemonMode/processidentifier/processidentifier.h \
    DaemonMode/daemon_keeper/daemon_keeper.h \
    DaemonMode/data/initialize_data.h \
    DaemonMode/data/record.h \
    DaemonMode/log/log.h \
    DaemonMode/macro/ip_to_d_d_d_d.h \
    DaemonMode/sniffer/sniffer.h \
    DaemonMode/store/store_simple.h \
    DaemonMode/tests/test_daemon.h \
    DaemonMode/tests/test_daemon_keeper.h \
    DaemonMode/tests/test_log.h \
    DaemonMode/tests/test_main.h \
    DaemonMode/tests/test_proccess_monitor.h \
    DaemonMode/tests/test_simple_store.h \
    DaemonMode/tests/test_sniffer.h \
    DaemonMode/tests/test_work_with_file.h \
    DaemonMode/workwithfile/workwithfile.h \
    DaemonMode/daemon/daemon.h \
    CliMode/climode.h

INCLUDEPATH += /usr/include/nptl
LIBS += -L/usr/lib/nptl -lpthread
