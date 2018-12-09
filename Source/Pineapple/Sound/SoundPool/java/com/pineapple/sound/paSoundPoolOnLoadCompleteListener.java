package com.pineapple.sound;

import android.media.SoundPool.OnLoadCompleteListener;
import android.media.SoundPool;
import java.util.concurrent.Semaphore;
import java.lang.InterruptedException;

public class paSoundPoolOnLoadCompleteListener implements OnLoadCompleteListener
{
	private final Semaphore semaphore;
	
	private int status;
	
	public paSoundPoolOnLoadCompleteListener()
	{
		semaphore = new Semaphore(0);
	}
	
	public int getStatus()
	{
		return status;
	}
	
	public void waitUntilLoaded() throws InterruptedException
	{
		semaphore.acquire();
	}
	
	@Override
	public void onLoadComplete(SoundPool soundPool, int sid, int status)
	{
		this.status = status;
		
		semaphore.release();
	}
}