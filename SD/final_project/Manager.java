import java.util.HashSet;
import java.util.HashMap;
import java.util.ArrayList;
import java.util.Collection;

import java.io.File;
import java.io.IOException;
import java.io.OutputStream;
import java.io.FileOutputStream;
import java.io.BufferedOutputStream;

import java.lang.SecurityException;

import static java.nio.file.StandardOpenOption.CREATE;
import static java.nio.file.StandardOpenOption.APPEND;

import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.Files;
import java.util.Properties;

/**
 *
 * Essa classe deve fazer o handler entre as estruturas de datanode e nomenode
 * para o servidor, ao invés do servidor fazer todo esse processamento, então
 * o servidor deve apenas usar um objeto dessa classe para recuperar os serviços
 * pedidos pelo cliente 
 *
 */
public class Manager {

	private static HashMap<Integer, Datanode> datanodes = new HashMap<Integer, Datanode>();
	private static Collection<Namenode> namenodes = new HashSet<Namenode>();

	/**
	 *
	 * Iniciando a aplicação com a criação dos diretórios
	 * e armazenando no arrayList local
	 */
	public static void startDatanodes(){
		// criando 3 diretórios datanodes iniciais
		File nodeOne = new File("datanodes/data_one");
		File nodeTwo = new File("datanodes/data_two");
		File nodeThree = new File("datanodes/data_three");
		if(!nodeOne.exists()){
			try {
				nodeOne.mkdirs();
			}catch(SecurityException se){ 
				System.err.println("Could not create directory");
			}
		}
		if(!nodeTwo.exists()){
			try {
				nodeTwo.mkdirs();
			}catch(SecurityException se){ 
				System.err.println("Could not create directory");
			}
		}
		if(!nodeThree.exists()){
			try {
				nodeThree.mkdirs();
			}catch(SecurityException se){ 
				System.err.println("Could not create directory");
			}
		}
		// Criando os objetos datanode
		Datanode one = new Datanode("one",0);
		Datanode two = new Datanode("two",1);
		Datanode three = new Datanode("three",2);
		datanodes.put(one.getId(),one);
		datanodes.put(two.getId(),two);
		datanodes.put(three.getId(),three);
	}
	/**
	 *
	 * Cria alguns namenodes e todos os arquivos do array abaixo e já relaciona 
	 * esses arquivos com os datanodes equivalentes, feito isso pela função hashcode de acordo
	 * com o comprimento do nome do arquivo.
	 */
	public static void startNamenodes(){
		String[] array = {"backup.txt","test.txt","movies.txt","shopping.txt","list.txt","sites.txt","run.txt","contacts.txt","grades.txt"};
			
		Properties prop = new Properties();
		OutputStream output = null;

		short i;
		for(i=0;i<array.length;i++){
			// criar os nomenodes
			namenodes.add(new Namenode(array[i])); 
		}
		// write files list and his path on files.properties.
		// if file already exists will do nothing
		File fileProperties = new File("files.properties");
		if(!fileProperties.exists()){
			try{
				i = 0;
				int bucket;
				Datanode datanode;
				output = new FileOutputStream(fileProperties, false);		
								
				for(Namenode namenode: namenodes){
					bucket = namenode.hashCode();
					datanode = (Datanode)datanodes.get(bucket);
					prop.setProperty(array[i],datanode.getUrl());
					i++;
				}
				
				prop.store(output, null);
			}catch (IOException io) {
				io.printStackTrace();
			} finally {
				if (output != null) {
					try {
						output.close();
					} catch (IOException e) {
						e.printStackTrace();
					}
				}
			}
		}

		for(Namenode n: namenodes){
			//System.out.println(n.hashCode());
			//System.out.println("Namenode " + n + " should stay on:");
			createFile(n);
		}

	}
	public static void createFile(Namenode namenode){
		Datanode d;
		int bucket = namenode.hashCode(); // 0,1,2
		d = (Datanode)datanodes.get(bucket);
		// Path do arquivo inicial
		Path path = Paths.get(d.getUrl()+namenode.getFileName());
		try (OutputStream out = new BufferedOutputStream(Files.newOutputStream(path, CREATE, APPEND))) {
	    } catch (IOException x) {
	      System.err.println(x);
	    }
	} 
}