package com.kymjs.coroutine

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import com.kymjs.coroutine.MainActivity.TestThread
import com.kymjs.coroutine.MainActivity.TestCoroutine
import com.kymjs.thread.LiteThread
import com.kymjs.coroutine.Coroutine
import com.kymjs.coroutine.databinding.ActivityMainBinding
import java.lang.Exception
import java.net.URL

class MainActivity : AppCompatActivity() {
    companion object {
        init {
            System.loadLibrary("coroutine")
        }
    }

    private var binding: ActivityMainBinding? = null
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding!!.root)
        val tv = binding!!.sampleText
        tv.text = "test ndk"
        binding!!.button1.setOnClickListener { TestThread().start() }
        binding!!.button2.setOnClickListener { TestCoroutine().async() }
        binding!!.button3.setOnClickListener { TestCoroutine(2).async() }
    }

    internal class TestThread : LiteThread() {
        override fun run() {
            super.run()
            println(Thread.currentThread().name)
            println("test in java despatch method")
            var i = 0
            while (true) {
                println("i=" + i++)
                sleep(1000, threadId)
                println("当前中断状态:$isInterrupt")
                if (i > 5) {
                    if (isInterrupt) {
                        resume()
                        println("恢复")
                    } else {
                        interrupt()
                        println("中断")
                    }
                    i = 0
                }
            }
        }
    }

    internal class TestCoroutine : Coroutine {
        constructor() : super() {}
        constructor(id: Long) : super(id) {}

        override fun run(): Any {
            super.run()
            try {
                return URL("https://baidu.com").readText()
            } catch (e: Exception) {
                e.printStackTrace()
            }
            return "test in java"
        }

        override fun <T> onAwait(result: T) {
            super.onAwait(result)
            println("========output::$result")
        }
    }
}