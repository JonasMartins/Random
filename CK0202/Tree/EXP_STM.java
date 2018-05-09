package Tree;

import Temp.Temp;
import Temp.Label;

public class EXP_STM extends Stm {
	public Exp exp;

	public EXP_STM(Exp e) {
		exp = e;
	}

	public ExpList kids() {
		return new ExpList(exp, null);
	}

	public Stm build(ExpList kids) {
		return new EXP_STM(kids.head);
	}
}
