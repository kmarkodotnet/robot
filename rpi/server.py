import cv2
import socket
import numpy
import time
import sys
from time import sleep
from datetime import datetime
import serial
import serial.tools.list_ports as port_list
from time import sleep

ports = list(port_list.comports())
for p in ports:
    print (p)

def GetVideo():
	return cv2.VideoCapture('C:\\temp\\python\\x\\y.mkv')

def GetCam():
	cap = cv2.VideoCapture(-1)
#cap.set(cv2.CAP_PROP_FRAME_WIDTH, 360)
#cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 240)
	return cap

cap = GetCam()
print(cap)
#ser = serial.Serial('/dev/ttyAMA0', 9600, serial.EIGHTBITS, serial.PARITY_NONE, serial.STOPBITS_ONE)
#ser = serial.Serial('COM1', 9600, serial.EIGHTBITS, serial.PARITY_NONE, serial.STOPBITS_ONE)
ser = serial.Serial('/dev/ttyUSB0',9600, serial.EIGHTBITS, serial.PARITY_NONE, serial.STOPBITS_ONE)
	
def WriteToSerial(command):
	global ser
	if ser is not None:
		try:
			ser.write(command.encode())
			print(command)
#c = ser.readline()
#print(c)
		except Exception as e:
			print("WriteToSerial" + str(e))
				
stop = "0"
fw = "1"
bw = "2"
right = "3"
left = "4"

send_length = 4096
end_sign = "!!!END!!!"


serv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serv.bind(('', 8084))
serv.listen(5)

print("start")

while True:
	conn, addr = serv.accept()
	data = b''
	print("accept: " + str(addr))
	
	while True:
		
		#print("recv")
		command_bytes = conn.recv(16)		
		
		#print("recv ok")
		command = command_bytes.decode(encoding='UTF-8',errors='ignore')
		print("command: " + str(command))
	
		if command == "PLAY" and cap.isOpened():
			print("open")
			ret, frame = cap.read()		
			print("ret: " + str(ret))
			if ret == True:
				
				data = cv2.imencode('.jpg', frame)[1]# + end_sign
				
				data_len = len(data) 
				send_rounds = int(data_len / send_length)
				if send_rounds * send_length != data_len:
					send_rounds = send_rounds + 1
				
				
				for i in range(0,send_rounds):
					data_to_send = data[i*send_length: (i+1)*send_length]
					conn.send(data_to_send)
				#print(type(data))
				
				#print(type(data[0][0]))
				
			WriteToSerial(stop)	
			
		elif command == "GO":
			WriteToSerial(stop)	
			sleep(1)
			print("GO")			
		
		elif command == "LEFT":
			WriteToSerial(left)
			print("LEFT")	
		elif command == "BACK":
			WriteToSerial(bw)
			print("BACK")	
		elif command == "RGHT":
			WriteToSerial(right)	
			print("RGHT")				
		elif command == "FWD":
			WriteToSerial(fw)
			print("FWD")	
			
		elif command == "QUIT":			
			print("QUIT")
			WriteToSerial(stop)	
			sys.exit()
			
	conn.close()
	print('client disconnected')
print("Finished")
cap.release()
sys.exit()

commands = []

#def PushCommand(command):
#	WriteToSerial(command)
#	##commands.append((datetime.now(), command))
#	
#def PullCommand():
#	
#	if len(commands) == 0:
#		return WriteToSerial(stop)
#		
#	now = datetime.now()
#	
#	commands_to_check = list(filter(lambda x: ( (now-x[0]).seconds*1000 +  (now-x[0]).microseconds/1000 > 200 ), commands))
#	
#	all_the_same = len(set([x for (dt,x) in commands_to_check])) == 1
	