#ifndef _HealbotAI_H
#define _HealbotAI_H

#include "Common.h"

class WorldPacket;
class Player;
class Unit;
class Object;
class Item;
class HealbotClassAI;

enum ScenarioType {
	SCENARIO_PVEEASY,
	SCENARIO_PVEHARD,
	SCENARIO_DUEL,
	SCENARIO_PVPEASY,
	SCENARIO_PVPHARD
};

enum {
	SPELL_HOLY,
	SPELL_SHADOWMAGIC,
	SPELL_DISCIPLINE
};

class MANGOS_DLL_SPEC HealbotAI {
    public:
	// ******* Stuff the outside world calls ****************************
        HealbotAI(Player* const master, Player* const bot);
        virtual ~HealbotAI();

        // This is called from Unit.cpp and is called every second (I think)
        void UpdateAI(const uint32 p_time);

        // This is called from ChatHandler.cpp when there is an incoming message to the bot
        // from a whisper or from the party channel
        void HandleCommand(const std::string& text, Player& fromPlayer);

		// all combat actions go here
		//void DoNextCombatManeuver(Unit*);

		// all non combat actions go here, ex buffs, heals, rezzes
		void DoNonCombatActions();

		// buff a specific player, usually a real PC who is not in group
		void BuffPlayer(Player *target);

        bool CanUseSpell(uint32 spell) { return spell > 0; }

        // This is called by WorldSession.pm
        // It provides a view of packets normally sent to the client.
        // Since there is no client at the other end, the packets are dropped of course.
        // For a list of opcodes that can be caught see Opcodes.cpp (SMSG_* opcodes only)
        void HandleBotOutgoingPacket(const WorldPacket& packet);

        // This is called whenever the master sends a packet to the server.
        // These packets can be viewed, but not edited.
        // It allows bot creators to craft AI in response to a master's actions.
        // For a list of opcodes that can be caught see Opcodes.cpp (CMSG_* opcodes only)
        // Notice: that this is static which means it is called once for all bots of the master.
        static void HandleMasterIncomingPacket(const WorldPacket& packet, WorldSession& masterSession);
        static void HandleMasterOutgoingPacket(const WorldPacket& packet, WorldSession& masterSession);

		// Returns what kind of situation we are in so the ai can react accordingly
		ScenarioType GetScenarioType() {return m_ScenarioType;}

		//HealbotClassAI* GetClassAI() {return m_classAI;}

    //protected:

	// ******* Utilities ***************************************************

	// finds spell ID for matching substring args
        // in priority of full text match, spells not taking reagents, and highest rank
	uint32 getSpellId(const char* args) const;

        // extracts item ids from links
        void extractItemIds(const std::string& text, std::list<uint32>& itemIds) const;

        // extracts currency from a string as #g#s#c and returns the total in copper
        uint32 extractMoney(const std::string& text) const;

        // finds items in bots inventory and adds them to foundItemList, removes found items from itemIdSearchList
        void findItemsInInv(std::list<uint32>& itemIdSearchList, std::list<Item*>& foundItemList) const;

        // currently bots only obey commands from the master
        bool canObeyCommandFrom(const Player& player) const;

        // get current casting spell (will return NULL if no spell!)
        Spell* GetCurrentSpell() const;

        bool HasAura(uint32 spellId, const Unit& player) const;
        bool HasAura(const char* spellName, const Unit& player) const;
        bool HasAura(const char* spellName) const;

        uint8 GetHealthPercent(const Unit& target) const;
        uint8 GetHealthPercent() const;
		uint8 GetBaseManaPercent(const Unit& target) const;
		uint8 GetBaseManaPercent() const;
		uint8 GetManaPercent(const Unit& target) const;
		uint8 GetManaPercent() const;
		uint8 GetRageAmount(const Unit& target) const;
		uint8 GetRageAmount() const;
		uint8 GetEnergyAmount(const Unit& target) const;
		uint8 GetEnergyAmount() const;


