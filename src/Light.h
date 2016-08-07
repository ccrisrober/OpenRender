#pragma once
class Light
{
protected:
	GLuint lightID;
public:
	bool enabled;
	glm::vec4 position;
	GLfloat constantAtt, linearAtt, quadraticAtt;
	Light();
	Light(glm::mat4 p, GLfloat ca, GLfloat la, GLfloat qa);
	~Light();
};

