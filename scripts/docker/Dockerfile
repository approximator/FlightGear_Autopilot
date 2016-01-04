FROM ubuntu:wily

RUN apt-get update && \
    apt-get install -y git gcc g++ qt5-default qtdeclarative5-dev libqt5svg5-dev qbs

CMD qbs setup-toolchains --detect        && \
    qbs setup-qt --detect                && \
    qbs setup-qt $(which qmake) qt       && \
    qbs config defaultProfile qt         && \
    cd /fgap/src                         && \
    qbs --command-echo-mode command-line && \
    qbs --clean-install-root qbs.installRoot:fgap_install && \
    cp -r fgap_install /result
