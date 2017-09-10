import java.io.Serializable;

public class Requisicao implements Serializable {

  /**
   * 
   */
  private static final long serialVersionUID = 1L;
  private int num1, num2, result;
  public String operacao;

  public Requisicao(int a, int b, String op) {
    setNum1(a);
    setNum2(b);
    this.operacao = op;
  }

  public int getNum1() {
    return num1;
  }

  public void setNum1(int num1) {
    this.num1 = num1;
  }

  public int getNum2() {
    return num2;
  }

  public void setNum2(int num2) {
    this.num2 = num2;
  }

  @Override
  public String toString() {
    return "object: " + getNum1() + " " + this.operacao + " " + getNum2();
  }

  public int getResult() {
    return result;
  }

  public void setResult(int result) {
    this.result = result;
  }

  public void doOperation(){
    if (this.operacao.equals("soma"))
      setResult(num1+num2);
    if (this.operacao.equals("subtracao"))
      setResult(num1-num2);
    if (this.operacao.equals("multiplicacao"))
      setResult(num1*num2);
    if (this.operacao.equals("divisao")){
      if(num2 == 0){
        System.out.println("Division by Zero...");
        System.exit(0);
      }
      setResult(num1/num2);     
    }
  }
}