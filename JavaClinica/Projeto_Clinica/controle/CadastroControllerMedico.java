package controle;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;

import javax.swing.JOptionPane;

import concretos.Medico;


public class CadastroControllerMedico {

	private CadastroMedico m;
	private ActionListener actionListener;

	
	public CadastroControllerMedico(CadastroMedico k) {
		this.m = k;
	}
	
	public void control() {
		actionListener = new ActionListener() {

			public void actionPerformed(ActionEvent e) {
					
					// ADICIONANDO MAIS UM MEDICO
				
				if(!RestricoesCadastro(m.getIdadeText(), m.getNomeText())){
					m.dispose();
				}else{
					Cadastra();
					// SÓ AQUI CADASTRAMOS
				}
					
			}
		};
		m.getOk().addActionListener(actionListener);

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
		Medico medico = new Medico(m.getIdadeText(), m.getNomeText());
		medico.setFone(m.getFoneText());
		medico.setAdress(m.getAdressText()); 
		medico.setSenha(m.getSenhaText());
		medico.setEspecialidade(m.getAreaSelected());
		SerializandoMedico(medico);
		JOptionPane.showMessageDialog(null, "Médico Cadastrado com Sucesso!");
		m.dispose();

	}
	

	public static void SerializandoMedico(Medico p) { // IMPORTANTE,
															// CRIANDO.....
		try {

			FileOutputStream fileOut = new FileOutputStream(
					"src/concretos/Medicos/" + p.getNome() + ".ser");
			ObjectOutputStream out = new ObjectOutputStream(fileOut);
			out.writeObject(p);
			out.close();
			fileOut.close();
		} catch (IOException i) {
			i.printStackTrace();
		}

	}
}
