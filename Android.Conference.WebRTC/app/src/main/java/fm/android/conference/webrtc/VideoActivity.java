package fm.android.conference.webrtc;

import fm.*;
import fm.icelink.webrtc.*;
import android.app.*;
import android.content.*;
import android.os.*;
import android.view.*;
import android.widget.*;

public class VideoActivity extends Activity
{
    private App app;

    private static boolean localMediaStarted;
    private static boolean conferenceStarted;

    private RelativeLayout layout;
    private Button leaveButton;
    private TextView sessionId;
    private static RelativeLayout container;
    private GestureDetector gestureDetector;
    
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        setContentView(R.layout.video);

        layout = (RelativeLayout)findViewById(R.id.layout);
        leaveButton = (Button)findViewById(R.id.leaveButton);
        sessionId = (TextView)findViewById(R.id.sessionId);

        try
        {
            app = App.getInstance();
    
            leaveButton.setOnClickListener(new View.OnClickListener()
            {
                public void onClick(View v)
                {
                	stopConference();
                }
            });
    
            sessionId.setText("Session ID: " + app.getSessionId());
    
            // For demonstration purposes, use the double-tap gesture
            // to switch between the front and rear camera.
            gestureDetector = new GestureDetector(this, new GestureDetector.SimpleOnGestureListener()
            {
                public boolean onDoubleTap(MotionEvent e)
                {
                    app.useNextVideoDevice();
                    return true;
                }
            });
    
            // Preserve a static container across
            // activity destruction/recreation.
            RelativeLayout c = (RelativeLayout)findViewById(R.id.container);
            if (container == null)
            {
                container = c;
    
                Toast.makeText(this, "Double-tap to switch camera.", Toast.LENGTH_SHORT).show();
            }
            layout.removeView(c);

            if (!localMediaStarted)
            {
                startLocalMedia();
            }
        }
        catch (Exception ex)
        {
            ex.printStackTrace();
        }
    }

    private void startLocalMedia() throws Exception
    {
        // Android's video providers need a context
        // in order to create surface views for video
        // rendering, so we need to supply one before
        // we start up the local media.
        DefaultProviders.setAndroidContext(this);

        localMediaStarted = true;
        app.startLocalMedia(container, new SingleAction<String>()
        {
            public void invoke(String error)
            {
                if (error != null)
                {
                    alert(error);
                }
                else
                {
                    try
                    {
                        // Start conference now that the local media is available.
                        if (!conferenceStarted)
                        {
                            startConference();
                        }
                    }
                    catch (Exception ex)
                    {
                        ex.printStackTrace();
                    }
                }
            }
        });
    }

    private void startConference() throws Exception
    {
        conferenceStarted = true;
        app.startConference(new SingleAction<String>()
        {
            public void invoke(String error)
            {
                if (error != null)
                {
                    alert(error);
                }
            }
        });
    }

    private void stopConference()
    {
    	try
    	{
	    	if (conferenceStarted)
	    	{
	    		conferenceStarted = false;
		        app.stopConference(new SingleAction<String>()
		        {
		            public void invoke(String error)
		            {
		            	try
		            	{
		            		stopLocalMedia();
		            	}
		            	catch (Exception ex)
		            	{
		            		ex.printStackTrace();
		            	}
		            }
		        });
	    	}
	    	else
	    	{
	    		stopLocalMedia();
	    	}
    	}
    	catch (Exception ex)
    	{
    		ex.printStackTrace();
    	}
    }

    private void stopLocalMedia()
    {
    	try
    	{
	    	if (localMediaStarted)
	    	{
	    		localMediaStarted = false;
		        app.stopLocalMedia(new SingleAction<String>()
		        {
		            public void invoke(String error)
		            {
		                container = null;

		                finish();
		            }
		        });
	    	}
	    	else
	    	{
                container = null;

                finish();
	    	}
    	}
    	catch (Exception ex)
    	{
    		ex.printStackTrace();
    	}
    }
    
    public void onBackPressed()
    {
        stopConference();
    }
    
    protected void onPause()
    {
        // Android requires us to pause the local
        // video feed when pausing the activity.
        // Not doing this can cause unexpected side
        // effects and crashes.
        if (localMediaStarted)
        {
            app.pauseLocalVideo();
        }
        
        // Remove the static container from the current layout.
        if (container != null)
        {
            layout.removeView(container);
        }

        super.onPause();
    }
    
    protected void onResume()
    {
        super.onResume();

        // Add the static container to the current layout.
        if (container != null)
        {
            layout.addView(container);
        }

        // Resume the local video feed.
        if (localMediaStarted)
        {
            app.resumeLocalVideo();
        }
    }
    
    public boolean onTouchEvent(MotionEvent event)
    {
        // Handle the double-tap event.
        if (gestureDetector == null || !gestureDetector.onTouchEvent(event))
        {
            return super.onTouchEvent(event);
        }
        return true;
    }

    public void alert(String format, Object... args)
    {
        final String text = String.format(format, args);
        final Activity self = this;
        self.runOnUiThread(new Runnable()
        {
            public void run()
            {
                if (!isFinishing())
                {
                    AlertDialog.Builder alert = new AlertDialog.Builder(self);
                    alert.setMessage(text);
                    alert.setPositiveButton("OK", new DialogInterface.OnClickListener()
                    {
                        public void onClick(DialogInterface dialog, int which)
                        { }
                    });
                    alert.show();
                }
            }
        });
    }
}
