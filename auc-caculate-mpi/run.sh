#!/bin/bash
process_number=3
Ip=("10.101.2.89" "10.101.2.90")
for ip in ${Ip[@]}
do
    ssh worker@$ip rm /home/worker/xiaoshu/AUC-caculate-mpi/auc_calculate
done
scp auc_calculate worker@10.101.2.89:/home/worker/xiaoshu/AUC-caculate-mpi/.
scp auc_calculate worker@10.101.2.90:/home/worker/xiaoshu/AUC-caculate-mpi/.
mpirun -f ./hosts -np $process_number ./auc_calculate ./data/auc_data
