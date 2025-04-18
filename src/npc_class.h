#pragma once

#include <functional>
#include <map>
#include <vector>
#include <string>

#include "string_id.h"
#include "translations.h"
#include "type_id.h"

class JsonObject;

class Trait_group;

namespace trait_group
{

using Trait_group_tag = string_id<Trait_group>;

} // namespace trait_group

// TODO: Move to better suited file (rng.h/.cpp?)
class distribution
{
    private:
        std::function<float()> generator_function;
        distribution( std::function<float()> gen );

    public:
        distribution();
        distribution( const distribution & );

        float roll() const;

        distribution operator+( const distribution &other ) const;
        distribution operator*( const distribution &other ) const;
        distribution &operator=( const distribution &other );

        static distribution constant( float val );
        static distribution rng_roll( int from, int to );
        static distribution dice_roll( int sides, int size );
        static distribution one_in( float in );
};

class npc_class
{
    private:
        translation name;
        translation job_description;

        bool common = true;

        distribution bonus_str;
        distribution bonus_dex;
        distribution bonus_int;
        distribution bonus_per;

        std::map<skill_id, distribution> skills;
        // Just for finalization
        std::map<skill_id, distribution> bonus_skills;

        item_group_id shopkeeper_item_group = item_group_id( "EMPTY_GROUP" );

    public:
        npc_class_id id;
        bool was_loaded = false;

        item_group_id worn_override;
        item_group_id carry_override;
        item_group_id weapon_override;

        std::map<mutation_category_id, distribution> mutation_rounds;
        trait_group::Trait_group_tag traits = trait_group::Trait_group_tag( "EMPTY_GROUP" );
        // the int is what level the spell starts at
        std::map<spell_id, int> _starting_spells;
        std::map<bionic_id, int> bionic_list;
        npc_class();

        std::string get_name() const;
        std::string get_job_description() const;

        int roll_strength() const;
        int roll_dexterity() const;
        int roll_intelligence() const;
        int roll_perception() const;

        int roll_skill( const skill_id & ) const;

        const item_group_id &get_shopkeeper_items() const;

        void load( const JsonObject &jo, const std::string &src );

        static const npc_class_id &from_legacy_int( int i );

        static const npc_class_id &random_common();

        static void load_npc_class( const JsonObject &jo, const std::string &src );

        static const std::vector<npc_class> &get_all();

        static void reset_npc_classes();

        static void finalize_all();

        static void check_consistency();
};

// TODO: Get rid of that
extern npc_class_id NC_NONE;
extern npc_class_id NC_EVAC_SHOPKEEP;
extern npc_class_id NC_SHOPKEEP;
extern npc_class_id NC_HACKER;
extern npc_class_id NC_CYBORG;
extern npc_class_id NC_DOCTOR;
extern npc_class_id NC_TRADER;
extern npc_class_id NC_NINJA;
extern npc_class_id NC_COWBOY;
extern npc_class_id NC_SCIENTIST;
extern npc_class_id NC_BOUNTY_HUNTER;
extern npc_class_id NC_THUG;
extern npc_class_id NC_SCAVENGER;
extern npc_class_id NC_ARSONIST;
extern npc_class_id NC_HUNTER;
extern npc_class_id NC_SOLDIER;
extern npc_class_id NC_BARTENDER;
extern npc_class_id NC_JUNK_SHOPKEEP;
extern npc_class_id NC_HALLU;


