#include "player.h"

using std::string;
using std::string_view;


char Player::nextID(0); 


Player::Player(string_view name) noexcept : sName(name), pSelected(nullptr), nActions(0), nAlive(0), nID(nextID)
{
	nextID++;
}


Player::~Player() noexcept
{
	nextID--;
}


const string& Player::name() const noexcept
{
	return sName;
}


unsigned Player::actions() const noexcept
{
	return nActions;
}


void Player::action() noexcept
{
	nActions++;
}


void Player::resetActions() noexcept
{
	nActions = 0;
}


unsigned Player::alive() const noexcept
{
	return nAlive;
}


void Player::incAlive() noexcept
{
	nAlive++;
}


void Player::decAlive() noexcept
{
	nAlive--;
}


size_t Player::spawns() const noexcept
{
	return amazon_map.size();
}


bool Player::existsAmazon(std::string_view name) const noexcept
{
	return amazon_map.find(static_cast<string>(name)) != amazon_map.end();
}


void Player::createAmazon(string_view name) noexcept
{
	amazon_map.emplace(name, name);
}


Amazon& Player::getAmazon(std::string_view name) noexcept
{
	return amazon_map.at(static_cast<string>(name));
}


const std::unordered_map<string, Amazon>& Player::amazons() const noexcept
{
	return amazon_map;
}


char Player::id() const noexcept
{
	return nID;
}


Amazon* Player::selected() const noexcept
{
	return pSelected;
}


void Player::selected(Amazon* const amazon) noexcept
{
	pSelected = amazon;
}




GameData::GameData(int i) noexcept : p1("Player 1"), p2("Player 2"), active(false), nMaxActions(i == 1 ? 3 : 3), nMaxSpawns(i == 1 ? 6 : 6), nMaxAlive(i == 1 ? 3 : 3) {}


Player& GameData::CurrentPlayer() noexcept
{
	return active ? p2 : p1;
}


Player& GameData::OtherPlayer() noexcept
{
	return active ? p1 : p2;
}


unsigned GameData::MaxActions() const noexcept
{
	return nMaxActions;
}


unsigned GameData::MaxSpawns() const noexcept
{
	return nMaxSpawns;
}


unsigned GameData::MaxAlive() const noexcept
{
	return nMaxAlive;
}


void GameData::turn() noexcept
{
	active = !active;
	p1.resetActions();
	p2.resetActions();
}