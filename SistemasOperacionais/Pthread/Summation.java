class Summation implements Runnable{
  private int upper;
  private Sum sumValue;
  public Summation(int upper, Sum sumValue) {
  if (upper < 0)
    throw new IllegalArgumentException();
    this.upper = upper;
    this.sumValue = sumValue;
  }
  /*Runnable is implemented by thread class

    Run é usado para criar uma thread, run é usado para
    executar uma thread separadamente

  */
  public void run() { /*implemented by a thread*/
  int sum = 0;
   for (int i = 0; i <= upper; i++)
        sum += i;
  sumValue.set(sum);
  }
 }
