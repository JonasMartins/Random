package controle;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.FileInputStream;

import concretos.Medico;
import concretos.Paciente;
import concretos.Pessoa;
import consulta.Consulta;


public class ControllerPaciente {
		
	static PacienteView telaPaciente;
	Paciente p;
	
	
	public ControllerPaciente(String path)
	{
		this.p = extrairPaciente(path);
		
		try{
			verConsultas(p);
		}catch(Exception e){
	         e.printStackTrace();
		}
		
		
	}
	
	
	public static void verConsultas(Paciente paciente) throws IOException, ClassNotFoundException{
		String nomePaciente; 
		int y= 0;
		boolean verif = true;
		Consulta c2 = null;
		String dados [][] = new String[paciente.listaConsultas.size()][4];
		for (String c : paciente.listaConsultas){
			verif = true;
			//System.out.println("aqui");
			try {
				FileInputStream fis = new FileInputStream(c);
				ObjectInputStream ois = new ObjectInputStream(fis);
				c2 = (Consulta) ois.readObject();
				ois.close();
			
			}catch(FileNotFoundException fnf){
				verif = false;
			}
				
			if (verif == true){
				dados [y][0] = c2.medico.getEspecialidade().toString();
			
				dados [y][1] = c2.medico.getNome().toString();
			
				dados [y][2] = c2.getData().toString();
			
				dados [y][3] = c2.getHora();
			
			y++;
			
			//System.out.println(c);
			}
			
		}
		nomePaciente = paciente.getNome();
		telaPaciente = new PacienteView(dados,nomePaciente);
		
	}	
	
	public PacienteView getPacientView()
	{
		return telaPaciente;
	}
	
	
	  //Deserializa os medicos armazenados
    private Paciente extrairPaciente(String path){
		  Paciente p = null;
	      try
	      {
	         FileInputStream fileIn = new FileInputStream(path);
	         ObjectInputStream in = new ObjectInputStream(fileIn);
	         
	        
	        	 p = (Paciente) in.readObject();
	         
	         in.close();
	         fileIn.close();
	      }catch(IOException i)
	      {
	         i.printStackTrace();
	       }catch(ClassNotFoundException c)
	       {
	    	 c.printStackTrace();
	       }
	       
	      
	      
	      return p;
	}

	/*
	public static void main(String[] args) throws ClassNotFoundException, IOException  {
		
		
		Paciente paciente = new Paciente(18,"Pacienteee");
	
		String path = ("/Users/arthurbrito/Documents/workspace/TesteTrabalhoFinals/src/Consultas/consulta1.ser");
		String path2 = ("/Users/arthurbrito/Documents/workspace/TesteTrabalhoFinals/src/Consultas/consulta2.ser");
		String path3 = ("/Users/arthurbrito/Documents/workspace/TesteTrabalhoFinals/src/Consultas/consulta3.ser");
		String path4 = ("/Users/arthurbrito/Documents/workspace/TesteTrabalhoFinals/src/Consultas/consulta4.ser");
		
		paciente.ListaConsultas.add(path);
		paciente.ListaConsultas.add(path2);
		paciente.ListaConsultas.add(path3);
		paciente.ListaConsultas.add(path4);
		
		//System.out.println(paciente.ListaConsultas);
		verConsultas(paciente);
		
		
		}*/
	}

