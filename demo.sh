#!/bin/sh

amixer -D bluealsa sset 'EWA Audio A106Pro -A2DP' 60%


lxterminal -e julius -C ~/Desktop/julius/julius-kit/dictation-kit-v4.4/am-gmm.jconf -nostrip -gram ~/Desktop/julius/dict/greeting -input mic -module

sleep 1

python3 audio.py


