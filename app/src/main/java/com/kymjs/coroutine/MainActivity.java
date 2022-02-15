package com.kymjs.coroutine;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import com.kymjs.coroutine.databinding.ActivityMainBinding;
import com.kymjs.thread.LiteThread;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("coroutine");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        TextView tv = binding.sampleText;
        tv.setText("test ndk");

        binding.button1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new TestThread().start();
            }
        });
        binding.button2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new TestThread().start();
            }
        });
    }

    static class TestThread extends LiteThread {
        @Override
        public void run() {
            super.run();
            System.out.println(Thread.currentThread().getName());
            System.out.println("test in java run method");
            int i = 0;
            while (true) {
                System.out.println("i=" + i++);
                sleep(1000, threadId);
                System.out.println("当前中断状态:" + isInterrupt());
                if (i > 5) {
                    if (isInterrupt()) {
                        resume();
                        System.out.println("恢复");
                    } else {
                        interrupt();
                        System.out.println("中断");
                    }
                    i = 0;
                }
            }
        }
    }
}