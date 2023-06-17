in vec3 aPosition;
in vec3 aColor;

smooth out lowp vec3 vColor;

void main()
{
	gl_Position = vec4(aPosition, 1);
	vColor = aColor;
}