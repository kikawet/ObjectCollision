#include "SpatialHash.h"

SpatialHash::SpatialHash(const sf::Vector2f& bMin, const sf::Vector2f& bMax, const sf::Vector2i& dimensions) :
	cells_(dimensions.x* dimensions.y, nullptr),
	dimensions_(dimensions),
	boundsMin_(bMin),
	boundsMax_(bMax),
	queryIds_(0)
{
}

SpatialHash::~SpatialHash()
{
}

std::shared_ptr<Entity> SpatialHash::addEntity(std::unique_ptr<Shape>& s)
{
	std::shared_ptr<SpatialHashEntity> client = std::make_shared<SpatialHashEntity>(s);

	this->insert(client);

	return client;
}

bool SpatialHash::updateEntity(const std::shared_ptr<Entity>& e)
{
	std::shared_ptr<SpatialHashEntity> she = std::dynamic_pointer_cast<SpatialHashEntity>(e);

	const sf::FloatRect& aabb = e->getBounds();

	const sf::Vector2i& indexTL = this->getCellIndex({ aabb.left , aabb.top });
	const sf::Vector2i& indexBR = this->getCellIndex({ aabb.left + aabb.width, aabb.top + aabb.height });


	if (she->getTLIndex() == indexTL && she->getBRIndex() == indexBR)
		return false;

	this->removeEntity(e);
	this->insert(she);

	return true;
}

std::vector<std::shared_ptr<Entity>> SpatialHash::detectCollision(const std::shared_ptr<Entity>& s)
{
	std::vector<std::shared_ptr<Entity>> result;

	const sf::Vector2f& position = s->getPosition();
	const float h = s->getBounds().height;
	const float w = s->getBounds().width;

	const sf::Vector2i topLeft = getCellIndex({ position.x - w / 2,position.y - h / 2 });
	const sf::Vector2i bottomRigh = getCellIndex({ position.x + w / 2,position.y + h / 2 });

	const int queryId = ++this->queryIds_;

	for (int x = topLeft.x; x <= bottomRigh.x; ++x)
	{
		for (int y = topLeft.y; y <= bottomRigh.y; ++y) {
			auto head = cells_[x * dimensions_.x + y];

			while (head)
			{
				const auto& v = head->entity;
				head = head->next;

				if (v->getId() != queryId)
				{
					v->setId(queryId);
					result.push_back(v);
				}
			}
		}
	}

	return result;
}

bool SpatialHash::removeEntity(const std::shared_ptr<Entity>& e)
{
	std::shared_ptr<SpatialHashEntity> she = std::dynamic_pointer_cast<SpatialHashEntity>(e);

	if (she->getTLIndex().x == -1)
		return false;

	const sf::Vector2i& indexTL = she->getTLIndex();
	const sf::Vector2i& indexBR = she->getBRIndex();
	int relativeIndex = 0;

	for (int x = indexTL.x; x <= indexBR.x; ++x) {
		for (int y = indexTL.y; y <= indexBR.y; ++y) {
			const int index = x * this->dimensions_.x + y;
			const auto& node = she->getNode(relativeIndex);

			if (node->next)
				node->next->prev = node->prev;

			if (node->prev)
				node->prev->next = node->next;

			if (!node->prev)
				this->cells_[index] = node->next;

			she->setNode(relativeIndex, nullptr);
			++relativeIndex;
		}
	}

	she->setTLIndex({ -1,-1 });
	she->setBRIndex({ -1,-1 });
	//she->clearNodes();

	return true;
}

