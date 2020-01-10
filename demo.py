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
            if float(line) < 0.97:
                cm = False


    print(word)
    print(cm)
    if(word == 'こんにちは' and cm):
        subprocess.call("mplayer -ao alsa:device=bt-receiver ~/Desktop/jisyupro/sound/pleasure.mp3",shell=True)

    if(word == 'おはよう' and cm):
        subprocess.call("mplayer -ao alsa:device=bt-receiver ~/Desktop/jisyupro/sound/pleasure.mp3",shell=True)

    if(word == 'ありがとう' and cm):
        subprocess.call("mplayer -ao alsa:device=bt-receiver ~/Desktop/jisyupro/sound/pleasure.mp3",shell=True)

    if(word == 'ごめんね' and cm):
        subprocess.call("mplayer -ao alsa:device=bt-receiver ~/Desktop/jisyupro/sound/pleasure.mp3",shell=True)
    
    if(word == 'いなばせんせい' and cm):
        subprocess.call("mplayer -ao alsa:device=bt-receiver ~/Desktop/jisyupro/sound/cat.mp3",shell=True)

    if(word == 'おかだせんせい' and cm):
        subprocess.call("mplayer -ao alsa:device=bt-receiver ~/Desktop/jisyupro/sound/cat.mp3",shell=True)

    if(word == 'かんざきせんせい' and cm):
        subprocess.call("mplayer -ao alsa:device=bt-receiver ~/Desktop/jisyupro/sound/cat.mp3",shell=True)

    if(word == 'くずおかせんせい' and cm):
        subprocess.call("mplayer -ao alsa:device=bt-receiver ~/Desktop/jisyupro/sound/cat.mp3",shell=True)

    if(word == 'くによしせんせい' and cm):
        subprocess.call("mplayer -ao alsa:device=bt-receiver ~/Desktop/jisyupro/sound/cat.mp3",shell=True)

    if(word == 'なかむらせんせい' and cm):
        subprocess.call("mplayer -ao alsa:device=bt-receiver ~/Desktop/jisyupro/sound/cat.mp3",shell=True)

    if(word == 'はらだせんせい' and cm):
        subprocess.call("mplayer -ao alsa:device=bt-receiver ~/Desktop/jisyupro/sound/cat.mp3",shell=True)

    if(word == 'ひろせせんせい' and cm):
        subprocess.call("mplayer -ao alsa:device=bt-receiver ~/Desktop/jisyupro/sound/cat.mp3",shell=True)

    if(word == 'たかはしせんせい' and cm):
        subprocess.call("mplayer -ao alsa:device=bt-receiver ~/Desktop/jisyupro/sound/cat.mp3",shell=True)

    if(word == 'なるみせんせい' and cm):
        subprocess.call("mplayer -ao alsa:device=bt-receiver ~/Desktop/jisyupro/sound/cat.mp3",shell=True)

    if(word == 'にいやませんせい' and cm):
        subprocess.call("mplayer -ao alsa:device=bt-receiver ~/Desktop/jisyupro/sound/cat.mp3",shell=True)

    if(word == 'もりもとせんせい' and cm):
        subprocess.call("mplayer -ao alsa:device=bt-receiver ~/Desktop/jisyupro/sound/cat.mp3",shell=True)

    if(word == 'やまもとせんせい' and cm):
        subprocess.call("mplayer -ao alsa:device=bt-receiver ~/Desktop/jisyupro/sound/cat.mp3",shell=True)

    if(word == 'じしゅぷろ' and cm):
        subprocess.call("mplayer -ao alsa:device=bt-receiver ~/Desktop/jisyupro/sound/thread.mp3",shell=True)

    if(word == 'かだい' and cm):
        subprocess.call("mplayer -ao alsa:device=bt-receiver ~/Desktop/jisyupro/sound/thread.mp3",shell=True)

    if(word == 'れぽーと' and cm):
        subprocess.call("mplayer -ao alsa:device=bt-receiver ~/Desktop/jisyupro/sound/thread.mp3",shell=True)

    if(word == 'しけん' and cm):
        subprocess.call("mplayer -ao alsa:device=bt-receiver ~/Desktop/jisyupro/sound/thread.mp3",shell=True)

    if(word == 'ばか' and cm):
        subprocess.call("mplayer -ao alsa:device=bt-receiver ~/Desktop/jisyupro/sound/sad.mp3",shell=True)
        subprocess.call("./depressed",shell=True)
            
    res = ''
        
