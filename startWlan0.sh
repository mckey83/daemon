#!/usr/bin/env bash
echo "Sniffer start Wlan0"
sudo start-stop-daemon -Sbvx /home/alex/workspaceCPP/build-SnifferC-Desktop_Qt_5_7_0_GCC_64bit-Release/SnifferC select_iface_[wlan0] start
exit
