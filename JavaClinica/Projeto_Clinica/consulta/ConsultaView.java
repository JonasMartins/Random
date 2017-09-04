package consulta;


import java.awt.CardLayout;
import java.awt.Color;
import java.awt.Container;
import java.awt.Font;
import java.awt.GridLayout;
import java.util.ArrayList;
import java.util.GregorianCalendar;

import javax.swing.ButtonGroup;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;


public class ConsultaView extends JFrame  {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	ConsultaController consController;
	
	JTextField obs, paciente, idadePaciente, especialidade, data, hora, medico;
	JButton marcarConsulta, avancarEspec, avancarMedico; //voltarMedico;
	String especValue, medicoValue;
	
	JPanel consultasInfo, consultasCalend, consultasEspec, consultasMedico, consultasCal, btnCalend;
	Container c;
	
	CardLayout c1 = new CardLayout();
	
	JList<String> listaEspec = new JList<String>();
	JList<String> listaMedicos = new JList<String>();
	DefaultListModel<String> listaGeralEspec = new DefaultListModel<String>();
	DefaultListModel<String> listaGeralMed = new DefaultListModel<String>();
	
	
	//Variaveis do calendario das consultas
	ArrayList<Integer> diaConsulta = new ArrayList<Integer>();
	JPanel cCalTitulos;
	ArrayList<Integer> diasRest = new ArrayList<Integer>();
	JButton[] vectorBtnCalend;
	int proxMes;
	int antMes;
	int anoCalend = 2015;
	int contAno = 6;
	int numMes;
	int contadorMeses = 0;
	boolean validate = false;
	boolean validar = false;
	
	boolean[][] agenda;
	
	//Variaveis para trabalhar com o dia e mes atual
	ArrayList<Integer> diaAtual = new ArrayList<Integer>();
	
	
	//Variaveis do painel consultasHora
	JRadioButton[] btnConsHora;
	
	/******Fontes******/
	Font subtitle1 = new Font("serif", Font.BOLD, 17);
	Font subtitle2 = new Font("times new roman", 100, 15);
	Font title1 = new Font("serif", Font.BOLD, 28);
	Font title2 = new Font("serif", Font.BOLD, 22);
	

	
	
