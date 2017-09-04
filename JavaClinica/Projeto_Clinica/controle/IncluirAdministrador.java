package controle;

import java.awt.Font;
import java.awt.GridLayout;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JPanel;


public class IncluirAdministrador extends JFrame {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1310628701369316347L;
	JComboBox<String> add;
	private JPanel contentPane;
	private Font fontePadrao;
	private JButton medico;
	private JButton paciente;
	private JButton atendente;

	public IncluirAdministrador() {

		setTitle("");
		// setSize(300, 100);
		setBounds(100, 100, 400, 100);
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		setVisible(true);
		// setResizable(false);

		contentPane = new JPanel();
		contentPane.setLayout(new GridLayout(1, 3));
		setContentPane(contentPane);
		fontePadrao = new Font("Serif", Font.BOLD, 15);

		medico = new JButton("Medico");
		medico.setFont(fontePadrao);
		paciente = new JButton("Paciente");
		paciente.setFont(fontePadrao);

		atendente = new JButton("Atendente");
		atendente.setFont(fontePadrao);

		contentPane.add(medico);
		contentPane.add(paciente);
		contentPane.add(atendente);
	}

	public JButton getMedico() {
		return medico;
	}

	public JButton getPaciente() {
		return paciente;
	}
	public JButton getAtendente() {
		return atendente;
	}
	
	/*
	public static void main(String[] args){
		new IncluirAdministrador();
	}*/
}
