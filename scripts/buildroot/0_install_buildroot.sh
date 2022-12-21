#!/bin/bash
BUILD_ENV_PATH= dirname $(pwd)
source "${BUILD_ENV_PATH}/build_env.sh"

cd ${ROOT_DIR}
git clone https://git.buildroot.net/buildroot

cd buildroot

git checkout 2021.08.1
sudo apt-get update
sudo apt-get upgrade
sudo apt install sed make binutils build-essential diffutils gcc g++ bash patch gzip bzip2 perl tar cpio unzip rsync file bc findutils wget python3 python-is-python3