package com.pineapple.sound;

import com.pineapple.util.paUtil;

import android.content.Context;
import android.media.MediaPlayer;
import android.content.res.AssetFileDescriptor;
import java.io.IOException;
import java.lang.IllegalStateException;
import java.util.HashMap;
import java.util.Map;
import android.util.Log;

public class paMediaPlayer
{
	private static Map<Integer, MediaPlayer> mediaPlayerMap;
	private static int nextId;
	private static Context context;
	
	public static void startup(Context context)
	{
		paMediaPlayer.context = context;
		
		mediaPlayerMap = new HashMap<Integer, MediaPlayer>();
		nextId = 1;
	}
	
	public static void shutdown()
	{
		for (Integer soundId : mediaPlayerMap.keySet())
		{
			unload(soundId);
		}
		
		nextId = 1;
		mediaPlayerMap = null;
	}
	
	public static int load(String path)
	{
		AssetFileDescriptor afd;
		
		try
		{
			afd = context.getAssets().openFd(path);
			Log.i(paUtil.TAG, "Loaded " + afd.getLength() + " bytes for music " + path);
		}
		catch (IOException exception)
		{
			Log.i(paUtil.TAG, "Could not load asset " + path);
			return -1;
		}
		
		MediaPlayer mediaPlayer = new MediaPlayer();
		
		try
		{
			mediaPlayer.setDataSource(afd.getFileDescriptor(), afd.getStartOffset(), afd.getLength());
		}
		catch (Exception exception)
		{
			Log.i(paUtil.TAG, "Could not prepare asset " + path);
			return -1;
		}
		
		Log.i(paUtil.TAG, "Loaded music " + nextId);
		
		mediaPlayerMap.put(nextId, mediaPlayer);
		
		return nextId ++;
	}
	
	public static void unload(int soundId)
	{
		mediaPlayerMap.get(soundId).release();
		mediaPlayerMap.remove(soundId);
	}
	
	public static void play(int soundId)
	{
		MediaPlayer mediaPlayer = mediaPlayerMap.get(soundId);
		
		try
		{
			mediaPlayer.prepare();
			mediaPlayer.setLooping(false);
			mediaPlayer.start();
		}
		catch (Exception exception)
		{
			Log.i(paUtil.TAG, "Could not prepare music " + soundId);
		}
	}
	
	public static void loop(int soundId)
	{
		MediaPlayer mediaPlayer = mediaPlayerMap.get(soundId);
		
		try
		{
			mediaPlayer.prepare();
			mediaPlayer.setLooping(true);
			mediaPlayer.start();
		}
		catch (Exception exception)
		{
			Log.i(paUtil.TAG, "Could not prepare music " + soundId);
		}
	}
	
	public static void stop(int soundId)
	{
		MediaPlayer mediaPlayer = mediaPlayerMap.get(soundId);
		
		mediaPlayer.stop();
	}
	
	public static void pause(int soundId)
	{
		MediaPlayer mediaPlayer = mediaPlayerMap.get(soundId);
		
		mediaPlayer.pause();
	}
	
	public static void resume(int soundId)
	{
		MediaPlayer mediaPlayer = mediaPlayerMap.get(soundId);
		
		mediaPlayer.start();
	}
}