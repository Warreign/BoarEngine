layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec3 aColor;

smooth out lowp vec3 vColor;

void main()
{
	gl_Position = vec4(aPosition.xy, 0.0, 1.0);
	vColor = aColor;
}