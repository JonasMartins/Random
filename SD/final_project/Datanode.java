/**
 *
 * Nesta classe o servidor deve usa-la afim de buscar o arquivo
 * solicitado, aqui serão um tipo de classe
 * aonde os arquivos deven ser armazenados.
 *
 */

public class Datanode {

	private String url;
	private int id; // 0 - 2

	public Datanode(String url, int id){
		this.url = url;
		this.id = id;
	}
	
	public String getUrl(){
		return "datanodes/data_" + this.url +"/";
	}
	public int getId(){
		return this.id;
	}
	@Override
	public String toString(){
		return "=> "+this.getUrl();
	}
}