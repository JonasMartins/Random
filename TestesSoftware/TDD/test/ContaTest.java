package test;

import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import conta.Conta;
import conta.Client;

public class ContaTest {
	private Client dummyClient = null;
	private Conta dummyAccount = null;
	private Conta dummyAccount2 = null;
	
	@Before
	public void setUp() throws Exception {
		this.dummyClient = new Client(10000);
		this.dummyAccount = new Conta(dummyClient);
		this.dummyAccount2 = new Conta(dummyClient);
		assertNotNull("O objeto não dever ser nulo",dummyAccount);
		assertNotNull("O objeto não dever ser nulo",dummyAccount);
	}
	
	@Test
	public void sholdHaveRightBalanceAfterDeposit(){
		double before = dummyAccount.getBalance();
		dummyAccount.deposito(100);
		assertEquals(dummyAccount.getBalance(),before+100,0.0);
	}	
	
	@Test
	public void shouldHaveAccountWithZeroBalance(){	
		assertEquals(dummyAccount.getBalance(),0.0,0.0);
	}
	@Test
	public void shouldHaveEnouthMoneyToCredit(){
		
		assertTrue(dummyAccount2.credito(2000));
	}
	
	@After
	public void tearDown() throws Exception {
		System.out.println("Running: tearDown");
		dummyClient = null;
		dummyAccount2 = dummyAccount = null;
		assertNull(dummyClient);
		assertNull(dummyAccount2);
		assertNull(dummyAccount);
	}
}
