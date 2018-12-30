#include "SimpleTimer.h"
#include "GraveyardLevel.h"
#include "ShaderManager.h"
#include "Layer.h"
#include "Label.h"
#include "Sprite.h"
#include "BatchRenderer.h"
#include "TextureManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Group.h"
#include "TileMap.h"
#include "HeroEntity.h"
#include <iostream>
#include "glfw3.h"
#include "SkeletonEntity.h"
#include "GhostEntity.h"
#include "HellCatEntity.h"
#include "Entity.h"
#include "EyeMonsterEntity.h"
#include "DemonEntity.h"
#include "AnimatedSprite.h"
#include "MessageDispatcher.h"
#include "Messages.h"
#include "EntityManager.h"
#include "Entity.h"
#include "FireGolemEntity.h"
#include "GhoulEntity.h"
#include "UndeadWarriorEntity.h"
#include "ReaperEntity.h"
#include "ImpEntity.h"
#include "NecromancerEntity.h"
#include "CollisionManager.h"
#include "BaseProjectileEntity.h"
#include "NecromancerProjectile.h"
#include "ImpProjectile.h"
#include "AdventurerProjectile.h"
#include "AdventurerProjectileArrow.h"
#include "CollisionManager.h"
#include "Effect.h"
#include "HitEffectSprite.h"
#include "DynamicLayer.h"
#include "PotionPickup.h"
#include "PotionSprite.h"
#include "PickupDestroyedSprite.h"
#include "BloodEffectSprite.h"
#include "EnemyHitEffectSprite.h"
#include "SwordHitEffectSprite.h"
#include "AdventurerSlideEffectSprite.h"
#include "AdventurerDropKickEffectSprite.h"
#include "TiledMapManager.h"
#include "EffectsGroup.h"

