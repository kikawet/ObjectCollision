#pragma once

#include "Entity.h"

class SpatialHashEntity : public Entity
{
public:
	struct Node {
		std::shared_ptr<SpatialHashEntity> entity = nullptr;
		std::shared_ptr<Node> prev = nullptr;
		std::shared_ptr<Node> next = nullptr;
	};

	SpatialHashEntity(std::unique_ptr<Shape>& s);

	inline void setTLIndex(const sf::Vector2i& index) { TLCell_ = index; };
	inline const sf::Vector2i& getTLIndex() { return TLCell_; };
	inline void setBRIndex(const sf::Vector2i& index) { BRCell_ = index; };
	inline const sf::Vector2i& getBRIndex() { return BRCell_; };
	inline void setNode(const size_t& index, const std::shared_ptr<Node> node) { nodes_[index] = node; };
	inline const std::shared_ptr<Node>& getNode(const size_t& index) { return nodes_[index]; };
	inline void reserveNodes(int newSize) { nodes_.resize(newSize, nullptr); }
	inline void clearNodes() { std::fill(nodes_.begin(), nodes_.end(), nullptr); };
	inline void setId(int id) { queryId_ = id; };
	inline int getId() { return queryId_; };


private:
	int queryId_;
	sf::Vector2i TLCell_;
	sf::Vector2i BRCell_;
	std::vector<std::shared_ptr<Node>> nodes_;
};

