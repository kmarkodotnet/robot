import cv2
import socket
import numpy
import time
from time import sleep

import sys

print("start")

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(('192.168.1.8', 8084))

print("connect")

send_length = 4096
end_sign = "!!!END!!!"

# FRAMES PER SECOND FOR VIDEO
fps = 25

command = "PLAY"


print("play")

while True:
	print(command)
	client.send(command.encode(encoding='UTF-8',errors='ignore'))
	print("sent")
	if command == "PLAY":
		data = b""
		
		while True:
			#print("recv")
			r = client.recv(4096)
			sleep(0.01)
			#print("recv ok")
			
			if len(r) == 0:
				print("exit")
				exit(0)
			if len(r) != 4096:
#data += r
				break
				
			data += r
		data = numpy.frombuffer(data,dtype=numpy.int8)
		data = numpy.array(data,dtype=numpy.int8)
		
		if len(data) > 0:
			frame = cv2.imdecode(data, cv2.IMREAD_COLOR)
			#print("frame: "+str(type(frame)))
		
			if type(frame) is type(None):
				print("pass")
			else:
				try:
					cv2.imshow("name",frame)
					sleep(1/25)
					
					oldframe = frame
					#print("imshow")
					key = cv2.waitKey(10)
					if key == ord('q'):
						command = "QUIT"
					elif key == ord('p'):
						command = "GO"
						
					elif key == ord('a'):
						command = "LEFT"
						
					elif key == ord('s'):
						command = "BACK"
						
					elif key == ord('d'):
						command = "RGHT"
						
					elif key == ord('w'):
						command = "FWD"
							
				except:
					print("close")
					client.close()
					exit(0)									
	elif command == "QUIT":
		client.close()
		sys.exit()
	
	else:
		command = "PLAY"
print("Finished")