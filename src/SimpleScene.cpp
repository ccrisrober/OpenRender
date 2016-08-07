#include "SimpleScene.h"

#include <cstdio>
#include <cstdlib>

#include <iostream>

#include <vector>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/constants.hpp"

SimpleScene::SimpleScene(int w, int h) : IScene(w, h) { }
SimpleScene::~SimpleScene() {
}

void SimpleScene::initScene() {
	compileAndLinkShader();
	glClearColor(0.5f,0.5f,0.5f,1.0f);

	cube = new Mesh("../models/cube.obj");

	for(int i = 0; i < 20; i++) {
		float r = ((float)( std::rand() % 1000)) * 0.001;
		float g = ((float)( std::rand() % 1000)) * 0.001;
		float b = ((float)( std::rand() % 1000)) * 0.001;
		float a = ((float)( std::rand() % 1000)) * 0.001;
		if(a >= 0.85) {
			a = 0.4;
		}
		colors.push_back(glm::vec4(r, g, b, a));
	}

	GLfloat verts[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f
	};
	GLuint bufHandle;
	glGenBuffers(1, &bufHandle);
	glBindBuffer(GL_ARRAY_BUFFER, bufHandle);
	glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(GLfloat), verts, GL_STATIC_DRAW);

	// Set up the vertex array object
	glGenVertexArrays(1, &fsQuad);
	glBindVertexArray(fsQuad);

	glBindBuffer(GL_ARRAY_BUFFER, bufHandle);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);  // Vertex position

	glBindVertexArray(0);

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}


void SimpleScene::update( float t ) {
	angle += 0.1 * t;
}

void SimpleScene::draw(Camera* camera) {
	prog.use();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	view = camera->GetViewMatrix();
	projection = camera->GetProjectionMatrix();

	// draw scene
	drawScene();

	prog.unuse();
}

void SimpleScene::updateMatrices() {
	glm::mat4 modelView = view * model;

	prog.send_uniform("normal", glm::mat3(glm::vec3(modelView[0]), glm::vec3(modelView[1]), glm::vec3(modelView[2])));
	prog.send_uniform("modelView", modelView);
	prog.send_uniform("modelViewProj", projection * modelView);
}

void SimpleScene::resize(int w, int h) {
	glViewport(0, 0, w, h);
	width = w;
	height = h;
}

void SimpleScene::compileAndLinkShader() {
	prog.load("../shaders/shader.vert", GL_VERTEX_SHADER);
	prog.load("../shaders/shader.frag", GL_FRAGMENT_SHADER);
	prog.compile_and_link();
	prog.add_uniform("normal");
	prog.add_uniform("modelView");
	prog.add_uniform("modelViewProj");
	prog.add_uniform("Kd");
}

void SimpleScene::drawScene() {
	int n = 0;
	int m = -1;
	float size = 0.025f;

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, cube->texture);
	glUniform1i(glGetUniformLocation(prog.program(), "texImage"), 1);

	for( int i = 0; i < 3; i++ ) {
		for( int j = 0; j < 3; j++ ) {
			for( int k = 0; k < 6; k++ ) {
				m *= -1;
				vec4 kd = colors[n++ % colors.size()];
				prog.send_uniform("Kd", kd);
				model = glm::translate(mat4(1.0f), vec3(i*2, j*2, k));
				model = glm::rotate(model, glm::radians(-angle), glm::vec3(0, 1, 0));
				model = glm::scale(model, glm::vec3(size));
				updateMatrices();
				cube->render();


				/*glBindVertexArray(fsQuad);
				glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
				glBindVertexArray(0);*/
			}
		}
	}
}
