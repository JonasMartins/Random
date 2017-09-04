package br.com.ufc.OS.Escalonador;

import java.util.ArrayList;
import java.util.List;


public class FirstComeFirstServed extends AllocationStrategy {
    
    int temp;
    int proceessArrivalTime;
    int waitingTime;
    double avgWaitingTime;
    double avgTurnAroundTime;
    
    public FirstComeFirstServed(List<Job> jobs) {
        super(jobs);
    }
    
    @Override
    public void run() {
        
    }
    
    public void run(List<Job> jobList) {
        int count = 0;
        System.out.println("============================================ ");
        System.out.println("Process ID | Turnaround time | Waiting time ");
        System.out.println("============================================ ");
        for(Job job:jobList){
            if(count==0){
                job.processArrivalTime = job.getArrivalTime();
                job.ProcessCompletionTime = job.getArrivalTime()+job.getCpuTime();
                }else{
                job.processArrivalTime = temp-job.getArrivalTime();
                job.ProcessCompletionTime = temp+job.getCpuTime();
            }
            
            temp = job.ProcessCompletionTime;
            job.turnAroundTime = temp-job.getArrivalTime();
            job.waitingTime = job.turnAroundTime-job.getCpuTime();
            count++;
            
            avgWaitingTime =  avgWaitingTime+job.waitingTime;
            avgTurnAroundTime = avgTurnAroundTime+job.turnAroundTime;
            System.out.println("   "+job.getProcessId()+"  | "+"   "+job.turnAroundTime+"  | "+"   "+job.waitingTime+" ");
            System.out.println("----------------------------------------");
        }
        System.out.println("===============================================");
        System.out.println("Avg waiting time:"+avgWaitingTime/jobList.size());
        System.out.println("===============================================");
        System.out.println("Avg turn around time:"+avgTurnAroundTime/jobList.size());
        System.out.println("===============================================");
        
    }
    
}

