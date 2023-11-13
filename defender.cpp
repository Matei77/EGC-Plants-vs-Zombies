#include "defender.h"
void PvZ::Defender::SpawnProjectile() {
    Projectile projectile = Projectile({position.x + PROJECTILE_OFFSET, position.y}, color);
    projectiles.push_back(projectile);
}
