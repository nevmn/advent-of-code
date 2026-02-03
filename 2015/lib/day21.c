#include "common.h"
#include "day21.h"

#include <assert.h>
#include <limits.h>
#include <stdio.h>

typedef struct {
  int cost;
  int damage;
  int armor;
} StoreItem;

static const StoreItem weapons[] = {
  {8, 4, 0},
  {10, 5, 0},
  {25, 6, 0},
  {40, 7, 0},
  {74, 8, 0},
};

static const StoreItem armors[] = {
  {0, 0, 0},
  {13, 0, 1},
  {31, 0, 2},
  {53, 0, 3},
  {75, 0, 4},
  {102, 0, 5},
};

static const StoreItem rings[] = {
  {0, 0, 0},
  {25, 1, 0},
  {50, 2, 0},
  {100, 3, 0},
  {0, 0, 0},
  {20, 0, 1},
  {40, 0, 2},
  {80, 0, 3},
};

static int turns_to_kill_target(const int target_hp, const int damage) {
  return (target_hp + damage - 1) / damage;
}

static int find_cost_for_outcome(const int boss_hp,
                                 const int boss_damage,
                                 const int boss_armor,
                                 const bool first_part) {
  int result_cost = first_part ? INT_MAX : 0;

  for (size_t w = 0; w < sizeof(weapons) / sizeof(weapons[0]); w++) {
    for (size_t a = 0; a < sizeof(armors) / sizeof(armors[0]); a++) {
      for (size_t r1 = 0; r1 < sizeof(rings) / sizeof(rings[0]) - 4; r1++) {
        for (size_t r2 = 4; r2 < sizeof(rings) / sizeof(rings[0]); r2++) {
          const int cost = weapons[w].cost + armors[a].cost + rings[r1].cost + rings[r2].cost;
          const int damage = weapons[w].damage + rings[r1].damage;
          const int armor = armors[a].armor + rings[r2].armor;

          const int player_attack = damage > boss_armor ? damage - boss_armor : 1;
          const int boss_attack = boss_damage > armor ? boss_damage - armor : 1;

          const int player_turns = turns_to_kill_target(boss_hp, player_attack);
          const int boss_turns = turns_to_kill_target(100, boss_attack);

          const bool player_wins = player_turns <= boss_turns;
          if (player_wins != first_part)
            continue;

          if (first_part) {
            if (cost < result_cost)
              result_cost = cost;
          } else {
            if (cost > result_cost)
              result_cost = cost;
          }
        }
      }
    }
  }

  return result_cost;
}

Result day21_part1(const char *input) {
  const int boss_hp = 0;
  const int boss_damage = 0;
  const int boss_armor = 0;

  const int parsed_count = sscanf(input, "Hit Points: %d\nDamage: %d\nArmor: %d", &boss_hp, &boss_damage, &boss_armor);
  assert(parsed_count == 3);

  return result_int(find_cost_for_outcome(boss_hp, boss_damage, boss_armor, true));
}

Result day21_part2(const char *input) {
  const int boss_hp = 0;
  const int boss_damage = 0;
  const int boss_armor = 0;

  const int parsed_count = sscanf(input, "Hit Points: %d\nDamage: %d\nArmor: %d", &boss_hp, &boss_damage, &boss_armor);
  assert(parsed_count == 3);

  return result_int(find_cost_for_outcome(boss_hp, boss_damage, boss_armor, false));
}