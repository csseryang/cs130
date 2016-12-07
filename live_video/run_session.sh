#!/bin/bash

#for readability
user_ip=$1
session_name=$1
server_ip=$2
video_rate=$3
router_ip=$4
v_ip1=$5
v_ip2=$6


declare -a dests=($v_ip1 $v_ip2)

# 1. create a script that runs ffmpeg
printf "./ffmpeg  -re -i sample.flv -b:v %sk -bufsize %sk -maxrate %sk -acodec copy -vcodec copy -f flv rtmp://" "$video_rate" "$video_rate" "$video_rate"> rffmpeg.sh
printf $server_ip >> rffmpeg.sh
printf "/live/%s" "$session_name">> rffmpeg.sh


chmod +x rffmpeg.sh
scp rffmpeg.sh ucr_video@$user_ip:
ssh -f ucr_video@$user_ip screen -d -m ./rffmpeg.sh    # 2. run the script remotely


# 1. create a script that runs tcpdump
printf 'sudo tcpdump -G 70 -W 1 -i eth0 -w %s.pcap\n' "$session_name">rtcpdump.sh
printf 'tshark -r %s.pcap -Y "tcp.analysis.ack_rtt and ip.src==' "$session_name" >>rtcpdump.sh
printf $router_ip >> rtcpdump.sh
printf '" -e tcp.analysis.ack_rtt -T fields -E separator=, -E quote=d | '>> rtcpdump.sh
printf "cut -d\'\"\' -f2 | awk \'{ sum += \$0; n++ } END { if (n > 0) print 1000*sum / n; }\'> rtt.txt
" >> rtcpdump.sh

chmod +x rtcpdump.sh
scp rtcpdump.sh ucr_video@$user_ip:
ssh -f ucr_video@$user_ip screen -d -m ./rtcpdump.sh   # 2. run the script remotely



# below is for viewers

# 1. create a script that runs tcpdump
printf 'sudo tcpdump -G 70 -W 1 -i eth0 -w %s.pcap\n' "$session_name">rtcpdump.sh
printf 'tshark -r %s.pcap -Y "tcp.analysis.ack_rtt and ip.src==' "$session_name" >>rtcpdump.sh
printf $server_ip >> rtcpdump.sh
printf '" -e tcp.analysis.ack_rtt -T fields -E separator=, -E quote=d | '>> rtcpdump.sh
printf "cut -d\'\"\' -f2 | awk \'{ sum += \$0; n++ } END { if (n > 0) print 1000*sum / n; }\'> rtt.txt
" >> rtcpdump_viewer.sh


# 1. create a script that runs vlc
printf "vlc -I dummy --novideo http://" > runvlc.sh
printf $server_ip >> runvlc.sh
printf ":1935/live/%s/playlist.m3u8 --run-time 70 vlc://quit" "$session_name">> runvlc.sh

printf "\n============== Upload scripts to viewers ==============\n"

chmod +x rtcpdump_viewer.sh
chmod +x runvlc.sh

# copy it to viewers
for dest in "${dests[@]}"; do 
  scp runvlc.sh rtcpdump.sh ucr_video@${dest}:
  ssh -f ucr_video@${dest} screen -d -m ./runvlc.sh
  ssh -f ucr_video@${dest} screen -d -m ./rtcpdump_viewer.sh
done



