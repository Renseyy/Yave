#!/bin/bash


#consts
PROJECT="Yave"
PACK_BASE="https://kk.gpk.opole.pl/pack?project=$PROJECT"

baseDir="$PWD"
vorkDir="$baseDir/.vork"
statusFile="$vorkDir/runStatus.sta"
buildDir="$vorkDir/build"
sourceDir="$vorkDir/source"
packDir="$vorkDir/pack"
identificationFile="$packDir/author.vrn"
manifestFile="$packDir/manifest.vrn"
tmpDir="$vorkDir/tmp"

function __debianInstall {
    sudo apt-get install cmake python3 pip -y;
}

function __archInstall {
    sudo pacman -S --noconfirm cmake python3 python-pip;
}

function util:getYaveVersion {
    cmakeFile="$sourceDir/CMakeLists.txt";
    cmakeLists=$(cat "$cmakeFile");
    regex='\(YAVE VERSION ([0-9]+\.[0-9]+\.[0-9]+)\)'
    [[ "$cmakeLists" =~ $regex ]];
    echo "${BASH_REMATCH[1]}";
}
function getArch {
    uname -m;
}

function web:getLast {
   curl -Ls "$PACK_BASE&action=lastVersion"
}

function web:haveVersion {
    version=$1
    arch=$(getArch)
    curl -Ls "$PACK_BASE&action=exist&version=$version&arch=$arch"
}

function web:sendFile {
    version=$1
    arch=$2
    checksum=$3
    file=$4
    curl -L -F package="@$file" -F project="$PROJECT" -F action=send -F version="$version" -F arch="$arch" -F checksum="$checksum" --progress-bar https://kk.gpk.opole.pl/pack/
}
function web:publicIp {
    curl -Ls "$PACK_BASE&action=ip"
}

function os:localIp {
    ip route get 1.2.3.4 | awk '{printf $7}'
}

function util:ip {
    echo "$(os:localIp)@$(web:publicIp)"
}
function compiler:prepare {
    echo -e "\e[35mPreparing to installation\e[0m"
    if [[ ! -f "$statusFile" ]]; then
        mkdir -p "$vorkDir";
        touch "$statusFile";
    fi
    status=$(cat "$statusFile");
    if [[ "$status" == "" ]]; then
        git:clone
    fi
    echo -e "\e[32mStatus file created\e[0m"
}
function compiler:install {
    status=$(cat "$statusFile");
    cd "$sourceDir" || exit
    if [[ "$status" == "" ]]; then
        # Install depending on platform
        idLike=$(grep 'ID_LIKE' /etc/os-release)
        baseOs=${idLike:8}
        echo -e "\e[35mInstalling dependences for base platform $baseOs \e[0m"
        case "$baseOs" in
            "arch")
                __archInstall;
                ;;

            "debian")
                __debianInstall;
                ;;
            *)
                echo "System $baseOs is not supported yet";
                cd "$baseDir" || exit
                exit 255;
                ;;
        esac
        if [ ! "$?" -eq 0 ]; then
            echo -e "\e[31mError occurred, exiting\e[0m"
            cd "$baseDir" || exit
            exit 255;    
        fi
        echo "1" > "$statusFile"
        echo -e "\e[32mInstalled all dependences\e[0m"
        cd "$baseDir" || exit
    fi
    status=$(cat "$statusFile");
    if [[ ! "$status" -gt 1 ]]; then
        echo -e "\e[35mBuilding\e[0m"
        mkdir -p "$buildDir"
        cmake -S . -B "$buildDir"
        if [ ! "$?" -eq 0 ]; then
            echo -e "\e[31mError occurred, exiting\e[0m"
            cd ../
            exit 255;    
        fi
        echo "2" > "$statusFile"
        echo -e "\e[32mBuilded\e[0m"
    fi
    status=$(cat "$statusFile");
    if [[ "$status" == "2" ]]; then
        echo -e "\e[35mBuilding libYave.a\e[0m"
        mkdir -p "$buildDir"
        cmake --build "$buildDir"
        if [ ! "$?" -eq 0 ]; then
            echo -e "\e[31mError occurred, exiting\e[0m"
            cd ../
            exit 255;    
        fi
        echo "2" > "$statusFile"
        echo -e "\e[32mBuilded libYave.a\e[0m"
    fi
    cd ../
}
function compiler:compile {
    compiler:prepare
    compiler:install
}
function git:clone {
    echo -e "\e[35mDownloading Yave source\e[0m"
    git clone https://github.com/Renseyy/Yave.git "$sourceDir"
    if [ ! "$?" -eq 0 ]; then
        echo -e "\e[31mError occurred, exiting\e[0m"
        cd ../
        exit 255;    
    fi
    echo -e "\e[32mDownloaded\e[0m"
}

