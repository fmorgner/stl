#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import subprocess

subprocess.call('cd ../../ && doxygen', shell=True)

html_theme = 'sphinx_rtd_theme'
extensions = [
    'breathe',
    'sphinx.ext.todo',
]
breathe_default_project = 'sophia'
breathe_projects = {
    'sophia': os.path.abspath('../../build/xml'),
}

source_suffix = '.rst'
master_doc = 'index'

project = 'sophia'
copyright = '2016,2017, Felix Morgner'
author = 'Felix Morgner'

version = '0.2.0'
release = '0.2.0'

language = 'en'

exclude_patterns = [
    'build',
    '.DS_Store',
]

pygments_style = 'sphinx'
todo_include_todos = True
htmlhelp_basename = 'sophiadoc'

rst_epilog = '.. |project_name| replace:: **%s**' % project

primary_domain = 'cpp'
highlight_language = 'c++'
