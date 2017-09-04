package controle;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;

import javax.swing.JOptionPane;

import concretos.Paciente;

public class CadastroControllerPaciente {

	private CadastroPaciente p;
	private ActionListener actionListener;


	public CadastroControllerPaciente(CadastroPaciente k) {
		this.p = k;
	}
	
	public void control() {
		actionListener = new ActionListener() {

			public void actionPerformed(ActionEvent e) {// PERFEITO!
				
				if(!RestricoesCadastro(p.getIdadeText(), p.getNomeText())){
					p.dispose();
				}else{
					Cadastra();
					// SÓ AQUI CADASTRAMOS
				}
			}
		};
		p.getOk().addActionListener(actionListener);

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
		Paciente paciente = new Paciente(p.getIdadeText(), p.getNomeText());
		paciente.setFone(p.getFoneText());
		paciente.setAdress(p.getAdressText()); 
		paciente.setSenha(p.getSenhaText());

		SerializandoPaciente(paciente);
		JOptionPane.showMessageDialog(null, "Paciente Cadastrado com Sucesso!");
		p.dispose();

	}
	

	public static void SerializandoPaciente(Paciente p) { // IMPORTANTE,
															// CRIANDO.....
		try {

			FileOutputStream fileOut = new FileOutputStream(
					"src/concretos/Pacientes/" + p.getNome() + ".ser");
			ObjectOutputStream out = new ObjectOutputStream(fileOut);
			out.writeObject(p);
			out.close();
			fileOut.close();
		} catch (IOException i) {
			i.printStackTrace();
		}

	}

}
