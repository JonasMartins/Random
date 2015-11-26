package controle;


import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileFilter;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.util.ArrayList;

import javax.swing.AbstractButton;
import javax.swing.JButton;
import javax.swing.JOptionPane;
import javax.swing.UIManager;
import javax.swing.plaf.FontUIResource;

import concretos.Pessoa;
import consulta.Consulta;
import consulta.ConsultaController;

public class ControleController {

	private Controle controle;
	private ActionListener actionListener;
	private IncluirAtendenteController incluirAtentendeController;
	private IncluirAtendente incluirAtentende;
	private IncluirAdministrador incluirAdministrador;
	private IncluirAdministradorController incluirAdministradorController;
	JButton[] calendar;
	int mesAtual = 6;
	
	ArrayList<Integer> diaConsulta = new ArrayList<Integer>();

	
	private String path;
	
	
	
	public ControleController(Controle c){
		this.controle = c;
		
		calendar = controle.getCalendar();
		
		for (int i = 0; i < 42; i++) {
			calendar[i].addActionListener(new BotoesCalendario());
		}
		
	}
	
	
	public class BotoesCalendario implements ActionListener {
		
		public void actionPerformed(ActionEvent e) {
			
			for (int i = 0; i < 42; i++) { // adicionar eventos para todos os
											// botões
				if (e.getSource() == calendar[i]) {
					
					try {
							listaConsultasDia(( (AbstractButton) e.getSource()).getText());
						
						} catch (ClassNotFoundException e1) {
							
							e1.printStackTrace();
						} catch (IOException e1) {
							
							e1.printStackTrace();
						}
				}
					
			}

		}
	}
	



