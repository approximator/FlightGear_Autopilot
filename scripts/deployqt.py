#!/usr/bin/env python
import os
import sys
import getopt
import subprocess
import re
import shutil
from glob import glob


def usage():
    print("Usage: %s <creator_install_dir> [qmake_path]" % os.path.basename(sys.argv[0]))


class QtDeployer():
    def __init__(self, install_dir, qmake, debug_build):
        self.install_dir = os.path.normpath(install_dir)
        self.qmake = os.path.normpath(qmake)
        self.debug_build = False
        if debug_build == "Debug":
            self.debug_build = True

        p = subprocess.Popen([self.qmake, '-query', 'QT_INSTALL_LIBS'], stdout=subprocess.PIPE)
        self.qt_libs_dir, err = p.communicate()
        self.qt_libs_dir = os.path.normpath(self.qt_libs_dir.rstrip().decode('utf-8'))
        p = subprocess.Popen([self.qmake, '-query', 'QT_INSTALL_BINS'], stdout=subprocess.PIPE)
        self.qt_bin_dir, err = p.communicate()
        self.qt_bin_dir = os.path.normpath(self.qt_bin_dir.rstrip().decode('utf-8'))
        p = subprocess.Popen([self.qmake, '-query', 'QT_INSTALL_PLUGINS'], stdout=subprocess.PIPE)
        self.qt_plugins_dir, err = p.communicate()
        self.qt_plugins_dir = os.path.normpath(self.qt_plugins_dir.rstrip().decode('utf-8'))
        p = subprocess.Popen([self.qmake, '-query', 'QT_INSTALL_QML'], stdout=subprocess.PIPE)
        self.qt_qml_dir, err = p.communicate()
        self.qt_qml_dir = os.path.normpath(self.qt_qml_dir.rstrip().decode('utf-8'))

        if not sys.platform.startswith('win'):
            self.chrpath = 'chrpath'

        print('Qt deployer starting...')
        print('Debug build:   ', self.debug_build)
        print('Install to:    ', self.install_dir)
        print('qmake:         ', self.qmake)
        print('Qt libs dir:   ', self.qt_libs_dir)
        print('Qt bin dir:    ', self.qt_bin_dir)
        print('Qt plugins dir:', self.qt_plugins_dir)
        print('Qt qml dir:    ', self.qt_qml_dir)

    def change_rpath(self, filename):
        directory = os.path.dirname(filename)
        relpath = os.path.relpath(self.install_dir + '/lib', directory)
        command = [self.chrpath, '-r', '$ORIGIN/' + relpath, filename]
        print(command)
        try:
            subprocess.check_call(command)
        except:
            print('Failed to change rpath')

    def copy_libs(self):
        print("copying Qt libraries...")

        lib_ext = '*.so.*'
        dest = os.path.normpath(os.path.join(self.install_dir, 'lib/'))
        if sys.platform.startswith('win'):
            lib_ext = '*.dll'
            dest = os.path.normpath(os.path.join(self.install_dir, 'bin/'))
            self.qt_libs_dir = self.qt_bin_dir

        for needed_lib in self.needed_libraries:
            for lib in glob(os.path.join(self.qt_libs_dir, needed_lib + lib_ext)):
                if sys.platform.startswith('win') and os.path.basename(lib).startswith('Qt'):
                    debug_lib = os.path.basename(lib).split('.')[0].endswith('d')
                    if self.debug_build:
                        if not debug_lib:
                            continue
                    else:
                        if debug_lib:
                            continue

                print('Copy: ', lib, '->', dest)
                if os.path.islink(lib):
                    linkto = os.readlink(lib)
                    try:
                        os.symlink(linkto, os.path.join(dest, os.path.basename(lib)))
                    except:
                        print('Link exists')
                else:
                    if not os.path.exists(dest):
                        os.makedirs(dest)
                    shutil.copy2(lib, os.path.join(dest, os.path.basename(lib)))
                    if not sys.platform.startswith('win'):
                        self.change_rpath(os.path.join(dest, os.path.basename(lib)))

        print('Copying plugins:', self.plugins)
        for plugin in self.plugins:
            target = os.path.join(self.install_dir, 'bin', 'plugins', plugin)
            if os.path.exists(target):
                shutil.rmtree(target)
            pluginPath = os.path.join(self.qt_plugins_dir, plugin)
            if os.path.exists(pluginPath):
                self.copytree(pluginPath, target, symlinks=True)

        if os.path.exists(self.qt_qml_dir):
            print('Copying qt quick 2 imports')
            target = os.path.join(self.install_dir, 'bin', 'qml')
            if os.path.exists(target):
                shutil.rmtree(target)
            self.copytree(self.qt_qml_dir, target, symlinks=True)

    def copy_libclang(self, install_dir, llvm_install_dir):
        libsource = os.path.join(llvm_install_dir, 'lib', 'libclang.so')
        libtarget = os.path.join(install_dir, 'lib')
        if sys.platform.startswith("win"):
            libsource = os.path.join(llvm_install_dir, 'bin', 'libclang.dll')
            libtarget = os.path.join(install_dir, 'bin')
        resourcesource = os.path.join(llvm_install_dir, 'lib', 'clang')
        resourcetarget = os.path.join(install_dir, 'share', 'cplusplus', 'clang')
        print("copying libclang...")
        shutil.copy(libsource, libtarget)
        if not sys.platform.startswith('win') and os.access(d, os.X_OK):
            self.change_rpath(libtarget)
        if os.path.exists(resourcetarget):
            shutil.rmtree(resourcetarget)
        self.copytree(resourcesource, resourcetarget, symlinks=True)

    def deploy(self):
        self.plugins = ['accessible', 'codecs', 'designer', 'iconengines', 'imageformats', 'platformthemes',
                        'platforminputcontexts', 'platforms', 'printsupport', 'sqldrivers']

        self.needed_libraries = [
            'Qt5Core', 'Qt5Widgets', 'Qt5Gui', 'Qt5Qml', 'Qt5Quick', 'Qt5Network',
            'Qt5DBus', 'Qt5Svg', 'icudata', 'icui18n', 'icuuc'
        ]

        if sys.platform.startswith('win'):
            self.needed_libraries.extend(['libgcc_s_dw2-1', 'libwinpthread-1', 'libstdc++-6', 'icuin53', 'icuuc53', 'icudt53'])
            self.copy_libs()
        else:
            self.needed_libraries = map(lambda lib: 'lib' + lib, self.needed_libraries)
            self.copy_libs()

        if 'LLVM_INSTALL_DIR' in os.environ:
            self.copy_libclang(self.install_dir, os.environ["LLVM_INSTALL_DIR"])

        self.write_qt_conf()

    def write_qt_conf(self):
        fileName = os.path.join(os.path.normpath(self.install_dir), os.path.normpath('bin/qt.conf'))
        print('Writing qt.conf:', fileName)
        f = open(fileName, 'w')
        f.write('[Paths]\n')
        f.write('Libraries=../lib\n')
        f.write('Plugins=plugins\n')
        f.write('Imports=imports\n')
        f.write('Qml2Imports=qml\n')
        f.close()

    def copytree(self, src, dst, symlinks=False, ignore=None):
        if not os.path.exists(dst):
            os.makedirs(dst)
        for item in os.listdir(src):
            s = os.path.join(src, item)
            d = os.path.join(dst, item)
            if os.path.isdir(s):
                self.copytree(s, d, symlinks, ignore)
            else:
                shutil.copy2(s, d)
                print('Copy:', s, '->', d)
                if not sys.platform.startswith('win') and os.access(d, os.X_OK):
                    self.change_rpath(d)

if __name__ == "__main__":
    if sys.platform == 'darwin':
        print("Use macqtdeploy!")
        sys.exit(2)
    else:
        try:
            opts, args = getopt.gnu_getopt(sys.argv[1:], 'hi', ['help', 'ignore-errors'])
        except:
            usage()
            sys.exit(2)

        deployer = QtDeployer(os.path.normpath(args[0]), args[1], args[2])
        deployer.deploy()
