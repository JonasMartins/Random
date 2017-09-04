package concretos;

import java.io.Serializable;

public class Administrador extends Atendente implements Serializable{
	
	/**
	 * 
	 */
	private static final long serialVersionUID = -5719878253078641689L;
	private String senha;
	final int id = 3;
	private String fone;
	
	public String getFone() {
		return fone;
	}

	public void setFone(String fone) {
		this.fone = fone;
	}

	Administrador(int idade, String nome) {
		super(idade, nome);
		// TODO Auto-generated constructor stub
	}

	@Override
	public void setSenha(String password) {
		this.senha = password;
		
	}
	public String getSenha(){
		return senha;
	}

	public int getId() {
		return id;
	}
	
}
