package com.example.jnicrashdemo;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.example.jnicrashdemo.databinding.ActivityMainBinding;

import java.io.File;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'jnicrashdemo' library on application startup.
    static {
        System.loadLibrary("jnicrashdemo");
    }

    private ActivityMainBinding binding;
    private Button btn;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        btn = (Button)findViewById(R.id.button);
        btn.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                testCrash();
            }
        });
        // Example of a call to a native method
        TextView tv = binding.sampleText;
        tv.setText(stringFromJNI());
    }

    public native String stringFromJNI();

    public static void init(Context context) {
        Context applicationContext = context.getApplicationContext();
//存储目录： /storage/emulated/0/Android/data/com.example.myapplication/cache/native_crash
        File file = new File(applicationContext.getExternalCacheDir(), "native_crash");
        if(!file.exists()){
            file.mkdirs();
        }
        initNative(file.getAbsolutePath());
    }

    public static native void testCrash();

    private static native void initNative(String path);
}