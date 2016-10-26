#!/bin/sh


IPV6_INCOMPATIBLE_FUNC_LIST="inet_addr inet_aton inet_lnaof inet_makeaddr inet_netof inet_network inet_ntoa inet_ntoa_r bindresvport getipv4sourcefilter setipv4sourcefilter gethostbyname gethostbyaddr getservbyname getservbyport gethostbyname2"

SCAN_PATH_LIST=`find . -type d -name trunk`

for i in $SCAN_PATH_LIST
do
    for j in $IPV6_INCOMPATIBLE_FUNC_LIST
    do
        grep --color -inrI "$j" ${i}*
    done
done

 
