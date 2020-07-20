#include "command.h"
#include <stdexcept>
#include <array>
#include <cmath>

using namespace std;


string commands::New(const vector<string>& v, Map& map, GameData& data) noexcept
{
	if (v.size() != 2)
		return "Invalid arguments.\n";

	if (data.CurrentPlayer().actions() == data.MaxActions())
		return "Maximum number of actions reached.\n";

	if (data.CurrentPlayer().spawns() == data.MaxSpawns())
		return "Maximum number of spawns reached.\n";

	if (data.CurrentPlayer().alive() == data.MaxAlive())
		return "Maximum number of living amazons reached.\n";

	if (data.CurrentPlayer().existsAmazon(v[1]))
		return v[1] + " already exists.\n";

	data.CurrentPlayer().createAmazon(v[1]);

	map.tile(Point(0,0)).add(&data.CurrentPlayer().getAmazon(v[1]));

	data.CurrentPlayer().incAlive();
	data.CurrentPlayer().action();

	return v[1] + " created.\n";
}


string commands::Select(const vector<string>& v, Map& map, GameData& data) noexcept
{
	if (v.size() != 2)
		return "Invalid arguments.\n";

	if (!data.CurrentPlayer().existsAmazon(v[1]))
		return v[1] + " does not exist.\n";

	if (data.CurrentPlayer().selected() && data.CurrentPlayer().selected()->name() == v[1])
		return v[1] + " is already selected.\n";

	data.CurrentPlayer().selected(&data.CurrentPlayer().getAmazon(v[1]));

	return v[1] + " selected.\n";
}


string commands::Move(const vector<string>& v, Map& map, GameData& data) noexcept
{
	if (v.size() != 3)
		return "Invalid arguments.\n";

	if (data.CurrentPlayer().actions() == data.MaxActions())
		return "Maximum number of actions reached.\n";

	if (!data.CurrentPlayer().selected())
		return "Select an amazon first!\n";

	if (data.CurrentPlayer().selected()->health() == 0.0)
		return data.CurrentPlayer().selected()->name() + " is dead.\n";

	try
	{
		int x = stoi(v[1]) - 1;
		int y = stoi(v[2]) - 1;
		auto p = map.find(data.CurrentPlayer().selected());

		if (x < 0 || y < 0 || x >= map.size() || y >= map.size())
			return "Target tile does not exist.\n";

		if (p.x + 1 < x || p.x - 1 > x || p.y + 1 < y || p.y - 1 > y)
			return "Target tile is too far.\n";

		if (p == Point(x,y))
			return "Target tile matches the current one.\n";

		map.tile(p).remove(data.CurrentPlayer().selected());
		map.tile(Point(x, y)).add(data.CurrentPlayer().selected());

		data.CurrentPlayer().action();

		return data.CurrentPlayer().selected()->name() + " moved to " + v[1] + ";" + v[2] + ".\n";
	}

	catch (invalid_argument&)
	{
		return "Invalid arguments.\n";
	}
}


string commands::Help(const vector<string>& v, Map& map, GameData& data) noexcept
{
	return "Available commands:\n"
		"\"new <name>\"\n"
		"\"select <name>\"\n"
		"\"move <x> <y>\"\n"
		"\"lookaround\"\n"
		"\"tame\"\n"
		"\"geton\"\n"
		"\"getoff\"\n"
		"\"pickup <item>\"\n"
		"\"drop <item>\"\n"
		"\"equip <item>\"\n"
		"\"attack <name>\"\n"
		"\"help\"\n"
		"\"end\"\n"
		"\"exit\"\n";
}


string commands::Lookaround(const vector<string>& v, Map& map, GameData& data) noexcept
{
	if (v.size() != 1)
		return "Invalid arguments.\n";

	if (!data.CurrentPlayer().selected())
		return "Select an amazon first!\n";

	if (data.CurrentPlayer().selected()->health() == 0.0)
		return data.CurrentPlayer().selected()->name() + " is dead.\n";

	static const struct Offset : public Point
	{
		string adj;
		string noun;

		Offset(const char x, const char y, string_view adj, string_view noun) : Point(x, y), adj(adj), noun(noun) {}
	} offsets[]
	{
		{0, 0, "Current", "Current tile"},
		{0, 1,"Northern", "North"},
		{1, 1, "Northeastern", "North East"},
		{1, 0, "Eastern", "East"},
		{1, -1, "Southeastern", "South East:"},
		{0, -1, "Southern", "South"},
		{-1, -1,"Southwestern", "South West"},
		{-1, 0, "Western", "West"},
		{-1, 1, "Northwestern", "North West"}
	};

	Point p(map.find(data.CurrentPlayer().selected()));
	string ret;
	string temp;

	for (const auto& offset : offsets)
		if (p.x + offset.x >= 0 && p.x + offset.x < map.size() && p.y + offset.y >= 0 && p.y + offset.y < map.size())
		{
			for (const auto& x : map.tile(Point(p.x + offset.x, p.y + offset.y)).AmazonContainer())
				if (x != data.CurrentPlayer().selected())
					temp.append(x->name() + ", ");

			for (const auto& x : map.tile(Point(p.x + offset.x, p.y + offset.y)).DinoContainer())
				temp.append((x->tamed() ? "Tamed" : "Untamed") + static_cast<string>(" Dino (") +  to_string(static_cast<int>(round(x->health()))) + " HP), ");

			for (const auto& x : map.tile(Point(p.x + offset.x, p.y + offset.y)).ItemContainer())
				for (const auto& y : x.second)
					temp.append(y->name() + ", ");

			if (temp.empty())
				ret.append(offset.adj + " tile empty.\n");

			else
			{
				ret.append(offset.noun + ": " + temp.substr(0, temp.length() - 2) + ".\n");
				temp.clear();
			}
		}

	return ret;
}


