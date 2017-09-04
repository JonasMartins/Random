package controle;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;

import concretos.Pessoa;
import concretos.Medico;

public class InfoViewController {
	
	
	private InfoView info;
	private ActionListener actionListener;
	private String caminho;
	
	
	public InfoViewController(InfoView _info,String _caminho){
		this.info = _info;
		this.caminho = _caminho;
	}
	
	public void control() {
		actionListener = new ActionListener() {

			public void actionPerformed(ActionEvent e) {
				
				setInfo(caminho);
				
			}
		};
		info.getShow().addActionListener(actionListener);
	}
	
	private void setInfo(String caminho){
		
		  Pessoa g = null;
	      try
	      {
	         FileInputStream fileIn = new FileInputStream(caminho);
	         ObjectInputStream in = new ObjectInputStream(fileIn);
	         g = (Pessoa) in.readObject();
	         in.close();
	         fileIn.close();
	      }catch(IOException i)
	      {
	         i.printStackTrace();
	       }catch(ClassNotFoundException c)
	       {
	    	 c.printStackTrace();
	       }
	      
	      info.setNomeText(g.getNome());
	      info.setIdadeText(g.getIdade());
	      info.setFoneText(g.getFone());
	      info.setAdressText(g.getAdress());
	      info.setSenhaText(g.getSenha());
	      
	      // 	ESCREVENTO NO CAMPO TIPO
	      switch(g.getId()){
	      	case 1:
	      		info.setTipoText("Paciente");
	      		break;
	      	case 2:
	      		info.setTipoText("Atendente");
	      		break;
	      	case 3:
	      		info.setTipoText("Administrador");
	      		break;
	      	case 4:
	      		info.setTipoText("Medico");
	      		break;
	      }
	      
	      if(g.getClass()==Medico.class){
	    	  
	    	  //Srializa novamente
	    	  
	    	  Medico m = null;
		      try
		      {
		         FileInputStream fileIn = new FileInputStream(caminho);
		         ObjectInputStream in = new ObjectInputStream(fileIn);
		         m = (Medico) in.readObject();
		         in.close();
		         fileIn.close();
		      }catch(IOException i)
		      {
		         i.printStackTrace();
		       }catch(ClassNotFoundException c)
		       {
		    	 c.printStackTrace();
		       }
	    	  info.setAreaText(m.getEspecialidade());
	    	  
	      }
	}
	
	
}
