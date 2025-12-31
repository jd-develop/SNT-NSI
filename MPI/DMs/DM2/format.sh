#!/usr/bin/sh
# requiert clang
clang-format --style="{BasedOnStyle: llvm, IndentWidth: 4}" -i *.c *.h

