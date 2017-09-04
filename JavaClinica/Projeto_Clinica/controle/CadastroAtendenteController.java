package controle;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;

import javax.swing.JOptionPane;

import concretos.Atendente;

public class CadastroAtendenteController {

	private CadastroAtendente ca;
	private ActionListener actionListener;

	public CadastroAtendenteController(CadastroAtendente e) {
		this.ca = e;
	}

	public void control() {
		actionListener = new ActionListener() {

			public void actionPerformed(ActionEvent e) {

				if(!RestricoesCadastro(ca.getIdadeText(), ca.getNomeText())){
					ca.dispose();
				}else{
					Cadastra();
					// SÓ AQUI CADASTRAMOS
				}
			}
		};
		ca.getOk().addActionListener(actionListener);

	}
	public boolean RestricoesCadastro(int idade, String nome){
		
		if(idade==-1 && nome.length()<4){
			JOptionPane.showMessageDialog(null,"Campos Idade e Nome Incorretos\n\tTente Novamente");
			return false;
		}else if(idade==-1){
			JOptionPane.showMessageDialog(null, "Idade Informada não confere, digite Números!\n\tTente Novamente");
			return false;
		}else if(nome.length()<4){
			JOptionPane.showMessageDialog(null, "Nome Informado deve ter no mínimo 4 caracteres!\n\tTente Novamente");
			return false;
		}
		return true;
	}
	public void Cadastra(){
		Atendente atendente = new Atendente(ca.getIdadeText(), ca.getNomeText());
		atendente.setFone(ca.getFoneText());
		atendente.setAdress(ca.getAdressText()); 
		atendente.setSenha(ca.getSenhaText());

		SerializandoAtendente(atendente);
		JOptionPane.showMessageDialog(null, "Atendente Cadastrado com Sucesso!");
		ca.dispose();

	}
	
	public static void SerializandoAtendente(Atendente p) {
		try {

			FileOutputStream fileOut = new FileOutputStream(
					"src/concretos/Atendentes/" + p.getNome() + ".ser");
			ObjectOutputStream out = new ObjectOutputStream(fileOut);
			out.writeObject(p);
			out.close();
			fileOut.close();
		} catch (IOException i) {
			i.printStackTrace();
		}

	}
}
