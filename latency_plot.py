import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import csv

number_of_tests=40

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

run_n=(len(stats)/3)+1
payload_size=(5184000/8)*run_n

latency=np.zeros(len(start_t))
packet_no=np.linspace(1,len(start_t),len(start_t))
packet_no2=np.linspace(1,len(start_t)-1,len(start_t)-1)

#Calculating latency and network speed

for i in range(len(start_t)):
    latency[i]=(end_t[i]-start_t[i])/1000

trt=np.zeros(len(start_t)-1)
    
for i in range(len(start_t)-1):
    trt[i]=(start_t[i+1]-start_t[i])/1000

packet_rate=np.zeros(len(start_t)-1)
for i in range(len(start_t)-1):
    packet_rate[i]=(payload_size/1000000)/(trt[i]/1000)

transmission_rate=np.zeros(len(start_t))
for i in range(len(start_t)):
    transmission_rate[i]=(payload_size/1000000)/(latency[i]/1000)
    
#Plotting latency and network speed against payload no

fig, axs = plt.subplots(3,figsize=(5,10))

axs[0].plot(packet_no,latency)
axs[0].set_xlabel("Payloads Sent")
axs[0].set_xlim(0,len(start_t))
axs[0].set_ylabel("Latency/ms")
axs[0].set_title(str(int(payload_size))+" bit payload")

axs[1].plot(packet_no2,packet_rate)
axs[1].set_xlabel("Payloads Sent")
axs[1].set_xlim(0,len(start_t))
axs[1].set_ylabel("Packet Rate/Mbs$^-$$^1$")

axs[2].plot(packet_no,transmission_rate)
axs[2].set_xlabel("Payloads Sent")
axs[2].set_xlim(0,len(start_t))
axs[2].set_ylabel("Transmission Rate/Mbs$^-$$^1$")

file_name="/home/ec2-user/file_sink/network_speed_plot"+str(run_n)+".png"

plt.savefig(file_name,bbox_inches='tight')

#Calculating averages
packet_rate_average=sum(packet_rate)/len(packet_rate)
latency_average=sum(latency)/len(latency)
transmission_rate_average=sum(transmission_rate)/len(transmission_rate)


#Reading and writing to csv to measure metrics against payload size


stats.append([packet_rate_average])
stats.append([latency_average])
stats.append([transmission_rate])

with open('/home/ec2-user/file_sink/network_info_store.csv', 'w', newline='') as file:
    writer = csv.writer(file)
    for i in range(len(stats)):
        writer.writerow(stats[i])
    #writer.writerow([network_speed_average])
    #writer.writerow([latency_average])
    
#Plotting and erasing data from csv once all measurements have been taken    
    
if len(stats)>=number_of_tests*3:
    packet_rate_plot=np.zeros(number_of_tests)
    latency_plot=np.zeros(number_of_tests)
    transmission_rate_plot=np.zeros(number_of_tests)
    
    for i in range(number_of_tests):
        packet_rate_plot[i]=stats[3*i][0]
        latency_plot[i]=stats[3*i+1][0]
        transmission_rate_plot=stats[3*i+2][0]
    payload_size_plot=np.linspace(1,number_of_tests,number_of_tests)
    for i in range(number_of_tests):
        payload_size_plot[i]=payload_size_plot[i]*5184000/(8*1000000)
    fig2, axs2 = plt.subplots(2,figsize=(5,7))
   
    axs[0].set_title('subplot 1')
    axs2[0].plot(payload_size_plot,latency_plot)
    axs2[0].set_xlabel("Payload Size/Mb")
    axs2[0].set_xlim(0,max(payload_size_plot)+min(payload_size_plot))
    axs2[0].set_ylabel("Latency/ms")
    
    axs2[1].plot(payload_size_plot,packet_rate_plot,label="Packet Rate")
    axs2[1].plot(payload_size_plot,transmission_rate_plot,label="Transmission Rate")
    axs2[1].set_xlabel("Payload Size/Mb")
    axs2[1].set_xlim(0,max(payload_size_plot)+min(payload_size_plot))
    axs2[1].set_ylabel("Network Speed/Mbs$^-$$^1$")
    axs2[1].legend()
    plt.savefig('/home/ec2-user/file_sink/network_speed_plot_variance.png',bbox_inches='tight')
    #Erases data from csv file
    with open('/home/ec2-user/file_sink/network_info_store.csv', 'w', newline='') as file:
        writer = csv.writer(file)
