
texture		tex;

sampler sampler0	= sampler_state
{
	Texture		= <tex>;
};

float4x4	world		: WORLD;
float4x4	view		: VIEW;
float4x4	projection	: PROJECTION;

struct VsOutput{
	float4	pos	: POSITION;
	float2	uv	: TEXCOORD0;
	float4 normal: TEXCOORD1;
};

VsOutput mainVS(  float3 local	: POSITION,
				  float2 uv		: TEXCOORD0,
				  float3 normal	: NORMAL )
{
	VsOutput	vertex = ( VsOutput )0;
	
	vertex.pos	 = mul( float4( local, 1.0f ), world );
	vertex.pos	 = mul( mul( vertex.pos, view ), projection );
	vertex.uv	 = uv;
	vertex.normal = float4( normal,1.0f );

	return vertex;
}

float4 mainPS( VsOutput input ) : COLOR 
{
	return tex2D( sampler0, input.uv );
}

technique Standard 
{
	pass p0 
	{
	
		CULLMODE			= NONE;
		VertexShader     = compile vs_2_0 mainVS();
		PixelShader      = compile ps_2_0 mainPS();
	}
}
