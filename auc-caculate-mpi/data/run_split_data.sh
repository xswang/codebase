rm auc_data-0000*
python split_data.py auc_data_20160831.txt 3 auc_data
scp auc_data-0000* slave1:/home/worker/xiaoshu/AUC-caculate-mpi/data
scp auc_data-0000* slave2:/home/worker/xiaoshu/AUC-caculate-mpi/data