void SpatialHash::show(sf::RenderWindow& rw)
{
	sf::RectangleShape outline;
	const float lineThickness = 2.f;
	const sf::Vector2f vlThick = sf::Vector2f(lineThickness, lineThickness);

	outline.setSize((boundsMax_ - boundsMin_) - vlThick * 2.f);
	outline.setPosition(boundsMin_ + vlThick);
	outline.setOutlineColor(sf::Color::Red);
	outline.setOutlineThickness(lineThickness);

	sf::RectangleShape line;
	line.setFillColor(sf::Color::Red);

	line.setSize(sf::Vector2f(lineThickness, outline.getSize().y));
	line.setPosition(outline.getPosition());
	rw.draw(outline);

	for (size_t x = 0; x < dimensions_.x - 1; ++x)
	{
		line.move(sf::Vector2f(outline.getSize().x / dimensions_.x, 0));
		rw.draw(line);
	}

	line.setSize(sf::Vector2f(outline.getSize().x, lineThickness));
	line.setPosition(outline.getPosition());

	for (size_t y = 0; y < dimensions_.y - 1; ++y) {
		line.move(sf::Vector2f(0, outline.getSize().y / dimensions_.y));
		rw.draw(line);
	}

	sf::RectangleShape cell;
	const sf::Vector2f size = sf::Vector2f(
		(boundsMax_.x - boundsMin_.x) / dimensions_.x,
		(boundsMax_.y - boundsMin_.y) / dimensions_.y
	);

	cell.setSize(size);
	cell.setFillColor(sf::Color(0, 0, 255, 128));

	for (size_t x = 0; x < dimensions_.x; ++x)
	{
		for (size_t y = 0; y < dimensions_.y; ++y) {
			size_t current = x * dimensions_.x + y;

			if (cells_[current]) {
				const sf::Vector2f offset = sf::Vector2f(
					size.x * x,
					size.y * y
				);

				cell.setPosition(boundsMin_ + offset + vlThick);

				auto head = cells_[current];

				while (head) {
					rw.draw(cell);
					head = head->next;
				}
			}
		}
	}
}

inline float clamp(float v, float min, float b) {
	return v < min ? min : (v > b ? b : v);
}

sf::Vector2i SpatialHash::getCellIndex(const sf::Vector2f& pos)
{
	float x = clamp((pos.x - this->boundsMin_.x) / (this->boundsMax_.x - this->boundsMin_.x), 0.f, 1.f);
	float y = clamp((pos.y - this->boundsMin_.y) / (this->boundsMax_.y - this->boundsMin_.y), 0.f, 1.f);

	int xi = static_cast<int>(floor(x * (this->dimensions_.x - 1)));
	int yi = static_cast<int>(floor(y * (this->dimensions_.y - 1)));

	return sf::Vector2i(xi, yi);
}

bool SpatialHash::insert(const std::shared_ptr<SpatialHashEntity>& she)
{
	if (!containsEntity(she))
		return false;

	const sf::FloatRect& aabb = she->getBounds();

	const sf::Vector2i indexTL = getCellIndex({ aabb.left, aabb.top });
	const sf::Vector2i indexBR = getCellIndex({ aabb.left + aabb.width, aabb.top + aabb.height });

	const sf::IntRect gridDimensions(indexTL.x, indexTL.y, indexBR.x - indexTL.x + 1, indexBR.y - indexTL.y + 1);

	she->reserveNodes(gridDimensions.width * gridDimensions.height);
	int index = 0;

	for (int x = indexTL.x; x <= indexBR.x; ++x)
	{
		for (int y = indexTL.y; y <= indexBR.y; ++y)
		{
			const int current = x * this->dimensions_.x + y;
			std::shared_ptr<SpatialHashEntity::Node> head = std::make_shared<SpatialHashEntity::Node>();

			head->entity = she;
			she->setNode(index++, head);
			head->next = this->cells_[current];

			if (this->cells_[current])
				this->cells_[current]->prev = head;

			this->cells_[current] = head;
		}
	}

	she->setTLIndex(indexTL);
	she->setBRIndex(indexBR);

	return true;
}

bool SpatialHash::containsEntity(const std::shared_ptr<SpatialHashEntity>& she)
{
	const sf::FloatRect aabb = she->getBounds();
	const sf::FloatRect outline(
		this->boundsMin_, // Position
		{ this->boundsMax_ - this->boundsMin_ } // Size
	);

	return outline.intersects(aabb);
}
