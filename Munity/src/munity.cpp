#include "opengl/opengl.h"

#include "munity/global.h"
#include "munity/input.h"
#include "munity/model.h"
#include "munity/light.h"
#include "munity/text.h"
#include "munity/game_objects.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

using namespace munity;

int main(int argc, char* argv[])
{
	global::initialize("munity v0.0.1", 1600, 900);
	GLFWwindow* window = opengl::initialize();
	camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	input::initialize(window, camera);
	text::initialize();
	light::initialize();

	point_light pointLight(glm::vec3(1.2f, 1.0f, 2.0f));

/*
	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	game_object* cube = game_object::light_cube();

	//model model(FileSystem::getPath)

	// texture
	texture tex("Res/Textures/container2.png", GL_TEXTURE_2D, GL_RGB, GL_RGBA);
	texture spe("Res/Textures/container2_specular.png", GL_TEXTURE_2D, GL_RGB, GL_RGBA);

	// light
	shader phongShader("Res/Shaders/phong.vert", "Res/Shaders/phong.frag");
	shader lampShader("Res/Shaders/lamp.vert", "Res/Shaders/lamp.frag");

	phongShader.use();
	phongShader.setMat4("projection", projection);
	phongShader.setInt("material.diffuse", 0);
	phongShader.setInt("material.specular", 1);
	phongShader.setFloat("material.shininess", 32.0f);
	// directional light
	phongShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	phongShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	phongShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	phongShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
	// point light 1
	phongShader.setVec3("pointLights[0].position", pointLightPositions[0]);
	phongShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
	phongShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
	phongShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
	phongShader.setFloat("pointLights[0].constant", 1.0f);
	phongShader.setFloat("pointLights[0].linear", 0.09);
	phongShader.setFloat("pointLights[0].quadratic", 0.032);
	// point light 2
	phongShader.setVec3("pointLights[1].position", pointLightPositions[1]);
	phongShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
	phongShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
	phongShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
	phongShader.setFloat("pointLights[1].constant", 1.0f);
	phongShader.setFloat("pointLights[1].linear", 0.09);
	phongShader.setFloat("pointLights[1].quadratic", 0.032);
	// point light 3
	phongShader.setVec3("pointLights[2].position", pointLightPositions[2]);
	phongShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
	phongShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
	phongShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
	phongShader.setFloat("pointLights[2].constant", 1.0f);
	phongShader.setFloat("pointLights[2].linear", 0.09);
	phongShader.setFloat("pointLights[2].quadratic", 0.032);
	// point light 4
	phongShader.setVec3("pointLights[3].position", pointLightPositions[3]);
	phongShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
	phongShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
	phongShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
	phongShader.setFloat("pointLights[3].constant", 1.0f);
	phongShader.setFloat("pointLights[3].linear", 0.09);
	phongShader.setFloat("pointLights[3].quadratic", 0.032);
	// spotLight
	phongShader.setVec3("spotLight.position", camera.Position);
	phongShader.setVec3("spotLight.direction", camera.Front);
	phongShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
	phongShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
	phongShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
	phongShader.setFloat("spotLight.constant", 1.0f);
	phongShader.setFloat("spotLight.linear", 0.09);
	phongShader.setFloat("spotLight.quadratic", 0.032);
	phongShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	phongShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
*/
	//text sampleText("This is sample text", glm::vec3(150.0, 150.0f, 0.0f),
	//				  glm::vec3(0.0f), glm::vec3(0.5f), glm::vec4(0.3f, 0.7f, 0.9f, 1.0f));
	//shader textShader("res/shaders/text.vert", "res/shaders/text.frag");
	//shader depthShader("res/shaders/depth.vert", "res/shaders/depth.frag");
	shader phongShader("res/shaders/phong.vert", "res/shaders/phong.frag");
	shader grassShader("res/shaders/grass.vert", "res/shaders/grass.frag");
	texture grassTex("Res/Textures/window.png", GL_TEXTURE_2D, GL_RGBA, GL_RGBA, true);

	model nanosuit("res/models/nanosuit/nanosuit.obj");
	nanosuit.position = glm::vec3(0.0f, -1.75f, 0.0f);
	nanosuit.scale = glm::vec3(0.2f, 0.2f, 0.2f);

	quad grass(glm::vec3(0.0f, 0.0f, 1.0f));

	button btn(100, 100, 200, 60, "This is a button");

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	glClearColor(0.1176f, 0.1176f, 0.1176f, 1.0f);
	glPolygonMode(GL_FRONT, GL_FILL); // GL_LINE

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_NOTEQUAL, 1, 0xff);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	
//	unsigned int fbo;
//	glGenFramebuffers(1, &fbo);
//	
//	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
//	
//	// todo framebuffer
//	unsigned int mainScreen;
//	glGenTextures(1, &mainScreen);
//	glBindTexture(GL_TEXTURE_2D, mainScreen);
//	// color attachment
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, global::appWidth, global::appHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mainScreen, 0);
//	// depth&&stencil attachment
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, global::appWidth, global::appHeight, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, mainScreen, 0);
//
//	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
//	{
//		
//	}
//
//	// todo rbo
//	unsigned int rbo;
//	glGenRenderbuffers(1, &rbo);
//	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
//
//	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, global::appWidth, global::appHeight);
//
//	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	while (opengl::Running())
	{
		time::calcDelta();
		input::processing();
		camera.updateview();
		light::configlights();
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		// diffuse objects
		nanosuit.renderer(phongShader);

	/*
		for (int i = 0; i < 4; i++)
		{
			glm::mat4 model;
			lightCube->renderer(lampShader, pointLightPositions[i], 0.0f, glm::vec3(1.0f, 0.3f, 0.5f));
			lampShader.setMat4("view", camera.GetViewMatrix());
			phongShader.setMat4("model", model);
		}		

		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model;
			float angle = 20.0f * i;
		
			tex.bind(0);
			spe.bind(1);
			cube->renderer(phongShader, cubePositions[i], glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			phongShader.setMat4("view", camera.GetViewMatrix());
			phongShader.setVec3("viewPos", camera.Position);
			phongShader.setVec3("lightPos", lightPos);
			phongShader.setMat4("model", model);
			//phongShader.setVec3("light.position", camera.Position);
			//phongShader.setVec3("light.direction", camera.Front);
			phongShader.setVec3("spotLight.position", camera.Position);
			phongShader.setVec3("spotLight.direction", camera.Front);
		}
	*/

		// transparent objects
		glDisable(GL_CULL_FACE);
		grassTex.bind(0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		grass.renderer(grassShader);
		glEnable(GL_CULL_FACE);

		// lights
		light::rendererlights();

		// ui
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		btn.renderer();
		//glClear(GL_DEPTH_BUFFER_BIT);
		//sampleText.renderer();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//glDeleteFramebuffers(1, &fbo);
	opengl::Clear();

	return 0;
}
