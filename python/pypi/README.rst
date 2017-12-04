
*******************
Package description
*******************

Package ``hfst`` contains python bindings for `HFST <https://hfst.github.io>`_
(Helsinki Finite-State Technology) C++ library. HFST toolkit is intended for
processing natural language morphologies. The toolkit is demonstrated by
wide-coverage implementations of a number of languages of varying
morphological complexity.

Requirements
############

For Windows and Mac OS X, we offer binary wheels on PyPI. Wheels are available
for python versions 2.7, 3.4, 3.5 and 3.6.
The wheels for Windows are 32-bit; they also require a 32-bit
python to work correctly. Wheels for Mac are compiled as universal binaries
that work both on 32- and 64-bit environments. OS X must be 10.6 or higher.

For Linux, we offer only the source code on PyPI. It is also possible to install hfst
using Debian binary packages. This is the recommended way if the environment supports Debian.
Compiling hfst from source requires a C++ compiler (tested with gcc 5.4.0),
readline and getline libraries for C++ compiler and setuptools package for python
(tested with version 28.8.0). Swig is no longer needed as pre-generated files are
included in source distribution.

Installation via PyPI
#####################

We recommend using ``pip`` tool for installation for Windows and OS X.
``pip`` also works for Linux, but everything will be compiled from
source. Before installation, see that dependencies given under heading 'Requirements' are met.

For python version 3, the ``pip`` tool is usually named ``pip3``, plain ``pip`` being used
for python version 2. Basic installation is done with:

``pip3 install [--upgrade] hfst``

``pip install [--upgrade] hfst``

Starting from python 3.4.0 and 2.7.9, pip is included by default
and can be called via python with option ``-m pip``:

``python3 -m pip install [--upgrade] hfst``

``python -m pip install [--upgrade] hfst``

The commands above are run in a shell/terminal/command prompt, but they can
also be run on python command line or via a graphical user interface
(e.g. IDLE) with ``pip.main`` that takes arguments in a list:

| ``import pip``
| ``pip.main(['install','--upgrade','hfst'])``

The option ``--upgrade`` makes sure that the newest version of hfst will be installed
replacing any earlier versions installed. The option ``--verbose``
will show what happens during the installation process. This can be useful when compiling from source.

Installation for Linux using Debian packages
############################################

Fetch newest Debian release (named ``python3-libhfst`` for python version 3 and ``python-libhfst`` for python version 2)
from `Apertium <http://apertium.projectjj.com/apt/nightly/pool/main/h/hfst/>`_ and install it with

``dpkg --install  python[3]-libhfst_***.deb``

When choosing the right package, the command ``lsb_release -a`` might be helpful.
It will e.g. print something like

| ``No LSB modules are available.``
| ``Distributor ID: Ubuntu``
| ``Description:    Ubuntu 16.04.2 LTS``
| ``Release:        16.04``
| ``Codename:       xenial``

In the example case, the line Codename shows that the right package is of form ``*~xenial1_*.deb``.

The command ``file /usr/bin/file`` is one way to check whether your system is 64-bit or 32-bit. It will print something like:

``/usr/bin/file: ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked ...``

In the case above, a package ending in ``amd64.deb`` is the right choice.

Compiling from scratch
######################

It is also possible to compile HFST C++ library and the python bindings from scratch.
Clone or download our `Github repository <https://github.com/hfst/hfst>`_ and
see `README <https://github.com/hfst/hfst/tree/master/python>`_ of the ``python`` subdirectory.

Documentation
#############

See Doxygen-generated `package documentation <https://hfst.github.io/python>`_
on our Github pages. In python, you can also use ``dir`` and ``help``
commands, e.g.:

``dir(hfst)``

``help(hfst.HfstTransducer)``

License
#######

HFST is licensed under Gnu GPL version 3.0.

Troubleshooting
###############

(In the commands below, ``python[3]`` means either ``python`` or ``python3`` depending of the version of python you are using;
the same goes for ``pip[3]`` meaning ``pip`` or ``pip3``.)

*Pip starts to compile from source although there is a wheel available:*

Try upgrading pip with

``pip[3] install --upgrade pip``

or

``python[3] -m pip install --upgrade pip``.

Another reason for this can be that
the source package on PyPI is newer (i.e. has a higher version number) than
the corresponding wheel for the given environment. Report this via our
`issue tracker <https://github.com/hfst/hfst/issues/>`_ so a fresh wheel
will be created.

*Error message "command ... failed with error code ...":*

Try rerunning pip in verbose mode with

``pip[3] install --verbose [--upgrade] hfst``

or

``python[3] -m pip install --verbose [--upgrade] hfst``

to get more information.

*Error message "error: could not delete ... : permission denied":*

You do not have sufficient rights to install packages. On Mac and Linux, try
installing as super user with

``sudo pip[3] install [--upgrade] hfst``

or

``sudo python[3] -m pip install [--upgrade] hfst``.

On Windows, reopen Command Prompt/Python command line/IDLE by right-clicking
and choose "Run as administrator", then run pip again.


Links
#####

`HFST project main page <https://hfst.github.io>`_: more information about
the project

`Github issue tracker <https://github.com/hfst/hfst/issues/>`_: for comments,
feature requests and bug reports

