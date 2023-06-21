#!/usr/bin/env python

"""
Generate test examples script.
./gen_tests.py ${CMAKE_SOURCE_DIR}

Required shell_source, pip install shell_source
"""

import os
import sys
from shell_source import source


def main():
  if len(sys.argv) == 1:
    print('no cmake source directory')
    sys.exit(1)

  source_dir = sys.argv[1]
  if not os.path.isdir(source_dir):
    print(f'{source_dir} is not a source directory')

  enable_riscv_script = os.path.join(source_dir, 'scripts', 'enable_riscv.sh')
  if not os.path.isfile(enable_riscv_script):
    print(f'{enable_riscv_script} is not a file')
  env_vars = source(enable_riscv_script, 'bash')
  riscv_home = env_vars['RISCV_HOME']
  os.environ['CC'] = f'{riscv_home}/bin/riscv64-unknown-elf-gcc'
  os.environ['CXX'] = f'{riscv_home}/bin/riscv64-unknown-elf-g++'

  curr_dir = os.path.dirname(sys.argv[0])
  curr_dir = os.path.abspath(curr_dir)

  py_exe = sys.executable

  for subdir in os.listdir(curr_dir):
    subdir = os.path.join(curr_dir, subdir)
    if not os.path.isdir(subdir):
      continue
    os.system(f'{py_exe} {subdir}/make.py')

if __name__ == '__main__':
  main()