	@SuppressWarnings({ "deprecation" })
	public ConsultaView(ConsultaController consController)
	{			
		super("Consulta");
		
		diasRest.add(contadorMeses, 0); //Inicializando o array dos dias restantes
		this.consController = consController;

		//Inicializando o array com data atual
		setDiaAtual();
		
		
		
		/******Criando Paineis e Containers******/
		c = getContentPane();
		consultasCalend = new JPanel();
			consultasCalend.setLayout(c1);
			consultasCalend.setBackground(new Color(169,169,169));

		consultasInfo = new JPanel(null);
			consultasInfo.setBackground(new Color(169,169,169));

		consultasEspec = new JPanel(null);
			consultasEspec.setBackground(new Color(169,169,169));

		consultasMedico = new JPanel(null);
			consultasMedico.setBackground(new Color(169,169,169));

		
		/******Tamanho das Frames e Paineis******/
		c.reshape(0, 0, 1116, 660);
		consultasCalend.reshape(550, 0, 558, 660);
		consultasInfo.reshape(0, 0, 558, 660);
		consultasEspec.reshape(550, 0, 558, 660);
		consultasMedico.reshape(550, 0, 558, 660);
		
		
		/******Criando Componentes do consultasInfo******/
		//cInfoObs
		marcarConsulta = new JButton("Marcar Consulta");
			marcarConsulta.addActionListener(consController.marcarCons);
		obs = new JTextField();
		JLabel titleObs = new JLabel("Observações sobre o Paciente:");
		
		//cInfoEspec
		JLabel titleNCons = new JLabel("Nova Consulta");
		JLabel titleCod = new JLabel("Idade:");
		JLabel titlePaciente = new JLabel("Paciente:");		
		JLabel titleEspec = new JLabel("Especialidade:");
		JLabel titleMedico = new JLabel("Medico:");
		JLabel titleData = new JLabel("Data:");
		JLabel titleHora = new JLabel("Hora:");
		
		//Campos
		idadePaciente = new JTextField("Idade do Paciente");
		paciente = new JTextField("Nome do paciente");
		especialidade = new JTextField("Selecione a especialidade");
		medico = new JTextField("Selecione o medico");
		data = new JTextField("Data");
		hora = new JTextField("Hora");
			
		//Acao de limpar o campo quando clicar nele
		paciente.addMouseListener(consController.mouseClick);
		
		//Açao quando PACIENTE perde o foco
		paciente.addFocusListener(consController.janelaFoco);  
				
		
		//Ação do ENTER do JTextField que vai procurar pelo paciente
		paciente.addActionListener(consController.apertarEnter);	
			
		
		/******Setando Fonte dos Componentes******/
		titleNCons.setFont(title1);		
		titleCod.setFont(subtitle1);
		titlePaciente.setFont(subtitle1);
		titleEspec.setFont(subtitle1);
		titleMedico.setFont(subtitle1);
		titleData.setFont(subtitle1);
		titleHora.setFont(subtitle1);
		titleObs.setFont(subtitle1);

		idadePaciente.setFont(subtitle2);
		paciente.setFont(subtitle2);
		especialidade.setFont(subtitle2);
		medico.setFont(subtitle2);
		data.setFont(subtitle2);
		hora.setFont(subtitle2);

		
		//Desativando campos
		idadePaciente.setEditable(false);
		especialidade.setEditable(false);
		medico.setEditable(false);
		data.setEditable(false);
		hora.setEditable(false);
		
		paciente.setEnabled(true);
		idadePaciente.setEnabled(false);
		especialidade.setEnabled(false);
		medico.setEnabled(false);
		data.setEnabled(false);
		hora.setEnabled(false);
		
		
		
		/******Organizando Componentes do consultasInfo******/
		marcarConsulta.setBounds(204, 580, 150, 25);
		obs.setBounds(20, 340, 518, 230);
		titleObs.setBounds(20, 310, 250, 25);
		titleNCons.setBounds(189, 5, 180, 30);
		
		titlePaciente.setBounds(20, 60, 125, 25);     //(20, 110, 125, 25);
		titleCod.setBounds(20, 110, 125, 25);             //(20, 60, 125, 25);
		titleEspec.setBounds(20, 160, 125, 25);
		titleMedico.setBounds(20, 210, 100, 25);
		titleData.setBounds(20, 260, 100, 25);
		titleHora.setBounds(319, 260, 100, 25);
		
		paciente.setBounds(145, 60, 393, 25);    //(145, 110, 393, 25);
		idadePaciente.setBounds(145, 110, 393, 25);    //(145, 60, 393, 25);
		especialidade.setBounds(145, 160, 393, 25);
		medico.setBounds(145, 210, 393, 25);
		data.setBounds(145, 260, 123, 25);
		hora.setBounds(415, 260, 123, 25);
		


				
		//Criando a escolha do medico
		//nadanada nada nada
		montarConsultasMedico();
		
		
		//consultasInfo.setBackground(new Color(193, 205, 193));
		
		
		/******Agrupando Estruturas******/
		consultasInfo.add(marcarConsulta);
		consultasInfo.add(obs);
		consultasInfo.add(titleObs);
		consultasInfo.add(titleNCons);
		consultasInfo.add(titleCod);
		consultasInfo.add(titlePaciente);
		consultasInfo.add(titleEspec);
		consultasInfo.add(titleMedico);
		consultasInfo.add(titleData);
		consultasInfo.add(titleHora);
		
		consultasInfo.add(idadePaciente);
		consultasInfo.add(idadePaciente);
		consultasInfo.add(paciente);
		consultasInfo.add(especialidade);
		consultasInfo.add(medico);
		consultasInfo.add(data);
		consultasInfo.add(hora);
		
		
		montarCEspec();
		consultasCalend.add(consultasMedico, "2");
		
		
		c.add(consultasInfo);
		c.add(consultasCalend);
		
		
		/******Janela******/
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		setBounds(0, 0, 1166, 660);
		setVisible(true);
		
	}
	
	
	
	
	void montarConsultasMedico()
	{
		/******Criando Componentes de consultasMedico******/
		JLabel titleCMedico = new JLabel("Medicos:");
		avancarMedico = new JButton("Avançar >>");
				
		
		/******Fontes******/
		titleCMedico.setFont(title2);

		
		/******Organizando Componentes do consultasMedico******/
		titleCMedico.setBounds(792, 60, 90, 40);
		avancarMedico.setBounds(762, 500, 150, 25);


		/******Setando Eventos consultasMedico******/
		avancarMedico.addActionListener(consController);
		
		/*******Adicionando Estruturas*******/
		consultasMedico.add(titleCMedico);
		consultasMedico.add(avancarMedico);
	}
	
	
	
	
	
	
	void setDiaAtual()
	{
		GregorianCalendar calendar = new GregorianCalendar(); 
		diaAtual.add(calendar.get(GregorianCalendar.DAY_OF_MONTH));  
		diaAtual.add(calendar.get(GregorianCalendar.MONTH)); 
		diaAtual.add(calendar.get(GregorianCalendar.YEAR)); 
	}
	
