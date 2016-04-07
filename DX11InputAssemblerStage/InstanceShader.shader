struct VOut
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

VOut VShader(float4 position : POSITION, float4 color : COLOR, float4 instancePos : INSTANCEPOS)
{
    VOut output;


    //position.x =+ positionInstanced.x;
    //position.y =+ positionInstanced.y;
    //position.z =+ positionInstanced.z;
    output.position = position;
    output.color = color;

    return output;
}


float4 PShader(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET
{
	if (position.x < 1.0f)
	{
		float mult = 0.9f;
		float4 res = color;
		for (int i=0; i<1; i++)
		{
			res = res*mult;
		}
		return res;
	}
    return color;
}