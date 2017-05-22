import requests
import time
import os
import subprocess
i = 0
url = 'http://bwj.iptime.org'
pwd = '/home/pi/images'

while i<75:

    os.system('fswebcam -r 640*480 -S 20 --no-banner --save /home/pi/images/%H%M%S.jpg')
    ps = subprocess.Popen(('ls','-tr','images'),stdout=subprocess.PIPE)
    output = subprocess.check_output(('tail','-1'),stdin=ps.stdout)
#    files = {'media' : open(path,'rb')}
#    r = requests.post(url,files=files)
    time.sleep(5)
    
    print output
    i = i+1;
    time.sleep(10)
