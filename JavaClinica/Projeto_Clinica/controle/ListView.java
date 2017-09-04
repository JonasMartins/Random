package controle;


import java.awt.BorderLayout;
import java.awt.Font;
import java.awt.GridLayout;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.UIManager;
import javax.swing.plaf.FontUIResource;

public class ListView extends JFrame{

	/**
	 * 
	 */
	private static final long serialVersionUID = 7452581594807824645L;
	private JPanel contentPane;
	private JTabbedPane abas;
	private static Font fontePadrao;

	/*
	String[] pacientes = {"a","a","a","a","a","a"};
	String[] medicos = {"a","a","a","a","a","a","a","a"};
	String[] atendentes = {"a","a","a","a","a","a","a"};
	*/
	public ListView(String[] PacientesList,String[] Medicoslist, String[]AtendentesList){
		
		setSize(500, 600);
		setDefaultCloseOperation(DISPOSE_ON_CLOSE);
		setTitle("Lista");
		setVisible(true);
		
		

		// PADRÃO PARA JOPTIONPANE
		UIManager.put("OptionPane.messageFont",new FontUIResource(new Font("Serif", Font.PLAIN, 15)));
		UIManager.put("OptionPane.buttonFont", new FontUIResource(new Font("Serif", Font.PLAIN, 10)));
		//*****************************
				
		
		fontePadrao = new Font("Serif", Font.PLAIN, 25);
		
		
		
		contentPane = new JPanel();
		JScrollPane scrollPaneConteiner = new JScrollPane(contentPane);
		setContentPane(scrollPaneConteiner);
		contentPane.setLayout(new BorderLayout());
	
		abas = new JTabbedPane();
		
		JScrollPane scrollPane = new JScrollPane(abas);
		

		addIt(abas,"Medicos",Medicoslist);
		addIt(abas,"Pacientes",PacientesList);
		addIt(abas,"Atendentes",AtendentesList);
	
		JLabel titulo = new JLabel("LOGINS: ");
		titulo.setFont(new Font ("Serif",Font.BOLD,30 ) );
		
		
		contentPane.add(titulo,BorderLayout.NORTH);
		contentPane.add(scrollPane,BorderLayout.CENTER);
		
		
	}

	static void addIt(JTabbedPane tabbedPane, String text,String[] nomes) {
	  
		int i;
		
		JLabel label = new JLabel("Logins:");
	    label.setFont(fontePadrao);
	   
	    
	    JPanel panel = new JPanel();
	    panel.setFont(fontePadrao);
	 
	   
	    
	    
	    
	    // panel é onde ficaram os nomes 
	    panel.setLayout(new GridLayout(nomes.length,1));
	   
	    
	    for(i = 0;i<nomes.length;i++){
	   
	
	    	
	    	JLabel nomesLabel = new JLabel(nomes[i]);
	    	nomesLabel.setFont(fontePadrao);
	    	
	    	panel.add(nomesLabel);
	    	
	    }
	  
	    
	    JLabel texto = new JLabel(text);
	    texto.setFont(fontePadrao);
	    
	    tabbedPane.addTab(text, panel);
	    tabbedPane.setTabComponentAt(tabbedPane.getTabCount() - 1, texto);

	}
	

	
	
}
