#include "Config.h"

#include "Entity.h"

namespace Config {
float speed(const Entity &entity) {
    if (entity.type == EntityProto_EntityType_Player) {
        if (entity.action.type == EntityProto_ActionType_KaisaE) {
            return 10;
        }
        if (entity.action.type == EntityProto_ActionType_KaisaR) {
            return 30;
        }
        return 3;
    } else if (entity.type == EntityProto_EntityType_Melee) {
        return 2.5;
    } else if (entity.type == EntityProto_EntityType_Bullet) {
        return 15;
    } else if (entity.type == EntityProto_EntityType_KaisaWBullet) {
        return 20;
    } else if (entity.type == EntityProto_EntityType_Urgot) {
        return 1;
    } else if (entity.type == EntityProto_EntityType_UrgotBullet) {
        return 5;
    }
    log_warn("no speed find, type={}\n", entity.type);
    return 1;
}

bool movable(const Entity &entity) {
    if (entity.action.type == EntityProto_ActionType_Attack &&
        entity.action.data.size() == 2) {
        return false;
    }
    if (entity.action.type == EntityProto_ActionType_KaisaW) {
        return false;
    }
    if (entity.action.type == EntityProto_ActionType_MeleeAttack) {
        return false;
    }
    if (entity.action.type == EntityProto_ActionType_Death) {
        return false;
    }
    if (entity.action.type == EntityProto_ActionType_KaisaR) {
        return false;
    }
    return true;
}

float attack_radius(const Entity &entity) {
    if (entity.type == EntityProto_EntityType_Player) {
        return 9;
    } else if (entity.type == EntityProto_EntityType_Melee) {
        return 2;
    } else if (entity.type == EntityProto_EntityType_Bullet) {
        return 0.2;
    } else if (entity.type == EntityProto_EntityType_KaisaWBullet) {
        return 1;
    } else if (entity.type == EntityProto_EntityType_UrgotBullet) {
        return 0.8f;
    }
    log_warn("no attack_radius find, type={}\n", entity.type);
    return 1;
}

EntityProto_ActionType action_proto(const Entity &entity) {
    if (entity.action.type == EntityProto_ActionType_MeleeAttack) {
        if (entity.action.data.size() == 2) {
            return EntityProto_ActionType_MeleeAttack;
        } else {
            return EntityProto_ActionType_Idle;
        }
    }
    if (entity.moving) {
        if (entity.action.type == EntityProto_ActionType_KaisaR) {
            return EntityProto_ActionType_KaisaR;
        }
        return EntityProto_ActionType_Move;
    }
    if (entity.action.type == EntityProto_ActionType_Undefined ||
        entity.action.type == EntityProto_ActionType_WaitAttack ||
        entity.action.type == EntityProto_ActionType_KaisaQ) {
        return EntityProto_ActionType_Idle;
    }
    if (entity.action.type == EntityProto_ActionType_Attack) {
        return entity.attack_hand ? EntityProto_ActionType_Attack1
                                  : EntityProto_ActionType_Attack;
    }
    return entity.action.type;
}

bool is_enemy(EntityProto_EntityType type) {
    return type == EntityProto_EntityType_Melee ||
           type == EntityProto_EntityType_Urgot;
}
}  // namespace Config