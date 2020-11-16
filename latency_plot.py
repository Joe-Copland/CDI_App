import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import csv

#Loading in timing data from test

start_time_log = pd.read_csv (r'/home/ec2-user/file_sink/start_time_log.csv', sep=",",header=None)
start_t=start_time_log.to_numpy(dtype=float)[0]

end_time_log = pd.read_csv (r'/home/ec2-user/file_sink/end_time_log.csv', sep=",",header=None)
end_t=end_time_log.to_numpy(dtype=float)[0]

print(start_t,end_t)

payload_size=5184000

latency=np.zeros(len(start_t))
packet_no=np.linspace(1,len(start_t),len(start_t))
packet_no2=np.linspace(1,len(start_t)-1,len(start_t)-1)

#Calculating latency and network speed

for i in range(len(start_t)):
    latency[i]=(end_t[i]-start_t[i])/1000

trt=np.zeros(len(start_t)-1)
    
for i in range(len(start_t)-1):
    trt[i]=(start_t[i+1]-start_t[i])/1000

network_speed=np.zeros(len(start_t)-1)
for i in range(len(start_t)-1):
    network_speed[i]=(payload_size/1000000)/(trt[i]/1000)

#Plotting latency and network speed against payload no

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

#Calculating averages

network_speed_average=sum(network_speed)/len(network_speed)
latency_average=sum(latency)/len(latency)
print("sum(network_speed)",sum(network_speed))
print("len(network_speed)",len(network_speed))
print("network_speed",network_speed)
print("len(latency)",len(latency))
print("sum(latency)", sum(latency))
print("latency", latency)


#Reading and writing to csv to measure metrics against payload size

stats=[]

with open('/home/ec2-user/file_sink/network_info_store.csv', 'r') as file:
    reader = csv.reader(file)
    for row in reader:
        if len(row)>0:
            #print(row)
            stats.append(row)

with open('/home/ec2-user/file_sink/network_info_store.csv', 'w', newline='') as file:
    writer = csv.writer(file)
    for i in range(len(stats)):
        writer.writerow(stats[i])
    writer.writerow([network_speed_average])
    writer.writerow([latency_average])
    
#Plotting and erasing data from csv once all measurements have been taken    
    
if len(stats)>=20:
    network_speed_plot=np.zeros(10)
    latency_plot=np.zeros(10)
    for i in range(10):
        network_speed_plot[i]=stats[2*i][0]
        latency_plot[i]=stats[2*i+1][0]
    payload_size_plot=np.linspace(1,10,10)
    for i in range(10):
        payload_size_plot[i]=payload_size_plot[i]*5184000/(2*1000000)
    fig, axs = plt.subplots(2,figsize=(5,7))
    axs[0].plot(payload_size_plot,latency_plot)
    axs[0].set_xlabel("Payload Size/Mb")
    axs[0].set_xlim(0,max(payload_size_plot)+min(payload_size_plot))
    axs[0].set_ylabel("Latency/ms")
    
    axs[1].plot(payload_size_plot,network_speed_plot)
    axs[1].set_xlabel("Payload Size/Mb")
    axs[1].set_xlim(0,max(payload_size_plot)+min(payload_size_plot))
    axs[1].set_ylabel("Network Speed/Mbs$^-$$^1$")
    
    plt.savefig('network_speed_plot_variance.png')
    #Erases data from csv file
    with open('network_info_store.csv', 'w', newline='') as file:
        writer = csv.writer(file)
