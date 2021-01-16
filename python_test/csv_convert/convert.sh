#!/bin/sh  

# # save into .csv files
# #rostopic echo -b <BAGFILE> -p <TOPIC> > <output>.csv 
# # BAGFILE: .bag file
# # output : .csv file

folder="."  
for file in ${folder}/*.bag
do  
    echo $file
    rostopic echo -b $file -p /vrpn_client_node/jonydata/pose > ${file%.*}".csv"
done
