#ifndef GUI_RENDERER_H
#define GUI_RENDERER_H

namespace gui {
	class Scene;
	class Camera;

	class Renderer {
	public:
		Renderer(int samples) : 
			samples(samples), 
			maxDepth(30),
			maxT(10000)
		{ }

		void render(const Scene& scene, Camera& camera) const;
		Vector3 radiance(const Ray& ray, const Scene& scene, int depth) const;

	public:
		int samples;
		int maxDepth;
		int maxT;

	public:
		void onRendering(void);
		void onEveryLine(float percent);
		void onEndRendering(void);
		float pastTime;
	};
}

#endif
