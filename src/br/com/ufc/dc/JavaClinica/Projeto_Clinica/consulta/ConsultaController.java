package consulta;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusAdapter;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.File;
import java.io.FileFilter;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;

import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JOptionPane;
import javax.swing.JRadioButton;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import concretos.Atendente;
import concretos.Medico;
import concretos.Paciente;
import concretos.Pessoa;

public class ConsultaController implements ActionListener{
	
	ConsultaView novaConsulta; 
			
			
	int contMedic = 0;

	static Paciente pacienteAtual;
	static Medico medicoAtual;
	boolean pacienteOk = false;
	
	
	public ConsultaController()
	{		
		novaConsulta = new ConsultaView(this);
		
	}		
		
	
	//Ação para limpar o JTextField do paciente quando clicar nele
	MouseAdapter mouseClick = new MouseAdapter() {  	  
    	public void mouseClicked(MouseEvent arg0) {  
    		novaConsulta.paciente.setText("");  
    	}    
    };

    
    //Ação para buscar o paciente quando apertar Enter
    ActionListener apertarEnter = new ActionListener() {	
		public void actionPerformed(ActionEvent e) {
			procurarPaciente();
		}
	};
	
	
	//Ação para buscar o paciente quando mexer no JTextField do paciente
	FocusAdapter janelaFoco = new FocusAdapter() {  
        public void focusLost(java.awt.event.FocusEvent evt) {  
            procurarPaciente();  
        }  
     };
    
     
       
     
    //Tratamento de eventos gerais 
    public void actionPerformed(ActionEvent e) 
    {
 		if (e.getSource() == novaConsulta.avancarEspec)
 		{
 	    	//Verifica se a especialidade e o paciente foram escolhidos para poder avancar
 			if (((novaConsulta.especialidade.getText()).equals("Selecione a especialidade")) || (pacienteOk == false))
 			{
 				JOptionPane.showMessageDialog   (null, "Selecione a especialidade e o paciente antes de avançar!");
 			}
 			else
 			{
 				if(contMedic > 0)
 				{
 					novaConsulta.listaMedicos.setSelectedIndex(0);
 				}
 				
 				//Exibe o painel dos medicos
 				novaConsulta.montarListaMedicos();
 				novaConsulta.c1.show(novaConsulta.consultasCalend, "2");
 				novaConsulta.listaMedicos.repaint();
 				novaConsulta.c.repaint();
 				contMedic++;
 			}
 		}
 		
 		
 		if (e.getSource() == novaConsulta.avancarMedico)
 		{
 	    	//Verifica se o medico e o paciente foram escolhidos para poder avancar
 			if (((novaConsulta.medico.getText()).equals("Selecione o medico")) || (pacienteOk == false))
 			{
 				JOptionPane.showMessageDialog   (null, "Selecione o medico antes de avançar!");
 			}
 			//Se for avancar ele armazena o medico escolhido no atributo medicoAtual
 			else
 			{
 				//Busca o medico escolhido
 	 	    	File arq = new File("src/concretos/Medicos"); 
 	 			File[] arquivos;
 	 			arquivos = arq.listFiles(filefilter);
 	 			int j = 0;
 	 			boolean verif = false;
 	 			while ((j < arquivos.length) && (verif == false)){  // PERCORRO OS OBJETOS LÁ DENTRO	
 	 				String path = arquivos[j].getAbsolutePath();
 	 				Medico med = (Medico) extrairPessoa(path, 0);
 	 					
 	 				//Quando achar o medico escolhido ele seta o medicoAtual
 	 				if (med.getNome().equals((novaConsulta.medico.getText())))
 	 				{
 	 					medicoAtual = med;
 	 					verif = true;
 	 				}
 	 			
 	 			j++;
 	 			}			
 			
 	 		//Monta o painel do calendario
 			novaConsulta.montarCDia();
 			}
 		
 		}

 	}
     
    
 	//Filtro para verificar somente os arquivos .ser	
 	FileFilter filefilter = new FileFilter() {
       public boolean accept(File file) {
    	   if (file.getName().endsWith(".ser")) {
    		   return true;
 	       }
 	       return false;
 	       }
 	};
 	    
    
 	//Procura o paciente escolhido e verifica se ele existe ou nao
 	public void procurarPaciente()
    {
     	boolean verif = false;
 		int j;
     	
    	File arq = new File("src/concretos/Pacientes"); 
 		File[] arquivos;
 		arquivos = arq.listFiles(filefilter);
 		j = 0;
 		
 		while ((j < arquivos.length) && (verif == false)) // PERCORRO OS OBJETOS LÁ DENTRO	
 		{ 
 			String path = arquivos[j].getAbsolutePath();
 			Paciente pac = (Paciente) extrairPessoa(path, 1);			
 			if (pac.getNome().equals(novaConsulta.paciente.getText()))
 			{
 				novaConsulta.idadePaciente.setText(String.valueOf(pac.getIdade()));
 				novaConsulta.idadePaciente.setEnabled(true);
 				verif = true;
 				
 				pacienteAtual = pac;
 				pacienteOk = true;
 			}
 				
 			j++;
 		}
 		
    	//Avisa que o paciente entrado nao foi encontrado 		
 		if (verif == false)
 		{
 			JOptionPane.showMessageDialog   (null, "O nome do paciente entrado não consta nos nossos registros!");
 			novaConsulta.paciente.setText("");
 			novaConsulta.idadePaciente.setText("Idade do Paciente");
 			novaConsulta.idadePaciente.setEnabled(false);
 			
 			pacienteOk = false;
 		}
 		
 	}
     
     
 	//Monta o calendario do mes seguinte
    ActionListener avancarMes = new ActionListener() {
    	public void actionPerformed(ActionEvent e) {
    		
 			novaConsulta.cCalTitulos.removeAll();
 			novaConsulta.consultasCal.removeAll();
 			novaConsulta.contadorMeses++;

 			
 			//Ajusta a transicao de ano
 			novaConsulta.contAno++;
 			if (novaConsulta.contAno == 13)
 			{
 				novaConsulta.contAno = 1;
 				novaConsulta.anoCalend++;
 			}
 			
 			novaConsulta.montarCalendDias(novaConsulta.proxMes);

 		}
 	};     
 	
 	
 	//Monta o calendario do mes anterior
 	ActionListener voltarMes = new ActionListener() {
 		public void actionPerformed(ActionEvent e) {
  			
 			novaConsulta.cCalTitulos.removeAll();
  			novaConsulta.consultasCal.removeAll();
  			novaConsulta.contadorMeses--;

  			
 			//Ajusta a transicao de ano
  			novaConsulta.contAno--;
  			if (novaConsulta.contAno == 0)
  			{
  				novaConsulta.contAno = 12;
  				novaConsulta.anoCalend--;
  			}
  			
  			novaConsulta.montarCalendDias(novaConsulta.antMes);

  		}
  	};     

 	
 	//Ação dos botões de dia do calendario
 	ActionListener setDaybtn = new ActionListener() {
 		public void actionPerformed(ActionEvent e) {
 			JButton b = new JButton();
 			b = (JButton) e.getSource();
 				
 			Integer temp = Integer.parseInt(b.getText());
 			
 			//Seta a data no campo do dia do painel consultasInfo
 			novaConsulta.diaConsulta.add(0, temp);
 			novaConsulta.diaConsulta.add(1, novaConsulta.numMes);
 			novaConsulta.diaConsulta.add(2, novaConsulta.anoCalend);
 				
 			String dataTemp = String.valueOf(novaConsulta.diaConsulta.get(0));
 			
 			dataTemp = dataTemp + "." + novaConsulta.diaConsulta.get(1) + "." + novaConsulta.diaConsulta.get(2);
 				
 			novaConsulta.data.setText(dataTemp);
 			novaConsulta.data.setEnabled(true);
 				
 			novaConsulta.montarCHora();
		}
 	};
     
 	
 	ActionListener marcarCons = new ActionListener() {	
		public void actionPerformed(ActionEvent e) {
			
			//Muda a agenda do medico, no dia e hora da consulta para ocupado
			medicoAtual.setAgenda(novaConsulta.diaConsulta.get(3), 
					novaConsulta.diaConsulta.get(0), novaConsulta.diaConsulta.get(1));
			
			
			//Cria um objeto consulta com as informacoes escolhidas
			Consulta consulta = new Consulta(pacienteAtual, medicoAtual, novaConsulta.data.getText(), novaConsulta.hora.getText(), novaConsulta.diaConsulta);
			
			try {
				serializandoConsulta(consulta);
			} catch (IOException e1) {
				e1.printStackTrace();
			} catch (ClassNotFoundException e1) {
				e1.printStackTrace();
			}
			
			novaConsulta.dispose();
			
			JOptionPane.showMessageDialog(null, "Consulta marcada com sucesso");
			
		}
	};

	
	//Pega a agenda do mes do medico atual
 	public boolean[][] getAgendaMed(int numDoMes)
 	{
 		return medicoAtual.getAgenda(numDoMes);
	}
 		
 		
 	//Seta a especialidade de acordo com a que foi escolhida pelo usuario
 	ListSelectionListener listaSelect =	new ListSelectionListener() {
 		public void valueChanged(ListSelectionEvent e) {
			novaConsulta.especialidade.setText(novaConsulta.listaGeralEspec.get(novaConsulta.listaEspec.getSelectedIndex()));
			novaConsulta.especialidade.setEnabled(true);
		}
	};
 		
	
	//Cria uma lista dos medicos disponiveis com a especialidade escolhida
	public void listarMedicos(String espec)
	{
		DefaultListModel<String> medicoList = new DefaultListModel<String>();
		int i;		
		ArrayList<String> med = new ArrayList<String>();
		
		med = getMedEspec(espec);

		for (i = 0 ; i < med.size(); i++)
		{
			medicoList.addElement(med.get(i));
			
		}
		
		novaConsulta.listaGeralMed = medicoList;
	}
	
	
	RadioButtonHandler selectHora = new RadioButtonHandler();
	
