package pk.muneebahmad.witype.activities;

import android.app.Activity;
import android.os.Bundle;
import android.os.PowerManager;
import android.view.Window;
import android.view.WindowManager;

import com.wiyun.engine.nodes.Director;
import com.wiyun.engine.opengl.WYGLSurfaceView;

/**
 * 
 * @author muneebahmad
 *
 */
public abstract class WiTypeActivity extends Activity implements 
								Director.IDirectorLifecycleListener {

	protected WYGLSurfaceView mGLSurfaceView;
	private PowerManager.WakeLock wakeLock;
	static final boolean IS_TRANSPARENT = false;
	
	static {
		System.loadLibrary("wiengine");
		System.loadLibrary("wiengine_binding");
		System.loadLibrary("box2d");
		System.loadLibrary("lua");
		System.loadLibrary("chipmunk");
		System.loadLibrary("wisound");
		System.loadLibrary("winetwork");
		System.loadLibrary("iap");
		System.loadLibrary("muneebahmad");
	}
	
	/**
	 * 
	 * @return
	 */
	public boolean isTransparent() {
		return IS_TRANSPARENT;
	}
	
	/**
	 * 
	 * @return
	 */
	protected String checkPrecondition() {
		return null;
	}
	
	/**
	 * 
	 */
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, 
				WindowManager.LayoutParams.FLAG_FULLSCREEN);
		this.mGLSurfaceView = new WYGLSurfaceView(this, isTransparent());
		setContentView(this.mGLSurfaceView);
		Director.getInstance().addLifecycleListener(this);
	}
	
	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
	}
	
	@Override
	protected void onPause() {
		// TODO Auto-generated method stub
		super.onPause();
		this.wakeLock.release();
	}
	
	@Override
	protected void onResume() {
		// TODO Auto-generated method stub
		super.onResume();
		this.wakeLock = ((PowerManager) getSystemService("power")).
				newWakeLock(PowerManager.FULL_WAKE_LOCK, "MainActivity");
		this.wakeLock.acquire();
		Director.getInstance().resume();
	}
	
	@Override
	public void onSurfaceCreated() {
		// TODO Auto-generated method stub
		
	}
	
	/**
	 * 
	 * @param scale
	 * @param width
	 * @param height
	 */
	protected void setBaseSize(int scale, int width, int height) {
		Director.getInstance().setScaleMode(scale);
		Director.getInstance().setBaseSize(width, height);
	}
	
}/** end class. */
