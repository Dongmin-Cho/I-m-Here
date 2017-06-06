import requests
import time
import os
import subprocess

url = 'http://bwj.iptime.org:3000/classAttend/attend'
pwd = '/home/pi/images'

while True:

    os.system('fswebcam -r 1920*1080 -s brightness=65% --no-banner --save /home/pi/images/%H%M%S.jpg')
    ps = subprocess.Popen(('ls','-tr','images'),stdout=subprocess.PIPE)
    output = subprocess.check_output(('tail','-1'),stdin=ps.stdout)
    path=os.path.join(pwd,output.strip())
    files = {'media' : open(path,'rb')}
    res = requests.post(url,files=files)
    print(res.status_code)
    print(res.text)
    time.sleep(10)
