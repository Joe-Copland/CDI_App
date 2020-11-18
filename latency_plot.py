import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import csv
from scipy.stats import sem
from scipy.optimize import curve_fit

print("---------------------PLOTS TIME---------------------------------------------")

number_of_tests=70

#Loading in timing data from this test run

start_time_log = pd.read_csv (r'/home/ec2-user/file_sink/start_time_log.csv', sep=",",header=None)
start_t=start_time_log.to_numpy(dtype=float)[0]

end_time_log = pd.read_csv (r'/home/ec2-user/file_sink/end_time_log.csv', sep=",",header=None)
end_t=end_time_log.to_numpy(dtype=float)[0]

#Loading in recorded data from previous tests
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

#Working out which test this is, looking at amount of data already recorded
run_n=(len(stats)/8)+1

#Working out payload size for this test
payload_size=(5184000/12)*run_n

print("Run Number: ", run_n)

latency=np.zeros(len(start_t))
jitter=np.zeros(len(start_t)-1)
packet_no=np.linspace(1,len(start_t),len(start_t))
packet_no2=np.linspace(1,len(start_t)-1,len(start_t)-1)

#Calculating latency, jitter, packet rate and transmission rate for this test, adjusting units

for i in range(len(start_t)):
    latency[i]=(end_t[i]-start_t[i])/1000

for i in range(len(start_t)-1):
    jitter[i]=latency[i+1]-latency[i]

jitter_average=sum(abs(jitter))/len(jitter)

#Fitting polynomial to latency plot to show jitter

def func(x, a, b, c, d, e, f, g, h):
    return a*x**7+b*x**6+c*x**5+d*x**4+e*x**3+f*x**2+g*x+h
popt, pcov = curve_fit(func, packet_no, latency)
packet_no_with_zero=np.insert(packet_no,0,0)

#Making top and bottom lines for jitter are plot
y_bottom=func(packet_no_with_zero, *popt)-jitter_average
y_top=func(packet_no_with_zero, *popt)+jitter_average
    
trt=np.zeros(len(start_t)-1)
    
for i in range(len(start_t)-1):
    trt[i]=(start_t[i+1]-start_t[i])/1000

packet_rate=np.zeros(len(start_t)-1)
for i in range(len(start_t)-1):
    packet_rate[i]=(payload_size/1000000)/(trt[i]/1000)

transmission_rate=np.zeros(len(start_t))
for i in range(len(start_t)):
    transmission_rate[i]=(payload_size/1000000)/(latency[i]/1000)
    
#Plotting latency, packet rate and payload no

print("latency", latency)
print("packet rate", packet_rate)
print("transmission rate", transmission_rate)

fig, axs = plt.subplots(3,figsize=(5,10))

#Displaying jitter solid area
axs[0].fill_between(packet_no_with_zero, y_bottom, y_top,alpha=0.3,label="Jitter")
axs[0].plot(packet_no,latency,label="Latency")
axs[0].set_xlabel("Payloads Sent")
axs[0].set_xlim(0,len(start_t))
axs[0].set_ylabel("Latency/ms")
axs[0].set_title(str(int(payload_size))+" bit payload")
axs[0].legend()

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
plt.close(fig)

#Calculating averages
packet_rate_average=sum(packet_rate)/len(packet_rate)
latency_average=sum(latency)/len(latency)
transmission_rate_average=sum(transmission_rate)/len(transmission_rate)

#Calculating standard errors
packet_rate_err=sem(packet_rate)
latency_err=sem(latency)
transmission_rate_err=sem(transmission_rate)
jitter_err=sem(jitter)

#Reading and writing to csv to measure metrics against payload size
print("averages",packet_rate_average,latency_average,transmission_rate_average,jitter_average)

stats.append([packet_rate_average])
stats.append([latency_average])
stats.append([transmission_rate_average])
stats.append([jitter_average])

