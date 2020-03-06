#version 330

in vec4 vCol;
in vec2 TexCoord;
in vec3 Normal;

out vec4 color;

struct DirectionalLight{
	vec3 colour;
	float ambientIntensity;
	vec3 direction;
	float diffuseIntensity;
};

uniform sampler2D theTexture;
uniform DirectionalLight directionalLight;

void main()
{
	vec4 ambientColour = vec4(directionalLight.colour, 1.0f) * directionalLight.ambientIntensity;
	// A.B = |A||B|cos(AB)
	float diffuseFactor = max(dot(normalize(Normal), normalize(directionalLight.direction)), 0.0f);
	vec4 diffuseColor = vec4(directionalLight.colour, 1.0f)* directionalLight.diffuseIntensity * diffuseFactor;

	color = texture(theTexture, TexCoord) * (ambientColour + diffuseColor);
}