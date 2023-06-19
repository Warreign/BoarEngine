smooth in lowp vec3 vColor;
smooth in highp vec2 vTexCoord;

out vec4 fColor;

uniform sampler2D uTexture;

void main()
{
//    fColor = vec4(vColor, 0.5);
	fColor = texture(uTexture, vTexCoord);
}