stats.append([packet_rate_err])
stats.append([latency_err])
stats.append([transmission_rate_err])
stats.append([jitter_err])

print("stats",stats)

with open('/home/ec2-user/file_sink/network_info_store.csv', 'w', newline='') as file:
    writer = csv.writer(file)
    for i in range(len(stats)):
        writer.writerow(stats[i])
    
#Plotting and erasing data from csv once all measurements have been taken    
    
if len(stats)>=number_of_tests*8:
    print("THE PROGRAM THINKS IT'S THE LAST RUN")
    packet_rate_plot=np.zeros(number_of_tests)
    latency_plot=np.zeros(number_of_tests)
    transmission_rate_plot=np.zeros(number_of_tests)
    jitter_plot=np.zeros(number_of_tests)
    packet_rate_plot_err=np.zeros(number_of_tests)
    latency_plot_err=np.zeros(number_of_tests)
    transmission_rate_plot_err=np.zeros(number_of_tests)
    jitter_plot_err=np.zeros(number_of_tests)
    
    #Getting data from all tests
    for i in range(number_of_tests):
        packet_rate_plot[i]=stats[8*i][0]
        latency_plot[i]=stats[8*i+1][0]
        transmission_rate_plot[i]=stats[8*i+2][0]
        jitter_plot[i]=stats[8*i+3][0]
        packet_rate_plot_err[i]=stats[8*i+4][0]
        latency_plot_err[i]=stats[8*i+5][0]
        transmission_rate_plot_err[i]=stats[8*i+6][0]
        jitter_plot_err[i]=stats[8*i+7][0]
        
    print("packet rate",packet_rate_plot)
    print("latency", latency_plot)
    print("transmission rate", transmission_rate_plot)
    print("jitter",jitter_plot)
    print("packet rate error",packet_rate_plot_err)
    print("latency error", latency_plot_err)
    print("transmission rate error", transmission_rate_plot_err)
    print("jitter error", jitter_plot_err)
    
    #Getting payload size for each test
    payload_size_plot=np.linspace(1,number_of_tests,number_of_tests)
    for i in range(number_of_tests):
        payload_size_plot[i]=payload_size_plot[i]*5184000/(12*1000000)
    fig2, axs2 = plt.subplots(3,figsize=(5,10))
    
    #Plotting with errorbars

    axs2[0].errorbar(payload_size_plot,latency_plot,yerr=latency_plot_err,fmt='none', capsize=3)
    axs2[0].set_xlabel("Payload Size/Mb")
    axs2[0].set_xlim(0,max(payload_size_plot)+min(payload_size_plot))
    axs2[0].set_ylabel("Latency/ms")
    

    axs2[1].errorbar(payload_size_plot,jitter_plot,yerr=jitter_plot_err,fmt='o', capsize=3)
    axs2[1].set_xlabel("Payload Size/Mb")
    axs2[1].set_xlim(0,max(payload_size_plot)+min(payload_size_plot))
    axs2[1].set_ylabel("Jitter/ms")
    
    axs2[2].errorbar(payload_size_plot,packet_rate_plot,yerr=packet_rate_plot_err,label="Packet Rate",fmt='none', capsize=3)
    axs2[2].errorbar(payload_size_plot,transmission_rate_plot,yerr=transmission_rate_plot_err,label="Transmission Rate",fmt='none', capsize=3)
    axs2[2].set_xlabel("Payload Size/Mb")
    axs2[2].set_xlim(0,max(payload_size_plot)+min(payload_size_plot))
    axs2[2].set_ylabel("Network Speed/Mbs$^-$$^1$")
    axs2[2].legend()
    plt.savefig('/home/ec2-user/file_sink/network_speed_plot_variance.png',bbox_inches='tight')
    
    #Erasing data from csv file
    with open('/home/ec2-user/file_sink/network_info_store.csv', 'w', newline='') as file:
        writer = csv.writer(file)
print("-------------FINISHED--------------------------------------------")
