#include "pch.h"
#include "PointLight.h"

PointLight::PointLight()
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	constant = 1.0f;
	linear = 0.0f;
	exponent = 0.0f;
}

PointLight::PointLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity, GLfloat xPos, GLfloat yPos, GLfloat zPos, GLfloat cons, GLfloat lin, GLfloat exp) :Light(red,green,blue,aIntensity,dIntensity)
{
	position = glm::vec3(xPos, yPos, zPos);
	constant = cons;
	linear = lin;
	exponent = exp;
}

void PointLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation, GLuint diffuseIntensityLocation, GLuint positionLocation, GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation)
{
	Light::UseLight(ambientIntensityLocation, ambientColourLocation, diffuseIntensityLocation);
	glUniform3f(positionLocation, position.x, position.y, position.z);
	glUniform1f(constantLocation, constant);
	glUniform1f(linearLocation, linear);
	glUniform1f(exponentLocation, exponent);
}

PointLight::~PointLight()
{
}
