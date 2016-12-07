#!/bin/bash
# delete results on users

pssh -h userlist.txt -l ucr_video -o ./tmp2 "rm *.pcap rtt.txt rffmpeg.sh rtcpdum*.sh runvlc.sh rping.sh"
