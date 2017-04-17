# datatable
R's data.table for Python

Python 3.6 is required; later on we will add option to convert to 3.5
format as well. We will not provide support for any Python version
below 3.5.

## Run instructions

Inside the `datatable` folder run:
```bash
$ make
```
which does this:
```bash
$ python setup.py build
$ pip install . --upgrade
```

Note that you'll need to have Python 3.6 as your default python. Also,
you have to have write permissions to the python's `setup-packages`.
The easiest way is to set up a virtual environment:
```bash
$ virtualenv --python=python3.6 ~/py36
$ source ~/py36/bin/activate
```


## Troubleshooting

If you see errors such as `"unknown type name 'PyModuleDef'"` or `"void
function 'PyInit__datatable' should not return a value`" -- it means you are
running under an old version of Python. Please switch to Python3.6 as described
above.

If there is an error about `"unrecognized command line option ‘-Weverything’"`,
then you need to use `clang` as the compiler. Download
[Clang + LLVM 4.0](http://releases.llvm.org/download.html#4.0.0), and
then specify environment variable
    ```bash
    export CC="/path/to/clang+llvm_4.0/bin/clang"
    ```
Runnind `$CC --version` should tell you that you have Clang version 4.0.

Likewise, if you run into an error `"clang: unsupported option ‘-fopenmp’`",
then your system's Clang is outdated -- please follow the step above to
install Clang+LLVM version 4.0.

If you run into installation errors with `llvmlite` dependency, you
might need to build it manually. This involves the following:

  1. Check that you have `llvm 4.0.x` installed on your system:
     ```bash
     $ llvm-config --version
     ```
     If this produces an error, **OR** if the reported version is
     anything other than 4.0.*, then you'll need to download the correct
     LLVM binaries from http://releases.llvm.org/download.html#4.0.0
     After you unpack this distribution to a folder of your choice, set
     up an environment variable
     ```bash
     $ export LLVM_CONFIG="/path/to/llvm_4.0/bin/llvm-config"
     ```
     Check that the path is correct:
     ```bash
     $ $LLVM_CONFIG --version
     ```

  2. Install `llvmlite`:
     ```bash
     $ pip install llvmlite
     ```

  3. If you're getting error `"invalid deployment target for
     -stdlib=libc++ (requires OS X 10.7 or later)"`, then set the
     environment variable
     ```bash
     $ export MACOSX_DEPLOYMENT_TARGET="10.7"
     ```
     (presumably your OS X version should be 10.7 or higher) and
     restart step 2.

  4. If you're getting error about missing
     `"llvmlite/binding/libllvmlite.dylib"`, then it is a
     [known problem](https://github.com/Rdatatable/data.table/pull/2084) of
     `llvmlite` package. You may try to install from this location:
     ```bash
     pip install -i https://pypi.anaconda.org/sklam/simple llvmlite
     ```


## Testing

  1. Make sure that `pytest` is installed in your virtualenv:
     ```bash
     $ pip install pytest
     $ pip install pytest-cov
     ```
  2. Run the tests:
     ```bash
     python -m pytest
     ```
  3. Generate coverage report:
     ```bash
     $ python -m pytest --cov=datatable --cov-report=html
     ```