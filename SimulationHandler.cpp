#include "SimulationHandler.h"
#include "SpatialHash.h"
#include "Ball.h"
#include "Utils.h"

SimulationHandler::SimulationHandler(sf::RenderWindow& rw, std::unique_ptr<CollisionDetector>&& cd) :
	entities_(),
	randomGen_(std::random_device()()),// set random seed
	random_(0.f,1.f) // set range of values
{
	rw_ = &rw;
	collisionDetector_ = std::move(cd);

	// @TODO: Generate N balls at random places
	// Add an initial object
	/*std::unique_ptr<Shape> pShape = std::make_unique<Ball>(sf::Vector2f({ 120,230 }));
	entities_.push_back(collisionDetector_->addEntity(pShape));
	entities_.back()->getShape()->applyForce({ 10, 0 });*/

	for (size_t i = 0; i < 5; i++)
	{
		const float randomY = 230 + this->getRandom() * 200.f;
		const float randomX = 120 + this->getRandom() * 200.f;

		// Add a new ball
		std::unique_ptr<Shape> pShape = std::make_unique<Ball>(sf::Vector2f({ randomX, randomY }));
		entities_.push_back(collisionDetector_->addEntity(pShape));
		entities_.back()->getShape()->applyForce({ 10, 0 });
	}
	
}

void SimulationHandler::processEvents()
{
	sf::Event event;
	while (rw_->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			rw_->close();
		else if (event.type == event.KeyReleased && event.key.code == sf::Keyboard::Q)
			rw_->close();
		else if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {

			for (size_t i = 0; i < 10; i++)
			{
				const float randomY = 230 + this->getRandom() * 200.f;
				const float randomX = 120 + this->getRandom() * 200.f;

				// Add a new ball
				std::unique_ptr<Shape> pShape = std::make_unique<Ball>(sf::Vector2f({ randomX, randomY}));
				entities_.push_back(collisionDetector_->addEntity(pShape));
				entities_.back()->getShape()->applyForce({ 10, 0 });
			}

		}

	}
}

void SimulationHandler::update(sf::Time dt)
{
	for (auto& entity : entities_) {
		entity->getShape()->update(dt);
		collisionDetector_->updateEntity(entity);
	}
}

void SimulationHandler::render()
{
	rw_->clear(sf::Color::White);
	collisionDetector_->show(*rw_);

	for (auto& entity : entities_) {
		entity->getShape()->show(*rw_);
	}

	rw_->display();
}

double SimulationHandler::getRandom()
{
	return this->random_(this->randomGen_);
}
