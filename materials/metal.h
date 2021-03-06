#ifndef GUI_METAL_H
#define GUI_METAL_H

#include "render/vector3.h"
#include "materials/material.h"

namespace gui {
	class Metal : public Material {
	public:
		Metal() {}

		Metal(const Vector3& albedo, float fuzzy = 0): albedo(albedo), fuzzy(fuzzy)
		{ }

		bool scatter(
			const Ray& in,
			const Intersection& intersection,
			Vector3& attenuation,
			Ray& scattered,
			bool& light
		) const override;

	public:
		Vector3 albedo;
		float fuzzy;
	};
}

#endif