README.txt 

------------------------------------------------------------

1. What is librnn?
2. How to compile librnn
  2.1 Mac OS X Leopard
  2.2 Linux
  2.3 Windows
3. Known issues
4. Roadmap

------------------------------------------------------------

1. What is librnn?

	librnn is a c++ implementation of a recurrent neural network (RNN) of
	arbitrary structure. There are two general methods to implement a RNN, as an
	adjacency matrix, and as an adjacency. librnn currently supports both.

	As learning algorithms play an essential role in the field of artificial
	recurrent neural networks, librnn will support extension mechanism to add
	neuron- and synapse-models, as well as local and global learning algorithms.

2. How to compile librnn

	Prerequisites:
		- cmake 2.5
		- gcc (4.x)
		- cppunit (currently required)
		- make
		- log4cpp (optional)

	2.1 Mac OS X Leopard

		To compile librnn, you need:
			- cmake 2.4 (www.cmake.org). Available through fink.
			- developer tools (gcc, part of Xcode)

		First run cmake and then compile it via make. Xcode is currently not
		supported, but will follow soon.

	2.2 Linux (tested with ubuntu)

		To compile librnn, you first need to run cmake (www.cmake.org) and then
		compile it via make. To install, run make install.

	2.3 Windows (tested with WinXP and MinGW/MSYS)

		To compile librnn on Windows you need the following:
			- cmake 2.4 (www.cmake.org)
			- MinGW     (www.mingw.org). Choose the following options, when asked
			  "Choose Components"
				- g++ compiler
				- MinGW Make
			- MSYS      (www.mingw.org)

		If you use MinGW/MSYS, you have to install log4pp and cppunit yourself. For log4pp
		use: 
		 http://opera7up.narod.ru/download/mingw-ddk/log4cpp-0.3.4b.tar.bz2

 		 > cmake -G "MinGW Makefiles"
		 > mingw32-make.exe
		 
		After successful installation, run cmake and make to compile librnn. 
		Microsoft Visual Studio currently not supported, but will follow soon.
	
3. Known issues

	3.1 General
		- No install routine (make install). Will be available with version 0.2
		- With Log4cpp enabled, the unittest take forever. The reason is currently unknown.

	3.2 WinXP
		- WinXP: In order for the testcases to run, the libraries must be copied manually
				 from the ./lib/ directory into the tests/matrix and tests/vector directories

4. Roadmap
	see doc/roadmap.olt (ASCII file)


--
Last edited 2008-07-19
