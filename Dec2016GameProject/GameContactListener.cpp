#include "GameContactListener.h"



GameContactListener::GameContactListener()
	:b2ContactListener()
{
	buoyancyController = BuoyancyController::create();
}


GameContactListener::~GameContactListener()
{
	delete buoyancyController;
	buoyancyController = NULL;

}

void GameContactListener::BeginContact(b2Contact * contact)
{
	buoyancyController->BeginContact(contact);

	b2Fixture*fixtureA = contact->GetFixtureA();
	b2Fixture*fixtureB = contact->GetFixtureB();
	void* userDataA = fixtureA->GetBody()->GetUserData();
	void* userDataB = fixtureB->GetBody()->GetUserData();
	
	if (userDataA&&userDataB) {
		if (((ObjectData*)userDataA)->ID == SomeDefine::MOVERID) {
			if(((ObjectData*)userDataB)->ID == SomeDefine::SURFACE_BRICK_ID)
				((Mover*)(((ObjectData*)userDataA)->pointer))->setOnGround(true);
			if(((ObjectData*)userDataB)->ID == SomeDefine::MONSTER_TOMATO)
				((Mover*)(((ObjectData*)userDataA)->pointer))->die();
			if (((ObjectData*)userDataB)->ID == SomeDefine::VALLEY_ID) 
				fixturePairs.insert(std::make_pair(fixtureB, fixtureA));
			if(((ObjectData*)userDataB)->ID == SomeDefine::LIGHTNING_KILLER)
				((Mover*)(((ObjectData*)userDataA)->pointer))->die();
			if(((ObjectData*)userDataB)->ID == SomeDefine::BIRD_ID)
				((Mover*)(((ObjectData*)userDataA)->pointer))->die();
			if(((ObjectData*)userDataB)->ID == SomeDefine::FISH_ID)
				((Mover*)(((ObjectData*)userDataA)->pointer))->die();
			if(((ObjectData*)userDataB)->ID == SomeDefine::GEARKILLER_ID)
				((Mover*)(((ObjectData*)userDataA)->pointer))->die();
			else if(((ObjectData*)userDataB)->ID == SomeDefine::PHOTON_LAZER_ID)
			{
				((Mover*)(((ObjectData*)userDataA)->pointer))->die();
				((Photon*)(((ObjectData*)userDataB)->pointer))->collapse();
			}
			else if(((ObjectData*)userDataB)->ID == SomeDefine::DESTINATION_ID)
				((LevelManager*)(((ObjectData*)userDataB)->pointer))->setNextLevel();
				
				
		
		}
		if (((ObjectData*)userDataB)->ID == SomeDefine::MOVERID) {
			if(((ObjectData*)userDataA)->ID == SomeDefine::SURFACE_BRICK_ID)
				((Mover*)(((ObjectData*)userDataB)->pointer))->setOnGround(true);
			else if(((ObjectData*)userDataA)->ID == SomeDefine::MONSTER_TOMATO)
				((Mover*)(((ObjectData*)userDataB)->pointer))->die();
			else if (((ObjectData*)userDataA)->ID == SomeDefine::VALLEY_ID) 
				fixturePairs.insert(std::make_pair(fixtureA, fixtureB));
			else if(((ObjectData*)userDataA)->ID == SomeDefine::LIGHTNING_KILLER)
				((Mover*)(((ObjectData*)userDataB)->pointer))->die();
			else if(((ObjectData*)userDataA)->ID == SomeDefine::BIRD_ID)
				((Mover*)(((ObjectData*)userDataB)->pointer))->die();
			else if(((ObjectData*)userDataA)->ID == SomeDefine::FISH_ID)
				((Mover*)(((ObjectData*)userDataB)->pointer))->die();
			else if(((ObjectData*)userDataA)->ID == SomeDefine::GEARKILLER_ID)
				((Mover*)(((ObjectData*)userDataB)->pointer))->die();
			else if(((ObjectData*)userDataA)->ID == SomeDefine::PHOTON_LAZER_ID)
			{
				((Mover*)(((ObjectData*)userDataB)->pointer))->die();
				((Photon*)(((ObjectData*)userDataA)->pointer))->collapse();
			}
			else if(((ObjectData*)userDataA)->ID == SomeDefine::DESTINATION_ID)
				((LevelManager*)(((ObjectData*)userDataA)->pointer))->setNextLevel();
		}
		

		if (((ObjectData*)userDataA)->ID == SomeDefine::MOVER_LIGHTNING) {
			if(((ObjectData*)userDataB)->ID == SomeDefine::MONSTER_TOMATO)
				((Monster*)(((ObjectData*)userDataB)->pointer))->die();
			if(((ObjectData*)userDataB)->ID == SomeDefine::BIRD_ID)
				((Bee*)(((ObjectData*)userDataB)->pointer))->die();
			
		}
		if (((ObjectData*)userDataB)->ID == SomeDefine::MOVER_LIGHTNING) {
			if(((ObjectData*)userDataA)->ID == SomeDefine::MONSTER_TOMATO)
				((Monster*)(((ObjectData*)userDataA)->pointer))->die();
			if(((ObjectData*)userDataA)->ID == SomeDefine::BIRD_ID)
				((Bee*)(((ObjectData*)userDataA)->pointer))->die();
			
		}

		if (((ObjectData*)userDataA)->ID == SomeDefine::PHOTON_LAZER_ID) {
			if(((ObjectData*)userDataB)->ID == SomeDefine::SURFACE_BRICK_ID||
				((ObjectData*)userDataB)->ID == SomeDefine::UNDERGROUND_BRICK_ID)
				((Photon*)(((ObjectData*)userDataA)->pointer))->collapse();
			if(((ObjectData*)userDataB)->ID == SomeDefine::REFLECTOR_ID)
				((Relector*)(((ObjectData*)userDataB)->pointer))->reflect(
					*(Photon*)(((ObjectData*)userDataA)->pointer));
				
						
		}
		
		if (((ObjectData*)userDataB)->ID == SomeDefine::PHOTON_LAZER_ID) {
			if(((ObjectData*)userDataA)->ID == SomeDefine::SURFACE_BRICK_ID||
				((ObjectData*)userDataA)->ID == SomeDefine::UNDERGROUND_BRICK_ID)
				((Photon*)(((ObjectData*)userDataB)->pointer))->collapse();
			if(((ObjectData*)userDataA)->ID == SomeDefine::REFLECTOR_ID)
				((Relector*)(((ObjectData*)userDataA)->pointer))->reflect(
					*(Photon*)(((ObjectData*)userDataB)->pointer));

		}

	}
	
}

