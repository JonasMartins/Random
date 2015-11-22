package concretos;

import java.io.Serializable;
import java.util.ArrayList;


public class Paciente extends Pessoa implements Serializable{

	
	/**
	 * 
	 */
	private static final long serialVersionUID = 7573131584209612385L;

	public ArrayList<String> listaConsultas;

	
	final int id = 1;
	private String senha;
	private String fone;
	
	
	public Paciente(int idade,String nome){
		this.setIdade(idade);
		this.setNome(nome);
		
		listaConsultas = new ArrayList<String>();
	}

	
	public void setConsulta(String path){
		listaConsultas.add(0, path);
	}
	
	public String getFone() {
		return fone;
	}

	public void setFone(String fone) {
		this.fone = fone;
	}
	
	public void setSenha(String password){
		this.senha = password;
	}
	
	@SuppressWarnings("unused")
	private void verConsulta(){}

	@Override
	public String getSenha() {
		return senha;
		
	}
	public int getId() {
		return id;
	}
	
}
