package controle;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class IncluirAtendenteController {

	private IncluirAtendente at;
	private ActionListener actionListener;
	private CadastroControllerMedico cc;
	private CadastroControllerPaciente cp;
	private CadastroPaciente p;
	private CadastroMedico m;
	
	public IncluirAtendenteController(IncluirAtendente e){
		this.at = e;
	}
	
	
	public void control() {

		actionListener = new ActionListener() {

			public void actionPerformed(ActionEvent e) {

				if(e.getSource()==at.getMedico()){	
					m = new CadastroMedico();
					cc = new CadastroControllerMedico(m);
					cc.control();
					at.dispose();
				}else if(e.getSource()==at.getPaciente()){
					
					p = new CadastroPaciente();
					cp = new CadastroControllerPaciente(p);
					cp.control();
					at.dispose();
				}
					
			}
		};

		at.getPaciente().addActionListener(actionListener);
		at.getMedico().addActionListener(actionListener);
		
		
	}
	

}
