#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL\glew.h>

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

#include "CommonValues.h"

class Shader
{
public:
	Shader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);
	std::string ReadFile(const char* fileLocation);

	GLuint GetModelLocation();
	GLuint GetProjectionLocation();
	GLuint GetViewLocation();
	GLuint GetAmbientIntensityLocation();
	GLuint GetAmbientColourLocation();
	GLuint GetUniformDiffuseIntensityLocation();
	GLuint GetUniformDirectionLocation();
	GLuint GetSpecularIntensityLocation();
	GLuint GetShinenessLocation();
	GLuint GetEyePositionLocation();

	void SetDirectionalLight(DirectionalLight* dLight);
	void SetPointLights(PointLight * pLight, unsigned int lightCount);
	void SetSpotLights(SpotLight* sLight, unsigned int lightCount);

	void UseShader();
	void ClearShader();

	~Shader();
private:
	int pointLightCount;
	int spotLightCount;
	GLuint shaderID, uniformProjection, uniformModel, uniformView, uniformEyePosition,
		uniformsSpecularIntensity, uniformShininess, uniformPointLightCount, uniformSpotLightCount;

	struct
	{
		GLuint uniformColor;
		GLuint unifromAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformDirection;
	} uniformDirectionalLight;

	struct
	{
		GLuint uniformColor;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint unifromExponent;
	} uniformPointLight[MAX_POINT_LIGHTS];

	struct
	{
		GLuint uniformColor;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint unifromExponent;

		GLuint uniformDirection;
		GLuint uniformEdge;
	} uniformSpotLight[MAX_SPOT_LIGHTS];

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};