function main:install {
    # Check is last version exists in cloud
    lastVersion="$(web:getLast)"
    lastVersion='1.0.2'
    inCloud="$(web:haveVersion "$lastVersion")"
    if [[ "$inCloud" == "true" ]]; then
        echo "Pobieram wersję z chmury";
    else
        echo -e "\e[35mWe do not have this version in the cloud, automatic compilation will take place\e[0m"
        compiler:compile
    fi
}
if [[ "$1" == "upload" ]]; then
    echo -e "\e[35mBy sending files to the server, you allow the identification file to be included\e[0m"
    echo "The identification file consists of:"
    echo " - the specifics of your system"
    echo " - ip address"
    echo " - your email adress"
    echo " - your name "
    echo ""
    echo -e -n "\e[33mDo you want to continue?\e[0m [Y/n]"
    read -N 1 -s -r input 
    if [[ "$input" == "n" || "$input" == "N" ]]; then 
        echo -e "\e[35mCancelled\e[0m"
        exit 0    
    fi
    echo -e "\n"
    echo -e "\e[35mProvide your personal information:\e[0m"

    ip=$(util:ip)
    id=$(uname -a)
    email=$(git config user.email)
    echo -e -n "\e[34mYour email adress:\e[0m"
    read -r -e -p " " -i "$email" email

    name=$(git config user.name)
    echo -e -n "\e[34mYour name:\e[0m"
    read -r -e -p " " -i "$name" name

    all="$email|$name|$ip|$id"
    hash=$(echo -n "$all" | sha512sum | awk '{printf $1}')
    allFormated="email: $email\nname: $name\nip: $ip\nid: $id\nhash: $hash"

    echo ""
    echo -e "\e[35mYour identification file preview:\e[0m"
    echo -e "\e[36mEmail: \e[0m$email"
    echo -e "\e[36mName:  \e[0m$name"
    echo -e "\e[36mIp:    \e[0m$ip"
    echo -e "\e[36mId:    \e[0m$id"
    echo -e "\e[36mHash:  \e[0m$hash"
    
    echo ""
    echo -e -n "\e[33mIs the data provided correct?\e[0m [Y/n]"
    read -N 1 -s -r input 
    if [[ "$input" == "n" || "$input" == "N" ]]; then 
        echo -e "\e[35mCancelled\e[0m"
        exit 0    
    fi

    echo -e "\n\e[35mCreating an identification file...\e[0m"
    mkdir -p "$packDir"
    echo -e "$allFormated" > "$identificationFile"
    echo -e "\e[32mCreated\e[0m"
    echo -e "\e[35mCopying files...\e[0m"
    cp "$buildDir/libYAVE.a" "$packDir/"
    cp -r "$sourceDir/API" "$packDir/"
    echo -e "\e[32mCopied\e[0m"

    echo -e "\e[35mCreating a manifest\e[0m"
    version=$(util:getYaveVersion)
    time=$(date +%s)
    arch=$(getArch)
    manifest="version: $version\ntime: $time\narch: $arch"
    echo -e "$manifest" > "$manifestFile"
    echo -e "\e[32mCreated manifest file\e[0m"

    echo -e "\e[35mPackaging\e[0m"
    mkdir -p "$tmpDir"
    tmpPackageFile="$tmpDir/package.tar.gz"
    tar cv "$packDir" | gzip --best > "$tmpPackageFile"
    checksum=$(sha512sum "$tmpPackageFile" | awk '{printf $1}')
    echo -e "\e[32mCreated package"
    echo -e "\e[35mSending to server\e[0m"
    web:sendFile "$version" "$arch" "$checksum" "$tmpPackageFile"
else 
    main:install
fi