	public void listaConsultasDia(String dia) throws ClassNotFoundException, IOException{
		String[] nomeMeses = {"","Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho", "Julho",
				"Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};
	
		ArrayList<String> caminhosCons = new ArrayList<String>();
	
		diaConsulta.add(1);
		diaConsulta.add(6);
	
	
		//File arq = new File("src/concretos/Consultas/"+ nomeMeses[diaConsulta.get(1)]+"/" + dia); // DENTRO DE CONCRETOS...
		File arq = new File("src/concretos/Consultas/"+ nomeMeses[mesAtual] +"/" + dia); // DENTRO DE CONCRETOS...
		
		if (!arq.exists())
			JOptionPane.showMessageDialog(null, "Nao existem consultas nesse dia!");
		else{
			
		
		File[] arquivos;
		arquivos = arq.listFiles(filefilter);
		for (int j = 0; j < arquivos.length; j++){  // PERCORRO OS OBJETOS LÁ DENTRO	
				String path = arquivos[j].getAbsolutePath();
				caminhosCons.add(path);
			
		}
	
		String data = dia + " de " + nomeMeses[diaConsulta.get(1)];
	
		verConsultas(caminhosCons, data);
		}
	}
	
	
	public static void verConsultas(ArrayList<String> listaConsultas, String dia) throws IOException, ClassNotFoundException{
		int y= 0;
		String dados [][] = new String[listaConsultas.size()][5];
		for(int i = 0; i < listaConsultas.size() ; i++){
			String c = listaConsultas.get(i);
			FileInputStream fis = new FileInputStream(c);
			ObjectInputStream ois = new ObjectInputStream(fis);
			Consulta c2 = (Consulta) ois.readObject();
			ois.close();
			
			dados [y][0] = c2.paciente.getNome();
					
			dados [y][1] = c2.medico.getEspecialidade().toString();
			
			dados [y][2] = c2.medico.getNome().toString();
			
			dados [y][3] = c2.getData().toString();
			
			dados [y][4] = c2.getHora();
			
			y++;
			
		}
		@SuppressWarnings("unused")
		VisualizarConsulta telaConsulta = new VisualizarConsulta(dados, dia);
		
	}
	


	FileFilter filefilter = new FileFilter() {
	    public boolean accept(File file) {
	        if (file.getName().endsWith(".ser")) {
	            return true;
            }
            return false;
	    }
	};


	public void control(){	// APENAS UMA FUNÇÃO AO INVÉS DE UMA CLASSE PARA FAZER O HANDLE EVENT (PRESSA)
		
		// PADRÃO PARA JOPTIONPANE
		UIManager.put("OptionPane.messageFont",new FontUIResource(new Font("Serif", Font.PLAIN, 15)));
		UIManager.put("OptionPane.buttonFont", new FontUIResource(new Font("Serif", Font.PLAIN, 10)));
		//*****************************
		
		actionListener = new ActionListener() {
			
			
			public void actionPerformed(ActionEvent e) {
			/*		
			 * 		AQUI FAZEMOS UM SWITCH CASE PARA DETERMINAR AS FUNÇÕES PARA CADA BOTÃO MAS 
			 * 		COMO A PRESSA É GRANDE VOU APENAS MOSTRAR UM JOPTIONPANE PARA TODOS E UM 
			 * 		CHANGE BACKGRUND PARA OS BOTÕES DO CALENDÁRIO
			 * 
				*/	
				if(e.getSource() == controle.getBtnNovaCons() || e.getSource() == controle.getBarraNovaConsulta()){
					
					@SuppressWarnings("unused")
					ConsultaController novaConsulta = new ConsultaController();
				}

				if(e.getSource()==controle.getBotaoIncluir() || e.getSource()==controle.getBarraIncluir() ){ // INCLUSÃO
				
					path = controle.getPath();
					
					switch (getId(path)){
					
					case  2:
						// INCLUSÃO DO ATENDENTE
						
						incluirAtentende = new IncluirAtendente();
						incluirAtentendeController = new IncluirAtendenteController(incluirAtentende);
						incluirAtentendeController.control();
						break;
					case 3:
						
						// INCLUSÃO DO ADMINISTRADOR
						
						incluirAdministrador = new IncluirAdministrador();
						incluirAdministradorController = new IncluirAdministradorController(incluirAdministrador);
						incluirAdministradorController.control();
						break;
					}
				}else if(e.getSource()==controle.getBotaoRemover() || e.getSource()==controle.getBarraExcluir()){ // REMOÇÃO
					
					String path2 = controle.getPath();
					
					switch (getId(path2)){
					
					// REMOÇÃO DO ATENDENTE
					case 2:
						//JOptionPane.showMessageDialog(null, "Digite o nome do paciente ou Medico a ser Removido");
						String nome = JOptionPane.showInputDialog("Nome: ");
						if(nome!=null){
							int aux=0;
							if(!RemoverMedico(nome))
								aux++;
							if(!RemoverPaciente(nome))
								aux++;
							if(aux==2){
								JOptionPane.showMessageDialog(null, "Nome Não Consta!");
							}else if(aux!=2){	
								JOptionPane.showMessageDialog(null, "Removido com Sucesso");
							}aux=0;
						}else{JOptionPane.showMessageDialog(null, "Remoção Cancelda");}
						break;
						
						// REMOÇÃO DO ADMIN
					case 3:
						//JOptionPane.showMessageDialog(null, "Digite o nome do paciente ou Medico ou Atendente a ser Removido");
						String nome2 = JOptionPane.showInputDialog("Nome: ");
						
						if(nome2!=null){
							int aux=0;
							if(!RemoverMedico(nome2))
								aux++;
							if(!RemoverPaciente(nome2))
								aux++;
							if(!RemoverAtendente(nome2))
								aux++;
							if(aux==3){
								JOptionPane.showMessageDialog(null, "Nome Não Consta!");
							}else if(aux!=3){	
								JOptionPane.showMessageDialog(null, "Removido com Sucesso");
							}aux=0;
						}else{JOptionPane.showMessageDialog(null, "Remoção Cancelda");}
						break;
					}
					
				}else if(e.getSource()==controle.getAboutMenuItem()){
					JOptionPane.showMessageDialog(null, "Sistema que simula uma Clínica\n"
							+ "Com cadastro, remoção de funcionários e agendamento de Consultas.");
				
				}else if(e.getSource()==controle.getExitMenuItem()){
					JOptionPane.showMessageDialog(null, "Saindo...");
					controle.dispose();
					//System.exit(0);
				
				}else if(e.getSource()==controle.getHelpMenuItem1()){
					JOptionPane.showMessageDialog(null, "Selecione o item File > Exit, e confirme sua saída");
				
				}else if(e.getSource()==controle.getBotaoInfo() || e.getSource()==controle.getBarraInfo()){
					
					String path2 = controle.getPath();
					
					switch (getId(path2)){
					
					case 2:
						//JOptionPane.showMessageDialog(null, "Digite o nome do Medico ou Paciente\npara colher Informações!");
						String nome = JOptionPane.showInputDialog("Nome: ");
						if(nome!=null){
						int aux=0;
						if(!FindMedico(nome))
							aux++;
						if(!FindPaciente(nome))
							aux++;
						if(aux==2){
							JOptionPane.showMessageDialog(null, "Nome Não Consta!");
						}else if(aux!=2){
							
							// 	AQUI EDITAMOS A INTERFACE PARA INFO
							nome = procurarAtendente(nome); // ENCONTRANDO O CAMINHO DO ARQUIVO
							
							
							InfoView info = new InfoView();
							InfoViewController info_controller = new InfoViewController(info, nome);
							info_controller.control();
							
							
							
						}aux=0;
					}else{JOptionPane.showMessageDialog(null, "Busca Informação Cancelda");}
					break;
				
					
					case 3:
						
						//JOptionPane.showMessageDialog(null, "Digite o nome do Medico ou Paciente\nOu Atendente para colher Informações!");
						String nome2 = JOptionPane.showInputDialog("Nome: ");
						if(nome2!=null){
							int aux=0;
							if(!FindMedico(nome2))
								aux++;
							if(!FindPaciente(nome2))
								aux++;
							if(!FindAtendende(nome2))
								aux++;
							if(aux==3){
								JOptionPane.showMessageDialog(null, "Nome Não Consta!");
							}else if(aux!=3){
								
								nome2 = procurarAdiministrador(nome2); // ENCONTRANDO O CAMINHO DO ARQUIVO
																
								InfoView info = new InfoView();
								InfoViewController info_controller = new InfoViewController(info, nome2);
								info_controller.control();
								
							}aux=0;
						}else{JOptionPane.showMessageDialog(null, "Busca Informação Cancelda");}
						break;
					}
					
					// ******** MODIFICAR
					
				}else if(e.getSource()==controle.getBotaoModificar() || e.getSource()==controle.getBarraModificar()){	
					
					String path2 = controle.getPath();
					
					switch (getId(path2)){
					
						// ATENDENTE
						case 2:
							//JOptionPane.showMessageDialog(null, "Digite o nome do Medico ou Paciente\npara modificar Cadastro!");
							String nome = JOptionPane.showInputDialog("Nome: ");
							if(nome!=null){
								int aux=0;
								if(!FindMedico(nome))
									aux++;
								if(!FindPaciente(nome))
									aux++;
								if(aux==2){
									JOptionPane.showMessageDialog(null, "Nome Não Consta!");
								}else if(aux!=2){	
									
									nome = procurarAtendente(nome); // ENCONTRANDO O CAMINHO DO ARQUIVO
																		
									
									ModificaView info = new ModificaView();
									ModificaController info_controller = new ModificaController(info, nome);
									info_controller.control();
									
								
								}aux=0;
							}else{JOptionPane.showMessageDialog(null, "Modificação Cancelda");}
							break;
						case 3:
							
						//	JOptionPane.showMessageDialog(null, "Digite o nome do Medico ou Paciente\nOu Atendente para modificar Cadastro!");
							String nome2 = JOptionPane.showInputDialog("Nome: ");
							if(nome2!=null){
								int aux=0;
								if(!FindMedico(nome2))
									aux++;
								if(!FindPaciente(nome2))
									aux++;
								if(!FindAtendende(nome2))
									aux++;
								if(aux==3){
									JOptionPane.showMessageDialog(null, "Nome Não Consta!");
								}else if(aux!=3){
									
									nome2 = procurarAdiministrador(nome2); // ENCONTRANDO O CAMINHO DO ARQUIVO
									
									ModificaView info = new ModificaView();
									ModificaController info_controller = new ModificaController(info, nome2);
									info_controller.control();
									
								}aux=0;
							}else{JOptionPane.showMessageDialog(null, "Modificação Cancelda");}
							break;
												
					}
					
						
				// TRANSIÇÃO DOS LABELS MESES
				}else if(e.getSource()==controle.getNextMes()){
					int i=controle.getMesTitulo();
					
					if(i<6){
						controle.setMesTitulo(i+1);
						controle.TransicaoMeses(i+1);
						
						mesAtual++;
					}
					
				}else if(e.getSource()==controle.getPrevMes()){
					int i = controle.getMesTitulo();
					
					if(i>0){
						controle.setMesTitulo(i-1);
						controle.TransicaoMeses(i-1);
						
						mesAtual--;
					}
				}else if(e.getSource()==controle.getCreditos()){
					@SuppressWarnings("unused")
					Creditos creditos = new Creditos();
	
				}else if(e.getSource()==controle.getList() || e.getSource()==controle.getBarraListar()){
				
					String path2 = controle.getPath();
					
					switch (getId(path2)){
					
					case 3:
						@SuppressWarnings("unused")
						ListView listview = new ListView(getArrayPacientes(),getArrayMedicos(),getArrayAtendenes());
						break;
					case 2:
						String[] notAtendentesInformations = new String[1];
						notAtendentesInformations[0] = "NÃO POSSUI INFORMAÇÕES SOBRE OUTROS ATENDENTES";
						@SuppressWarnings("unused")
						ListView listview2 = new ListView(getArrayPacientes(),getArrayMedicos(),notAtendentesInformations);
						break;
					}
				}
				
			
				
				
			}
		};
		

		controle.getBotaoIncluir().addActionListener(actionListener);
		controle.getAboutMenuItem().addActionListener(actionListener);
		controle.getExitMenuItem().addActionListener(actionListener);
		controle.getHelpMenuItem1().addActionListener(actionListener);
		controle.getBotaoRemover().addActionListener(actionListener);
		controle.getBotaoInfo().addActionListener(actionListener);
		controle.getNextMes().addActionListener(actionListener);
		controle.getPrevMes().addActionListener(actionListener);
		controle.getBotaoModificar().addActionListener(actionListener);
		controle.getBtnNovaCons().addActionListener(actionListener);
		controle.getBarraIncluir().addActionListener(actionListener);
		controle.getBarraExcluir().addActionListener(actionListener);
		controle.getCreditos().addActionListener(actionListener);
		controle.getBarraModificar().addActionListener(actionListener);
		controle.getBarraInfo().addActionListener(actionListener);
		controle.getBarraNovaConsulta().addActionListener(actionListener);
		controle.getList().addActionListener(actionListener);
		controle.getBarraListar().addActionListener(actionListener);
	}
	
	// PEGANDO TODOS OS NOMES DOS PACIENTES
	public String[] getArrayPacientes(){
		
		String[] arrayPacientes;
		
		File arq = new File("src/concretos/Pacientes");
		File[] subpastas = arq.listFiles(filefilter);
			
		// ADCICONANDO A QUANTIDADE DE LOGINS
		arrayPacientes = new String[subpastas.length];
		
		for (int i = 0; i < subpastas.length; i++) {
			int aux = (int) subpastas[i].getName().length()-4;
			
			String stringAux = subpastas[i].getName().substring(0, aux);
			arrayPacientes[i] = stringAux;
			
			}
			return arrayPacientes;
		}
		
	// PEGANDO TODOS OS NOMES DOS Medicos
	public String[] getArrayMedicos(){
		
		String[] arrayMedicos;
		
		File arq = new File("src/concretos/Medicos");
		File[] subpastas = arq.listFiles(filefilter);
			
		// ADCICONANDO A QUANTIDADE DE LOGINS
		arrayMedicos = new String[subpastas.length];
		
		for (int i = 0; i < subpastas.length; i++) {
			int aux = (int) subpastas[i].getName().length()-4;
			
			String stringAux = subpastas[i].getName().substring(0, aux);
			arrayMedicos[i] = stringAux;
			
			}
			return arrayMedicos;
		}
	// PEGANDO TODOS OS NOMES DOS ATENDENTES
		public String[] getArrayAtendenes(){
			
			String[] arrayAtendentes;
			
			File arq = new File("src/concretos/Atendentes");
			File[] subpastas = arq.listFiles(filefilter);
				
			// ADCICONANDO A QUANTIDADE DE LOGINS
			arrayAtendentes = new String[subpastas.length];
			
			for (int i = 0; i < subpastas.length; i++) {
				int aux = (int) subpastas[i].getName().length()-4;
				
				String stringAux = subpastas[i].getName().substring(0, aux);
				arrayAtendentes[i] = stringAux;
				
				}
				return arrayAtendentes;
			}
		
		

	
	
	
	//Procura os medicos com uma especialidade específica
	// 0 - Medico , 1 - Paciente
    public String procurarAtendente(String nome)
    {
    	@SuppressWarnings("unused")
		ArrayList<String> medicos = new ArrayList<String>();
    	int op = 0;
   
    	int i = 1;
    	boolean achar = false;
    	
    	File arq = null;
    	
    	while ((i <= 2) && (achar == false)){
    	if (i == 1){
    		arq = new File("src/concretos/Medicos"); 
    		op = 0;
    	}else if (i == 2){
    		arq = new File("src/concretos/Pacientes");
    		op = 1;
    	}
    	
		File[] arquivos;
		arquivos = arq.listFiles(filefilter);
		for (int j = 0; j < arquivos.length; j++){  // PERCORRO OS OBJETOS LÁ DENTRO	
			String path = arquivos[j].getAbsolutePath();
			Pessoa p = (Pessoa) ConsultaController.extrairPessoa(path, op);
				
			if (nome.equals(p.getNome()))
			{
				achar = true;

				return path;
			}
		}
		i++;
    	}
		return "";	
    }
    public String procurarAdiministrador(String nome)
    {
    	@SuppressWarnings("unused")
		ArrayList<String> medicos = new ArrayList<String>();
    	int op = 0;
   
    	int i = 1;
    	boolean achar = false;
    	
    	File arq = null;
    	
    	while ((i <= 3) && (achar == false)){
    	if (i == 1){
    		arq = new File("src/concretos/Medicos"); 
    		op = 0;
    	}else if (i == 2){
    		arq = new File("src/concretos/Pacientes");
    		op = 1;
    	}else if (i == 3){ // PEQUNA DIFERENÇA.........
    		arq = new File("src/concretos/Atendentes");
    		op = 2;
    	}
    	
		File[] arquivos;
		arquivos = arq.listFiles(filefilter);
		for (int j = 0; j < arquivos.length; j++){  // PERCORRO OS OBJETOS LÁ DENTRO	
			String path = arquivos[j].getAbsolutePath();
			Pessoa p = (Pessoa) ConsultaController.extrairPessoa(path, op);
				
			if (nome.equals(p.getNome()))
			{
				achar = true;

				return path;
			}
		}
		i++;
    	}
		return "";	
    }

	
    
    
	private int getId(String caminho){
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
	
	/**
	 * 		INFORMAÇÕES 
	 * */
	
	public boolean FindMedico(String file){
		
		File arq = new File("src/concretos/Medicos");
		File[] subpastas = arq.listFiles(filefilter);
		for (int i = 0; i < subpastas.length; i++) {
			int aux = (int) subpastas[i].getName().length()-4;
			if(file.equalsIgnoreCase(subpastas[i].getName().substring(0, aux))){

				return true;
			}
		}return false;
	}
	public boolean FindPaciente(String file){
		
		File arq = new File("src/concretos/Pacientes");
		File[] subpastas = arq.listFiles(filefilter);
		for (int i = 0; i < subpastas.length; i++) {
			int aux = (int) subpastas[i].getName().length()-4;
			if(file.equalsIgnoreCase(subpastas[i].getName().substring(0, aux))){

				return true;
			}
		}return false;
	}
	public boolean FindAtendende(String file){
		
		File arq = new File("src/concretos/Atendentes");
		File[] subpastas = arq.listFiles(filefilter);
		for (int i = 0; i < subpastas.length; i++) {
			int aux = (int) subpastas[i].getName().length()-4;
			if(file.equalsIgnoreCase(subpastas[i].getName().substring(0, aux))){

				return true;
			}
		}return false;
	}
	
	/**
	 * 		REMOÇÕES 
	 * */
	
	public boolean RemoverMedico(String file){
		
		File arq = new File("src/concretos/Medicos");
		File[] subpastas = arq.listFiles(filefilter);
		for (int i = 0; i < subpastas.length; i++) {
			int aux = (int) subpastas[i].getName().length()-4;
			if(file.equalsIgnoreCase(subpastas[i].getName().substring(0, aux))){
			
				subpastas[i].delete(); // destruo o arquivo;
				return true;
			}
		}return false;
	}
	public boolean RemoverPaciente(String file){
		
		File arq = new File("src/concretos/Pacientes");
		File[] subpastas = arq.listFiles(filefilter);
		for (int i = 0; i < subpastas.length; i++) {
			int aux = (int) subpastas[i].getName().length()-4;
			if(file.equalsIgnoreCase(subpastas[i].getName().substring(0, aux))){
			
				subpastas[i].delete(); // destruo o arquivo;
				return true;
			}	
		}return false;
	}
	public boolean RemoverAtendente(String file){
		
		File arq = new File("src/concretos/Atendentes");
		File[] subpastas = arq.listFiles(filefilter);
		for (int i = 0; i < subpastas.length; i++) {
			int aux = (int) subpastas[i].getName().length()-4;
			if(file.equalsIgnoreCase(subpastas[i].getName().substring(0, aux))){
			
				subpastas[i].delete(); // destruo o arquivo;
				return true;
			}
		}return false;
	}
	
	public String searchLogin(String login){
		
		/**
		 * 	ESTE METODO PROCURA OS ARQUIVOS DO LOGIN, SE ACHAR RETORNA TRUE, SE NÃO, FALSE
		 * 
		 * */		
		File arq = new File("src/concretos"); // DENTRO DE CONCRETOS...
		File[] subpastas = arq.listFiles(filefilter);
		File arq2; 
		File[] arquivos;
		for (int i = 0; i < subpastas.length; i++) { // PERCORRO TUDO LÁ...
			if (subpastas[i].isDirectory()) {   // SE FOREM DIRETORIOS.... OU SEJA PACIENTES, MEDICOS ETC
				arq2 = new File(subpastas[i].getPath());
				arquivos = arq2.listFiles(filefilter);
				for (int j = 0; j < arquivos.length; j++){  // PERCORRO OS OBJETOS LÁ DENTRO	
					int aux = (int) arquivos[j].getName().length()-4;  // PARA TIRAR O .SER DOS OBJETOS
					if(login.equalsIgnoreCase(arquivos[j].getName().substring(0, aux))){ // SE OUVER UM LOGIN OK. VOU AGORA CHECAR A SENHA
						return path = arquivos[j].getAbsolutePath();
					}
				}
			}		
		}
		return " ";
	}
	
		
}
