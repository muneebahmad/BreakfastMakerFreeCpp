package com.algorithmi.maker.breakfast.free.main;

import com.wiyun.engine.nodes.Director;
import com.wiyun.engine.opengl.WYGLSurfaceView;

import pk.muneebahmad.witype.activities.WiTypeActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;

public class MainActivity extends WiTypeActivity {
	
	private boolean mStarted;
	public static final int WIN_WIDTH = 480;
	public static final int WIN_HEIGHT = 800;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		this.mStarted = false;
		setBaseSize(1, WIN_WIDTH, WIN_HEIGHT);
		this.mGLSurfaceView.setDrawingCacheQuality(View.DRAWING_CACHE_QUALITY_HIGH);
	}
	
	/**
	 * 
	 */
	private native void nativeKick();

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}
	
	@Override
	protected void onPause() {
		super.onPause();
		Director.getInstance().pause();
	}
	
	@Override
	protected void onDestroy() {
		Director.getInstance().end();
		super.onDestroy();
	}
	
	@Override
	protected void onStart() {
		super.onStart();
	}
	
	@Override
	protected void onStop() {
		super.onStop();
	}
	
	@Override
	public void onBackPressed() {
		super.onBackPressed();
	}

	@Override
	public void onSurfaceChanged(int w, int h) {
		if (!(this.mStarted)) {
			this.mStarted = true;
			if (this.mGLSurfaceView == null) {
				setContentView(new WYGLSurfaceView(this, isTransparent()));
			}
			nativeKick();
		}
	}

	@Override
	public void onSurfaceDestroyed() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onDirectorPaused() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onDirectorResumed() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onDirectorEnded() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onDirectorScreenCaptured(String path) {
		// TODO Auto-generated method stub
		
	}
}/** end class. */