	public void montarCHora()
	{
		//Criando os Paineis principais		
		JPanel consultasHora = new JPanel(null);
			consultasHora.setBackground(new Color(169,169,169));

		JPanel panelHora = new JPanel();
			panelHora.setBackground(new Color(169,169,169));

		JLabel tituloHora = new JLabel("Hora:");
		btnConsHora = new JRadioButton[10];
		ButtonGroup btnHoraGroup = new ButtonGroup();

		String[] nomeBtn = {"08:00 h", "08:30 h", "09:00 h", "09:30 h", "10:00 h", "10:30 h",
							"11:00 h", "11:30 h", "12:00 h", "12:30 h"};
		
		boolean[][] agenda; //Vai receber a agenda do Medico
		
		agenda = consController.getAgendaMed(diaConsulta.get(1));
	
		//Cria os botoes do radiobutton e seta os textos das horas equivalentes
		for (int i= 0; i<10; i++)
		{
			btnConsHora[i] = new JRadioButton();
			btnConsHora[i].setText(nomeBtn[i]);
			btnHoraGroup.add(btnConsHora[i]);
			panelHora.add(btnConsHora[i]);
			btnConsHora[i].setFont(new Font("serif", 0, 20));
			
			btnConsHora[i].addItemListener(consController.selectHora);
			
			//Desabilita os dias que estao lotados 
			if (agenda[diaConsulta.get(0)][i+1] == false) 
				btnConsHora[i].setEnabled(false);
			
		}
		
		
		panelHora.setLayout(new GridLayout(10,1));
		tituloHora.setFont(title2);
		
		//Organizando Componentes
		consultasHora.setBounds(558, 0, 558, 660);
		tituloHora.setBounds(811, 50, 60, 40);
		panelHora.setBounds(797, 150, 100, 300);
		
		
		//Adicionando componentes
		consultasHora.add(tituloHora);
		consultasHora.add(panelHora);
		
		//Mostrar o painel das Horas
		consultasCalend.add(consultasHora, "4");
		c1.show(consultasCalend, "4");
		c.repaint();
	}
		
	@SuppressWarnings("deprecation")
	public void montarCDia()
	{
		consultasCal = new JPanel(null);
		consultasCal.reshape(550, 0, 558, 660);
		consultasCal.setBackground(new Color(169,169,169));

		
	
		//montar o calendario do Medico
		montarCalendDias(6);
				
		//consultasCal.add(titleCCalend);		
		consultasCalend.add(consultasCal, "3");

		c1.show(consultasCalend, "3");
		c.repaint();
			
	}
		