string commands::Attack(const vector<string>& v, Map& map, GameData& data) noexcept
{
	if (v.size() != 2)
		return "Invalid arguments.\n";

	if (data.CurrentPlayer().actions() == data.MaxActions())
		return "Maximum number of actions reached.\n";

	if (!data.CurrentPlayer().selected())
		return "Select an amazon first!\n";

	if (data.CurrentPlayer().selected()->health() == 0.0)
		return data.CurrentPlayer().selected()->name() + " is dead.\n";

	if (!data.CurrentPlayer().selected()->hand())
		return data.CurrentPlayer().selected()->name() + " is not holding any weapon.\n";

	if (!data.OtherPlayer().existsAmazon(v[1]))
		return "Enemy " + v[1] + " does not exist.\n";

	if (map.find(data.CurrentPlayer().selected()) != map.find(&data.OtherPlayer().getAmazon(v[1])))
		return v[1] + " is out of range.\n";

	if (data.OtherPlayer().getAmazon(v[1]).health() == 0.0)
		return v[1] + " is already dead.\n";

	double dmg = data.CurrentPlayer().selected()->hand()->dmg();

	data.CurrentPlayer().action();

	if (data.OtherPlayer().getAmazon(v[1]).riding())
	{
		if (data.OtherPlayer().getAmazon(v[1]).dino()->health() - dmg < 0.0)
			data.OtherPlayer().getAmazon(v[1]).dino()->health(0.0);
		else
			data.OtherPlayer().getAmazon(v[1]).dino()->health(data.OtherPlayer().getAmazon(v[1]).dino()->health() - dmg);

		if (data.OtherPlayer().getAmazon(v[1]).dino()->health() == 0.0)
		{
			map.tile(map.find(&data.OtherPlayer().getAmazon(v[1]))).add(move(data.OtherPlayer().getAmazon(v[1]).riding()));
			return v[1] + "'s dino died.\n";
		}

		return v[1] + "'s dino suffered " + to_string(static_cast<int>(round(dmg))) + " points of damage.\n";
	}
		
		

	if (data.OtherPlayer().getAmazon(v[1]).health() - dmg < 0.0)
		data.OtherPlayer().getAmazon(v[1]).health(0.0);
	else
		data.OtherPlayer().getAmazon(v[1]).health(data.OtherPlayer().getAmazon(v[1]).health() - dmg);

	if (data.OtherPlayer().getAmazon(v[1]).health() == 0.0)
	{
		data.OtherPlayer().decAlive();
		return v[1] + " died.\n";
	}

	return v[1] + " suffered " + to_string(static_cast<int>(round(dmg))) + " points of damage.\n";
}


string commands::Pickup(const vector<string>& v, Map& map, GameData& data) noexcept
{
	if (v.size() != 2)
		return "Invalid arguments.\n";

	if (data.CurrentPlayer().actions() == data.MaxActions())
		return "Maximum number of actions reached.\n";

	if (!data.CurrentPlayer().selected())
		return "Select an amazon first!\n";

	if (data.CurrentPlayer().selected()->health() == 0.0)
		return data.CurrentPlayer().selected()->name() + " is dead.\n";

	if (!ItemFactory::isValid(v[1]))
		return "Invalid item type.\n";

	Point p = map.find(data.CurrentPlayer().selected());

	if (!map.tile(p).has(v[1]))
		return v[1] + " cannot be found on the current tile.\n";

	if (!data.CurrentPlayer().selected()->hasFreeSlot(ItemFactory::lookUp(v[1])))
		return "Can't pick up " + v[1] + ". " + data.CurrentPlayer().selected()->name() + "'s inventory is full.\n";

	data.CurrentPlayer().selected()->take(map.tile(p).remove(v[1]));

	data.CurrentPlayer().action();

	return "Picked up " + v[1] + ".\n";
}


string commands::Drop(const vector<string>& v, Map& map, GameData& data) noexcept
{
	if (v.size() != 2)
		return "Invalid arguments.\n";

	if (data.CurrentPlayer().actions() == data.MaxActions())
		return "Maximum number of actions reached.\n";

	if (!data.CurrentPlayer().selected())
		return "Select an amazon first!\n";

	if (data.CurrentPlayer().selected()->health() == 0.0)
		return data.CurrentPlayer().selected()->name() + " is dead.\n";

	if (!ItemFactory::isValid(v[1]))
		return "Invalid item type.\n";

	if (!data.CurrentPlayer().selected()->hasItem(v[1]))
		return v[1] + " cannot be found in " + data.CurrentPlayer().selected()->name() + "'s inventory.\n";

	Point p = map.find(data.CurrentPlayer().selected());

	unique_ptr<Item> item(data.CurrentPlayer().selected()->drop(v[1]));

	if (item.get() == data.CurrentPlayer().selected()->hand())
		data.CurrentPlayer().selected()->hand(nullptr);

	map.tile(p).add(move(item));

	data.CurrentPlayer().action();

	return v[1] + " dropped.\n";
}


