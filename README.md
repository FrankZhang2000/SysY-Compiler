# SysY_Compiler

A simple but efficient SysY-to-RiscV compiler written by C++


## How To Download
1. Clone this repository
2. `cd SysY_Compiler/`
3. `./build.sh` or `make`


## Usage
```shell
compiler −S −e testcase.c −o testcase.S   # Translate SysY code to Eeyore intermediate representation
compiler −S −t testcase.c −o testcase.S   # Translate SysY code to Tigger intermediate representation
compiler −S testcase.c −o testcase.S      # Translate SysY code to Risc-V assembly
```