        Item* FindFood() const;
        Item* FindDrink() const;
        Item* FindBandage() const;
		Item* FindPoison() const;
        Item* FindMount(uint32 matchingRidingSkill) const;
        //Item* FindManaPot() const; //doesnt work yet

        // ******* Actions ****************************************
        // Your handlers can call these actions to make the bot do things.
        void TellMaster(const std::string& text);
        void SendWhisper(const std::string& text, Player& player);
        bool CastSpell(const char* args, uint8 ignoreAIUpdatesTime = 6);
        bool CastSpell(uint32 spellId, uint8 ignoreAIUpdatesTime = 6);
        bool CastSpell(uint32 spellId, Unit& target, uint8 ignoreAIUpdatesTime = 6);
        void UseItem(Item& item);
        void EquipItem(Item& item);
        void Stay();
        bool Follow(Player& player);
        void SendNotEquipList(Player& player);
        void Rest();
        void InterruptCurrentCastingSpell();
        void GetCombatOrders();
        void DoNextCombatManeuver(); //void DoNextCombatManeuver(Unit*);
		void SetIgnoreUpdateTime(uint8 t) {m_ignoreAIUpdatesUntilTime=time(0) + t; };

		Player *GetHealbot() {return m_bot;}

    private:

	// ****** Closed Actions ********************************
	// These actions may only be called at special times.
	// Trade methods are only applicable when the trade window is open
	// and are only called from within HandleCommand.
        bool TradeItem(const Item& item);
        bool TradeCopper(uint32 copper);

	// it is safe to keep these back reference pointers because m_bot
        // owns the "this" object and m_master owns m_bot. The owner always cleans up.
	Player* const m_master;
	Player* const m_bot;
		//HealbotClassAI* m_classAI;

	// ignores AI updates until time specified
	// no need to waste CPU cycles during casting etc
	time_t m_ignoreAIUpdatesUntilTime;

	// Heals the target based off its hps
	void HealTarget (Unit& target, uint8 hp);

	// holy
	uint32 RENEW, HEAL, FLASH_HEAL, REZZ, SMITE, CLEARCASTING, HOLY_NOVA, HOLY_FIRE, DESPERATE_PRAYER, PRAYER_OF_HEALING, CIRCLE_OF_HEALING, BINDING_HEAL, PRAYER_OF_MENDING;

	// shadowmagic
	uint32 FADE, PAIN, MIND_BLAST, SCREAM, MIND_FLAY, DEVOURING_PLAGUE, SHADOW_PROTECTION, VAMPIRIC_TOUCH, PRAYER_OF_SHADOW_PROTECTION, SHADOWFIEND, MIND_SEAR;

	// discipline
	uint32 PWS, INNER_FIRE, FORTITUDE, TOUCH_OF_WEAKNESS, FEAR_WARD, DSPIRIT, POWER_INFUSION, MASS_DISPEL;

    uint32 WAND;

	uint32 SpellSequence, LastSpellHoly, LastSpellShadowMagic, LastSpellDiscipline;


	// masters orders that should be obeyed by the AI during the updteAI routine
	// the master will auto set the target of the bot
	enum CombatOrderType {
		ORDERS_NONE,
		ORDERS_KILL,
		ORDERS_CC,
		ORDERS_HEAL,
		ORDERS_TANK,
		ORDERS_PROTECT,
		ORDERS_REGEN
	};
	CombatOrderType m_combatOrder;

		ScenarioType m_ScenarioType;

	time_t m_TimeDoneEating;
	time_t m_TimeDoneDrinking;
	uint32 m_CurrentlyCastingSpellId;
	bool m_IsFollowingMaster;

	// if master commands bot to do something, store here until updateAI
	// can do it
	uint32 m_spellIdCommand;
	uint64 m_targetGuidCommand;
};


#endif
