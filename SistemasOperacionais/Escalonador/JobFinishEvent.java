package br.com.ufc.OS.Escalonador;

public interface JobFinishEvent {
    public void onFinish(Job j);
}
