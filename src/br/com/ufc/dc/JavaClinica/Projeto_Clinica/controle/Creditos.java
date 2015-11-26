package controle;

import java.awt.BorderLayout;
import java.awt.Font;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class Creditos extends JFrame{
		
	/**
	 * 
	 */
	private static final long serialVersionUID = 4244881770191233802L;

	
	private JPanel contentPane;
	private Font fontePadrao;
	private JLabel titulo;
	private JLabel agradecimentos;
	private ImageIcon imagem;
	
	public Creditos(){
		
		
		setDefaultCloseOperation(DISPOSE_ON_CLOSE);
		setSize(500, 500);
		setTitle("Créditos");
		setVisible(true);
		//setResizable(false);
		contentPane = new JPanel();
		setContentPane(contentPane);
		contentPane.setLayout(new BorderLayout());
		fontePadrao = new Font("Serif", Font.BOLD, 25);
		
		
		titulo = new JLabel("CRÉDITOS");
		titulo.setBounds(150, 10, 360, 20);
		titulo.setFont(fontePadrao);
		contentPane.add(titulo);
		
		imagem = new ImageIcon(getClass().getResource("Imagens/dalborga.gif"));
		
		agradecimentos = new JLabel(imagem);
		contentPane.add(BorderLayout.CENTER,agradecimentos);
		
		
		
	}
	
	public static void main(String[] args){
		new Creditos();
	}
	
	

}