void GraveyardLevel::Initialize()
{
	lastX = 640.0f;
	lastY = 360.0f;
	myHeight = 720.0f;
	myWidth = 1280.0f;
	myMouseMovement = false;

	glm::mat4 ortho = glm::ortho(-320.0f - 64, 320.0f + 64, -180.0f - 36, 180.0f + 36, -100.0f, 100.0f);
	myCamera = new Camera(666, "Camera1");
	myCamera->setScreenPosition(glm::vec2(lastX, lastY));
	myCamera->setProjectionMatrix(ortho);
	myCamera->setWidth(myWidth);
	myCamera->setHeight(myHeight);
	EntityMan->registerEntity(myCamera);

	myShader = ShaderMan->getShader(SIMPLE_GRAVEYARD_SHADER);

	myTileLayer = new Layer(new BatchRenderer(), myShader, glm::ortho(-320.0f - 64, 320.0f + 64, -180.0f - 36, 180.0f + 36, -100.0f, 100.0f));

	//Moon
	myMoonBackground = new Sprite(glm::vec4(0, 0, -99.0f, 1), glm::vec2(768.0f, 432.0f), TextureMan->GetTexture("moonbackground"));
	myTileLayer->Add(myMoonBackground);
	//Mountain
	myMountainBackground = new Sprite(glm::vec4(0, -108, -98.0f, 1), glm::vec2(768.0f, 432.0f), TextureMan->GetTexture("mountains"));
	myMountainBackground->setUVSpecialized(glm::vec2(0, 0), glm::vec2(0, 1), glm::vec2(2, 1), glm::vec2(2, 0));
	myTileLayer->Add(myMountainBackground);
	//Background
	myGraveyardBackground = new Sprite(glm::vec4(0, -108, -97.0f, 1), glm::vec2(768.0f, 216.0f), TextureMan->GetTexture("graveyard"));
	myTileLayer->Add(myGraveyardBackground);


	myPlayer = new HeroEntity(0, "Player");
	myNumberOfEntities = 2;
	myEntitites.push_back(myPlayer);
	for (Entity* entity : myEntitites)
	{
		EntityMan->registerEntity(entity);
	}

	Group* fpsGroup = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(260, 160, 0.8)));
	myFPSLabel = new Label("", glm::vec4(-55, -10, 0, 1), "DefaultFont32", glm::vec4(0, 1, 0, 1));
	fpsGroup->Add(new Sprite(glm::vec4(0, 0, -0.1, 1), glm::vec2(120.5f, 40.5f), glm::vec4(0.2f, 0.2f, 0.2f, 0.9)));
	fpsGroup->Add(myFPSLabel);

	myTileLayer->Add(fpsGroup);



	myMap = new TileMap("CemetaryMap", "CemetaryTileset");
	myMap->printMap();

	std::vector<Tile*> myPath3;
	myMap->GetPath(1, 1, 18, 10, myPath3);

	myMap->printPath(myPath3);
	myPlayer->mPosition.x = myMap->GetPlayerStartTile()->myWorldPosition.x;
	myPlayer->mPosition.y = myMap->GetPlayerStartTile()->myWorldPosition.y;
	myPlayer->myAABB->myOrigin = glm::vec2(myPlayer->mPosition.x, myPlayer->mPosition.y);
	myMap->setPlayerTile(myPlayer->mPosition.x, myPlayer->mPosition.y);
	myMap->SetPlayerTile2(myPlayer->myAABB);
	std::vector<Tile*> map = myMap->GetMap();

	propGroup = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -50)), -50);
	tileGroup = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -30)), -30);
	effectsGroupBack = new EffectsGroup(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0)), -1.0);
	effectsGroup = new EffectsGroup(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 10.0f)), 10.0f);


	myRenderGroups.push_back(propGroup);
	myRenderGroups.push_back(tileGroup);
	my…ffectsGroups.push_back(effectsGroupBack);
	my…ffectsGroups.push_back(effectsGroup);

	for(int i = 0 ; i < map.size(); i++)
	{
		if(map[i]->myTileType != "-1")
		{
			tileGroup->Add(new Sprite(glm::vec4(map[i]->myWorldPosition.x, map[i]->myWorldPosition.y, 0.0, 1), glm::vec2(32.0f, 32.0f), TextureMan->GetTexture("cemetarytileset"),std::stoi(map[i]->myTileType)));
		}
	}

	XMLMap* xmlMap = TiledMan->GetMap("CemetaryMap");
	XMLLayer* xmlLayer = xmlMap->GetLayer("Prop Layer");

	myMapWidth = std::stoi(xmlLayer->myWidth);
	myMapHeight = std::stoi(xmlLayer->myHeight);
	myCameraMinBoundX = 32.0f * 12.0f;
	myCameraMaxBoundX = ((myMapWidth) - 13.0f) * 32.0f;

	for(int i = 0 ; i < xmlLayer->myData.size(); i++)
	{
		if(xmlLayer->myData[i] != "0")
		{
			int tileIdentifier = std::stoi(xmlLayer->myData[i]) - 1;
			propGroup->Add(new Sprite(glm::vec4(map[i]->myWorldPosition.x, map[i]->myWorldPosition.y, 0.0, 1), glm::vec2(32.0f, 32.0f), TextureMan->GetTexture("cemetarytileset"), tileIdentifier));
		}
	}




	myTileLayer->Add(propGroup);
	myTileLayer->Add(tileGroup);
	myTileLayer->Add(effectsGroupBack);
	myTileLayer->Add(myPlayer->mySprite);
	myTileLayer->Add(effectsGroup);

	lastPlayerX = myPlayer->mPosition.x;
	myScreenDirection = 0.0f;

	myLayers.push_back(myTileLayer);
	myPlayer->myTileMap = myMap;


}
GraveyardLevel::~GraveyardLevel()
{
	delete myMap;
	EntityMan->DeleteAllEntities();
}
void GraveyardLevel::UpdatePlayer()
{
	EntityMan->Update();
	CollisionMan->Update();
	MessageMan->dispatchDelayedMessages();

	myPlayer->UpdateTransformationMatrix(*myCamera);
	glm::vec2 mouseScreenWorld = myCamera->mouseScreenToWorld(glm::vec2(lastX, lastY));
	glm::mat4 tran = glm::mat4(1.0f);
	tran = glm::translate(tran, glm::vec3(mouseScreenWorld.x, mouseScreenWorld.y, 0.0f));

	for (Group* group : myRenderGroups)
	{
		glm::mat4 camTranslation = myCamera->mTranslationMatrix;
		group->UpdateXYAxis(glm::vec2(myCamera->mPosition.x, myCamera->mPosition.y));
	}

	for (EffectsGroup* group : my…ffectsGroups)
	{
		glm::mat4 camTranslation = myCamera->mTranslationMatrix;
		group->UpdateXYAxis(glm::vec2(myCamera->mPosition.x, myCamera->mPosition.y));
	}

	myScreenDirection = 0.0f;
	if ((myPlayer->mPosition.x > myCameraMinBoundX) && (myPlayer->mPosition.x < myCameraMaxBoundX) && !myBossBattle)
	{
		float newPlayerX = myPlayer->mPosition.x;
		if (lastPlayerX > newPlayerX)
			myScreenDirection = -1.0f;
		else if (lastPlayerX < newPlayerX)
			myScreenDirection = 1.0f;
		else
			myScreenDirection = 0.0f;

		lastPlayerX = newPlayerX;
	}
	myMountainBackground->increaseUVAlongX(myScreenDirection *0.001f);
	myGraveyardBackground->increaseUVAlongX(myScreenDirection *0.002f);
}
void GraveyardLevel::Tick(const unsigned int ups, const unsigned int fps)
{
	myFPSLabel->myText = std::to_string(fps) + " fps";
	std::cout << ups << " ups, " << fps << " fps" << std::endl;
}
void GraveyardLevel::Update()
{
	UpdatePlayer();
	myMap->setPlayerTile(myPlayer->mPosition.x, myPlayer->mPosition.y);
	myMap->SetPlayerTile2(myPlayer->myAABB);
	//myCamera.setPosition(-myPlayer->mPosition);
	//if (myPlayer->mPosition.x > 75.5f && myPlayer->mPosition.x < 3155.0f && (!myBossBattle))
	if (myPlayer->mPosition.x > 75.5f && myPlayer->mPosition.x < 3155.0f)
		int hoho = 6;
		//myCamera->setPosition(glm::vec3(-myPlayer->mPosition.x, 32.0f, -myPlayer->mPosition.z));
	if(!myBossBattle)
		myCamera->setPosition(glm::vec3(-myPlayer->mPosition.x, 384, -myPlayer->mPosition.z));

	if(myPlayer->mPosition.x < myCameraMinBoundX)
		myCamera->setPosition(glm::vec3(-myCameraMinBoundX, 384, -myPlayer->mPosition.z));
	if (myPlayer->mPosition.x > myCameraMaxBoundX)
		myCamera->setPosition(glm::vec3(-myCameraMaxBoundX, 384, -myPlayer->mPosition.z));

	if (myPlayer->mPosition.x > myCameraMaxBoundX && !myBossBattle)
	{
		myBossBattle = true;
		for(int i = 1; i < myMapHeight - 1; i++)
		{
			myMap->GetTile2(myMapWidth - 25, i)->myIsBlockingFlag = true;
		}

	}
		

	myCamera->Update();
}
void GraveyardLevel::Render()
{
	for (Layer* layer : myLayers)
		layer->Render();
}
void GraveyardLevel::DeInitialize()
{

}
void GraveyardLevel::ProcessKeyBoard(int key, float deltaTime, int action)
{
	myPlayer->processKeyBoard(key, deltaTime, action);
}
void GraveyardLevel::ProcessMouse(double xpos, double ypos, bool movement)
{
	myMouseMovement = movement;

	lastX = xpos;
	lastY = ypos;

	myCamera->setScreenPosition(glm::vec2(lastX, lastY));
}
void GraveyardLevel::AddEntity(Entity* entity)
{
	myEntitites.push_back(entity);
}

