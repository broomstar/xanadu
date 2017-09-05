//

#include "quest_data_provider.hpp"

#include "quest_data.hpp"
#include "world.hpp"
#include "wznode.hpp"
#include "wzmain.hpp"

// singleton

QuestDataProvider *QuestDataProvider::singleton_ = nullptr;

QuestDataProvider *QuestDataProvider::get_instance()
{
	if (!singleton_)
	{
		singleton_ = new QuestDataProvider();
	}

	return singleton_;
}

void QuestDataProvider::load_data()
{
	// Quest.wz

	WZMain *wz_reader = World::get_instance()->wz_reader_;
	WZNode node1 = wz_reader->base_["Quest"]["QuestInfo"];

	for (auto it1 : node1)
	{
		std::string valuename1 = it1.name();
		int quest_id = std::stoi(valuename1);
		QuestData *quest = new QuestData(quest_id);
		quests_[quest_id] = quest;
	}

	// Act.img / Rewards

	WZNode node2 = wz_reader->base_["Quest"]["Act"];

	for (auto it2 : node2)
	{
		std::string valuename1 = it2.name();
		int quest_id = std::stoi(valuename1);
		QuestData *quest = quests_[quest_id];

		if (!quest)
		{
			continue;
		}

		WZNode node21 = wz_reader->base_["Quest"]["Act"][valuename1.c_str()]["1"];

		QuestRewardData *rew = new QuestRewardData();

		rew->start = false;
		rew->item = false;
		rew->mesos = false;
		rew->exp = false;
		rew->fame = false;
		rew->id = 0;
		rew->count = 0;

		for (auto it3 : node21)
		{
			std::string valuename3 = it3.name();
			
			/*if (valuename3 == "start")
			{
				bool start = it3.get_int_value() ? 0 : 1;
				rew->start = start;
			}

			else if (valuename3 == "item")
			{
				bool item = it3.get_int_value() ? 1 : 0;
				rew->item = item;
			}*/

			/*else */if (valuename3 == "exp")
			{
				int exp = it3.get_int_value();
				rew->exp = exp != 0;
				rew->id = exp;
			}

			/*else if (valuename3 == "mesos")
			{
				bool mesos = it3.get_int_value() ? 1 : 0;
				rew->mesos = mesos;
			}

			else if (valuename3 == "fame")
			{
				bool fame = it3.get_int_value() ? 1 : 0;
				rew->fame = fame;
			}

			else if (valuename3 == "oid")
			{
				int oid = it3.get_int_value();
				rew->id = oid;
			}

			else if (valuename3 == "count")
			{
				int count = it3.get_int_value();
				rew->count = count;
			}*/

			// TO-DO: fix this

			/*			rew->setStart(rs["start"] == 0);
						rew->setItem(rs["item"] == 1);
						rew->set_exp(rs["exp"] == 1);
						rew->setMesos(rs["mesos"] == 1);
						rew->set_fame(rs["fame"] == 1);
						rew->setID(rs["oid"]);
						rew->setCount(rs["count"]);*/
		}

		quest->add_reward(rew);
	}

	// Check.img / Requests

	WZNode node3 = wz_reader->base_["Quest"]["Check"];

	for (auto it3 : node3)
	{
		std::string valuename1 = it3.name();
		int quest_id = std::stoi(valuename1);
		QuestData *quest = quests_[quest_id];

		WZNode node31 = wz_reader->base_["Quest"]["Check"][valuename1.c_str()];

		// TO-DO: fix this

		/*
			for (size_t col = 0; col < rs.rowCount(); ++col)
			{
			int object_id = rs["oid"];
			int amount = rs["count"];

			if (rs["mob"] == 1)
			{
			quest->addMonsterRequirement(object_id, amount);
			}
			else if (rs["item"] == 1)
			{
			quest->addItemRequirement(object_id, amount);
			}
			rs.moveNext();
			}
			*/
	}
}

QuestData *QuestDataProvider::get_quest_data(int quest_id)
{
	if (quests_.find(quest_id) == quests_.end())
	{
		return nullptr;
	}

	return quests_[quest_id];
}

std::unordered_map<int, QuestData *> *QuestDataProvider::get_data()
{
	return &quests_;
}
