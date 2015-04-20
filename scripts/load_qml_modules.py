import os
import sys
import shutil
import urllib2
import zipfile
import tempfile

MODULES_VERSION = '0.0.5'


class ModulesLoader:
    def __init__(self, build_tree, sources_path, install_path):
        self.build_tree = build_tree
        self.sources_path = sources_path
        self.install_path = install_path

    def download(self, url, download_dir, src_dir):
        target_file = os.path.join(download_dir, src_dir + '.zip')
        print 'Downloading module from:', url

        if os.path.exists(target_file):
            print 'File', target_file, 'already exists.'
        else:
            print 'Saving to: ', target_file
            f = urllib2.urlopen(url)
            data = f.read()
            with open(target_file, 'wb') as target_f:
                target_f.write(data)
                target_f.close()

        with zipfile.ZipFile(target_file, 'r') as z:
            zip_dirname = z.namelist()[0]
            extract_to = os.path.join(download_dir, zip_dirname)
            rename_to = os.path.join(download_dir, src_dir)
            print 'Extracting to ', extract_to
            if os.path.exists(extract_to):
                shutil.rmtree(extract_to)
            if os.path.exists(rename_to):
                shutil.rmtree(rename_to)
            z.extractall(download_dir)
            print 'Rename ', extract_to, ' -> ', rename_to
            os.rename(extract_to, rename_to)

    def deploy(self, module_dir, module_name):
        print 'Deploy module', module_name
        dest_dir = os.path.join(self.install_path, module_name)
        if os.path.exists(dest_dir):
            shutil.rmtree(dest_dir)   # WARNING: take care of this rmtree!
        m_dir = os.path.join(module_dir, 'modules')
        m_dir = os.path.join(m_dir, module_name)
        print m_dir, ' -> ', dest_dir
        shutil.copytree(m_dir, dest_dir)

    def download_and_deploy(self, src_dir, module_name, url):
        download_dir = tempfile.gettempdir()
        self.download(url, download_dir, src_dir)
        self.deploy(os.path.join(download_dir, src_dir), module_name)

    def run(self):
        self.download_and_deploy('qml-material',  'Material', 'https://github.com/papyros/qml-material/archive/v' + MODULES_VERSION + '.zip')
        self.download_and_deploy('qml-extras', 'Material/Extras', 'https://github.com/papyros/qml-extras/archive/v' + MODULES_VERSION + '.zip')
        self.deploy(os.path.join(self.sources_path, 'qml-fgear'), 'FGear')

if __name__ == '__main__':
    if len(sys.argv) < 3:
        print 'Usage: \n       ', os.path.basename(__file__), ' <module_source_path> <install_path>'
        sys.exit(1)

    ml = ModulesLoader(os.path.dirname(os.path.dirname(os.path.realpath(__file__))), sys.argv[1], sys.argv[2])
    ml.run()
