#!/bin/bash

systemctl start docker
docker build -t armlinux . 
docker run -it --name my-container armlinux /bin/bash 
