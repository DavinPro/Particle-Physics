#ifndef QUADTREE_H
#define	QUADTREE_H

#include <list>
#include <vector>
#include <memory>

#include "rectangle.hpp"
#include "particle.h"

template <typename T, typename RectType = float>
class QuadTree {

	static_assert(std::is_arithmetic_v<RectType>, "RectType must be an arithmetic type.");

	static const uint16_t CAP = 6;

public:
	QuadTree()
		: boundBox(Rectangle<RectType>(0, 0, 0, 0)) {}

	QuadTree(Rectangle<RectType> boundBox) 
		: boundBox(boundBox) {}

	bool insert(T& t) {
		if (!boundBox.contains(t.pos))
			return false;

		if (values.size() < CAP) {
			values.push_back(&t);
			return true;
		}

		if (!nodes[0])
			subdivide();

		for (int i = 0; i < 4; i++) {
			if (nodes[i]->insert(t))
				return true;
		}
		return false;
	}

	void query(std::vector<T*>& foundPs, const Rectangle<RectType>& rect) {
		if (!boundBox.intersects(rect))
			return;

		for (auto& v : values) {
			if (rect.contains(v->pos))
				foundPs.push_back(v);
		}

		if (nodes[0]) {
			for (auto& n : nodes)
				n->query(foundPs, rect);
		}
	}

	void getBoundBoxes(std::vector<Rectangle<RectType>>& boundBoxes) const {
		boundBoxes.push_back(boundBox);

		if (nodes[0]) {
			for (auto& n : nodes)
				n->getBoundBoxes(boundBoxes);
		}
	}

private:
	Rectangle<RectType> boundBox;

	std::list<T*> values;

	std::unique_ptr<QuadTree> nodes[4]{ nullptr };

	void subdivide() {
		nodes[0].reset(new QuadTree(Rectangle<RectType>(boundBox.left, boundBox.top, boundBox.width / 2, boundBox.height / 2)));
		nodes[1].reset(new QuadTree(Rectangle<RectType>(boundBox.left + boundBox.width/2, boundBox.top, boundBox.width / 2, boundBox.height / 2)));
		nodes[2].reset(new QuadTree(Rectangle<RectType>(boundBox.left, boundBox.top + boundBox.height/2, boundBox.width / 2, boundBox.height / 2)));
		nodes[3].reset(new QuadTree(Rectangle<RectType>(boundBox.left + boundBox.width / 2, boundBox.top + boundBox.height / 2, boundBox.width / 2, boundBox.height / 2)));

	}
};

#endif