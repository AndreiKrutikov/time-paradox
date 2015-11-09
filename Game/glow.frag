uniform sampler2D texture;
uniform vec4 glowColor;
uniform float intensity;

void main()
{
    //float factor = 64;
    //vec2 pos = floor(gl_TexCoord[0].xy * factor + 0.5) / factor;
	float len = intensity*(pow(gl_TexCoord[0].x -0.5, 2) + pow(gl_TexCoord[0].y -0.5, 2));
	//vec4 color = glowColor*len;
    gl_FragColor = texture2D(texture, gl_TexCoord[0].xy)*(1-len)+glowColor*len;
}
