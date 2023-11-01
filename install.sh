#!/bin/bash
function __debianInstall {
    sudo apt-get install cmake python3 pip -y;
}

function __archInstall {
    sudo pacman -S --noconfirm cmake python3 python-pip;
}


vorkDir='.vork';
statusFile="$vorkDir/runStatus.stat";
buildDir="$vorkDir/build"
# Create status file if not exists
if [[ ! -f "$statusFile" ]]; then
    mkdir -p "$vorkDir";
    touch "$statusFile";
fi

# Check current state of build
status=$(cat "$statusFile");
if [[ "$status" == "" ]]; then
    # Install depending on platform
    idLike=$(grep 'ID_LIKE' /etc/os-release)
    baseOs=${idLike:8}
    echo -e "\e[33mInstalling dependences for base platform $baseOs \e[0m"
    case "$baseOs" in
        "arch")
            __archInstall;
            ;;

        "debian")
            __debianInstall;
            ;;
        *)
            echo "System $baseOs is not supported yet";
            exit 255;
            ;;
    esac
    if [ ! "$?" -eq 0 ]; then
        echo -e "\e[31mError occurred, exiting\e[0m"
        exit 255;    
    fi
    echo "1" > "$statusFile"
    echo -e "\e[32mInstalled all dependences\e[0m"
fi

if [[ ! "$status" -gt 1 ]]; then
    echo -e "\e[33mBuilding[0m"
    mkdir -p "$buildDir"
    cmake -S . -B "$buildDir"
    if [ ! "$?" -eq 0 ]; then
        echo -e "\e[31mError occurred, exiting\e[0m"
        exit 255;    
    fi
    echo "2" > "$statusFile"
    echo -e "\e[32mBuilded[0m"
fi

if [[ "$status" == 2 ]]; then
    echo -e "\e[33mBuilding libYave.a\e[0m"
    mkdir -p "$buildDir"
    cmake --build "$buildDir"
    if [ ! "$?" -eq 0 ]; then
        echo -e "\e[31mError occurred, exiting\e[0m"
        exit 255;    
    fi
    echo "2" > "$statusFile"
    echo -e "\e[32mBuilded libYave.a\e[0m"
fi
