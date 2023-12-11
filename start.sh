#!/bin/bash

systemctl start docker
docker build -t armlinux . 
docker run --privileged -it --name my-container -v /dev/sdb:/dev/sdb armlinux /bin/bash
