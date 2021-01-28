package com.heaven7.android.glew.app.render;

import android.app.Activity;

import com.heaven7.android.glew.app.IGLRender;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import static android.opengl.GLES20.*;

/**
 * 绘制点，线，三角形
 */
public class AirHockeyRenderer extends IGLRender {
    private static final String A_POSITION = "a_Position";
    private static final String A_COLOR = "a_Color";    
    private static final int POSITION_COMPONENT_COUNT = 2;
    private static final int COLOR_COMPONENT_COUNT = 3;    
    private static final int BYTES_PER_FLOAT = 4;
    private static final int STRIDE = 
        (POSITION_COMPONENT_COUNT + COLOR_COMPONENT_COUNT) * BYTES_PER_FLOAT;
    
    private final FloatBuffer vertexData;
    private int aPositionLocation;
    private int aColorLocation;

    public AirHockeyRenderer(Activity context) {
        super(context);
        /*
        float[] tableVerticesWithTriangles = {
            // Triangle Fan
               0,     0,            
            -0.5f, -0.5f,             
             0.5f, -0.5f,
             0.5f,  0.5f,
            -0.5f,  0.5f,            
            -0.5f, -0.5f,
            // Line 1
            -0.5f, 0f, 
             0.5f, 0f,
            // Mallets
            0f, -0.25f,
            0f,  0.25f 
        };*/
                
        //
        // Vertex data is stored in the following manner:
        // 
        // The first two numbers are part of the position: X, Y
        // The next three numbers are part of the color: R, G, B
        //
        float[] tableVerticesWithTriangles = {   
            // Order of coordinates: X, Y, R, G, B
            
            // Triangle Fan
               0f,    0f,   1f,   1f,   1f,         
            -0.5f, -0.5f, 0.7f, 0.7f, 0.7f,            
             0.5f, -0.5f, 0.7f, 0.7f, 0.7f,
             0.5f,  0.5f, 0.7f, 0.7f, 0.7f,
            -0.5f,  0.5f, 0.7f, 0.7f, 0.7f,
            -0.5f, -0.5f, 0.7f, 0.7f, 0.7f,

            // Line 1
            -0.5f, 0f, 1f, 0f, 0f,
             0.5f, 0f, 1f, 0f, 0f,

            // Mallets
            0f, -0.25f, 0f, 0f, 1f,
            0f,  0.25f, 1f, 0f, 0f
        };

        vertexData = ByteBuffer
            .allocateDirect(tableVerticesWithTriangles.length * BYTES_PER_FLOAT)
            .order(ByteOrder.nativeOrder()).asFloatBuffer();

        vertexData.put(tableVerticesWithTriangles);
    }

    @Override
    public void onSurfaceCreated(GL10 glUnused, EGLConfig config) {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        loadAndLinkShaderFromAssets("glsl/vertex_gradient.sh", "glsl/frag_gradient.sh");

        glUseProgram(mProgram);
        
        aPositionLocation = glGetAttribLocation(mProgram, A_POSITION);
        aColorLocation = glGetAttribLocation(mProgram, A_COLOR);

        // Bind our data, specified by the variable vertexData, to the vertex
        // attribute at location A_POSITION_LOCATION.
        vertexData.position(0);
        glVertexAttribPointer(aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, 
            false, STRIDE, vertexData);

        glEnableVertexAttribArray(aPositionLocation);     
        
        // Bind our data, specified by the variable vertexData, to the vertex
        // attribute at location A_COLOR_LOCATION.
        vertexData.position(POSITION_COMPONENT_COUNT);        
        glVertexAttribPointer(aColorLocation, COLOR_COMPONENT_COUNT, GL_FLOAT, 
            false, STRIDE, vertexData);        

        glEnableVertexAttribArray(aColorLocation);
    }

    /**
     * onSurfaceChanged is called whenever the surface has changed. This is
     * called at least once when the surface is initialized. Keep in mind that
     * Android normally restarts an Activity on rotation, and in that case, the
     * renderer will be destroyed and a new one created.
     * 
     * @param width
     *            The new width, in pixels.
     * @param height
     *            The new height, in pixels.
     */
    @Override
    public void onSurfaceChanged(GL10 glUnused, int width, int height) {
        // Set the OpenGL viewport to fill the entire surface.
        glViewport(0, 0, width, height);
    }

    /**
     * OnDrawFrame is called whenever a new frame needs to be drawn. Normally,
     * this is done at the refresh rate of the screen.
     */
    @Override
    public void onDrawFrame(GL10 glUnused) {
        // Clear the rendering surface.
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the table.        
        glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

        /*
         * 这里的6 ， 8， 9 代表的是组的索引。因为上面顶点数据5个为一组.
         */
        // Draw the center dividing line.
        glDrawArrays(GL_LINES, 6, 2);

        // Draw the first mallet.        
        glDrawArrays(GL_POINTS, 8, 1);

        // Draw the second mallet.
        glDrawArrays(GL_POINTS, 9, 1);
    }
}