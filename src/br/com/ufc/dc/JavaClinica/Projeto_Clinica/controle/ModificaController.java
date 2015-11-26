package controle;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileFilter;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;

import javax.swing.JOptionPane;

import concretos.Atendente;
import concretos.Medico;
import concretos.Paciente;
import concretos.Pessoa;
import consulta.ConsultaController;

public class ModificaController {

	private ModificaView mv;
	private ActionListener actionListener;
	
	
	private String caminho;
	private String loginAnterior;
	
	public ModificaController(ModificaView _mv, String _caminho) {
		this.mv = _mv;
		this.caminho = _caminho;
	}

	public void control() {
		
		
		actionListener = new ActionListener() {
			
			public void actionPerformed(ActionEvent e) {
				if (e.getSource() == mv.getShow()) {
					setInfo(caminho);
				} else if (e.getSource() == mv.getSave()) {
					
					
					if(!Cadastra(getId(caminho))){ // se cadastra retorna false, então o login foi alterado
						
						//removo das possiveis pastas
						
						RemoverMedico(procurarAdiministrador(loginAnterior));
						RemoverPaciente(procurarAdiministrador(loginAnterior));
						RemoverAtendente(procurarAdiministrador(loginAnterior));
						JOptionPane.showMessageDialog(null, "Login Anterior Excuido");
					}
					
				}
				
			}
		};
		mv.getShow().addActionListener(actionListener);
		mv.getSave().addActionListener(actionListener);
		
		
	}
	
	// PRECISEI COPIAR AQUI
	FileFilter filefilter = new FileFilter() {
	    public boolean accept(File file) {
	        if (file.getName().endsWith(".ser")) {
	            return true;
            }
            return false;
	    }
	};
	
	private int getId(String caminho){
		
		Pessoa g = null;
		try {
			FileInputStream fileIn = new FileInputStream(caminho);
			ObjectInputStream in = new ObjectInputStream(fileIn);
			g = (Pessoa) in.readObject();
			in.close();
			fileIn.close();
		} catch (IOException i) {
			i.printStackTrace();
		} catch (ClassNotFoundException c) {
			c.printStackTrace();
		}

		return g.getId();
		
	}
	

	private void setInfo(String caminho) {

		Pessoa g = null;
		try {
			FileInputStream fileIn = new FileInputStream(caminho);
			ObjectInputStream in = new ObjectInputStream(fileIn);
			g = (Pessoa) in.readObject();
			in.close();
			fileIn.close();
		} catch (IOException i) {
			i.printStackTrace();
		} catch (ClassNotFoundException c) {
			c.printStackTrace();
		}

		loginAnterior = g.getNome();
		
		mv.setNomeText(g.getNome());
		mv.setIdadeText(g.getIdade());
		mv.setFoneText(g.getFone());
		mv.setAdressText(g.getAdress());
		mv.setSenhaText(g.getSenha());

		// ESCREVENTO NO CAMPO TIPO
		switch (g.getId()) {
		case 1:
			mv.setTipoText("Paciente");
			break;
		case 2:
			mv.setTipoText("Atendente");
			break;
		case 3:
			mv.setTipoText("Administrador");
			break;
		case 4:
			mv.setTipoText("Medico");
			break;
		}

		if (g.getClass() == Medico.class) {

			// Srializa novamente

			Medico m = null;
			try {
				FileInputStream fileIn = new FileInputStream(caminho);
				ObjectInputStream in = new ObjectInputStream(fileIn);
				m = (Medico) in.readObject();
				in.close();
				fileIn.close();
			} catch (IOException i) {
				i.printStackTrace();
			} catch (ClassNotFoundException c) {
				c.printStackTrace();
			}
			mv.setAreaText(m.getEspecialidade());

		}
	}

	// SALVANDO
	public boolean Cadastra(int id){
		
		//System.out.println("login anterior: "+loginAnterior);
		
		switch(id){
			
		case 4:
			Medico medico = new Medico(Integer.valueOf(mv.getIdadeText()), mv.getNomeText());
			medico.setFone(mv.getFoneText());
			medico.setAdress(mv.getAdressText()); 
			medico.setSenha(mv.getSenhaText());
			medico.setEspecialidade(mv.getTipoText());
			//System.out.println(mv.getTipoText());
			SerializandoMedico(medico);
			mv.dispose();
			JOptionPane.showMessageDialog(null, "Modificação feita com Sucesso!");
		
			if(!mv.getNomeText().equals(loginAnterior))
				return false;
			//return true;
			break;
		case 2:
			Atendente atendente = new Atendente(Integer.valueOf(mv.getIdadeText()), mv.getNomeText());
			atendente.setFone(mv.getFoneText());
			atendente.setAdress(mv.getAdressText()); 
			atendente.setSenha(mv.getSenhaText());

			SerializandoAtendente(atendente);
			mv.dispose();
			JOptionPane.showMessageDialog(null, "Modificação feita com Sucesso!");
		
			if(!mv.getNomeText().equals(loginAnterior))
				return false;
			break;
		case 1:
			Paciente paciente = new Paciente(Integer.valueOf(mv.getIdadeText()), mv.getNomeText());
			paciente.setFone(mv.getFoneText());
			paciente.setAdress(mv.getAdressText()); 
			paciente.setSenha(mv.getSenhaText());

			SerializandoPaciente(paciente);
			mv.dispose();
			JOptionPane.showMessageDialog(null, "Modificação feita com Sucesso!");
			if(!mv.getNomeText().equals(loginAnterior))
				return false;
			break;
		}
		return true;
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
	
	public void RemoverMedico(String file){
		
		File arq = new File(file);
		arq.delete();
	
	}
	public void RemoverPaciente(String file){
		File arq = new File(file);
		arq.delete();
	
	}
	public void RemoverAtendente(String file){
		
		File arq = new File(file);
		arq.delete();
	
	}
	
	public String procurarAdiministrador(String nome)
    {
    	@SuppressWarnings("unused")
		ArrayList<String> medicos = new ArrayList<String>();
    	int op = 0;
   
    	int i = 1;
    	boolean achar = false;
    	
    	File arq = null;
    	
    	while ((i <= 3) && (achar == false)){
    	if (i == 1){
    		arq = new File("src/concretos/Medicos"); 
    		op = 0;
    	}else if (i == 2){
    		arq = new File("src/concretos/Pacientes");
    		op = 1;
    	}else if (i == 3){ // PEQUNA DIFERENÇA.........
    		arq = new File("src/concretos/Atendentes");
    		op = 2;
    	}
    	
		File[] arquivos;
		arquivos = arq.listFiles(filefilter);
		for (int j = 0; j < arquivos.length; j++){  // PERCORRO OS OBJETOS LÁ DENTRO	
			String path = arquivos[j].getAbsolutePath();
			Pessoa p = (Pessoa) ConsultaController.extrairPessoa(path, op);
				
			if (nome.equals(p.getNome()))
			{
				achar = true;

				return path;
			}
		}
		i++;
    	}
		return "";	
    }

	
	

}
