#version 460

in vec2 TexCoord;
in vec4 color;
in vec3 fN;
in vec3 fE;
in vec3 fL;

uniform vec4 AmbientProduct;
uniform vec4 DiffuseProduct;
uniform vec4 SpecularProduct;
uniform float Shininess;
uniform bool Gouraud;
out vec4 FragColor;
uniform vec4 ourColor;
uniform sampler2D myTexture;

void main()
{
	if(!Gouraud){
		vec3 N = normalize(fN);
		vec3 E = normalize(fE);
		vec3 L = normalize(fL);

		vec3 H = normalize(L + E);
		vec4 ambient = AmbientProduct;
		float Kd = max(dot(L, N), 0.0);
		vec4 diffuse = Kd * DiffuseProduct;

		float Ks = pow(max(dot(N, H), 0.0), Shininess);
		vec4 specular = Ks * SpecularProduct;

		if(dot(L, N) < 0.0)
			specular = vec4(0.0, 0.0, 0.0, 1.0);
		FragColor = ambient + diffuse + specular;
		FragColor.a = 1.0;
		FragColor = ourColor * FragColor;
	}
	else
		FragColor = color * ourColor;
}