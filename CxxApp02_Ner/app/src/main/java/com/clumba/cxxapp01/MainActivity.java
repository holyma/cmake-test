package com.clumba.cxxapp01;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import android.Manifest;
import android.content.Context;
import android.content.pm.PackageManager;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Arrays;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    private final int MY_PERMISSIONS_CODE = 1;
    private static final List<String> resource = Arrays.asList(
            "export-script.pt","export-trace.pt",
            "tags.txt","words.txt"
    );

    // Used to load the 'native-lib' library on application startup.

    // 申请权限
    // 文件复制
    // 调用

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Context mContext = this;


        // 申请权限&文件拷贝
//        requestAudioPermissions();
        try {
            assetsInit(this);
        } catch (IOException e) {
            e.printStackTrace();
        }

        // 初始化
        Ner ner = new Ner();
        ner.init(getFilesDir().getAbsolutePath());

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String str = "They marched from the Houses of Parliament to a rally in Hyde Park .";
                tv.setText(str);
                String res = ner.decode(str);
                Toast.makeText(mContext, res, Toast.LENGTH_LONG).show();
            }
        });

    }

    private void requestAudioPermissions() {
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.RECORD_AUDIO)
                != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this,
                    new String[]{Manifest.permission.RECORD_AUDIO},
                    MY_PERMISSIONS_CODE);
        }else{

        }
    }
    @Override
    public void onRequestPermissionsResult(int requestCode,
                                           String[] permissions, int[] grantResults) {
        if (requestCode == MY_PERMISSIONS_CODE) {
            if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
            } else {
                Toast.makeText(this, "Android Permissions denied ", Toast.LENGTH_LONG).show();
            }
        }
    }

    public static void assetsInit(Context context) throws IOException {
        AssetManager assetMgr = context.getAssets();
        // Unzip all files in resource from assets to context.
        // Note: Uninstall the APP will remove the resource files in the context.
        for (String file : assetMgr.list("")) {
            if (!resource.contains(file)){
                continue;
            }
            File dst = new File(context.getFilesDir(), file);
            Log.e("TAG", "assetsInit: "+dst.getAbsolutePath() );
            if (!dst.exists() || dst.length() == 0) {
//                    Log.i(LOG_TAG, "Unzipping " + file + " to " + dst.getAbsolutePath());
                InputStream is = assetMgr.open(file);
                OutputStream os = new FileOutputStream(dst);
                byte[] buffer = new byte[4 * 1024];
                int read;
                while ((read = is.read(buffer)) != -1) {
                    os.write(buffer, 0, read);
                }
                os.flush();
                os.close();
                is.close();
            }


        }
    }

}