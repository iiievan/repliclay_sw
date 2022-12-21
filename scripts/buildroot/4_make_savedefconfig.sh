SCRIPT_DIR=$( cd -- "$( dirname -- "${0}" )" &> /dev/null && pwd )
cd ..
./build_env.sh

cd ${BUILDROOT_DIR}

make savedefconfig