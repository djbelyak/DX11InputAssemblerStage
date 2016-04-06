struct VOut
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

VOut VShader(float4 position : POSITION, float4 color : COLOR)
{
    VOut output;

    output.position = position;
    output.color = color;

    return output;
}


float4 PShader(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET
{
	if (position.x < 100.0f)
	{
		float mult = 0.9f;
		float4 res = color;
		for (int i=0; i<100000; i++)
		{
			res = res*mult;
		}
		return res;
	}
    return color;
}