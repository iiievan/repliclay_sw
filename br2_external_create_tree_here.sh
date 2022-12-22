#!/bin/bash
echo "Enter buildroot project name: "
read PROJ_NAME

mkdir board
mkdir package
mkdir patches
mkdir configs
mkdir board/${PROJ_NAME}
mkdir board/rootfs_overlay
sudo chmod 777 board/
sudo chmod 777 package/
sudo chmod 777 patches/
sudo chmod 777 configs/
sudo chmod 777 board/${PROJ_NAME}
sudo chmod 777 board/${PROJ_NAME}
echo -n > board/${PROJ_NAME}/users.txt
echo -n > board/${PROJ_NAME}/linux.config
echo -n > Config.in
echo -n > external.mk
echo 'name: repliclay_sw
desc: Repliclay project external-tree for buildroot' > external.desc

sudo chmod 777 board/${PROJ_NAME}/users.txt
sudo chmod 777 board/${PROJ_NAME}/linux.config
sudo chmod 777 Config.in
sudo chmod 777 external.desc
sudo chmod 777 external.mk