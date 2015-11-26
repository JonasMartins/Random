package login;


import java.awt.Color;
import java.awt.Font;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JTextField;
import javax.swing.UIManager;
import javax.swing.border.LineBorder;
import javax.swing.plaf.FontUIResource;



public class PaginaInicial extends JFrame{

	
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 8741626395580374111L;
	
	private JButton botaEntrar;
	private JPanel contentPane;
	private JTextField loginTexto;
	private JPasswordField password;
	private Font fontePadraoLogin;
	

	public PaginaInicial() {
		
		// PADRÃO PARA JOPTIONPANE
				UIManager.put("OptionPane.messageFont",new FontUIResource(new Font("Serif", Font.PLAIN, 15)));
				UIManager.put("OptionPane.buttonFont", new FontUIResource(new Font("Serif", Font.BOLD, 10)));
				//*****************************
				
		fontePadraoLogin = new Font("Serif", Font.PLAIN, 15);	
				
				
		
		setTitle("ClinicaSystem");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		//setBounds(0, 0, 1366, 760); // guardar estas configurações
		setBounds(0, 0, 1366, 760);
		contentPane = new JPanel();
		contentPane.setBorder(new LineBorder(new Color(0, 0, 0), 10));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		contentPane.setBackground(new Color(169,169,169));
		
		setVisible(true);
		
		JLabel login = new JLabel("Login:");
		login.setFont(fontePadraoLogin);
		login.setForeground(Color.BLACK);
		login.setBounds(513, 420, 70, 25);
		contentPane.add(login);
		
		loginTexto = new JTextField();
		
		loginTexto.setBounds(593, 420, 114, 25);
		loginTexto.setBorder(new LineBorder(Color.BLACK));
		loginTexto.setFont(fontePadraoLogin);
		contentPane.add(loginTexto);
		loginTexto.setColumns(10);

		JLabel Senha = new JLabel("Senha: ");
		Senha.setFont(fontePadraoLogin);
		Senha.setForeground(Color.BLACK);
		Senha.setBounds(513, 455, 70, 25);
		contentPane.add(Senha);

		password = new JPasswordField();
		password.setFont(fontePadraoLogin);
		password.setBounds(593, 455, 114, 25);
		password.setBorder(new LineBorder(Color.BLACK));
		contentPane.add(password);

		botaEntrar = new JButton("Entrar");
		botaEntrar.setToolTipText("Logar");
		botaEntrar.setBorder(new LineBorder(Color.BLACK));
		botaEntrar.setFont(fontePadraoLogin);
		botaEntrar.setBounds(591, 485, 117, 40); // padrão 30 de altura
	
		contentPane.add(botaEntrar);
		
		JLabel titulo1 = new JLabel("Sistema de Clínica");
		titulo1.setFont(new Font("Lucida Bright", Font.BOLD, 35));
		titulo1.setBounds(500, 150, 1000, 40);
		contentPane.add(titulo1);
		
		JLabel titulo2 = new JLabel("Trabalho Técnicas de Programação");
		titulo2.setFont(new Font("Lucida Bright", Font.BOLD, 35));
		titulo2.setBounds(400, 230, 1000, 40);
		contentPane.add(titulo2);
		
		
		

	}
	
	public JButton getBotaoEntrar(){
		return botaEntrar;
	}
	
	public JTextField getLoginTexto() {
		return loginTexto;
	}

	public JPasswordField _getPassword() {
		return password;
	}
	public void setLoginTexto(String texto){
		this.loginTexto.setText(texto); 
	}
}
