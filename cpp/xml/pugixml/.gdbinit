file ./a.out
set args 11

#file ./service.mpss.bin
#set args --XMLConfigFile /home/spring/project/bobqf/product/Linux64/etc/instance1/services/main/service.main.sendfe_bob.com.xml >/dev/null 2>&1

set logging off
set print element 0
source /tmp/bts.tmp

start
#run

set follow-fork-mode child
set detach-on-fork on
set scheduler-locking off

