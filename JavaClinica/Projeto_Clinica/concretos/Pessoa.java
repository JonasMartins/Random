package concretos;

import java.io.Serializable;


abstract public class Pessoa implements Serializable{

	

	/**
	 * 	
	 */
	private static final long serialVersionUID = -3778813093845762220L;
	private int id;
	private int idade;
	private String fone;
	private String adress;	
	private String nome;
	
	public String getAdress() {
		return adress;
	}

	public void setAdress(String adress) {
		this.adress = adress;
	}
	private String senha;

	public int getIdade() {
		return idade;
	}

	public void setIdade(int idade) {
		this.idade = idade;
	}
	public void setFone(String fone) {
		this.fone = fone;
	}

	public String getFone() {
		return fone;
	}

	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}
	
	public void setSenha(String password) {
		this.senha = password;
	}

	
	public String getSenha() {
		return senha;
	}
	public int getId() {
		return id;
	}

}
