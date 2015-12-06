package br.com.ufc.OS.Escalonador;

/*	
 * 	EXAMPLE FOUND AT:
 * 
 * 	http://javahungry.blogspot.com/2013/04/scheduling-algorithm-first-come-first.html	
 * 
 * 
 * */

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;
import java.util.List;
import java.util.Queue;

/* implement this class for all three strategies */

public abstract class AllocationStrategy {

	protected List<Job> Jobs;
    protected ArrayList<Job> Queue;
    
    public AllocationStrategy(List<Job> jobs) {
        super();
        Jobs = jobs;
    }
    
    public abstract void run();
    // update current job by 1 tick
    // check if the job queue might need to be changed.
    // check for jobs to add to the queue
}

	
