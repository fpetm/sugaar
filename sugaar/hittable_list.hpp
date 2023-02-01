#pragma once

#include "hittable.hpp"

namespace sugaar {
	class HittableList : public Hittable {
	public:
		HittableList() {}
		HittableList(std::shared_ptr<Hittable> object) { add(object); }
		
		void clear() { objects.clear(); }
		void add(std::shared_ptr<Hittable> obj) { objects.push_back(obj); }

		virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;


	public:
		std::vector<std::shared_ptr<Hittable>> objects;
	};

	bool HittableList::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
		HitRecord temp_rec;
		bool hit_anything = false;
		double closest_so_far = t_max;

		for (const auto& object : objects) {
			if (object->hit(r, t_min, closest_so_far, temp_rec)) {
				hit_anything = true;
				closest_so_far = temp_rec.t;
				rec = temp_rec;
			}
		}
		return hit_anything;
	}
}