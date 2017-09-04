package login;

import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;

import javax.swing.JOptionPane;
import javax.swing.UIManager;
import javax.swing.plaf.FontUIResource;

import concretos.*;
import controle.Controle;
import controle.ControleController;
import controle.ControllerMedico;
import controle.ControllerPaciente;
import controle.MedicoView;
import controle.PacienteView;



public class PaginaInicialController { // ESTA CLASSE SE RELACIONA COM TODOS OS OUTROS CONTROLLERS

	
	private Controle ctrl;
	private ControleController _ctrl;
	
	
	private  MedicoView mv;
	private ControllerMedico _mv;
	
	private PacienteView pv;
	private ControllerPaciente _pv;
	
	
	private PaginaInicial page;
	private ActionListener actionListener;
	public String login;
	public String senha;
	private String path;

	public PaginaInicialController(PaginaInicial p) {
		this.page = p;
	}

	public void control() {
		
		
		// PADRÃO PARA JOPTIONPANE
		UIManager.put("OptionPane.messageFont",new FontUIResource(new Font("Serif", Font.PLAIN, 15)));
		UIManager.put("OptionPane.buttonFont", new FontUIResource(new Font("Serif", Font.PLAIN, 15)));
		//*****************************
		

		actionListener = new ActionListener() {

			public void actionPerformed(ActionEvent e) {
				Run();
				Autentica();
			}
		};
		page.getBotaoEntrar().addActionListener(actionListener);// funcionalizando
																// o botão

	}
	// METODO RUN PEGA "CATCH" OS CAMPOS LOGIN E SENHA
	private void Run() {

		// PEGANDO OS CAMPOS LOGIN E PASSWORD

		login = page.getLoginTexto().getText();
		senha = new String(page._getPassword().getPassword());

	}
	public boolean searchLogin(){
		
		/**
		 * 	ESTE METODO PROCURA OS ARQUIVOS DO LOGIN, SE ACHAR RETORNA TRUE, SE NÃO, FALSE
		 * 
		 * */
		
		
		File arq = new File("src/concretos"); // DENTRO DE CONCRETOS...
		File[] subpastas = arq.listFiles();
		File arq2; 
		File[] arquivos;
		for (int i = 0; i < subpastas.length; i++) { // PERCORRO TUDO LÁ...
			if (subpastas[i].isDirectory()) {   // SE FOREM DIRETORIOS.... OU SEJA PACIENTES, MEDICOS ETC
				arq2 = new File(subpastas[i].getPath());
				arquivos = arq2.listFiles();
				for (int j = 0; j < arquivos.length; j++){  // PERCORRO OS OBJETOS LÁ DENTRO	
					int aux = (int) arquivos[j].getName().length()-4;  // PARA TIRAR O .SER DOS OBJETOS
					if(login.equalsIgnoreCase(arquivos[j].getName().substring(0, aux))){ // SE OUVER UM LOGIN OK. VOU AGORA CHECAR A SENHA
						path = arquivos[j].getAbsolutePath();
						return true;
					}
				}
			}		
		}
		return false;
	}
	
	
	public void Autentica() { 
		/**
		 * 			AQUI FAZEMOS AS COMPARAÇÕES SE LOGIN OK, CHAMA O DESSERIALIZA,
		 * 		SE ESTE TAMBÉM RETORNAR TRUE, O USUÁRIO LOGA, SE ERRAR A SENNHA TENTA NOVAMENTE
		 *		SE ERRAR O LOGIN REESCREVE TUDO.
		 * */

		if(searchLogin()){
			if(Desserializa(path)){
				JOptionPane.showMessageDialog(null, "Bem Vindo "+login+"!");
				
				SelectView(RetornaId(path)); // SELECIONA A JANELA CORRETA
				
			}else{
			JOptionPane.showMessageDialog(null, "Senha Incorreta!"+"\nTente Novamente");
		
			}
		}else{
			JOptionPane.showMessageDialog(null, login+" Não consta em nossos arquivos\n Tente Novamente.");
			page.setLoginTexto("");
		
		}
		
		
	}
	// DESSERIALIZO O ARQUIVO E COMPARO A SENHA COM A SENHA DO USUÁRIO DAQUELE ARQUIVO
	private boolean Desserializa(String caminho){
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
	       if(senha.equalsIgnoreCase(g.getSenha()) ){
	    	   return true;
	       }return false;
	}

	private int RetornaId(String caminho){
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
	      return g.getId();
	   }
	private void SelectView(int id){
		
		switch (id){
		
		case 2: // VIEW DO ATENDENTE
			 ctrl = new Controle(path);// IMPORTANTE
			_ctrl = new ControleController(ctrl);
			_ctrl.control();
			page.dispose(); // FECHANDO O LOGIN INICIAL
			break;
			
		case 3: // VIEW DO ADIMISTRADOR
			 ctrl = new Controle(path);// IMPORTANTE
			_ctrl = new ControleController(ctrl);
			_ctrl.control();
			page.dispose(); // FECHANDO O LOGIN INICIAL
			break;
			
		case 4: // VIWE DO MEDICO
			_mv = new ControllerMedico(path);
			 mv = _mv.getMedicoView();// IMPORTANTE

			//_mv.control();
			page.dispose(); // FECHANDO O LOGIN INICIAL
			break;
			
		case 1: // VIWE DO PACIENTE
			_pv = new ControllerPaciente(path);
			pv = _pv.getPacientView();// IMPORTANTE
			//_pv.control();
			page.dispose(); // FECHANDO O LOGIN INICIAL
			break;	
		default:
			System.err.println("Id não identificado");
		}
		
	}

}
