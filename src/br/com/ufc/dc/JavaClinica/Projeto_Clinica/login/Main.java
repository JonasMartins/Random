package login;

import javax.swing.SwingUtilities;


public class Main
{
    public static void main(String[] args) {           

    	SwingUtilities.invokeLater(new Runnable() {
            public void run() {                                           

            	PaginaInicial p = new PaginaInicial();            	
            	
            	            	
            	PaginaInicialController controller = new PaginaInicialController(p);
                controller.control();
             
                	
            }
        });  
    }
}
	