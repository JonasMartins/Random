package controle;

import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Font;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.TableCellRenderer;


public class MedicoView extends JFrame{
	
	private static final long serialVersionUID = 8741626395580374111L;
	
	public MedicoView(String[][] dados,String nomeMedico){
		super("Paciente");
	
		String[] colunas = {"Nome do Paciente", "Idade", "Data", "Horas"};
		
		
		JLabel medico = new JLabel(nomeMedico);
		medico.setFont(new Font("serif", 0, 45));
		JPanel painelUsuario = new JPanel(null);
			painelUsuario.setBackground(new Color(169,169,169));

		JTable tabela = new JTable(dados, colunas){

			public Component prepareRenderer(TableCellRenderer r, int dados, int colunas){
				Component comp = super.prepareRenderer(r, dados, colunas);
			
				if (dados % 2 == 0)
					comp.setBackground(Color.WHITE);
			
				else
					comp.setBackground(Color.LIGHT_GRAY);
			
				return comp;
			}
	
		};
	
		tabela.setPreferredScrollableViewportSize(new Dimension(1000, 200));
		tabela.setFillsViewportHeight(true);
		tabela.getTableHeader().setReorderingAllowed(false);
		tabela.setBounds(100, 250, 500, 160);
		tabela.setEnabled(false);
		tabela.setRowHeight(75);
		tabela.setFont(new Font("serif", Font.ITALIC, 17));
		
		JScrollPane scrollbar = new JScrollPane(tabela);
		
		scrollbar.setBounds(50, 100, 1250, 500);
		painelUsuario.add(scrollbar);


		
		painelUsuario.reshape(0, 0, 1500, 1000);
		medico.setBounds(50, 30, 500, 50);
		medico.setForeground(Color.BLACK);

		
		painelUsuario.add(medico);
		
		painelUsuario.repaint();
		add(painelUsuario);
		repaint();
		
		setBounds(0, 0, 1500, 1000);
		setVisible(true);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
	}
	
}