	//Metodo para montar o calendario com base na agenda do Medico escolhido
	public void montarCalendDias(int numDoMes)
	{
		numMes = numDoMes;
		int diasMes;
		int contDias, contTemp = 1;
		String[] nomeMeses = {"","Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho", "Julho",
							"Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};

		int[] numMeses = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		
		JLabel diasDaSemana = new JLabel("Segunda      Terça       Quarta       Quinta       Sexta        Sábado     Domingo");
		diasDaSemana.setFont(new Font("serif", Font.BOLD, 13)); 
		diasDaSemana.setBounds(29, 38, 400, 25);
		
		
		//Criando titulo dia
		JLabel titleCCalend = new JLabel("Dia:");
		titleCCalend.setFont(new Font("serif", Font.BOLD, 22));
		titleCCalend.setBounds(817, 60, 40, 40);

		//Criando e setando o painel de titulos do calendario
		cCalTitulos = new JPanel(null);
		cCalTitulos.setBackground(Color.WHITE);
		cCalTitulos.setBounds(612, 100, 450, 500);
		
		//Criando e setando a area onde ficarao os botoes do calendario
		btnCalend = new JPanel();
		btnCalend.setLayout(new GridLayout(6,7));
		btnCalend.setBounds(637, 160, 400, 400);
		
		//Criando titulos do calendario
		String ano = String.valueOf(anoCalend);
		JLabel tituloMesAno = new JLabel(nomeMeses[numDoMes] + " de " + ano);
		tituloMesAno.setFont(new Font("serif", Font.BOLD, 20));
		tituloMesAno.setBounds(150, 0, 200, 25);
		

		diasMes = numMeses[numDoMes];
				
		agenda = consController.getAgendaMed(numDoMes);
		
		
		//Criando botoes e agrupando no local certo	
		JButton[] vectorBtnCalend = new JButton[42]; 
		contDias = 1;
		int diasRestantes = diasRest.get(contadorMeses);
		
		
		//Insere os 42 botoes do calendario
		for(int i = 0; i <= 41; i++)
		{
			//Se ja tiver passado os diasRestantes e tiver dentro da quantidade de dias que o mes tem ele cria o botao e seta o text equivalente ao dia
			if ((i >= diasRestantes) && (contDias <= diasMes))
			{
				String nomeBtn = String.valueOf(contDias);
				vectorBtnCalend[i] = new JButton(nomeBtn);
				vectorBtnCalend[i].addActionListener(consController.setDaybtn);

				//Se o dia do medico estiver lotado o botao daquele dia eh desabilitado
				if (agenda[contDias][0] == false)
					vectorBtnCalend[i].setEnabled(false);

				btnCalend.add(vectorBtnCalend[i]);
				contDias++;
			}
			//Se o botao nao fizer parte dos dias do mes o botao eh criado, mas fica desabilitado e com texto " - "
			else
			{
				vectorBtnCalend[i] = new JButton("-");
				btnCalend.add(vectorBtnCalend[i]);
				vectorBtnCalend[i].setEnabled(false);
			}
			
			//Desabilitando botões do domingo
			if ((i == 6) || (i == 13) || (i == 20) || (i == 27) || (i == 34) || (i == 41))
			{
				vectorBtnCalend[i].setEnabled(false);
			}
			
			//Contador para ajudar no calculo do diasRest
			if (contDias <= diasMes)
				contTemp++;			
		}
		
		
		//Calculando o diasRest
		if ((contTemp >= 29) && (contTemp <= 35))
		{
			contTemp = contTemp - 28;
		}
		else if((contTemp >= 36) && (contTemp <= 42))
		{
			contTemp = contTemp - 35;
		}	
			
		
		//Avaca o mes ate chegar no mes atual, uma vez que chegue no mes atual o validar recebe true
		if ((numDoMes <= diaAtual.get(1)+1) && (validar == false))
			contadorMeses = 0;
		else
			validar = true;
			
		
		//Seta o dia restante do mes seguinte	
		diasRest.add((contadorMeses+1) , contTemp);

				
		//Botoes para avançar e voltar mes
		JButton avancarMes = new JButton();
		JButton voltarMes = new JButton();
		
		
		//Indice do mes seguinte
		proxMes = numDoMes;
		proxMes++;
		if (proxMes == 13)
		{
			proxMes = 1;
		}
		
		
		//Indice do mes anterior
		if (numDoMes == 1)
			antMes = 12;
		else
			antMes = numDoMes-1;
		
		//Configurando botao de avancar Mes
		avancarMes.setText(nomeMeses[proxMes]);
		avancarMes.setBounds(300, 475, 150, 25);
		avancarMes.addActionListener(consController.avancarMes);
		
		
		//Configurando botao de voltar Mes
		voltarMes.setText(nomeMeses[antMes]);
		voltarMes.setBounds(0, 475, 150, 25);
		voltarMes.addActionListener(consController.voltarMes);
		
		
		//Bloqueando calendario para marcar consulta apenas ate 1 ano depois do mes atual
		if (contadorMeses == 11)
		{
			avancarMes.setEnabled(false);
 			JOptionPane.showMessageDialog(null, "Não é possivel avançar além deste mes , pois nós "
 					+ "so marcamos\n consultas com atecedencia de no maximo 1 ano.");
		}
			
		if (contadorMeses == 0)
		{
			voltarMes.setEnabled(false);
		}
		
		
		//Adicionando e atualizando estruturas
		cCalTitulos.add(diasDaSemana);
		cCalTitulos.add(avancarMes);
		cCalTitulos.add(voltarMes);
		cCalTitulos.add(tituloMesAno);
		
		btnCalend.repaint();
		cCalTitulos.repaint();
				
		consultasCal.add(btnCalend);
		consultasCal.add(cCalTitulos);

		btnCalend.validate();
		cCalTitulos.validate();
		
		consultasCal.add(titleCCalend);		

		consultasCal.repaint();
		c.repaint();
		

		//Avanca o mes ate chegar no mes atual
		if ((numDoMes != (diaAtual.get(1)+1)) && (validate == false))
		{
			avancarMes.doClick();
		}
		else
			validate = true;

		
	}

	//Montar painel de escolher especialidade
	public void montarCEspec()
	{
		
		JLabel titleCEspec = new JLabel("Especialidade:");		
		avancarEspec = new JButton("Avançar");

		//Pesquisa a especialidade dos medicos cadastrados
		listarEspecialidades();
		
		//Configurando listaEspec
		listaEspec.setModel(listaGeralEspec);
		
		listaEspec.setVisibleRowCount(10);
		listaEspec.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		add(new JScrollPane(listaEspec));
		
		//Ações do listaEspec
		listaEspec.addListSelectionListener(consController.listaSelect);

		
		/******Setando Fontes de consultasCalend******/
		titleCEspec.setFont(title2);
		
		
		/******Setando Eventos consultasEspec******/
		avancarEspec.addActionListener(consController);
		
		
		/******Organizando Componentes do consultasEspec******/
		titleCEspec.setBounds(767, 60, 140, 40);
		listaEspec.setBounds(737, 130, 200, 350);
		avancarEspec.setBounds(762, 500, 150, 25);

		consultasEspec.add(titleCEspec);
		consultasEspec.add(avancarEspec);
		consultasEspec.add(listaEspec);
		
		consultasCalend.add(consultasEspec, "1");
		c1.show(consultasCalend, "1");
		consultasEspec.repaint();
		c.repaint();

	}
		
	
	//Montar JList dos Medicos
	public void montarListaMedicos()
	{
		//Chama metodo que lista os medicos baseado na especialidade escolhida
		consController.listarMedicos(especialidade.getText());
		//Lista de Medicos
				
				
		//Configurando listaEspec
		listaMedicos.setModel(listaGeralMed);				
			
		listaMedicos.setVisibleRowCount(10);
		listaMedicos.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		add(new JScrollPane(listaMedicos));
				
		
		//Ações do listaEspec
		listaMedicos.addListSelectionListener(new ListSelectionListener() {
			public void valueChanged(ListSelectionEvent e) {
				medico.setText(listaGeralMed.get(listaMedicos.getSelectedIndex()));
				medico.setEnabled(true);
			}
		});
		
		
		listaMedicos.setBounds(737, 130, 200, 350);
		consultasMedico.add(listaMedicos);
		
	}
		
	
	//Pesquisa todas as especialidades disponiveis e tira elementos repetidos
	public void listarEspecialidades()
	{
		DefaultListModel<String> especList = new DefaultListModel<String>();
		String espec;
		int i;
		boolean contem = false;
		ArrayList<String> especsDes;
		
		
		//Recebe todas as especialidades disponiveis
		especsDes = consController.getEspec();
			
		
		//Verifica se tem elementos repetidos
		for (int j = 0; j < especsDes.size()  ; j++) {
			espec = especsDes.get(j);
		
			contem = false;
			i = 0;
			while ((i < (especList.size())) && (contem == false))
			{
				if  (espec.equals(especList.get(i)))
				{
					contem = true;
				}
				i++;
			}
			if (contem == false)
				especList.addElement(espec);
		
		}

		try{
		
		listaGeralEspec =  especList;
		}catch(Exception e){
			e.printStackTrace();
		}

	}
	
}

