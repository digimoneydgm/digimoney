# digimoney
BUILD LINUX

    git clone https://github.com/juninhodecio/digimoney.git

    cd digimoney/src

    make -f makefile.unix # Headless

(optional)

    strip digimoneyd

    sudo cp digimoneyd /usr/local/bin


Deps

apt-get install git

apt-get install build-essential libtool automake autotools-dev autoconf pkg-config libssl-dev libgmp3-dev libevent-dev bsdmainutils 

apt-get install libboost-all-dev

add-apt-repository ppa:bitcoin/bitcoin

apt-get update

apt-get install libdb4.8-dev libdb4.8++-dev

apt-get install libminiupnpc-dev




For digimoney-qt


apt-get install libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler

apt-get install libqrencode-dev qrencode 

apt-get install qt5-default
