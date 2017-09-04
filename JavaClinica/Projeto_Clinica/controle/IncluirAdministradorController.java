package controle;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class IncluirAdministradorController {

	
	private IncluirAdministrador ad;
	private ActionListener actionListener;
	private CadastroControllerMedico cc;
	private CadastroControllerPaciente cp;
	private CadastroPaciente p;
	private CadastroMedico m;
	private CadastroAtendente ca;
	private CadastroAtendenteController cac;
	
	
	public IncluirAdministradorController(IncluirAdministrador e){
		this.ad = e;
	}
	
	public void control() {
		actionListener = new ActionListener() {

			public void actionPerformed(ActionEvent e) {
	
				if(e.getSource()==ad.getMedico()){	
					m = new CadastroMedico();
					cc = new CadastroControllerMedico(m);
					cc.control();
					ad.dispose();
				}else if(e.getSource()==ad.getPaciente()){
					p = new CadastroPaciente();
					cp = new CadastroControllerPaciente(p);
					cp.control();
					ad.dispose();

				}else if(e.getSource()==ad.getAtendente()){
					ca = new CadastroAtendente();
					cac= new CadastroAtendenteController(ca);
					cac.control();
					ad.dispose();
				}
				
				
			}

		};
		ad.getPaciente().addActionListener(actionListener);
		ad.getMedico().addActionListener(actionListener);
		ad.getAtendente().addActionListener(actionListener);
	}
	
}
