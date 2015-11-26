package consulta;

import java.util.ArrayList;

import concretos.Medico;
import concretos.Paciente;


public class Consulta implements java.io.Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	public Paciente paciente;
	public Medico medico;
	private String data;
	private String hora;
	ArrayList<Integer> diaConsulta = new ArrayList<Integer>();
	
	public Consulta(Paciente p, Medico m, String data, String hora, ArrayList<Integer> diaConsulta){
		this.paciente = p;
		this.medico = m;
		this.data = data;
		this.hora = hora;
		this.diaConsulta = diaConsulta;
		
	}
	
	
	
	public void setData(String data) {
		this.data = data;
	}
	
	public String getData(){
		return data;
	}
	
	public void setHora(String hora){
		this.hora = hora;
	}
	public String getHora(){
		return hora;
	}
	
}
