import os
import sys

curr_dir = os.path.dirname(sys.argv[0])
curr_dir = os.path.abspath(curr_dir)

os.chdir(curr_dir)
os.system('make')