string commands::Equip(const vector<string>& v, Map& map, GameData& data) noexcept
{
	if (v.size() != 2)
		return "Invalid arguments.\n";

	if (!data.CurrentPlayer().selected())
		return "Select an amazon first!\n";

	if (data.CurrentPlayer().selected()->health() == 0.0)
		return data.CurrentPlayer().selected()->name() + " is dead.\n";

	if (!ItemFactory::isValid(v[1]) || ItemFactory::lookUp(v[1]) != ItemType::gun)
		return "Invalid weapon type.\n";

	if (!data.CurrentPlayer().selected()->hasItem(v[1]))
		return v[1] + " cannot be found in " + data.CurrentPlayer().selected()->name() + "'s inventory.\n";

	data.CurrentPlayer().selected()->hand(static_cast<Gun*>(data.CurrentPlayer().selected()->item(v[1])));

	return v[1] + " equipped.\n";
}


string commands::End(const vector<string>& v, Map& map, GameData& data) noexcept
{
	if (v.size() != 1)
		return "Ivalid arguments.\n";

	data.turn();

	return "\n### END OF TURN ###\n";
}


string commands::Tame(const vector<string>& v, Map& map, GameData& data) noexcept
{
	if (v.size() != 1)
		return "Ivalid arguments.\n";

	if (data.CurrentPlayer().actions() == data.MaxActions())
		return "Maximum number of actions reached.\n";

	if (!data.CurrentPlayer().selected())
		return "Select an amazon first!\n";

	if (data.CurrentPlayer().selected()->health() == 0.0)
		return data.CurrentPlayer().selected()->name() + " is dead.\n";

	if (data.CurrentPlayer().selected()->dino())
		return data.CurrentPlayer().selected()->name() + " already has a dino.\n";

	const auto& dinos(map.tile(map.find(data.CurrentPlayer().selected())).DinoContainer());

	if (dinos.empty())
		return "There are no dinos nearby.\n";

	Dino* temp(dinos.front().get());

	for (const auto& x : dinos)
		if (x->health() >= temp->health() && !x->tamed())
			temp = x.get();

	if (temp->tamed())
		return "There are no free dinos nearby.\n";

	data.CurrentPlayer().selected()->dino(temp);
	temp->tamed(!temp->tamed());

	return "Dino (" + to_string(static_cast<int>(round(temp->health()))) + " HP) tamed.\n";
}


string commands::Geton(const vector<string>& v, Map& map, GameData& data) noexcept
{
	if (v.size() != 1)
		return "Invalid arguments.\n";

	if (!data.CurrentPlayer().selected())
		return "Select an amazon first!\n";

	if (data.CurrentPlayer().selected()->health() == 0.0)
		return data.CurrentPlayer().selected()->name() + " is dead.\n";

	if (!data.CurrentPlayer().selected()->dino())
		return data.CurrentPlayer().selected()->name() + " does not have a dino. Tame one first!\n";

	if (data.CurrentPlayer().selected()->riding())
		return data.CurrentPlayer().selected()->name() + " is already riding their dino.\n";

	const auto point(map.find(data.CurrentPlayer().selected()));

	if (!map.tile(point).has(data.CurrentPlayer().selected()->dino()))
		return data.CurrentPlayer().selected()->name() + "'s dino is not nearby.\n";

	if (data.CurrentPlayer().selected()->dino()->health() == 0.0)
		return data.CurrentPlayer().selected()->name() + "'s dino is dead.\n";

	data.CurrentPlayer().selected()->riding(map.tile(point).remove(data.CurrentPlayer().selected()->dino()));
	return data.CurrentPlayer().selected()->name() + " got on their dino.\n";
}


string commands::Getoff(const vector<string>& v, Map& map, GameData& data) noexcept
{
	if (v.size() != 1)
		return "Invalid arguments.\n";

	if (!data.CurrentPlayer().selected())
		return "Select an amazon first!\n";
	
	if (data.CurrentPlayer().selected()->health() == 0.0)
		return data.CurrentPlayer().selected()->name() + " is dead.\n";

	if (!data.CurrentPlayer().selected()->dino())
		return data.CurrentPlayer().selected()->name() + " does not have a dino. Tame one first!\n";

	if (!data.CurrentPlayer().selected()->riding())
		return data.CurrentPlayer().selected()->name() + " is currently not riding their dino.\n";

	map.tile(map.find(data.CurrentPlayer().selected())).add(move(data.CurrentPlayer().selected()->riding()));

	return data.CurrentPlayer().selected()->name() + " got off their dino.\n";
}