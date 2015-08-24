#!/usr/bin/env python
import os
import sys
import getopt
import subprocess
import shutil
from glob import glob

# Packages to install:
#    libglib2.0-0
#    libxext6
#    libgl1-mesa-glx
#    libxi6
#    libsm6
#    libxrender1
#    libfontconfig1


def usage():
    print("Usage: %s <creator_install_dir> [qmake_path]" % os.path.basename(sys.argv[0]))


class QtDeployer():
    def __init__(self, fgap_exe_file, install_dir, data_dir, libraries_dir, qmake, debug_build):
        self.fgap_exe_file = os.path.normpath(fgap_exe_file)
        self.install_dir = os.path.normpath(install_dir)
        self.data_dir = os.path.normpath(data_dir)
        self.libraries_dir = os.path.normpath(libraries_dir)
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
            self.chrpath = 'patchelf'

        print('Qt deployer starting...')
        print('fgap_exe_file: ', self.fgap_exe_file)
        print('Install dir:   ', self.install_dir)
        print('Data dir:      ', self.data_dir)
        print('Libraries dir: ', self.libraries_dir)
        print('qmake:         ', self.qmake)
        print('Debug build:   ', self.debug_build)
        print('Qt libs dir:   ', self.qt_libs_dir)
        print('Qt bin dir:    ', self.qt_bin_dir)
        print('Qt plugins dir:', self.qt_plugins_dir)
        print('Qt qml dir:    ', self.qt_qml_dir)

    def change_rpath(self, filename, new_rpath):
        rpath = '$ORIGIN/' + new_rpath
        if new_rpath == '.':
            rpath = '$ORIGIN'
        command = [self.chrpath, '--set-rpath', rpath, filename]
        try:
            subprocess.check_call(command)
        except:
            print('Failed to change rpath')

    def get_dependencies(self, file_name, dependencies):
        try:
            p = subprocess.Popen([file_name], stdout=subprocess.PIPE,
                                 env=dict(os.environ.copy(), LD_TRACE_LOADED_OBJECTS='1'))
            deps, err = p.communicate()
        except OSError:
            return

        for lib in deps.split('\n'):
            lib_name = ''
            lib_dir = ''
            lib_name_and_dir = lib.split('=>')
            if len(lib_name_and_dir) > 1:
                lib_name = lib_name_and_dir[0].strip()
                lib_dir = lib_name_and_dir[1].strip()
                lib_dir = lib_dir[0:lib_dir.find('(')].strip()
            if lib_name and lib_dir:
                self.get_dependencies(lib_dir, dependencies)
                dependencies[lib_name] = lib_dir

    def copy_libs(self):
        print("copying Qt libraries...")

        lib_ext = '*.so.*'
        dest = self.libraries_dir
        if sys.platform.startswith('win'):
            lib_ext = '*.dll'
            dest = os.path.normpath(os.path.join(self.data_dir, '..'))
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

                # print('Copy: ', lib, '->', dest)
                if os.path.islink(lib):
                    linkto = os.readlink(lib)
                    try:
                        os.symlink(linkto, os.path.join(dest, os.path.basename(lib)))
                    except:
                       # print('Link exists')
                       pass
                else:
                    if not os.path.exists(dest):
                        os.makedirs(dest)
                    shutil.copy2(lib, os.path.join(dest, os.path.basename(lib)))
                    if not sys.platform.startswith('win'):
                        self.change_rpath(os.path.join(dest, os.path.basename(lib)),
                                          os.path.relpath(dest, self.libraries_dir))

        print('Copying plugins:', self.plugins)
        for plugin in self.plugins:
            target = os.path.join(self.data_dir, 'plugins', plugin)
            if os.path.exists(target):
                shutil.rmtree(target)
            pluginPath = os.path.join(self.qt_plugins_dir, plugin)
            if os.path.exists(pluginPath):
                self.copytree(pluginPath, target, symlinks=True)

        if os.path.exists(self.qt_qml_dir):
            print('Copying qt quick 2 imports')
            target = os.path.join(self.data_dir, 'qml')

            for lib in filter(lambda x: os.path.basename(x) in self.needed_qml, glob(self.qt_qml_dir+'/*')):
                self.copytree(lib,os.path.join(target, os.path.basename(lib)), symlinks=True)

    def copy_libclang(self, data_dir, llvm_install_dir):
        libsource = os.path.join(llvm_install_dir, 'lib', 'libclang.so')
        libtarget = os.path.join(self.libraries_dir)
        if sys.platform.startswith("win"):
            libsource = os.path.join(llvm_install_dir, '..', 'libclang.dll')
            libtarget = os.path.join(data_dir, '..')
        resourcesource = os.path.join(llvm_install_dir, 'lib', 'clang')
        resourcetarget = os.path.join(data_dir, 'share', 'cplusplus', 'clang')
        print("copying libclang...")
        shutil.copy(libsource, libtarget)
        if not sys.platform.startswith('win') and os.access(d, os.X_OK):
            self.change_rpath(libtarget)
        if os.path.exists(resourcetarget):
            shutil.rmtree(resourcetarget)
        self.copytree(resourcesource, resourcetarget, symlinks=True)

    def deploy(self):
        if not sys.platform.startswith('win'):
            self.change_rpath(self.fgap_exe_file,
                              os.path.relpath(self.libraries_dir, os.path.dirname(self.fgap_exe_file)))

        self.plugins = ['iconengines', 'imageformats', 'platformthemes',
                        'platforminputcontexts', 'platforms', 'xcbglintegrations']

        self.needed_libraries = [
            'Qt5Core', 'Qt5Widgets', 'Qt5Gui', 'Qt5Qml', 'Qt5Quick', 'Qt5Network',
            'Qt5DBus', 'Qt5Svg', 'icudata', 'icui18n', 'icuuc'
        ]

        self.needed_qml = ["QtQuick", "QtQuick.2", "QtGraphicalEffects"]

        if sys.platform.startswith('win'):
            self.needed_libraries.extend(['libgcc_s_dw2-1', 'libwinpthread-1', 'libstdc++-6', 'icuin53', 'icuuc53', 'icudt53'])
            self.copy_libs()
        else:
            self.needed_libraries = map(lambda lib: 'lib' + lib, self.needed_libraries)
            self.copy_libs()

        if 'LLVM_INSTALL_DIR' in os.environ:
            self.copy_libclang(self.data_dir, os.environ["LLVM_INSTALL_DIR"])

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
#                print('Copy:', s, '->', d)
                if not sys.platform.startswith('win') and os.access(d, os.X_OK):
                    self.change_rpath(d, os.path.relpath(self.libraries_dir, os.path.dirname(d)))


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
                              # fgap_exe_name, install_dir, data_dir, libraries_dir, qmake, debug_build
        deployer = QtDeployer(os.path.normpath(args[0]), args[1], args[2], args[3], args[4], args[5])
        deployer.deploy()
