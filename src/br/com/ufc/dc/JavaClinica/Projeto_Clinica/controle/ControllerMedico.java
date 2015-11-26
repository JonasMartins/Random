package controle;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.FileInputStream;

import concretos.Medico;
import concretos.Paciente;
import consulta.Consulta;


public class ControllerMedico {
		
	static MedicoView telaMedico;
	Medico m;
	
	public ControllerMedico(String path)
	{
		this.m = extrairMedico(path);
		
		try{
			verConsultas(m);
		}catch(Exception e){
	         e.printStackTrace();
		}
		
		
	}
	
	public static void verConsultas(Medico medico) throws IOException, ClassNotFoundException{
		String nomeMedico; 
		int y= 0;
		boolean verif = true;
		Consulta c2 = null;
		String dados [][] = new String[medico.listaConsultas.size()][4];
		for (String c : medico.listaConsultas){
			verif = true;
			try{
				FileInputStream fis = new FileInputStream(c);
				ObjectInputStream ois = new ObjectInputStream(fis);
				c2 = (Consulta) ois.readObject();
				ois.close();
			}catch(FileNotFoundException flf){
				verif = false;
			}
						
			if (verif == true){
				dados [y][0] = c2.paciente.getNome().toString();
			
				dados [y][1] =  String.valueOf(c2.paciente.getIdade());
			
				dados [y][2] = c2.getData().toString();
			
				dados [y][3] = c2.getHora();
			
				y++;
			}
		}
		nomeMedico = medico.getNome();
		telaMedico = new MedicoView(dados,nomeMedico);
		
	}
	
	public MedicoView getMedicoView()
	{
		return telaMedico;
	}
	
	  //Deserializa os medicos armazenados
    private Medico extrairMedico(String path){
		  Medico p = null;
	      try
	      {
	         FileInputStream fileIn = new FileInputStream(path);
	         ObjectInputStream in = new ObjectInputStream(fileIn);
	         
	        
	        	 p = (Medico) in.readObject();
	         
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
		
		
		Medico medico = new Medico(18,"Robervaldo");
	
		String path = ("/Users/arthurbrito/Documents/workspace/TesteTrabalhoFinals/src/Consultas/consulta1.ser");
		String path2 = ("/Users/arthurbrito/Documents/workspace/TesteTrabalhoFinals/src/Consultas/consulta2.ser");
		String path3 = ("/Users/arthurbrito/Documents/workspace/TesteTrabalhoFinals/src/Consultas/consulta3.ser");
		
		String path4 = ("/Users/arthurbrito/Documents/workspace/TesteTrabalhoFinals/src/Consultas/consulta4.ser");
		
		medico.ListaConsultas.add(path);
		medico.ListaConsultas.add(path2);
		medico.ListaConsultas.add(path3);
		medico.ListaConsultas.add(path4);
		
		//System.out.println(paciente.ListaConsultas);
		verConsultas(medico);
		
		
		}*/
	}

