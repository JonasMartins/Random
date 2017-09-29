package conta;

public class Client {
	
	private double money = 0;
	public Client(double money){
		setMoney(money);
	}
	public double getMoney() {
		return money;
	}
	public void setMoney(double money) {
		this.money = money;
	}
}
