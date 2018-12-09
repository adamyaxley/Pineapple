package com.pineapple.util;

import android.content.Context;
import android.content.Intent;
import android.net.Uri;

public class paUtil
{
	public static final String TAG = "PINEAPPLE_JAVA";
	
	private static Context context;
	
	public static void setContext(Context context)
	{
		paUtil.context = context;
	}
	
	public static void openUrl(String url)
	{
		Uri uri = Uri.parse(url); 
		Intent intent = new Intent(Intent.ACTION_VIEW, uri); 
		intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK); 
		context.startActivity(intent); 
	}
}