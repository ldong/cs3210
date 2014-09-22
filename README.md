cs3210
======

## Setup virtual image environment

From factor-3210 ssh session

```
user@factor-3210 $ ssh ubuntu@10.0.0.xx
$ sudo -i
# cp /home/ubuntu/.ssh/authorized_keys /root/.ssh/
# apt-get install git
# git clone https://github.com/leecom3025/cs3210.git
# cd cs3210
# chmod +x configenv.sh
# ./configenv.sh
```

Then exit out of the openstack virtual image and log back in as root

```
# exit
$ exit

user@factor-3210 $ ssh root@10.0.0.xx
```

For vim open vim and
`:PluginInstall`

