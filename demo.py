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

    #get information of word    
    word = ''
    for line in res.split('\n'):
        index = line.find('WORD=')
        if index != -1:
            line = line[index + 6 : line.find('"', index + 6)]
            if (line != '[s]' and line != '[/s]') :
                word = word + line

    #get information of reliability
    cm = True
    for line in res.split('\n'):
        index = line.find('CM=')
        if index != -1:
            line = line[index + 4 : line.find('"', index + 4)]
            if line != '1.000':
                cm = False
   
    
    if(word == 'こんにちは' and cm):
        subprocess.call("mplayer -ao alsa:device=bt-receiver ~/Desktop/jisyupro/sound/cat3a.mp3",shell=True)
        
    
            
    res = ''
        
