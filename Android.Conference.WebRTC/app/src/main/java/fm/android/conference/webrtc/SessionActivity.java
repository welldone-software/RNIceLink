package fm.android.conference.webrtc;

import android.app.*;
import android.content.*;
import android.os.*;
import android.text.*;
import android.view.*;
import android.widget.*;

import fm.*;

public class SessionActivity extends Activity
{
    private App app;

    private static boolean signallingStarted;

    private TextView createSession;
    private Button createButton;
    private EditText joinSession;
    private Button joinButton;
    
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_ALWAYS_HIDDEN);
        setContentView(R.layout.session);

        createSession = (TextView)findViewById(R.id.createSession);
        createButton = (Button)findViewById(R.id.createButton);
        joinSession = (EditText)findViewById(R.id.joinSession);
        joinButton = (Button)findViewById(R.id.joinButton);

        try
        {
            app = App.getInstance();
    
            // Create a random 6 digit number for the new session ID.
            createSession.setText(String.valueOf(new Randomizer().next(100000, 999999)));
    
            joinSession.setFilters(new InputFilter[] { new InputFilter.LengthFilter(6) });
    
            createButton.setOnClickListener(new View.OnClickListener()
            {
                public void onClick(View v)
                {
                    switchToVideoChat(createSession.getText().toString());
                }
            });
            joinButton.setOnClickListener(new View.OnClickListener()
            {
                public void onClick(View v)
                {
                    switchToVideoChat(joinSession.getText().toString());
                }
            });
    
            // Start signalling when the view loads
            // (if it hasn't started already).
            if (!signallingStarted)
            {
                startSignalling();
            }
        }
        catch (Exception ex)
        {
            ex.printStackTrace();
        }
    }

    private void startSignalling()
    {
        try
        {
            signallingStarted = true;
            app.startSignalling(new SingleAction<String>()
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
        catch (Exception ex)
        {
            ex.printStackTrace();
        }
    }

    private void switchToVideoChat(String sessionId)
    {
        if (sessionId.length() == 6)
        {
            app.setSessionId(sessionId);

            // Show the video chat.
            startActivity(new Intent(getApplicationContext(), VideoActivity.class));
        }
        else
        {
            alert("Session ID must be 6 digits long.");
        }
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
