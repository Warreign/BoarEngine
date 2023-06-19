layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aColor;

smooth out lowp vec3 vColor;
smooth out highp vec2 vTexCoord;

uniform mat4 mMVP;

void main()
{
	gl_Position = mMVP * vec4(aPosition.xy, 0.0, 1.0);
	vColor = aColor;
	vTexCoord = aTexCoord;
}