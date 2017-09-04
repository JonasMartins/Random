package concretos;

import java.io.Serializable;

public class Atendente extends Funcionario implements Serializable{

	/**
	 * 
	 */
	private static final long serialVersionUID = -7979705955899340592L;
	
	private String senha;
	private String fone;
	
	public String getFone() {
		return fone;
	}
	public void setFone(String fone) {
		this.fone = fone;
	}
	public Atendente(int idade, String nome) {
		super(idade, nome);
		// TODO Auto-generated constructor stub
	}

	final int id = 2;


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
