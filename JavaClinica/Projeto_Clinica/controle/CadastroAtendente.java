package controle;

import java.awt.Font;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JTextField;

public class CadastroAtendente extends JFrame{

	/**
	 * 
	 */
	private static final long serialVersionUID = 2560382135811955757L;
	
	private JLabel nome;
	private JLabel fone;
	private JLabel senha;
	private JLabel idade;
	private JTextField idadeText;
	private JPasswordField senhaText;
	private JTextField nomeText;
	private JTextField foneText;
	private JPanel contentPane;
	private Font fontePadrao;
	private JLabel titulo;
	private JButton ok;
	private JLabel adress;
	private JTextField adressText;
	
	public CadastroAtendente(){
		
		setTitle("Adicionar Atendente");
		setVisible(true);
		setBounds(100,100,400, 405);
		//setResizable(false)
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		contentPane = new JPanel();
		setContentPane(contentPane);
		contentPane.setLayout(null);
		fontePadrao = new Font("Serif", Font.PLAIN, 25);
		
		
		nomeText = new JTextField();
		nomeText.setBounds(110,55,230,30);
		nomeText.setFont(fontePadrao);
		contentPane.add(nomeText);

		idade = new JLabel("Idade: ");
		idade.setFont(fontePadrao);
		idade.setBounds(10, 100, 200, 40);
		contentPane.add(idade);
		
		idadeText = new JTextField();
		idadeText.setFont(fontePadrao);
		idadeText.setBounds(110, 105, 60, 30);
		contentPane.add(idadeText);
		
		
		
		foneText = new JTextField();
		foneText.setBounds(110,155,190,30);
		foneText.setFont(fontePadrao);
		contentPane.add(foneText);
		
		
		senhaText = new JPasswordField();
		senhaText.setBounds(110,205,190,30);
		senhaText.setFont(fontePadrao);
		contentPane.add(senhaText);
		
		
		
		titulo = new JLabel("ADICIONAR ATENDENTE");
		titulo.setBounds(35, 15, 360, 20);
		titulo.setFont(fontePadrao);
		contentPane.add(titulo);
		
		nome = new JLabel("Nome: ");
		nome.setFont(fontePadrao);
		nome.setBounds(10, 50, 200, 40);
		contentPane.add(nome);
		
		fone = new JLabel("Fone: ");
		fone.setFont(fontePadrao);
		fone.setBounds(10, 150, 200, 40);
		contentPane.add(fone);
	
		senha = new JLabel("Senha: ");
		senha.setFont(fontePadrao);
		senha.setBounds(10, 200, 200, 40);
		contentPane.add(senha);
		
		
		adress = new JLabel("Endereço: ");
		adress.setFont(fontePadrao);
		adress.setBounds(10, 250, 200, 40);//250
		contentPane.add(adress);
		
		adressText = new JTextField();
		adressText.setFont(fontePadrao);
		adressText.setBounds(145, 255, 200, 30);//255
		contentPane.add(adressText);
		
		
		ok = new JButton("Cadastrar");
		ok.setBounds(10,315,370,60);
		ok.setFont(fontePadrao);
		contentPane.add(ok);		
	}
	public String getAdressText() {
		return adressText.getText();
	}

	public String getSenhaText() {
		String aux = new String(senhaText.getPassword());
		return aux;
	}

	public String getNomeText() {
		return nomeText.getText();
	}
	public void setNomeText(String nome){
		nomeText.setText(nome);
	}
	
	public int getIdadeText() {
		int aux=-1;
		try{
			aux = Integer.parseInt(idadeText.getText());
			return aux;
		}catch(NumberFormatException e){
		}
		return aux;
	}
	public void setIdadeText(String idade){
		idadeText.setText(idade);
	}
	
	public String getFoneText() {
		return foneText.getText();
	}

	public JButton getOk() {
		return ok;
	}
	/*
	public static void main(String[] args){
		new CadastroAtendente();
	}*/


}
