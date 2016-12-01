.PHONY: install install-python2 install-python3 module2 module3 clean

install: install-python2 install-python3

if FOUND_PYTHON2
module2: NormalizModule.cpp setup.py
	python2 setup.py build_ext --inplace

install-python2: module2
	python2 setup.py install
endif

if FOUND_PYTHON3
module3: NormalizModule.cpp setup.py
	python3 setup.py build_ext --inplace

install-python3: module3
	python3 setup.py install
endif

clean:
	rm PyNormaliz*.so
