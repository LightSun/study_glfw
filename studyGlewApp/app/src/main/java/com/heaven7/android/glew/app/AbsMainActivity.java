package com.heaven7.android.glew.app;

import android.app.Activity;
import android.app.ListActivity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.ListView;

import com.heaven7.adapter.ISelectable;
import com.heaven7.adapter.QuickAdapter;
import com.heaven7.core.util.ViewHelper;

import java.util.ArrayList;
import java.util.List;

public abstract class AbsMainActivity extends ListActivity {

    protected final List<ActivityInfo> mInfos = new ArrayList<>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
       // setListAdapter(new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1, options));
       addDemos(mInfos);
       setListAdapter(new QuickAdapter<ActivityInfo>(android.R.layout.simple_list_item_1, mInfos) {
           @Override
           protected void onBindData(Context context, int position, final ActivityInfo item,
                                     int itemLayoutId, ViewHelper helper) {
                   helper.setText(android.R.id.text1, item.desc)
                           .setRootOnClickListener(new View.OnClickListener() {
                               @Override
                               public void onClick(View v) {
                                   Intent intent = new Intent(AbsMainActivity.this, item.clazz);
                                   if(item.args != null){
                                       intent.putExtras(item.args);
                                   }
                                   startActivity(intent);
                               }
                           });
           }
       });
    }

    protected abstract void addDemos(List<ActivityInfo> list);

    @Override
    protected void onListItemClick(ListView l, View v, int position, long id) {

    }

    public static class ActivityInfo implements ISelectable {
        final String desc;
        final Class<? extends Activity> clazz;
        Bundle args;

        public ActivityInfo(Class<? extends Activity> clazz, String desc) {
            this.clazz = clazz;
            this.desc = desc;
        }
        public ActivityInfo(Context context, Class<? extends Activity> clazz, int stringResId) {
            this.clazz = clazz;
            this.desc = context.getResources().getString(stringResId);
        }

        public Bundle getArgs() {
            return args;
        }
        public void setArgs(Bundle args) {
            this.args = args;
        }

        @Override
        public void setSelected(boolean selected) {
        }
        @Override
        public boolean isSelected() {
            return false;
        }
    }
}
