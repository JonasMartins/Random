/**
 *
 * Namenode uma classe onde manterá uma espécie de estrutura de 
 * mapeamento entre nome de arquivos e datanodes
 *
 */
public class Namenode {

	//private Datanode datanode;
	private String file;
	public Namenode(String arq){
		//this.datanode = datanode;
		this.file = arq;
	}
	public String getFileName(){
		return this.file;
	}
	/* Aqui o arquivo a ser buscado vai ser agrupado de 
	acordo com o comprimento do seu nome em um dos 3 datanodes iniciais */
	@Override 
	public int hashCode(){
		return this.file.length() % 3;
	}

	@Override
	public boolean equals(Object obj){
		Namenode nomenode = (Namenode) obj;
		return this.file.equals(nomenode.getFileName());
	}

	@Override
	public String toString(){
		return this.getFileName();
	}
}