import numpy as np
import pandas as pd
import matplotlib.pyplot as pyplot

start_time_log = pd.read_csv (r'/home/ec2-user/file_sink/start_time_log.csv', sep=",",header=None)
start_t=start_time_log.to_numpy(dtype=float)[0]

end_time_log = pd.read_csv (r'/home/ec2-user/file_sink/end_time_log.csv', sep=",",header=None)
end_t=end_time_log.to_numpy(dtype=float)[0]

payload_size=5184000

latency=np.zeros(len(start_t))
packet_no=np.linspace(1,len(start_t),len(start_t))
packet_no2=np.linspace(1,len(start_t)-1,len(start_t)-1)

for i in range(len(start_t)):
    latency[i]=(end_t[i]-start_t[i])/1000

trt=np.zeros(len(start_t)-1)
    
for i in range(len(start_t)-1):
    trt[i]=(start_t[i+1]-start_t[i])/1000

network_speed=np.zeros(len(start_t)-1)
for i in range(len(start_t)-1):
    network_speed[i]=(payload_size/1000000)/(trt[i]/1000)

fig, axs = plt.subplots(2,figsize=(5,7))

axs[0].plot(packet_no,latency)
axs[0].set_xlabel("Payloads Sent")
axs[0].set_xlim(0,len(start_t))
axs[0].set_ylabel("Latency/ms")

axs[1].plot(packet_no2,network_speed)
axs[1].set_xlabel("Payloads Sent")
axs[1].set_xlim(0,len(start_t))
axs[1].set_ylabel("Network Speed/Mbs$^-$$^1$")

plt.savefig('network_speed_plot.png')
