
<h3>iptables show rules:</h3>

```bash
sudo iptables -t nat -L
```

<h3>delete rules:</h3>
[reference](http://stackoverflow.com/questions/8239047/iptables-how-to-delete-postrouting-rule) 

on router:
```bash
sudo iptables -t nat -D PREROUTING 1
sudo iptables -t nat -D POSTROUTING 1 
```

on user:

```
sudo iptables -t nat -D OUTPUT 1
```

<h3>Approach one: change both user and router</h3>
<h4>On user: direct outgoing traffic to a port </h4>
```
sudo iptables -t nat -A OUTPUT -p tcp --dport [router-port] -j DNAT --to-destination  [routerip]:[router-port]
```
<h4>On router:</h4>
```
sudo iptables -t nat -A PREROUTING -s [user-ip] -p tcp --dport [router-port] -j DNAT --to-destination [server-ip]:[server-port]

```
```
sudo iptables -t nat -A POSTROUTING -j MASQUERADE
```

But actuallly I should just use:
...