	//Classe para tratar o evento dos JRadioButtons
	private class RadioButtonHandler implements ItemListener {

		public void itemStateChanged(ItemEvent e) {
			JRadioButton b = new JRadioButton();
			b = (JRadioButton) e.getSource();
			novaConsulta.hora.setText(b.getText());
			novaConsulta.hora.setEnabled(true);
				
				
			//Salva o indice da hora da consulta baseado no array agenda do medico
			if (b.getText().equals("08:00 h"))
				novaConsulta.diaConsulta.add(3, 1);
			else if (b.getText().equals("08:30 h"))
				novaConsulta.diaConsulta.add(3, 2);
			else if (b.getText().equals("09:00 h"))
				novaConsulta.diaConsulta.add(3, 3);
			else if (b.getText().equals("09:30 h"))
				novaConsulta.diaConsulta.add(3, 4);
			else if (b.getText().equals("10:00 h"))
				novaConsulta.diaConsulta.add(3, 5);
			else if (b.getText().equals("10:30 h"))
				novaConsulta.diaConsulta.add(3, 6);
			else if (b.getText().equals("11:00 h"))
				novaConsulta.diaConsulta.add(3, 7);
			else if (b.getText().equals("11:30 h"))
				novaConsulta.diaConsulta.add(3, 8);
			else if (b.getText().equals("12:00 h"))
				novaConsulta.diaConsulta.add(3, 9);
			else if (b.getText().equals("12:30 h"))
				novaConsulta.diaConsulta.add(3, 10);
									
		}
			
	}
 	
	
	//Insere o caminho da consulta criada no paciente e medico da consulta
	public static void atualizarCaminho(Medico medicoAtual, Paciente pacienteAtual,String path){
		pacienteAtual.setConsulta(path);
		medicoAtual.setConsulta(path);
	}
		
			
	//Retorna a especialidade de todos os medicos cadastrados	
    public ArrayList<String> getEspec()
    {
    	ArrayList<String> especs = new ArrayList<String>();
    	File arq = new File("src/concretos/Medicos"); 
		File[] arquivos;
		arquivos = arq.listFiles(filefilter);
		for (int j = 0; j < arquivos.length; j++){  // PERCORRO OS OBJETOS LÁ DENTRO	
			String path = arquivos[j].getAbsolutePath();
				Medico med = (Medico) extrairPessoa(path, 0);
				
				especs.add(med.getEspecialidade());			
		}
		
		return especs;
	}
    
    
    //Deserializa os medicos armazenados
    public static Pessoa extrairPessoa(String path, int op){
		  Medico m = null;
		  Paciente p = null;
		  Atendente a = null;
	      try
	      {
	         FileInputStream fileIn = new FileInputStream(path);
	         ObjectInputStream in = new ObjectInputStream(fileIn);
	         
	         if (op == 0)
	        	 m = (Medico) in.readObject();
	         else if (op == 1)
	        	 p = (Paciente) in.readObject();
	         else if (op == 2)
	        	 a = (Atendente) in.readObject();
	         
	         in.close();
	         fileIn.close();
	      }catch(IOException i)
	      {
	         i.printStackTrace();
	       }catch(ClassNotFoundException c)
	       {
	    	 c.printStackTrace();
	       }
	       
	      if (op == 0)
	    	  return m;
	      else if (op == 1)
	    	  return p;
	      else
	    	  return a;
	}
    
    
    //Procura os medicos com uma especialidade específica
    public ArrayList<String> getMedEspec(String espec)
    {
    	ArrayList<String> medicos = new ArrayList<String>();
    	File arq = new File("src/concretos/Medicos"); 
		File[] arquivos;
		arquivos = arq.listFiles(filefilter);
		for (int j = 0; j < arquivos.length; j++){  // PERCORRO OS OBJETOS LÁ DENTRO	
			String path = arquivos[j].getAbsolutePath();
			Medico med = (Medico) extrairPessoa(path, 0);
				
			if (med.getEspecialidade().equals(espec))
			{
				medicos.add(med.getNome());
			}
		}
		
		return medicos;
    		
    }
		
    
    //Armazenar as alterações que foram feitas no medico
    public static void serializandoMedico(Medico p) 
    { // IMPORTANTE,
		// CRIANDO.....
    	try {

    		FileOutputStream fos = new FileOutputStream("src/concretos/Medicos/" + p.getNome() + ".ser");
			ObjectOutputStream oos = new ObjectOutputStream(fos);
			oos.writeObject(p);
			oos.close();
			fos.close();
		} catch (IOException i) {
			i.printStackTrace();
		}

    }
    
    
    //Armazenar as alterações que foram feitas no Paciente
    public static void serializandoPaciente(Paciente p) 
    { // IMPORTANTE,
		// CRIANDO.....
    	try {

    		FileOutputStream fos = new FileOutputStream(
					"src/concretos/Pacientes/" + p.getNome() + ".ser");
			ObjectOutputStream oos = new ObjectOutputStream(fos);
			oos.writeObject(p);
			oos.close();
			fos.close();
		} catch (IOException i) {
			i.printStackTrace();
		}

    }
    
    
    //Armazena a consulta criada
    public static void serializandoConsulta(Consulta c) throws IOException, ClassNotFoundException
    {	
    	String[] nomeMeses = {"","Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho", "Julho",
				"Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};
    	
    	
    	//Extrai o contador das consultas que esta armazenado
    	Integer contadorConsultas = new Integer(1);
    	String path = ("src/Variaveis/contadorConsultas.ser");
    	
		try {	
			FileInputStream fis = new FileInputStream(path);
			ObjectInputStream ois = new ObjectInputStream(fis);
			contadorConsultas = (Integer) ois.readObject();
			ois.close();
		} catch (FileNotFoundException e) {
			
			FileOutputStream fos = new FileOutputStream(path);
			ObjectOutputStream oos = new ObjectOutputStream(fos);
			oos.writeObject(contadorConsultas);
			oos.close();
			
			FileInputStream fis = new FileInputStream(path);
			ObjectInputStream ois = new ObjectInputStream(fis);
			contadorConsultas = (Integer) ois.readObject();
			ois.close();
			
		} catch (IOException e) {
			e.printStackTrace();
			
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
    	
		
		//Armazenando a consulta
		String path2 = ("src/concretos/Consultas/" + nomeMeses[c.diaConsulta.get(1)] +"/"
	    		+c.diaConsulta.get(0)+"/consulta"+contadorConsultas+".ser");
		
	
    	try {

    	    File diretorio = new File("src/concretos/Consultas/" + nomeMeses[c.diaConsulta.get(1)] +"/"
    	    		+c.diaConsulta.get(0));
    	    if (!diretorio.exists()) {  
    	       diretorio.mkdirs(); //mkdir() cria somente um diretório, mkdirs() cria diretórios e subdiretórios.  
    	    }   
    		
    	    FileOutputStream fos = new FileOutputStream(path2);
    		
			ObjectOutputStream oos = new ObjectOutputStream(fos);
			oos.writeObject(c);
			oos.close();
			fos.close();
			
		} catch (IOException i) {
			i.printStackTrace();
		}
    	
    	
    	atualizarCaminho(medicoAtual, pacienteAtual, path2);
    	
    	
    	contadorConsultas++;
    	
    	//Amazena o contador de consultas
    	FileOutputStream fos = new FileOutputStream(path);
		ObjectOutputStream oos = new ObjectOutputStream(fos);
		oos.writeObject(contadorConsultas);
		oos.close();
	
		//Serializa o paciente e médico atual
		serializandoPaciente(pacienteAtual);
		serializandoMedico(medicoAtual);
		
    }
    
}

