public class Calculadora{
    int a; int b; int operation;
    double result;
    public Calculadora(int a, int b, int op){
        this.a = a;
        this.b = b;
        this.operation = op;
        runOperation();
    }

    public double runOperation(){
        switch(this.op){
            case 1:
                return a+b
            case 2:
                return a-b;
            case 3:
                return a*b;
            case 4:
                if(b == 0){
                    System.out.println("Division by Zero");
                    System.exit(0);
                } else {
                    return a/b;
                }
            
        }
        
    }  

}