void GraveyardLevel::SpawnEntity(const std::string& type, const glm::vec3&  inpos, const glm::vec3& indir, int heading)
{
	myNumberOfEntities++;
	/*if (type == "Necromancer Projectile")
	{
		NecromancerProjectile* necroProjectile = new NecromancerProjectile(myNumberOfEntities, "NecromancerProjectile" + std::to_string(myNumberOfEntities), inpos, indir);
		myEntitites.push_back(necroProjectile);
		enemyGroup->Add(necroProjectile->mySprite);
		CollisionMan->RegisterProjectile(necroProjectile);
		EntityMan->registerEntity(necroProjectile);
	}
	else if (type == "Imp Projectile")
	{
		ImpProjectile* impProjectile = new ImpProjectile(myNumberOfEntities, "ImpProjectile" + std::to_string(myNumberOfEntities), inpos, indir);
		myEntitites.push_back(impProjectile);
		enemyGroup->Add(impProjectile->mySprite);
		CollisionMan->RegisterProjectile(impProjectile);
		EntityMan->registerEntity(impProjectile);
	}
	else if (type == "Adventurer Projectile")
	{
		AdventurerProjectile* impProjectile = new AdventurerProjectile(myNumberOfEntities, "AdventurerProjectile" + std::to_string(myNumberOfEntities), inpos, indir);
		myEntitites.push_back(impProjectile);
		enemyGroup->Add(impProjectile->mySprite);
		CollisionMan->RegisterHeroProjectile(impProjectile);
		EntityMan->registerEntity(impProjectile);
	}
	else if (type == "Adventurer Arrow")
	{
		AdventurerProjectileArrow* impProjectile = new AdventurerProjectileArrow(myNumberOfEntities, "AdventurerProjectile" + std::to_string(myNumberOfEntities), inpos, indir);
		myEntitites.push_back(impProjectile);
		enemyGroup->Add(impProjectile->mySprite);
		CollisionMan->RegisterHeroProjectile(impProjectile);
		EntityMan->registerEntity(impProjectile);
	}*/
	if (type == "Medium Hit")
	{
		Effect* effect = new Effect(myNumberOfEntities, "MediumHit" + std::to_string(myNumberOfEntities), inpos, new HitEffectSprite(glm::vec4(inpos.x, inpos.y, 0.0f, 1.0f), glm::vec2(100, 100), TextureMan->GetTexture("hiteffect"), Heading::RIGHTFACING), "HitEffect");
		myEntitites.push_back(effect);
		effectsGroup->Add(effect);
		EntityMan->registerEntity(effect);
	}
	else if (type == "Large Hit")
	{
		Effect* effect = new Effect(myNumberOfEntities, "LargeHit" + std::to_string(myNumberOfEntities), inpos, new HitEffectSprite(glm::vec4(inpos.x, inpos.y, 0.0f, 1.0f), glm::vec2(200, 200), TextureMan->GetTexture("hiteffectslow"), Heading::RIGHTFACING), "HitEffectSlow");
		myEntitites.push_back(effect);
		effectsGroup->Add(effect);
		EntityMan->registerEntity(effect);
	}
	else if (type == "Large Hit Fast")
	{
		Effect* effect = new Effect(myNumberOfEntities, "LargeHitFast" + std::to_string(myNumberOfEntities), inpos, new HitEffectSprite(glm::vec4(inpos.x, inpos.y, 0.0f, 1.0f), glm::vec2(200, 200), TextureMan->GetTexture("hiteffect"), Heading::RIGHTFACING), "HitEffect");
		myEntitites.push_back(effect);
		effectsGroup->Add(effect);
		EntityMan->registerEntity(effect);
	}
	else if (type == "Extra Large Hit")
	{
		Effect* effect = new Effect(myNumberOfEntities, "ExtraLargeHit" + std::to_string(myNumberOfEntities), inpos, new HitEffectSprite(glm::vec4(inpos.x, inpos.y, 0.0f, 1.0f), glm::vec2(400, 400), TextureMan->GetTexture("hiteffectslow"), Heading::RIGHTFACING), "HitEffectSlow");
		myEntitites.push_back(effect);
		effectsGroup->Add(effect);
		EntityMan->registerEntity(effect);
	}
	else if (type == "Blood Effect Random")
	{
		int number = (rand() % 3);
		if (number == 0)
			number = 1;
		else if (number == 1)
			number = 3;
		else if (number == 2)
			number = 4;
		std::string blood = "HitEffectBlood" + std::to_string(number);
		Effect* effect = new Effect(myNumberOfEntities, "BloodHit" + std::to_string(myNumberOfEntities), inpos, new BloodEffectSprite(glm::vec4(inpos.x, inpos.y, 0.0f, 1.0f), glm::vec2(96, 96), TextureMan->GetTexture("bloodeffect2"), heading == 1 ? Heading::RIGHTFACING : Heading::LEFTFACING), blood);
		myEntitites.push_back(effect);
		effectsGroup->Add(effect);
		EntityMan->registerEntity(effect);
	}
	else if (type == "Blood Effect 1")
	{
		Effect* effect = new Effect(myNumberOfEntities, "BloodHit" + std::to_string(myNumberOfEntities), inpos, new BloodEffectSprite(glm::vec4(inpos.x, inpos.y, 0.0f, 1.0f), glm::vec2(96, 96), TextureMan->GetTexture("bloodeffect2"), heading == 1 ? Heading::RIGHTFACING : Heading::LEFTFACING), "HitEffectBlood1");
		myEntitites.push_back(effect);
		effectsGroup->Add(effect);
		EntityMan->registerEntity(effect);
	}
	else if (type == "Blood Effect 2")
	{
		Effect* effect = new Effect(myNumberOfEntities, "BloodHit" + std::to_string(myNumberOfEntities), inpos, new BloodEffectSprite(glm::vec4(inpos.x, inpos.y, 0.0f, 1.0f), glm::vec2(96, 96), TextureMan->GetTexture("bloodeffect2"), heading == 1 ? Heading::RIGHTFACING : Heading::LEFTFACING), "HitEffectBlood2");
		myEntitites.push_back(effect);
		effectsGroup->Add(effect);
		EntityMan->registerEntity(effect);
	}
	else if (type == "Blood Effect 3")
	{
		Effect* effect = new Effect(myNumberOfEntities, "BloodHit" + std::to_string(myNumberOfEntities), inpos, new BloodEffectSprite(glm::vec4(inpos.x, inpos.y, 0.0f, 1.0f), glm::vec2(96, 96), TextureMan->GetTexture("bloodeffect2"), heading == 1 ? Heading::RIGHTFACING : Heading::LEFTFACING), "HitEffectBlood3");
		myEntitites.push_back(effect);
		effectsGroup->Add(effect);
		EntityMan->registerEntity(effect);
	}
	else if (type == "Blood Effect 4")
	{
		Effect* effect = new Effect(myNumberOfEntities, "BloodHit" + std::to_string(myNumberOfEntities), inpos, new BloodEffectSprite(glm::vec4(inpos.x, inpos.y, 0.0f, 1.0f), glm::vec2(96, 96), TextureMan->GetTexture("bloodeffect2"), heading == 1 ? Heading::RIGHTFACING : Heading::LEFTFACING), "HitEffectBlood4");
		myEntitites.push_back(effect);
		effectsGroup->Add(effect);
		EntityMan->registerEntity(effect);
	}
	else if (type == "Enemy Hit Effect")
	{
		int number = (rand() % 2);
		if (number == 0)
			number = 1;
		else if (number == 1)
			number = 2;
		std::string hit = "EnemyHitEffect" + std::to_string(number);
		Effect* effect = new Effect(myNumberOfEntities, "EnemyHitEffect" + std::to_string(myNumberOfEntities), inpos, new EnemyHitEffectSprite(glm::vec4(inpos.x, inpos.y, 0.0f, 1.0f), glm::vec2(96, 96), TextureMan->GetTexture("enemyhiteffect"), heading == 1 ? Heading::RIGHTFACING : Heading::LEFTFACING), hit);
		myEntitites.push_back(effect);
		effectsGroup->Add(effect);
		EntityMan->registerEntity(effect);
	}
	else if (type == "Sword Effect 1")
	{

		Effect* effect = new Effect(myNumberOfEntities, "EnemyHitEffect" + std::to_string(myNumberOfEntities), inpos, new SwordHitEffectSprite(glm::vec4(inpos.x, inpos.y, 0.0f, 1.0f), glm::vec2(96, 96), TextureMan->GetTexture("swordhiteffect"), heading == 1 ? Heading::RIGHTFACING : Heading::LEFTFACING), "SwordHitEffect1");
		myEntitites.push_back(effect);
		effectsGroup->Add(effect);
		EntityMan->registerEntity(effect);
	}
	else if (type == "Sword Effect 2")
	{

		Effect* effect = new Effect(myNumberOfEntities, "EnemyHitEffect" + std::to_string(myNumberOfEntities), inpos, new SwordHitEffectSprite(glm::vec4(inpos.x, inpos.y, 0.0f, 1.0f), glm::vec2(96, 96), TextureMan->GetTexture("swordhiteffect"), heading == 1 ? Heading::RIGHTFACING : Heading::LEFTFACING), "SwordHitEffect1");
		myEntitites.push_back(effect);
		effectsGroup->Add(effect);
		EntityMan->registerEntity(effect);
	}
	else if (type == "Sword Effect 3")
	{  

		Effect* effect = new Effect(myNumberOfEntities, "EnemyHitEffect" + std::to_string(myNumberOfEntities), inpos, new SwordHitEffectSprite(glm::vec4(inpos.x, inpos.y, 0.0f, 1.0f), glm::vec2(96, 96), TextureMan->GetTexture("swordhiteffect"), heading == 1 ? Heading::RIGHTFACING : Heading::LEFTFACING), "SwordHitEffect1");
		myEntitites.push_back(effect);
		effectsGroup->Add(effect);
		EntityMan->registerEntity(effect);
	}
	else if (type == "Enemy Hit Death")
	{
		Effect* effect = new Effect(myNumberOfEntities, "EnemyHitEffect" + std::to_string(myNumberOfEntities), inpos, new EnemyHitEffectSprite(glm::vec4(inpos.x, inpos.y, 0.0f, 1.0f), glm::vec2(96, 96), TextureMan->GetTexture("enemyhiteffect"), heading == 1 ? Heading::RIGHTFACING : Heading::LEFTFACING), "EnemyDeathEffect");
		myEntitites.push_back(effect);
		effectsGroup->Add(effect);
		EntityMan->registerEntity(effect);

	}
	else if (type == "Enemy Hit Death Large")
	{
		Effect* effect = new Effect(myNumberOfEntities, "EnemyHitEffect" + std::to_string(myNumberOfEntities), inpos, new EnemyHitEffectSprite(glm::vec4(inpos.x, inpos.y, 0.0f, 1.0f), glm::vec2(192, 192), TextureMan->GetTexture("enemyhiteffect"), heading == 1 ? Heading::RIGHTFACING : Heading::LEFTFACING), "EnemyDeathEffect");
		myEntitites.push_back(effect);
		effectsGroup->Add(effect);
		EntityMan->registerEntity(effect);
	}
	else if (type == "Enemy Hit Death Small")
	{
		Effect* effect = new Effect(myNumberOfEntities, "EnemyHitEffect" + std::to_string(myNumberOfEntities), inpos, new EnemyHitEffectSprite(glm::vec4(inpos.x, inpos.y, 0.0f, 1.0f), glm::vec2(32, 32), TextureMan->GetTexture("enemyhiteffect"), heading == 1 ? Heading::RIGHTFACING : Heading::LEFTFACING), "EnemyDeathEffect");
		myEntitites.push_back(effect);
		effectsGroup->Add(effect);
		EntityMan->registerEntity(effect);
	}
	else if (type == "Pickup Destroyed")
	{
		Effect* effect = new Effect(myNumberOfEntities, "PickupDestroyed" + std::to_string(myNumberOfEntities), inpos, new PickupDestroyedSprite(glm::vec4(inpos.x, inpos.y, 0.0f, 1.0f), glm::vec2(16, 16), TextureMan->GetTexture("pickupdestroyed"), Heading::RIGHTFACING), "PickupDestroyed");
		myEntitites.push_back(effect);
		effectsGroup->Add(effect);
		EntityMan->registerEntity(effect);
	}
	else if (type == "Adventurer Slide")
	{
		Effect* effect = new Effect(myNumberOfEntities, "AdventurerSlide" + std::to_string(myNumberOfEntities), inpos, new AdventurerSlideEffectSprite(glm::vec4(inpos.x, inpos.y, 0.0f, 1.0f), glm::vec2(100 - 25, 74 - 18.5), TextureMan->GetTexture("slideeffect"), heading == 1 ? Heading::RIGHTFACING : Heading::LEFTFACING), "AdventurerSlideEffect", true);
		myEntitites.push_back(effect);
		effectsGroupBack->Add(effect);
		EntityMan->registerEntity(effect);
	}
	else if (type == "Adventurer DropKick")
	{
		Effect* effect = new Effect(myNumberOfEntities, "AdventurerDropKick" + std::to_string(myNumberOfEntities), inpos, new AdventurerDropKickEffectSprite(glm::vec4(inpos.x, inpos.y, 0.0f, 1.0f), glm::vec2(100 - 25, 74 - 18.5), TextureMan->GetTexture("dropkickeffect"), heading == 1 ? Heading::RIGHTFACING : Heading::LEFTFACING), "AdventurerDropKickEffect", true);
		myEntitites.push_back(effect);
		effectsGroupBack->Add(effect);
		EntityMan->registerEntity(effect);
	}
	/*else if (type == "HP Potion")
	{
		PotionPickup* potion = new PotionPickup(myNumberOfEntities, "HPPotion" + std::to_string(myNumberOfEntities), inpos, "hppotion");
		myEntitites.push_back(potion);
		effectsGroup->Add(potion);
		CollisionMan->RegisterPickup(potion);
		EntityMan->registerEntity(potion);

	}*/

}
void GraveyardLevel::RemoveEntity(Entity* entity)
{
	if (dynamic_cast<BaseProjectileEntity*>(entity))
	{
		if ((dynamic_cast<BaseProjectileEntity*>(entity)->isHeroProjectile))
			CollisionMan->RemoveHeroProjectile((BaseProjectileEntity*)entity);
		else
			CollisionMan->RemoveProjectile((BaseProjectileEntity*)entity);
		EntityMan->removeEntity(entity);
	}
	else
	{
		CollisionMan->RemoveEntity((BaseEnemy*)entity);
		EntityMan->removeEntity(entity);
	}
}