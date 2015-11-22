package controle;


import java.awt.Font;
import java.awt.GridLayout;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class IncluirAtendente extends JFrame{

	/**
	 * 
	 */
	private static final long serialVersionUID = -3645583524938869975L;

	JComboBox<String> add;
	private JPanel contentPane;
	private Font fontePadrao;
	private JButton medico;
	private JButton paciente;
	
	public IncluirAtendente(){
		
		
		setTitle("");
		//setSize(300, 100);
		setBounds(100, 100, 300, 100);
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		setVisible(true);
		//setResizable(false);
		
		contentPane = new JPanel();
		contentPane.setLayout(new GridLayout(1,2));
		setContentPane(contentPane);
		fontePadrao = new Font("Serif",Font.BOLD, 15);
		
		medico = new JButton("Medico");
		medico.setFont(fontePadrao);
		paciente = new JButton("Paciente");
		paciente.setFont(fontePadrao);
		
		contentPane.add(medico);
		contentPane.add(paciente);	
	}

	public JButton getMedico() {
		return medico;
	}

	public JButton getPaciente() {
		return paciente;
	}
		
}
