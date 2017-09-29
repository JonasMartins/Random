package conta;

public class Conta {
	private Client cliente;
	private double balance;
	
	public Conta(Client c){
		setBalance(0);
	}
		
	public void deposito(double value){
		setBalance(getBalance()+value);
	}
	public boolean credito(double value){
		boolean flag = false;
		if((this.getBalance() - value) > 0){
			flag = true;
			this.setBalance(this.getBalance() - value);
		}
		return flag;
	}

	public Client getCliente() {
		return cliente;
	}

	public void setCliente(Client cliente) {
		this.cliente = cliente;
	}

	public double getBalance() {
		return balance;
	}

	public void setBalance(double balance) {
		this.balance = balance;
	}
	
	
}
