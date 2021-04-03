#include "pch.h"
#include "SpotLight.h"

SpotLight::SpotLight():PointLight()
{
	direction = glm::vec3(0,0,0);
	edge = 0;
	procEdge = cosf(glm::radians(edge));
}

SpotLight::SpotLight(GLfloat red,        GLfloat green, GLfloat blue,
					 GLfloat aIntensity, GLfloat dIntensity, 
					 GLfloat xPos,       GLfloat yPos, GLfloat zPos,
					 GLfloat xDir,       GLfloat yDir, GLfloat zDir, GLfloat cons, GLfloat lin, GLfloat exp, GLfloat edg) : PointLight(red, green, blue, aIntensity, dIntensity,xPos,yPos, zPos,cons,lin,exp)
{
	direction = glm::normalize(glm::vec3(xDir, yDir, zDir));
	edge = edg;
	procEdge = cosf(glm::radians(edge));
}

void SpotLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation, GLuint diffuseIntensityLocation, GLuint positionLocation, GLuint directionLocation, GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation, GLuint edgeLocation)
{
	PointLight::UseLight(ambientIntensityLocation, ambientColourLocation, diffuseIntensityLocation, positionLocation, constantLocation, linearLocation, exponentLocation);
	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(edgeLocation, procEdge);
}

void SpotLight::SetFlash(glm::vec3 pos, glm::vec3 dir)
{
	position = pos;
	direction = dir;
}

SpotLight::~SpotLight()
{

}
