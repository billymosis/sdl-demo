# Setup

I'm using Ubuntu 22.04, my IDE is neovim and using CLANG as LSP.
There is something messed up with clang package on ubuntu, I'm following this advice on stack overflow to satisfies clangd LSP on neovim.
https://askubuntu.com/questions/1449769/clang-cannot-find-iostream

`sudo apt install g++-12`

to build and run this

```
cd build
cmake ..
make
./SDL3Test
```

also don't forgot to run ./setup.sh it will generate `compile_commands.json` to support clangd LSP.
