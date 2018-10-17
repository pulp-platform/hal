import os
import subprocess
import shlex
import plpconfig
import SCons.Util

install_dir = os.environ.get('INSTALL_DIR')
target_install_dir = os.environ.get('TARGET_INSTALL_DIR')

if install_dir is None:
  install_dir = 'install'

if target_install_dir is None:
  target_install_dir = 'install'

files = [ 'hal/pulp.h', 'hal/utils.h', 'hal/pulp_io.h', 'hal/debug_bridge/debug_bridge.h' ]

files += subprocess.check_output(shlex.split('plpfiles copy --item=hal_files')).split()
src_files = subprocess.check_output(shlex.split('plpfiles copy --item=hal_src_files')).split()


configs = plpconfig.get_configs_from_env()

def append_file(file):
  global files
  if not file in files:
    files += file


for config in configs:

  udma_i2s = config.get_child_int('**/udma/i2s/version')
  if udma_i2s is not None:
    append_file('hal/udma/i2s/udma_i2s_v%d.h' % udma_i2s)

targets = []

for file in files:
  file_path = os.path.join('include', file)
  targets.append(InstallAs(os.path.join(target_install_dir, file_path), file_path))

for file in src_files:
  file_path = os.path.join('src', file)
  targets.append(InstallAs(os.path.join(target_install_dir, file_path), file_path))


Default(targets)