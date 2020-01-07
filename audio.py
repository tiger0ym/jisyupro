# -*- coding: utf-8 -*-
import socket
import time
import subprocess

host = 'localhost'
port = 10500

# socket communication setting
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((host, port))

#divide sentences by "¥n"
res = 	''
while True:
    while (res.find('\n.') == -1):
        res += str(sock.recv(1024),'utf-8')

    word = ''
    for line in res.split('\n'):
        # search word
        index = line.find('WORD=')
        
        #put word into variable "word"
        if index != -1:
            line = line[index + 6 : line.find('"', index + 6)]
            if line != '[s]':
                word = word + line

        #
        if word == 'こんにちは':
            #subprocess.call("aplay cat15.wav",shell=True)
            print("hello")

        #
        if word == 'こんばんは':
            #subprocess.call("aplay cat15.wav",shell=True)
            print("good evenig")

        
        res = ''
