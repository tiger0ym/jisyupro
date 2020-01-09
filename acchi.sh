#!/bin/sh

lxterminal -e julius -C ~/Desktop/julius/julius-kit/dictation-kit-v4.4/am-gmm.jconf -nostrip -gram ~/Desktop/julius/dict/demo2 -input mic -module

sleep 1

python3 acchi.py
