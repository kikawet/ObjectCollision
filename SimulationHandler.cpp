#include "SimulationHandler.h"
#include "SpatialHash.h"
#include "Ball.h"

SimulationHandler::SimulationHandler(sf::RenderWindow& rw, std::unique_ptr<CollisionDetector>&& cd):
	//rw_(rw)
	shapes_(),
	entities_()
{
	rw_ = &rw;
	collisionDetector_ = std::move(cd);

	// Add an initial object
	// @TODO remove this temp code
	shapes_.emplace_back(std::make_unique<Ball>(sf::Vector2f({ 120,230 })));
	entities_.push_back(collisionDetector_->addEntity(shapes_.back()));
	entities_.back()->getShape()->applyForce({ 10, 0 });
	//entities_.back()->getShape()->show(*rw_);
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
			
			// Add a new ball
			shapes_.emplace_back(std::make_unique<Ball>(sf::Vector2f({ 120,230 })));
			entities_.push_back(collisionDetector_->addEntity(shapes_.back()));
			entities_.back()->getShape()->applyForce({ 10, 0 });
			//entities_.back()->getShape()->show(*rw_);
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
		//entity->getShape()->update(1.f / 60);
		//collisionDetector_->updateEntity(entity);
		entity->getShape()->show(*rw_);
	}

	rw_->display();
}
