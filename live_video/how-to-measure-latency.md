
Given: 
client `c1`, server `s1`

Protocol:

1. `ssh` into `c1`

2. upload a video file as live stream to `s1` by `ffmpeg`, meanwhile capturing traffic to a pcap file on `s1` by `tcpdump`

3. extract `rtt` by 
```
tshark -r [filename].pcap -Y "tcp.analysis.ack_rtt and ip.src==[server_ip]" -e tcp.analysis.ack_rtt -T fields -E separator=, -E quote=d | cut -d'"' -f2 | awk '{ sum += $0; n++ } END { if (n > 0) print 1000*sum / n; }'
```

It equals the ping result I got by  pinging `s1` from `c1` (Actually I use a tool called `hping3` instead of `ping`)

