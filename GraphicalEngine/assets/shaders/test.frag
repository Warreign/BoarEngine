smooth in lowp vec3 vColor;

out vec4 fColor;

void main()
{
    fColor = vec4(vColor, 0.5);
}