/**
 *
 * Nesta classe o servidor deve usa-la afim de buscar o arquivo
 * solicitado, aqui serão um tipo de classe
 * aonde os arquivos deven ser armazenados.
 *
 */
public class Datanode {

	//private static Collection<Namenode> namenodes = new HashSet<Namenode>();
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

	// public void startNamenodes(){
	// 	String[] array = {"backup.txt","test.txt","movies.txt","shopping.txt","list.txt","sites.txt","run.txt","contacts.txt","grades.txt"};
	// 	Properties prop = new Properties();
	// 	OutputStream output = null;
	// 	short i;
	// 	for(i=0;i<array.length;i++){
	// 		// criar os nomenodes
	// 		namenodes.add(new Namenode(array[i])); 
	// 	}
	// 	File fileProperties = new File("files.properties");
	// }

	// public static void main(String[] args){

	// }

}