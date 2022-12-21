#!/bin/bash
BE_DIR=$(pwd)
ROOT_DIR= dirname $BE_DIR

BUILDROOT_DIR="${ROOT_DIR}/buildroot"
NFSROOT_DIR="${ROOT_DIR}/nfsroot"
TFTP_DIR="${ROOT_DIR}/tftpboot"

BBB_DEFCONFIG="beaglebone_defconfig"
BBB_OVERLAY="beaglebone"

BUILDROOT_DEFCONFIG_DIR="${BUILDROOT_DIR}/configs"
BUILDROOT_OVERLAY_DIR="${BUILDROOT_DIR}/board"

reset