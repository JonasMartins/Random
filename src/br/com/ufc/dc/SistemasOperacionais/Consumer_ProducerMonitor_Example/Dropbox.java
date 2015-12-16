//package evenOdd;

public class Dropbox {

    private int number=-1;
	private boolean evenNumber = false;
	private boolean turn = false;

    public synchronized int take(final boolean even) {
    	while(turn==false){
    		try{
    			wait();
    		}catch(InterruptedException e){}
    	}
    	if(evenNumber){
    		System.out.format("%s CONSUMIDOR obtem %d.%n", evenNumber ? "PAR" : "IMPAR", number);
      		turn=false;
    	}else{
    		System.out.format("%s CONSUMIDOR obtem %d.%n", evenNumber ? "PAR" : "IMPAR", number);
    		turn=false;
    	}
        return number;
    }

    public synchronized void put(int number) {

        this.number = number;
        evenNumber = number % 2 == 0;
        System.out.format("PRODUTOR gera %d.%n", number);
        turn=true;
        notify();
    }
}
