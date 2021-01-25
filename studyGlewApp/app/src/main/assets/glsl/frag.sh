precision mediump float;

varying vec4 vSpecular;                         //用于传递给片元着色器的镜面光分量

void main()
{
    vec4 vFinalColor = vec4(1.0, 0.0, 1.0, 0.0);

    gl_FragColor = vFinalColor * vSpecular;  //通过镜面光分量获得最终颜色
}