void GameContactListener::EndContact(b2Contact * contact)
{

	buoyancyController->EndContact(contact);

	b2Fixture*fixtureA = contact->GetFixtureA();
	b2Fixture*fixtureB = contact->GetFixtureB();
	void* userDataA = fixtureA->GetBody()->GetUserData();
	void* userDataB = fixtureB->GetBody()->GetUserData();


	if (userDataA&&userDataB) {
		
		if (((ObjectData*)userDataA)->ID == SomeDefine::MOVERID) {
			if(((ObjectData*)userDataB)->ID == SomeDefine::SURFACE_BRICK_ID)
				((Mover*)(((ObjectData*)userDataA)->pointer))->setOnGround(false);
			if (((ObjectData*)userDataB)->ID == SomeDefine::VALLEY_ID)
				fixturePairs.erase(std::make_pair(fixtureB, fixtureA));

		}
		if (((ObjectData*)userDataB)->ID == SomeDefine::MOVERID) {
			if(((ObjectData*)userDataA)->ID == SomeDefine::SURFACE_BRICK_ID)
				((Mover*)(((ObjectData*)userDataB)->pointer))->setOnGround(false);
			if (((ObjectData*)userDataA)->ID == SomeDefine::VALLEY_ID)
				fixturePairs.erase(std::make_pair(fixtureA, fixtureB));

		}
		
		
	}

}

void GameContactListener::PreSolve(b2Contact * contact, const b2Manifold * oldManifold)
{

	//go through all buoyancy fixture pairs and apply necessary forces
	std::set<FixturePair>::iterator it = fixturePairs.begin();
	std::set<FixturePair>::iterator end = fixturePairs.end();
	while (it != end) {

		//fixtureA is the fluid
		b2Fixture* fixtureA = it->first;
		b2Fixture* fixtureB = it->second;
		void*userDataA = fixtureA->GetBody()->GetUserData();
		void*userDataB = fixtureB->GetBody()->GetUserData();
		if (userDataA&&userDataB) {
			//printf("keep track mover.\n");
			if (((ObjectData*)userDataB)->ID == SomeDefine::MOVERID)
				((GroupOfDarkCloud*)((ObjectData*)userDataA)->pointer)->findOut(
					*((Mover*)((ObjectData*)userDataB)->pointer)->getPosition());

		}

		++it;
	}

}

void GameContactListener::PostSolve(b2Contact * contact, const b2ContactImpulse * impulse)
{


}
void GameContactListener::step()
{
	buoyancyController->step();
}
