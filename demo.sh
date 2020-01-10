#!/bin/sh

amixer -D bluealsa sset 'EWA Audio A106Pro - A2DP' 100%


lxterminal -e julius -C ~/Desktop/julius/julius-kit/dictation-kit-v4.4/am-gmm.jconf -nostrip -gram ~/Desktop/julius/dict/demo2 -input mic -module

sleep 1

lxterminal -e ./demo

python3 demo.py



