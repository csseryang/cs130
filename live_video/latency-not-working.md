We can have this:

<h4>on c1 we ping s1, let's say 20ms.</h4>

 After adding netem 500ms, ping again, it will be 520 ms.
 
To add:

`sudo tc qdisc add dev eth0 root netem delay 500ms`
	
To delete rule:

`sudo tc qdisc del dev eth0 root`

<h4>c1 uploads video to s1, I extracted RTT from the traffic, let's say 21ms.</h4>

on c1(need to edit rffmpeg.sh first): `./rffmpeg.sh`


To run tcpdump for 70s:

`sudo tcpdump -G 70 -W 1 -i eth0 -w [name].pcap`
      
The rules to extract:

`tshark -r [name].pcap -Y "tcp.analysis.ack_rtt and ip.dst==[server-ip]" -e tcp.analysis.ack_rtt -T fields -E separator=, -E quote=d | cut -d'"' -f2 | awk '{ sum += $0; n++ } END { if (n > 0) print 1000*sum / n; }`
			
After adding netem 500ms, it should be 521 ms. But now it's still 21ms.


