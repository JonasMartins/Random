package controle;

import java.awt.Font;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class InfoView extends JFrame{

	/**
	 * 
	 */
	private static final long serialVersionUID = -417920950789161968L;
	
	private JLabel nome;
	private JLabel fone;
	private JLabel senha;
	private JLabel area;
	private JLabel idade;
	private JLabel areaText;
	private JLabel idadeText;
	private JLabel senhaText;
	private JLabel nomeText;
	private JLabel foneText;
	private JPanel contentPane;
	private Font fontePadrao;
	private JLabel titulo;
	private JButton show;
	private JLabel adress;
	private JLabel tipo;
	private JLabel tipoText;
	private JLabel adressText;
	
	
	
	public InfoView(){
		
		
		setTitle("Dados");
		setVisible(true);
		setBounds(100,100,420, 530);
		//setResizable(false)
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		contentPane = new JPanel();
		setContentPane(contentPane);
		contentPane.setLayout(null);
		fontePadrao = new Font("Serif", Font.PLAIN, 25);
		
		
		titulo = new JLabel("INFORMAÇÃO CADASTRO");
		titulo.setBounds(40, 15, 360, 20);
		titulo.setFont(fontePadrao);
		contentPane.add(titulo);
		
		nome = new JLabel("Nome: ");
		nome.setFont(fontePadrao);
		nome.setBounds(10, 50, 200, 40);
		contentPane.add(nome);
		
		idade = new JLabel("Idade: ");
		idade.setFont(fontePadrao);
		idade.setBounds(10, 100, 200, 40);
		contentPane.add(idade);
		
		fone = new JLabel("Fone: ");
		fone.setFont(fontePadrao);
		fone.setBounds(10, 150, 200, 40);
		contentPane.add(fone);
	
		senha = new JLabel("Senha: ");
		senha.setFont(fontePadrao);
		senha.setBounds(10, 200, 200, 40);
		contentPane.add(senha);
		
		area = new JLabel("Área: ");
		area.setFont(fontePadrao);
		area.setBounds(10, 255, 200, 40);//205
		contentPane.add(area);
		
		adress = new JLabel("Endereço: ");
		adress.setFont(fontePadrao);
		adress.setBounds(10, 300, 200, 40);//250
		contentPane.add(adress);
		
		tipo = new JLabel("Tipo: ");
		tipo.setFont(fontePadrao);
		tipo.setBounds(10, 350, 200, 40);//250
		contentPane.add(tipo);
		

		nomeText = new JLabel("?");
		nomeText.setFont(fontePadrao);
		nomeText.setBounds(110, 50, 200, 40);
		contentPane.add(nomeText);
		
		idadeText = new JLabel("?");
		idadeText.setFont(fontePadrao);
		idadeText.setBounds(110, 100, 200, 40);
		contentPane.add(idadeText);
		
		foneText = new JLabel("?");
		foneText.setBounds(110,155,190,30);
		foneText.setFont(fontePadrao);
		contentPane.add(foneText);
		
		
		senhaText = new JLabel("?");
		senhaText.setBounds(110,205,190,30);
		senhaText.setFont(fontePadrao);
		contentPane.add(senhaText);
		
		areaText = new JLabel("?");
		areaText.setFont(fontePadrao);
		areaText.setBounds(110, 255, 200, 30);//205
		contentPane.add(areaText);
		
		adressText = new JLabel("?");
		adressText.setFont(fontePadrao);
		adressText.setBounds(160, 300, 200, 40);//250
		contentPane.add(adressText);
		
		tipoText = new JLabel("?");
		tipoText.setFont(fontePadrao);
		tipoText.setBounds(110, 350, 200, 40);//250
		contentPane.add(tipoText);
		
		show = new JButton("Mostrar Info");
		show.setBounds(10,420,370,60);
		show.setFont(fontePadrao);
		contentPane.add(show);
		
	}

	public JButton getShow() {
		return show;
	}
	public void setAreaText(String areaText) {
		this.areaText.setText(areaText);
	}
	public void setIdadeText(int idadeText) {
		this.idadeText.setText(String.valueOf(idadeText));
	}
	public void setSenhaText(String senhaText) {
		this.senhaText.setText(senhaText);
	}
	public void setNomeText(String nomeText) {
		this.nomeText.setText(nomeText);
	}
	public void setFoneText(String foneText) {
		this.foneText.setText(foneText);
	}
	public void setAdressText(String adressText) {
		this.adressText.setText(adressText);
	}
	public void setTipoText(String tipoText) {
		this.tipoText.setText(tipoText);
	}
	public static void main (String[] args){
		new InfoView();
	}
	

}
