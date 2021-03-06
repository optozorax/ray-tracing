#include "render/math.h"
#include "render/film.h"
#include "render/camera.h"
#include "render/renderer.h"

#include "objects/all.h"
#include "materials/all.h"

using namespace gui;

float myrandom() {
	static std::mt19937 generator(1);
	static std::uniform_real_distribution<float> distribution(0, 1);
	return distribution(generator);
}


void initScene(Scene& scene) {
	auto& shapes = scene.shapes;
	shapes.push_back(new Sky());

	for(int i = -11; i < 11; ++i) {
		for(int j = -11; j < 11; ++j) {
			Vector3 c(i + 0.9f * myrandom(), 0.2f, j + 0.9f * myrandom());
			float p = myrandom();
			if(p < 0.8f) {
				shapes.push_back(new Sphere(c, 0.2f, new Diffuse(Vector3(myrandom(), myrandom(), myrandom()))));
			} else if(p < 0.95f) {
				float r = 0.5f * (1 + myrandom());
				float g = 0.5f * (1 + myrandom());
				float b = 0.5f * (1 + myrandom());
				shapes.push_back(new Sphere(c, 0.2f, new Metal(Vector3(r, g, b), 0.5f * myrandom())));
			} else {
				shapes.push_back(new Sphere(c, 0.2f, new Dielectric(1.5f)));
			}
		}
	}
	shapes.push_back(new Sphere(Vector3(0, 1, 0), 1, new Dielectric(1.5f)));
	shapes.push_back(new Sphere(Vector3(-4, 1, 0), 1, new Diffuse(Vector3(0.4f, 0.2f, 0.1f))));
	shapes.push_back(new Sphere(Vector3(4, 1, 0), 1, new Metal(Vector3(0.7f, 0.6f, 0.5f))));
	shapes.push_back(new Sphere(Vector3(0, -1000, 0), 1000, new Diffuse(Vector3(0.5f))));
}

int main() {
	Scene scene;
	initScene(scene);

	Film film(1024, 576);

	Camera camera(film, 20, 0.1f, 12);
	camera.position = Vector3(12, 2, 3);
	camera.lookAt(Vector3(0, 1, 0));

	Renderer renderer(2);
	renderer.render(scene, camera);

	film.gammaCorrection();
	film.writeBMP("image1.bmp");

	return 0;
}