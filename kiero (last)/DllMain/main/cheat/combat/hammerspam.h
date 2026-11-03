int iarr;   

Vector3 arr[48] = {
    Vector3(1.0, 2.0, 0.0),
    Vector3(0.8, 2.0, 0.0),
    Vector3(0.6, 2.0, 0.0),
    Vector3(0.4, 2.0, 0.0),
    Vector3(0.2, 2.0, 0.0),
    Vector3(0.0, 2.0, 0.0),
    Vector3(0.0, 1.9, 0.0),
    Vector3(0.0, 1.7, 0.0),
    Vector3(0.0, 1.5, 0.0),
    Vector3(0.0, 1.3, 0.0),
    Vector3(0.0, 1.1, 0.0),
    Vector3(0.0, 1.0, 0.0),
    Vector3(0.0, 0.9, 0.0),
    Vector3(0.0, 0.7, 0.0),
    Vector3(0.0, 0.5, 0.0),
    Vector3(0.0, 0.3, 0.0),
    Vector3(0.0, 0.1, 0.0),
    Vector3(0.0, 0.0, 0.0),
    Vector3(-0.1, 0.0, 0.0),
    Vector3(-0.3, 0.0, 0.0),
    Vector3(-0.5, 0.0, 0.0),
    Vector3(-0.7, 0.0, 0.0),
    Vector3(-0.9, 0.0, 0.0),
    Vector3(-1.0, 0.0, 0.0),
    Vector3(-0.1, 1.0, 0.0),
    Vector3(-0.3, 1.0, 0.0),
    Vector3(-0.5, 1.0, 0.0),
    Vector3(-0.7, 1.0, 0.0),
    Vector3(-0.9, 1.0, 0.0),
    Vector3(-1.0, 1.0, 0.0),
    Vector3(-1.0, 1.1, 0.0),
    Vector3(-1.0, 1.3, 0.0),
    Vector3(-1.0, 1.5, 0.0),
    Vector3(-1.0, 1.7, 0.0),
    Vector3(-1.0, 1.9, 0.0),
    Vector3(-1.0, 2.0, 0.0),
    Vector3(0.1, 1.0, 0.0),
    Vector3(0.3, 1.0, 0.0),
    Vector3(0.5, 1.0, 0.0),
    Vector3(0.7, 1.0, 0.0),
    Vector3(0.9, 1.0, 0.0),
    Vector3(1.0, 1.0, 0.0),
    Vector3(1.0, 0.9, 0.0),
    Vector3(1.0, 0.7, 0.0),
    Vector3(1.0, 0.5, 0.0),
    Vector3(1.0, 0.3, 0.0),
    Vector3(1.0, 0.1, 0.0),
    Vector3(1.0, 0.0, 0.0) 
};

void hammerspam() {
    auto held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
    BaseMelee* melee = LocalPlayer::Entity()->GetHeldEntity<BaseMelee>();
    BasePlayer* target_player = reinterpret_cast<BasePlayer*>(settings::closestPlayer);
    if (settings::misc::hammer_spam && (held->class_name_hash() == STATIC_CRC32("Hammer") || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1803831286)) {
        if (iarr > 48) iarr = 0;
        Vector3 hitpoint;
        Vector3 origin;
        Vector3 localDir;
        if (settings::misc::spam_mode == 0 && Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(head), target_player->GetBoneByID(head)) <= 2.5f) {
            hitpoint = target_player->transform()->position() + (target_player->eyes()->BodyForward() * 2) + arr[iarr];

            origin = target_player->eyes()->position();
            localDir = target_player->eyes()->BodyForward();
            localDir.y = 0.00f;

            HitTest* hit = HitTest::New();

            hit->HitEntity() = NULL;
            hit->DidHit() = true;
            hit->MaxDistance() = melee->maxDistance();
            hit->HitTransform() = nullptr;
            hit->AttackRay() = Ray(hitpoint, Vector3::Zero());
            hit->HitNormal() = localDir;
            hit->HitPoint() = hitpoint;
            hit->HitMaterial_() = il2cpp::String::New(("glass"));
            melee->DoAttack(hit);
            melee->StartAttackCooldown(0.01f);
        }
        else if (settings::misc::spam_mode == 1) {
            hitpoint = LocalPlayer::Entity()->transform()->position() + (LocalPlayer::Entity()->eyes()->BodyForward() * 2) + arr[iarr];

            origin = LocalPlayer::Entity()->eyes()->position();
            localDir = LocalPlayer::Entity()->eyes()->BodyForward();
            localDir.y = 0.00f;

            HitTest* hit = HitTest::New();

            hit->HitEntity() = NULL;
            hit->DidHit() = true;
            hit->MaxDistance() = melee->maxDistance();
            hit->HitTransform() = nullptr;
            hit->AttackRay() = Ray(hitpoint, Vector3::Zero());
            hit->HitNormal() = localDir;
            hit->HitPoint() = hitpoint;
            hit->HitMaterial_() = il2cpp::String::New(("glass"));
            melee->DoAttack(hit);
            melee->StartAttackCooldown(0.01f);
        }

        iarr += 1;
    }
}