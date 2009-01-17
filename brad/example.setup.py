#!/usr/bin/env python
# build with: $ python setup.py build_ext --inplace
# clean with: # python setup.py clean --all
# see:
# http://www.scipy.org/Documentation/numpy_distutils
# http://docs.cython.org/docs/tutorial.html



from numpy.distutils.misc_util import get_numpy_include_dirs
from numpy.distutils.misc_util import Configuration
from numpy.distutils.core import setup
from numpy.distutils.core import Command

# ADAPT THIS TO FIT YOUR SYSTEM
include_dirs = [get_numpy_include_dirs(),'../cppad-20081128']
extra_compile_args = ['-ftemplate-depth-100 -DBOOST_PYTHON_DYNAMIC_LIB']
library_dirs = ['/usr/lib']
libraries = ['boost_python']


# IT IS USUALLY NOT NECESSARY TO CHANGE ANTHING BELOW THIS POINT
# override default setup.py help output
import sys
if len(sys.argv) == 1:
	print """

	You didn't enter what to do!

	Options:
	1: build the extension with
	   python setup.py build_ext --inplace

	2: remove generated files with
	   python setup.py clean --all


	Remark: This is an override of the default behaviour of the distutils setup.
	"""
	exit()

class clean(Command):
	"""
	This class is used in numpy.distutils.core.setup.
	When $python setup.py clean is called, an instance of this class is created and then it's run method is called.
	"""

	description = "Clean everything"
	user_options = [("all","a","the same")]

	def initialize_options(self):
		self.all = None

	def finalize_options(self):
		pass

	def run(self):
		import os
		os.system("rm -rf build")
		os.system("rm -rf *.o")
		os.system("rm -rf cppad_.so")
		os.system("rm -rf *.pyc")


config = Configuration('',parent_package='',top_path='')
config.add_extension(
	name = 'cppad_',
	sources = ['adfun.cpp', 'pycppad.cpp', 'vec2array.cpp', 'vector.cpp'],
	include_dirs = include_dirs,
	extra_compile_args = extra_compile_args,
	library_dirs = library_dirs,
	runtime_library_dirs = library_dirs,
	libraries = libraries
)
#include_dirs, define_macros, undef_macros, library_dirs, libraries, runtime_library_dirs, extra_objects, extra_compile_args, extra_link_args, export_symbols, swig_opts, depends, language, f2py_options, module_dirs, extra_info.

options_dict = config.todict()
options_dict['cmdclass'] = {'clean':clean}
#, cmdclass = {'clean':clean}
#setup(**config.todict())
setup(**options_dict)

