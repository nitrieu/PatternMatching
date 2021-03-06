# SWiM: Secure Wildcard Pattern Matching
This is the implementation of our [FC 2018](http://xxx)  paper: **SWiM: Secure Wildcard Pattern Matching From OT Extension**[[ePrint](https://eprint.iacr.org/2017/xxx)]. 

Evaluating on a single Intel Xeon server (`2 36-cores Intel Xeon CPU E5-2699 v3 @ 2.30GHz and 256GB of RAM`), ours protocol requires only `60` seconds to securely compute the Secure Wildcard Pattern Matching for text size n = 2^22 and pattern size m = 2^14

## Installations

### Required libraries
 C++ compiler with C++14 support. There are several library dependencies including [`Boost`](https://sourceforge.net/projects/boost/), [`Miracl`](https://github.com/miracl/MIRACL), and [`libOTe`](https://github.com/osu-crypto/libOTe). For `libOTe`, it requires CPU supporting `PCLMUL`, `AES-NI`, and `SSE4.1`. Optional: `nasm` for improved SHA1 performance.   Our code has been tested on both Windows (Microsoft Visual Studio) and Linux. To install the required libraries: 
  * windows: open PowerShell,  `cd ./libOTe/cryptoTools/thirdparty/win`, and `getBoost.ps1; getMiracl.ps1` 
  * linux: `cd ./libOTe/cryptoTools/thirdparty/linux`, and `bash all.get`.   

NOTE: If you meet problem with `getBoost.ps1; getMiracl.ps1` or `all.get` which builds boost, miracl and libOTe, please follow the more manual instructions at [`libOTe`](https://github.com/osu-crypto/libOTe) 

### Building the Project
After cloning project from git,
##### Windows:
1. build cryptoTools,and libOTe projects in order.
2. add argument for frontend project (for example: -t)
3. run frontend project
 
##### Linux:
1. make (requirements: `CMake`, `Make`, `g++` or similar)
2. for test:
	./bin/frontend.exe -t


## Running the code
The database is generated randomly. The outputs include the average online/offline/total runtime that displayed on the screen and output.txt. 
#### Flags:
    -t		unit test which computes the Secure Wildcard Pattern Matching for text size 2^14 and pattern size 2^9
	-r		role (`-r 0` as sender, `-r 1` as receiver)		
	-nn		logarithm of text size. For example, `-nn 14` means that the text size is 2^14
	-n		text size
	-mm		logarithm of pattern size. For example, `-mm 9` means that the text size is 2^9
	-m		pattern size		
#### Examples: 
##### 1. Unit test:
	./bin/frontend.exe -t
	
##### 2. SWiM:
Compute Secure Wildcard Pattern Matching for text size  2^14 and pattern size 2^9 in semihonest setting

	./bin/frontend.exe -r 0 -nn 14 -mm 9 
	& ./bin/frontend.exe -r 1 -nn 14 -mm 9 
	
Compute Secure Wildcard Pattern Matching for text size 10000 and pattern size 256 in semihonest setting

	./bin/frontend.exe -r 0 -n 10000 -m 256
	& ./bin/frontend.exe -r 1 -n 10000 -m 256
	
## Help
For any questions on building or running the library, please contact [`Ni Trieu`](http://people.oregonstate.edu/~trieun/) at trieun at oregonstate dot edu