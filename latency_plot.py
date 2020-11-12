import numpy as np
import pandas as pd
import matplotlib.pyplot as pyplot

start_time_log = pd.read_csv (r'\home\ec2-user\file_sink/start_time_log.csv', sep=",",header=None)
start_t=start_time_log.to_numpy(dtype=float)[0]

end_time_log = pd.read_csv (r'\home\ec2-user\ec2-user/end_time_log.csv', sep=",",header=None)
end_t=end_time_log.to_numpy(dtype=float)[0]

payload_size=5184000

latency=np.zeros(100)
packet_no=np.linspace(1,100,100)

for i in range(len(start_t)):
    latency[i]=(end_t[i]-start_t[i])/1000

network_speed=np.zeros(100)
for i in range(len(start_t)):
    network_speed[i]=(payload_size/1000000)/(latency[i]/1000)
    
"""
pyplot.figure()
pyplot.plot(packet_no,latency)
pyplot.xlim(0,100)
pyplot.xlabel("Packets Sent")
pyplot.ylabel("Latency/ms")
pyplot.show()
"""
pyplot.figure()
pyplot.plot(packet_no,network_speed)
pyplot.xlim(0,100)
pyplot.xlabel("Payloads Sent")
pyplot.ylabel("Network Speed/Mbs$^-$$^1$")
pyplot.savefig('Network Speed Plot.png')
