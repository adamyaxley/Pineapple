package com.pineapple.sound;

import com.pineapple.util.paUtil;

import android.app.Activity;
import android.content.Context;
import android.content.res.AssetFileDescriptor;
import android.media.AudioAttributes;
import android.media.AudioManager;
import android.media.SoundPool;
import android.media.SoundPool.OnLoadCompleteListener;
import android.os.Build;
import android.util.Log;
import java.util.concurrent.Semaphore;
import java.io.IOException;
import java.lang.InterruptedException;
import java.lang.Thread;

public class paSoundPool
{
	private static SoundPool soundPool;
	private static Context context;
	private static AudioManager audioManager;
	private static boolean playingLoopedMutedHack;
	
	public static void startup(Context context)
	{
		playingLoopedMutedHack = false;
		
		paSoundPool.context = context;
		audioManager = (AudioManager)context.getSystemService(Context.AUDIO_SERVICE);

		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP)
		{
			AudioAttributes audioAttrib = new AudioAttributes.Builder()
					.setUsage(AudioAttributes.USAGE_GAME)
					.setContentType(AudioAttributes.CONTENT_TYPE_SONIFICATION)
					.build();
			soundPool = new SoundPool.Builder().setAudioAttributes(audioAttrib).setMaxStreams(16).build();
		}
		else
		{
			soundPool = new SoundPool(16, AudioManager.STREAM_MUSIC, 0);
		}
	}
	
	public static void shutdown()
	{
		soundPool.release();
		soundPool = null;
	}
	
	public static int load(String path)
	{
		int soundId;
		
		paSoundPoolOnLoadCompleteListener onLoadCompleteListener = new paSoundPoolOnLoadCompleteListener();
		soundPool.setOnLoadCompleteListener(onLoadCompleteListener);
		
		try
		{
			AssetFileDescriptor afd = context.getAssets().openFd(path);
			Log.i(paUtil.TAG, "Loaded " + afd.getLength() + " bytes for effect " + path);
			
			soundId = soundPool.load(afd, 1);
		}
		catch (IOException exception)
		{
			Log.i(paUtil.TAG, "Could not load asset " + path);
			return -1;
		}
		
		// Will block since there is not permits (the semaphore is initialized with 0)
		// then will continue once semaphore.release(); is called i.e. after loading is finished
		try
		{
			onLoadCompleteListener.waitUntilLoaded();
		}
		catch (InterruptedException exception)
		{
			Log.i(paUtil.TAG, "failed to acquire semaphore");
			return -1;
		}
		
		if (onLoadCompleteListener.getStatus() == 0)
		{
			if (!playingLoopedMutedHack)
			{
				// Play the first loaded sound in a muted loop to keep the sound pool alive 
				soundPool.play(soundId, 0, 0, 1, -1, 1f);
				Log.i(paUtil.TAG, "playing sound " + soundId + " muted and looping to keep the sound player active");
				playingLoopedMutedHack = true;
			}
			// Play sound 3 times to cache it into sound pool
			/*for (int i = 0; i < 3; i++)
			{
				int streamId = soundPool.play(soundId, 0, 0, 1, soundId, 1.f);
				Log.i(paUtil.TAG, "playing sound " + soundId + " muted (streamId=" + streamId + ")");
			}*/
			
			return soundId;
		}
		else
		{
			Log.i(paUtil.TAG, "Failed to load sound " + soundId + ", status is " + onLoadCompleteListener.getStatus());
			return -1;
		}
	}
	
	public static void unload(int soundId)
	{
		soundPool.unload(soundId);
	}
	
	public static int play(int soundId)
	{
		Log.i(paUtil.TAG, "play sound " + soundId);
		
		float currentVolume = ((float)audioManager.getStreamVolume(AudioManager.STREAM_MUSIC)) / ((float)audioManager.getStreamMaxVolume(AudioManager.STREAM_MUSIC));
		
		int streamId = 0;
		int attempts = 0;
		
		while (streamId == 0 && attempts ++ < 3)
		{
			streamId = soundPool.play(soundId, currentVolume, currentVolume, attempts, 0, 1.f);
			
			if (streamId == 0)
			{
				// failed to play sound
				Log.i(paUtil.TAG, "failed to play sound (attempt=" + attempts + " streamId=" + streamId + ")");
			}
		}
		
		if (streamId > 0)
		{
			Log.i(paUtil.TAG, "played sound " + soundId + " (streamId=" + streamId + ")");
			return streamId;
		}
		else
		{
			return -1;
		}
	}
}