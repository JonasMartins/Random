package concretos;

import java.io.Serializable;


public class Funcionario extends Pessoa implements Serializable{


	/**
	 * 
	 */
	private static final long serialVersionUID = 5947658230149119032L;


	@SuppressWarnings("unused")
	private double salario;

	
	private String senha;
	
	Funcionario(int idade, String nome){
		this.setIdade(idade);
		this.setNome(nome);
	}
	
	@Override
	public void setSenha(String password) {
		this.senha = password;
	}

	@Override
	public String getSenha() {
		return senha;
	}
	
}
