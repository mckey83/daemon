#!/usr/bin/env bash
echo "Sniffer start Ethernet"
sudo start-stop-daemon -Sbvx /home/alex/workspaceCPP/build-SnifferC-Desktop_Qt_5_7_0_GCC_64bit-Release/SnifferC select_iface_[eth0] start
exit
