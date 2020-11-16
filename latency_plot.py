import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import csv

number_of_tests=50

#Loading in timing data from test

start_time_log = pd.read_csv (r'/home/ec2-user/file_sink/start_time_log.csv', sep=",",header=None)
start_t=start_time_log.to_numpy(dtype=float)[0]

end_time_log = pd.read_csv (r'/home/ec2-user/file_sink/end_time_log.csv', sep=",",header=None)
end_t=end_time_log.to_numpy(dtype=float)[0]

stats=[]

with open('/home/ec2-user/file_sink/network_info_store.csv', 'r') as file:
    reader = csv.reader(file)
    for row in reader:
        if len(row)>0:
            #print(row)
            stats.append(row)

#Last number gives nan for some reason so delete it

start_t=start_t[:-1]
end_t=end_t[:-1]

run_n=(len(stats)/2)+1
payload_size=(5184000/4)*run_n

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

file_name="network_speed_plot"+str(run_n)+".png"

plt.savefig(file_name,bbox_inches='tight')

#Calculating averages

network_speed_average=sum(network_speed)/len(network_speed)
latency_average=sum(latency)/len(latency)


#Reading and writing to csv to measure metrics against payload size


stats.append([network_speed_average])
stats.append([latency_average])

with open('/home/ec2-user/file_sink/network_info_store.csv', 'w', newline='') as file:
    writer = csv.writer(file)
    for i in range(len(stats)):
        writer.writerow(stats[i])
    #writer.writerow([network_speed_average])
    #writer.writerow([latency_average])
    
#Plotting and erasing data from csv once all measurements have been taken    
    
if len(stats)>=number_of_tests*2:
    network_speed_plot=np.zeros(number_of_tests)
    latency_plot=np.zeros(number_of_tests)
    for i in range(number_of_tests):
        network_speed_plot[i]=stats[2*i][0]
        latency_plot[i]=stats[2*i+1][0]
    payload_size_plot=np.linspace(1,number_of_tests,number_of_tests)
    for i in range(10):
        payload_size_plot[i]=payload_size_plot[i]*5184000/(4*1000000)
    fig2, axs2 = plt.subplots(2,figsize=(5,7))
    axs2[0].plot(payload_size_plot,latency_plot)
    axs2[0].set_xlabel("Payload Size/Mb")
    axs2[0].set_xlim(0,max(payload_size_plot)+min(payload_size_plot))
    axs2[0].set_ylabel("Latency/ms")
    
    axs2[1].plot(payload_size_plot,network_speed_plot)
    axs2[1].set_xlabel("Payload Size/Mb")
    axs2[1].set_xlim(0,max(payload_size_plot)+min(payload_size_plot))
    axs2[1].set_ylabel("Network Speed/Mbs$^-$$^1$")
    plt.savefig('network_speed_plot_variance.png',bbox_inches='tight')
    #Erases data from csv file
    with open('/home/ec2-user/file_sink/network_info_store.csv', 'w', newline='') as file:
        writer = csv.writer(file)
