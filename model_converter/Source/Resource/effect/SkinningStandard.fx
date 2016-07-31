
texture		tex;

sampler sampler0	= sampler_state
{
	Texture		= <tex>;
};

float4x4	skinMat[35];
float4x4	world		: WORLD;
float4x4	view		: VIEW;
float4x4	projection	: PROJECTION;

struct VsOutput
{
	float4	pos	: POSITION;
	float2	uv	: TEXCOORD0;
	float4 normal: TEXCOORD1;
};
//	スキニングメッシュ
VsOutput mainVS(  float3 local	: POSITION,
				  float2 uv		: TEXCOORD0,
				  float3 normal	: NORMAL,
				  float4 blend	: BLENDWEIGHT,
				  int4	 idx	: BLENDINDICES)
{
	VsOutput	vertex = ( VsOutput )0;
	
	float weight[ 4 ] = (float[4])blend;
								
	float4x4 comb = ( float4x4 )0;
								
	for( int i = 0; i < 4; i++)
	{
		comb += ( skinMat[ idx[ i ] ] * weight[ i ]);
	}
	
	
	vertex.pos	 = mul( float4( local, 1.0f ), comb );
	vertex.pos	 = mul( vertex.pos, world );
	vertex.pos	 = mul( vertex.pos, view );
	vertex.pos	 = mul( vertex.pos, projection );
	vertex.uv	 = uv;
	vertex.normal = mul( float4( normal,1.0f ), comb );

	return vertex;
}

// 階層メッシュの場合
VsOutput mainVS2(  float3 local	: POSITION,
				  float2 uv		: TEXCOORD0,
				  float3 normal	: NORMAL,
				  float4 blend	: BLENDWEIGHT,
				  int4	 idx	: BLENDINDICES)
{
	VsOutput	vertex = ( VsOutput )0;
	
	float weight[ 4 ] = (float[4])blend;
	
	float4x4 comb = float4x4(	1, 0, 0, 0,
								0, 1, 0, 0,
								0, 0, 1, 0,
								0, 0, 0, 1  );
								
	for( int i = 0; i < 4; i++)
	{
		comb += ( skinMat[ idx[ i ] ] * weight[ i ]);
	}
	
	vertex.pos	 = mul( float4( local, 1.0f ), comb );
	vertex.pos	 = mul( vertex.pos, world );
	vertex.pos	 = mul( vertex.pos, view );
	vertex.pos	 = mul( vertex.pos, projection );
	vertex.uv	 = uv;
	vertex.normal = mul( float4( normal,1.0f ), comb );

	return vertex;
}

float4 mainPS( VsOutput input ) : COLOR 
{
	return tex2D( sampler0, input.uv );
}

technique SkinningStandard 
{
	pass p0 
	{
	
		CULLMODE		 = NONE;
		VertexShader     = compile vs_2_0 mainVS();
		PixelShader      = compile ps_2_0 mainPS();
	}
	pass p1 
	{
	
		CULLMODE		 = NONE;
		VertexShader     = compile vs_2_0 mainVS2();
		PixelShader      = compile ps_2_0 mainPS();
	}
}
